/* omega copyright (C) by Laurence Raphael Brothers, 1987,1988,1989 */
/* effect3.c */

#include "glob.h"

/* if know id, then summon that monster; else (if < 0) get one. */
void summon(int blessing, int id)
{
  int i, looking = TRUE, x, y;
  Monsterlist* tml;

  if (id < 0)
  {
    if (blessing > 0)
    {
      id = monsterlist();
      xredraw();
    }
    /* for (id ==0) case, see below -- get a "fair" monster */
    else if (blessing < 0)
      id = random_range(NUMMONSTERS);
  }
  for (i = 0; ((i < 8) && looking); i++)
  {
    x = player.x + Dirs[0][i];
    y = player.y + Dirs[1][i];
    looking = ((!inbounds(x, y)) ||
               (level->site[x][y].locchar != FLOOR) ||
               (level->site[x][y].creature != NULL));
  }

  if (!looking)
  {
    if ((blessing == 0) && (id < 0))
      level->site[x][y].creature = m_create(x, y, WANDERING, difficulty());
    else
      level->site[x][y].creature = make_creature(id);
    level->site[x][y].creature->x = x;
    level->site[x][y].creature->y = y;
    tml = ((Monsterlist*)checkmalloc(sizeof(Monsterlist)));
    tml->m = level->site[x][y].creature;
    if (blessing > 0)
      m_status_reset(tml->m, HOSTILE);
    else if (blessing < 0)
      m_status_set(tml->m, HOSTILE);
    tml->next = level->mlist;
    level->mlist = tml;
  }
}

int itemlist(int itemindex, int num)
{
  int i, itemno;

  print2("Show ID list? ");
  if (ynq2() == 'y')
  {
    menuclear();
    for (i = 0; i < num; i++)
    {
      menunumprint(i + 1);
      menuprint(":");
      menuprint(Objects[i + itemindex].truename);
      menuprint("\n");
    }
    showmenu();
  }
  mprint("Item ID? ");
  itemno = (int)parsenum() - 1;
  if ((itemno >= num) || (itemno < 0))
    itemno = ABORT;
  return (itemno);
}

int monsterlist()
{
  int i, itemno;
  print2("Show ID list? ");
  if (ynq2() == 'y')
    do
    {
      clearmsg();
      print1("Summon monster: ");
      menuclear();
      for (i = 0; i < NUMMONSTERS; i++)
      {
        menunumprint(i + 1);
        menuprint(":");
        menuprint(Monsters[i].monstring);
        menuprint("\n");
      }
      showmenu();
      itemno = (int)parsenum() - 1;
      if ((itemno < 0) || (itemno > NUMMONSTERS - 1))
      {
        print3("How about trying a real monster?");
        morewait();
      }
    } while ((itemno < 0) || (itemno > NUMMONSTERS - 1));
  else
    do
    {
      print1("Summon monster: ");
      itemno = (int)parsenum() - 1;
    } while ((itemno < 0) || (itemno > NUMMONSTERS - 1));
  return (itemno);
}

/* uncurse all items, cure diseases, and neutralize poison */
void cleanse(int blessing)
{
  int i;

  if (blessing > -1)
  {
    if (blessing > 0)
      for (i = 0; i < MAXITEMS; i++)
        if (player.possessions[i] != NULL)
        {
          if ((player.possessions[i]->used) &&
              (player.possessions[i]->blessing < 0))
          {
            player.possessions[i]->used = FALSE;
            item_use(player.possessions[i]);
            player.possessions[i]->blessing = 0;
            player.possessions[i]->used = TRUE;
            item_use(player.possessions[i]);
          }
        }

    if (player.status[POISONED] > 0)
    {
      player.status[POISONED] = 0;
    }
    if (player.status[DISEASED] > 0)
    {
      player.status[DISEASED] = 0;
    }
    showflags();
    mprint("You feel radiant!");
  }
  else
  {
    player.status[POISONED] += 10;
    player.status[DISEASED] += 10;
    mprint("You feel besmirched!");
    showflags();
  }
}

void annihilate(int blessing)
{
  Monsterlist* ml;
  int i;

  if (blessing == 0)
  {
    mprint("Lightning strikes flash all around you!!!");
    for (i = 0; i < 9; i++)
      if (level->site[player.x + Dirs[0][i]][player.y + Dirs[1][i]].creature !=
          NULL)
        m_death(level->site[player.x + Dirs[0][i]][player.y + Dirs[1][i]].creature);
  }
  if (blessing > 0)
  {
    if (Current_Environment == E_COUNTRYSIDE)
    {
      clearmsg();
      print1("Bolts of lightning flash down for as far as you can see!!!");
      morewait();
      print1("There is a rain of small birds and insects from the sky, and you");
      print2("notice that you can't hear any animal noises around here any more...");
      player.alignment -= 3;
    }
    else
    {
      mprint("Thousands of bolts of lightning flash throughout the level!!!");
      for (ml = level->mlist; ml != NULL; ml = ml->next)
        if (ml->m != NULL && ml->m->hp > 0)
          m_death(ml->m);
    }
  }
  else
  {
    mprint("You are hit by a bolt of mystic lightning!");
    p_death("self-annihilation");
  }
}

void sleep_monster(int blessing)
{
  Monsterlist* ml;
  int x = player.x, y = player.y;
  struct monster *target;

  if (blessing == 0)
    setspot(&x, &y);

  if (blessing < 0)
    sleep_player(abs(blessing) + 2);
  else if (blessing > 0)
  {
    mprint("A silence pervades the area.");
    for (ml = level->mlist; ml != NULL; ml = ml->next)
    {
      m_status_reset(ml->m, AWAKE);
      ml->m->wakeup = 0;
    }
  }
  else
  {
    target = level->site[x][y].creature;
    if (target != NULL)
    {
      if (target->uniqueness == COMMON)
      {
        strcpy(Str1, "The ");
        strcat(Str1, target->monstring);
      }
      else
        strcpy(Str1, target->monstring);
      if (!m_immunityp(target, SLEEP))
      {
        strcat(Str1, " seems to have fallen asleep.");
        m_status_reset(target, AWAKE);
        target->wakeup = 0;
      }
      else
        strcat(Str1, " is bright eyed, and bushy tailed!");
      mprint(Str1);
    }
    else
      mprint("Nothing to sleep there!");
  }
}

void sleep_player(int amount)
{
  if (player.status[SLEPT] == 0)
  { /* prevent player from sleeping forever */
    mprint("You feel sleepy...");
    if (!p_immune(SLEEP))
    {
      player.status[SLEPT] += random_range(amount * 2) + 2;
    }
    else
      mprint("but you shrug off the momentary lassitude.");
  }
}

void hide(int x, int y)
{
  if (inbounds(x, y))
  {
    lset(x, y, SECRET);
    lset(x, y, CHANGED);
    putspot(x, y, WALL);
    mprint("You feel sneaky.");
  }
}

void clairvoyance(int vision)
{
  int i, j;
  int x = player.x, y = player.y;
  mprint("Clairvoyance... ");
  setspot(&x, &y);
  for (i = x - vision; i < x + vision + 1; i++)
    for (j = y - vision; j < y + vision + 1; j++)
    {
      if (inbounds(i, j))
      {
        level->site[i][j].showchar = SPACE;
        lreset(i, j, SECRET);
        lset(i, j, CHANGED);
        dodrawspot(i, j);
      }
    }
  levelrefresh();
}

void aggravate()
{
  Monsterlist* tm;

  for (tm = level->mlist; tm != NULL; tm = tm->next)
  {
    m_status_set(tm->m, AWAKE);
    m_status_set(tm->m, HOSTILE);
  }
}

void learnspell(int blessing)
{
  int i, spell, done = FALSE;
  if (blessing < 0)
  {
    for (i = NUMSPELLS; ((i > -1) && (!done)); i--)
      if (Spells[i].known)
      {
        done = TRUE;
        Objects[SCROLLID + 1].known = TRUE;
        mprint("You feel forgetful.");
        Spells[i].known = FALSE;
      }
    if (i == ABORT)
      mprint("You feel fortunate.");
  }
  else
  {
    Objects[SCROLLID + 1].known = TRUE;
    spell = random_range(NUMSPELLS);
    print1("Spell Research");
    if ((random_range(4 * Spells[spell].powerdrain) +
         Spells[spell].powerdrain) <
        (4 * player.iq + 8 * player.level))
    {
      nprint1(" -- Research successful: ");
      nprint1(spellid(spell));
      if (Spells[spell].known)
      {
        print2("...is now easier to cast.");
        Spells[spell].powerdrain = ((int)((Spells[spell].powerdrain + 1) / 2));
      }
      else
      {
        print2("...is added to your repertoire");
        Spells[spell].known = TRUE;
        gain_experience(Spells[spell].powerdrain * 10);
      }
    }
    else
      nprint1(" -- Research unsuccessful.");
  }
}

void amnesia()
{
  int i, j;
  for (j = 0; j < LENGTH; j++)
    for (i = 0; i < WIDTH; i++)
      lreset(i, j, SEEN);

  erase_level();
  drawvision(player.x, player.y);
}

/*affects player only */
void level_drain(int levels, char* source)
{
  int decrement = ((int)(player.maxhp / (player.level + 1)));

  player.level -= levels;

  player.maxhp -= (levels * decrement);
  player.hp -= (levels * decrement);

  if ((player.hp < 1) || (player.level < 0))
    p_death(source);
}

void disrupt(int x, int y, int amount)
{
  struct monster *target;

  if ((x == player.x) && (y == player.y))
  {
    mprint("You feel disrupted!");
    p_damage(amount, NORMAL_DAMAGE, "magical disruption");
  }
  else
  {
    target = level->site[x][y].creature;
    if (target != NULL)
    {
      if (target->uniqueness == COMMON)
      {
        strcpy(Str1, "The ");
        strcat(Str1, target->monstring);
      }
      else
        strcpy(Str1, target->monstring);
      if (!m_immunityp(target, NORMAL_DAMAGE))
      {
        strcat(Str1, " was blasted!");
        mprint(Str1);
        m_damage(target, amount, NORMAL_DAMAGE);
        target->wakeup = 0;
      }
      else
      {
        strcat(Str1, " does not seem affected.");
        mprint(Str1);
      }
    }
  }
}

void disintegrate(int x, int y)
{
  struct monster *target;
  if (!inbounds(x, y))
    mprint("You feel a sense of wastage.");
  else if ((x == player.x) && (y == player.y))
  {
    if (player.possessions[O_CLOAK] != NULL)
    {
      mprint("Your cloak disintegrates!");
      dispose_lost_objects(1, player.possessions[O_CLOAK]);
    }
    else if (player.possessions[O_ARMOR] != NULL)
    {
      mprint("Your armor disintegrates!");
      dispose_lost_objects(1, player.possessions[O_ARMOR]);
    }
    else
    {
      mprint("Uh, oh....");
      mprint("Zzzap! You've been disintegrated!");
      p_damage(250, UNSTOPPABLE, "disintegration");
    }
  }
  else
  {
    if (!view_los_p(player.x, player.y, x, y))
      setgamestatus(SUPPRESS_PRINTING);
    if ((target = level->site[x][y].creature) != NULL)
    {
      if (target->uniqueness == COMMON)
      {
        strcpy(Str1, "The ");
        strcat(Str1, target->monstring);
      }
      else
        strcpy(Str1, target->monstring);
      strcat(Str1, " disintegrates!");
      mprint(Str1);
      m_damage(target, 100, UNSTOPPABLE);
      if (target->hp > 0)
        mprint("It was partially protected by its armor.");
    }
    else if (level->site[x][y].locchar == ALTAR)
    {
      mprint("Zzzzap! the altar seems unaffected...");
      mprint("But an angry deity retaliates....");
      disintegrate(player.x, player.y);
    }
    else if (level->site[x][y].p_locf == L_TRAP_PIT)
    {
      if (Current_Environment == Current_Dungeon)
      {
        mprint("A hole is blasted in the base of the pit!");
        level->site[x][y].locchar = TRAP;
        level->site[x][y].p_locf = L_TRAP_DOOR;
        level->site[x][y].aux = S_DISINTEGRATE;
        lset(x, y, CHANGED);
      }
      else
        mprint("The hole just gets deeper....");
    }
    else if (level->site[x][y].locchar == FLOOR)
    {
      mprint("You zap a hole in the floor!");
      level->site[x][y].locchar = TRAP;
      level->site[x][y].p_locf = L_TRAP_PIT;
      lset(x, y, CHANGED);
    }
    else if ((level->site[x][y].locchar == WALL) ||
             (level->site[x][y].locchar == OPEN_DOOR) ||
             (level->site[x][y].locchar == CLOSED_DOOR) ||
             (level->site[x][y].locchar == PORTCULLIS) ||
             (level->site[x][y].locchar == STATUE))
    {
      mprint("The site is reduced to rubble!");
      if (level->site[x][y].locchar == WALL)
        tunnelcheck();
      level->site[x][y].p_locf = L_RUBBLE;
      level->site[x][y].locchar = RUBBLE;
      lreset(x, y, SECRET);
      lset(x, y, CHANGED);
    }
    else if ((level->site[x][y].locchar == RUBBLE) ||
             (level->site[x][y].locchar == TRAP))
    {
      mprint("The site is blasted clear!");
      level->site[x][y].p_locf = L_NO_OP;
      level->site[x][y].locchar = FLOOR;
      lreset(x, y, SECRET);
      lset(x, y, CHANGED);
    }
    else if (level->site[x][y].locchar == HEDGE)
    {
      if (level->site[x][y].p_locf == L_TRIFID)
      {
        mprint("The trifid screams as it disintgrates!");
        gain_experience(50);
        level->site[x][y].p_locf = L_NO_OP;
        level->site[x][y].locchar = FLOOR;
        lreset(x, y, SECRET);
        lset(x, y, CHANGED);
      }
      else
      {
        mprint("The hedge is blasted away!");
        level->site[x][y].p_locf = L_NO_OP;
        level->site[x][y].locchar = FLOOR;
        lreset(x, y, SECRET);
        lset(x, y, CHANGED);
      }
    }
    else
      mprint("The blast has no effect.");
    if (!view_los_p(player.x, player.y, x, y))
      resetgamestatus(SUPPRESS_PRINTING);
    else
      plotspot(x, y, TRUE);
  }
}

void acid_cloud()
{
  mprint("You are caught in an acid cloud!  ");
  if (player.possessions[O_CLOAK] != NULL)
  {
    (void)damage_item(player.possessions[O_CLOAK]);
    mprint("You are burned by acid.");
    p_damage(3, ACID, "an acid cloud");
  }
  else if (player.possessions[O_ARMOR] != NULL)
  {
    mprint("You are burned by acid.");
    p_damage(3, ACID, "an acid cloud");
    (void)damage_item(player.possessions[O_ARMOR]);
  }
  else if (p_immune(ACID))
  {
    mprint("You resist the effects!");
    return;
  }
  else
  {
    mprint("The acid eats away at your bare skin!");
    p_damage(25, ACID, "an acid cloud");
  }
}

/* teleport player */
void p_teleport(int type)
{
  int x = player.x, y = player.y;
  drawspot(x, y);
  if (type < 0)
  {
    x = random_range(WIDTH);
    y = random_range(LENGTH);
    if ((level->site[x][y].locchar != FLOOR) &&
        (level->site[x][y].locchar != OPEN_DOOR))
    {
      mprint("You teleported into a solid object....");
      mprint("You are dead!");
      p_death("teleportation into a solid object");
    }
    else
    {
      player.x = x;
      player.y = y;
    }
  }
  else if (type == 0)
    findspace(&(player.x), &(player.y), -1);
  else
  {
    setspot(&player.x, &player.y);
    if ((level->site[player.x][player.y].locchar != FLOOR) ||
        (level->site[player.x][player.y].creature != NULL))
    {
      mprint("You feel deflected.");
      p_teleport(0);
    }
  }
  screencheck(player.y);
  roomcheck();
}

void p_poison(int toxicity)
{
  mprint("You feel sick.");
  if (!p_immune(POISON))
    player.status[POISONED] += toxicity;
  else
    mprint("The sickness fades!");
  showflags();
}

void apport(int blessing)
{
  int i, index, x = player.x, y = player.y;
  if (blessing > -1)
  {
    mprint("Apport from:");
    setspot(&x, &y);
    if (level->site[x][y].things != NULL)
    {
      pickup_at(x, y);
      plotspot(x, y, TRUE);
    }
    else
      mprint("There's nothing there to apport!");
  }
  else
  {
    mprint("You have a sense of loss.");
    for (i = 0; i < abs(blessing); i++)
    {
      index = random_item();
      if (index != ABORT)
      {
        drop_at(x, y, player.possessions[index]);
        dispose_lost_objects(player.possessions[index]->number,
                             player.possessions[index]);
      }
    }
  }
}

void strategic_teleport(int blessing)
{
  int new_env;

  /* WDT HACK: Game balance issue: the star gem is supposed to be the only
   * way out of the astral plane (including the Circle of Sorcerors).  However,
   * Hy Magic offers the Location wish, and some artifacts grant this
   * as well.  Seems to me that Hy Magic ought to allow it, and nothing
   * else (aside from the Star Gem, of course). */
  if ((Current_Environment == E_CIRCLE || Current_Environment == E_ASTRAL) &&
      !gamestatusp(CHEATED))
  {
    mprint("Some property of this eerie place interferes with the magic!\n");
    return;
  }
  mprint("Magic portals open up all around you!");
  if (blessing < 0)
  {
    morewait();
    mprint("You are dragged into one!");
    change_environment(E_COUNTRYSIDE);
    do
    {
      player.x = random_range(WIDTH);
      player.y = random_range(LENGTH);
    } while (Country[player.x][player.y].base_terrain_type == CHAOS_SEA);
  }
  else
  {
    mprint("Below each portal is a caption. Enter which one:");
    menuclear();
    menuprint("a: Rampart\n");
    menuprint("b: Village of Star View\n");
    menuprint("c: Village of Woodmere\n");
    menuprint("d: Village of Stormwatch\n");
    menuprint("e: Village of Thaumaris\n");
    menuprint("f: Village of Skorch\n");
    menuprint("g: Village of Whorfen\n");
    menuprint("h: Temple of the Noose\n");
    menuprint("i: The Parthenon\n");
    menuprint("j: Temple of the Black Hand\n");
    menuprint("k: Temple of the Hidden Moon\n");
    menuprint("l: WoodHenge\n");
    menuprint("m: Temple of Destiny\n");
    menuprint("n: HellWell Volcano\n");
    if (gamestatusp(CHEATED))
      menuprint("z: Anywhere\n");
    menuprint("ANYTHING ELSE: Avoid entering a portal.");
    showmenu();
    switch ((char)mcigetc())
    {
    case 'a':
      change_environment(E_COUNTRYSIDE);
      player.x = 27;
      player.y = 19;
      break;
    case 'b':
      change_environment(E_COUNTRYSIDE);
      player.x = 56;
      player.y = 5;
      break;
    case 'c':
      change_environment(E_COUNTRYSIDE);
      player.x = 35;
      player.y = 11;
      break;
    case 'd':
      change_environment(E_COUNTRYSIDE);
      player.x = 10;
      player.y = 40;
      break;
    case 'e':
      change_environment(E_COUNTRYSIDE);
      player.x = 7;
      player.y = 6;
      break;
    case 'f':
      change_environment(E_COUNTRYSIDE);
      player.x = 41;
      player.y = 43;
      break;
    case 'g':
      change_environment(E_COUNTRYSIDE);
      player.x = 20;
      player.y = 41;
      break;
    case 'h':
      change_environment(E_COUNTRYSIDE);
      player.x = 22;
      player.y = 30;
      break;
    case 'i':
      change_environment(E_COUNTRYSIDE);
      player.x = 51;
      player.y = 11;
      break;
    case 'j':
      change_environment(E_COUNTRYSIDE);
      player.x = 45;
      player.y = 45;
      break;
    case 'k':
      change_environment(E_COUNTRYSIDE);
      player.x = 19;
      player.y = 46;
      break;
    case 'l':
      change_environment(E_COUNTRYSIDE);
      player.x = 32;
      player.y = 5;
      break;
    case 'm':
      change_environment(E_COUNTRYSIDE);
      player.x = 49;
      player.y = 59;
      break;
    case 'n':
      change_environment(E_COUNTRYSIDE);
      player.x = 30;
      player.y = 58;
      break;
    default:
      if (gamestatusp(CHEATED))
      {
        mprint("Enter environment number: ");
        new_env = (int)parsenum();
        change_environment(new_env);
      }
    }
    xredraw();
    if (gamestatusp(LOST))
    {
      print1("You know where you are now.");
      resetgamestatus(LOST);
      Precipitation = 0;
    }
  }
  setlastxy(player.x, player.y);
  screencheck(player.y);
  drawvision(player.x, player.y);
  if (Current_Environment == E_COUNTRYSIDE)
    terrain_check(FALSE);
}

void hero(int blessing)
{
  if (blessing > -1)
  {
    mprint("You feel super!");
    player.status[HERO] += random_range(5) + 1 + blessing;
    calc_melee();
  }
  else
  {
    player.status[HERO] = 0;
    calc_melee();
    mprint("You feel cowardly.");
    level_drain(abs(blessing), "a potion of cowardice");
  }
}

void levitate(int blessing)
{
  if (blessing > -1)
  {
    if (gamestatusp(MOUNTED))
      mprint("You have a strange feeling of lightness in your saddle.");
    else
    {
      mprint("You start to float a few inches above the floor.");
      mprint("You discover you can easily control your altitude...");
      mprint("(Note use of '@' command may be useful while levitating)");
      player.status[LEVITATING] += random_range(5) + 1 + blessing;
    }
  }
  else
    mprint("Nothing much happens.");
}

/* has effect of switching between 1st level and deepest level attained */
void level_return()
{
  if (Current_Environment == Current_Dungeon)
  {
    mprint("The vortex of mana carries you off!");
    if (level->depth > 1)
      change_level(level->depth, 1, FALSE);
    else
      change_level(level->depth, deepest[Current_Environment], FALSE);
  }
  else if (Current_Environment == E_COUNTRYSIDE)
  {
    mprint("A mysterious force wafts you back home!");
    player.x = 27;
    player.y = 19;
    screencheck(player.y);
    drawvision(player.x, player.y);
    locprint("Back Outside Rampart.");
  }
  else
    mprint("A feeble vortex of magic swirls by and has no further effect.");
}

void cure(int blessing)
{
  int happened = FALSE;
  if (blessing > -1)
  {
    if (player.status[DISEASED])
    {
      player.status[DISEASED] = 0;
      mprint("You feel hygienic!");
      happened = TRUE;
    }
    if (player.status[POISONED])
    {
      player.status[POISONED] -= 5 + blessing * 10;
      if (player.status[POISONED] > 0)
        mprint("The effect of the poison has been reduced.");
      else
      {
        player.status[POISONED] = 0;
        mprint("The poison has been purged from your system.");
      }
      happened = TRUE;
    }
    if (player.status[BLINDED])
    {
      player.status[BLINDED] = 0;
      happened = TRUE;
      mprint("Cobwebs clear from before your eyes.");
    }
    if (!happened)
      mprint("Nothing much happens.");
  }
  else
    disease(12);
  showflags();
}

void disease(int amount)
{
  mprint("You feel ill.");
  if (!player.immunity[INFECTION])
  {
    mprint("You begin to shiver with ague.");
    player.status[DISEASED] += random_range(amount * 2) + 1;
  }
  else
    mprint("The illness fades.");
}

void truesight(int blessing)
{
  if (blessing > -1)
  {
    player.status[TRUESIGHT] += random_range(10) + 1;
    mprint("You feel sharp.");
  }
  else
  {
    player.status[BLINDED] += random_range(10) + 1;
    mprint("You've been blinded!");
  }
}

void dispel(int blessing)
{
  int i, x = player.x, y = player.y;
  Object* o;
  if (blessing > -1)
  {
    setspot(&x, &y);
    if ((x == player.x) && (y == player.y))
    {
      for (i = 0; i < MAXITEMS; i++)
      {
        o = player.possessions[i];
        if (o != NULL)
          if ((o->used) && (o->blessing < 0))
          {
            if (blessing + 1 + o->blessing >= 0)
            {
              o->used = FALSE;
              setgamestatus(SUPPRESS_PRINTING);
              item_use(o);
              resetgamestatus(SUPPRESS_PRINTING);
              mprint("You hear a sighing sound from");
              mprint(itemid(o));
              o->blessing = 0;
              o->used = TRUE;
              setgamestatus(SUPPRESS_PRINTING);
              item_use(o);
              resetgamestatus(SUPPRESS_PRINTING);
            }
            else
            {
              mprint("You hear dark laughter from");
              mprint(itemid(o));
            }
          }
      }
    }
    else if (level->site[x][y].creature != NULL)
    {
      if (level->site[x][y].creature->level < blessing * 3)
      {
        level->site[x][y].creature->specialf = M_NO_OP;
        if (level->site[x][y].creature->meleef != M_NO_OP)
          level->site[x][y].creature->meleef = M_MELEE_NORMAL;
        level->site[x][y].creature->strikef = M_NO_OP;
        level->site[x][y].creature->immunity = 0;
        m_status_reset(level->site[x][y].creature, M_INVISIBLE);
        m_status_reset(level->site[x][y].creature, INTANGIBLE);
      }
      else
        mprint("The monster ignores the effect!");
    }
    else if ((level->site[x][y].p_locf == L_TRAP_FIRE) ||
             (level->site[x][y].p_locf == L_STATUE_WAKE) ||
             (level->site[x][y].p_locf == L_TRAP_TELEPORT) ||
             (level->site[x][y].p_locf == L_TRAP_DISINTEGRATE))
    {
      level->site[x][y].p_locf = L_NO_OP;
      if (level->site[x][y].locchar == TRAP)
        level->site[x][y].locchar = FLOOR;
      lset(x, y, CHANGED);
    }
    else if (level->site[x][y].p_locf == L_MAGIC_POOL)
      level->site[x][y].p_locf = L_WATER;
    else
      mprint("Nothing much seems to happen.");
  }
  else
  {
    mprint("A smell of ozone and positive ions fills the air..");
    if (player.status[ACCURACY] && (player.status[ACCURACY] < 1000))
      player.status[ACCURACY] = 1;
    if (player.status[DISPLACED] && (player.status[DISPLACED] < 1000))
      player.status[DISPLACED] = 1;
    if (player.status[HASTED] && (player.status[HASTED] < 1000))
      player.status[HASTED] = 1;
    if (player.status[BREATHING] && (player.status[BREATHING] < 1000))
      player.status[BREATHING] = 1;
    if (player.status[INVISIBLE] && (player.status[INVISIBLE] < 1000))
      player.status[INVISIBLE] = 1;
    if (player.status[REGENERATING] && (player.status[REGENERATING] < 1000))
      player.status[REGENERATING] = 1;
    if (player.status[ALERT] && (player.status[ALERT] < 1000))
      player.status[ALERT] = 1;
    if (player.status[HERO] && (player.status[HERO] < 1000))
      player.status[HERO] = 1;
    if (player.status[LEVITATING] && (player.status[LEVITATING] < 1000))
      player.status[LEVITATING] = 1;
    if (player.status[ACCURATE] && (player.status[ACCURATE] < 1000))
      player.status[ACCURATE] = 1;
    if (player.status[TRUESIGHT] && (player.status[TRUESIGHT] < 1000))
      player.status[TRUESIGHT] = 1;
    tenminute_status_check();
  }
}

void polymorph(int blessing)
{
  int x = player.x, y = player.y, newmonster;
  struct monster *m;
  setspot(&x, &y);
  clearmsg();
  if ((x == player.x) && (y == player.y))
  {
    /* WDT HACK: shouldn't this use one of the 'getarticle' functions
     * to prevent things like "a elder grue" (should be "an elder grue")?
     */
    mprint("You enjoy your new life as a");
    mprint(Monsters[random_range(NUMMONSTERS)].monstring);
    mprint("But your game is over....");
    p_death("polymorphing oneself");
  }
  else if ((m = level->site[x][y].creature) == NULL)
    mprint("Nothing happens.");
  else
  {
    if (m_immunityp(m, OTHER_MAGIC) || (m->level > random_range(12)))
    {
      strcpy(Str1, "The ");
      strcat(Str1, m->monstring);
      strcat(Str1, " resists the change!");
      m_status_set(m, HOSTILE);
    }
    else
    {
      if (blessing < 0)
      {
        do
          newmonster = random_range(NUMMONSTERS);
        while ((newmonster == NPC) ||
               (newmonster == MAST_THIEF) ||
               (Monsters[newmonster].level <= m->level) ||
               (Monsters[newmonster].uniqueness != COMMON));
      }
      else
      {
        do
          newmonster = random_range(NUMMONSTERS);
        while ((newmonster == NPC) ||
               (newmonster == MAST_THIEF) ||
               (Monsters[newmonster].uniqueness != COMMON));
      }
      /* WDT HACK: most of this could (and should) be implemented by 
       * the following line: "*m = Monsters[newmonster];".  The exception,
       * of course, are the parts where the new monster inherits the old
       * one's abilities.  This would be better because it would be robust
       * even in the face of additions to the monster structure. */
      m->id = Monsters[newmonster].id;
      m->hp = max(m->hp, Monsters[newmonster].id);
      m->speed = Monsters[newmonster].speed;
      m->hit = Monsters[newmonster].hit;
      m->ac = Monsters[newmonster].ac;
      m->dmg = Monsters[newmonster].dmg;
      m->sense = Monsters[newmonster].sense;
      m->wakeup = Monsters[newmonster].wakeup;
      m->level = max(m->level, Monsters[newmonster].level);
      m->status = Monsters[newmonster].status;
      m->immunity = (m->immunity | Monsters[newmonster].immunity);
      m->xpv = max(m->xpv, Monsters[newmonster].wakeup);
      m->transformid = Monsters[newmonster].transformid;
      m->corpsevalue = Monsters[newmonster].corpsevalue;
      m->corpseweight = Monsters[newmonster].corpseweight;
      m->monchar = Monsters[newmonster].monchar;
      m->meleestr = Monsters[newmonster].meleestr;
      m->monstring = Monsters[newmonster].monstring;
      m->corpsestr = Monsters[newmonster].corpsestr;
      m->talkf = Monsters[newmonster].talkf;
      m->movef = Monsters[newmonster].movef;
      m->meleef = Monsters[newmonster].meleef;
      m->strikef = Monsters[newmonster].strikef;
      m->specialf = Monsters[newmonster].specialf;
      m_status_set(m, HOSTILE);
    }
  }
}

void hellfire(int x, int y, int blessing)
{
  struct monster *m;
  if ((x == player.x) && (y == player.y))
  {
    mprint("You have been completely annihilated. Congratulations.");
    p_death("hellfire");
  }
  else if ((m = level->site[x][y].creature) == NULL)
  {
    mprint("The gods are angry over your waste of power...");
    level_drain(5, "indiscriminate use of hellfire");
  }
  else
  {
    mprint("The monster writhes in the flames...");
    if (blessing < 0)
    {
      mprint("...and appears stronger.");
      morewait();
      mprint("Much stronger.");
      m->hp += 1000;
      m->hit += 20;
      m->dmg += 100;
      m_status_set(m, HOSTILE);
    }
    else
    {
      if (m->uniqueness == COMMON)
      {
        mprint("and is utterly annihilated. Only a greasy spot remains...");
        m->corpsestr = "a greasy spot";
        m->id = 0;
        m->possessions->free();
        m->possessions = NULL;
      }
      else
        mprint("and dies, cursing your name and the uncaring gods....");
      m_death(m);
    }
  }
}

void drain(int blessing)
{
  int x = player.x, y = player.y;
  struct monster *m;
  setspot(&x, &y);
  mprint("You begin to drain energy...");
  if ((x == player.x) && (y == player.y))
  {
    mprint("You drain your own energy....");
    mprint("Uh, oh, positive feedback....");
    level_drain(player.level, "self-vampirism");
  }
  else if ((m = level->site[x][y].creature) != NULL)
  {
    if ((blessing > -1) && (!m_immunityp(m, NEGENERGY)))
    {
      mprint("The monster seems weaker...");
      m_damage(m, m->level * m->level, NEGENERGY);
      m->hit = max(m->hit - m->level, 1);
      m->dmg = max(m->dmg - m->level * m->level, 1);
      m->ac = max(m->ac - m->level, 1);
      m->level = max(1, m->level - 1);
      mprint("You feel stronger...");
      gain_experience(m->level * 5);
      player.hp += (m->level * m->level / 2);
    }
    else
    {
      mprint("The effect reverses itself!");
      mprint("The monster seems stronger...");
      m->hp += player.level * player.level;
      m->hit += player.level;
      m->dmg += player.level * player.level;
      m->ac += player.level;
      m->level++;
      mprint("You feel weaker...");
      player.mana = min(0, player.level * player.level);
      level_drain(m->level, "negative energy conflict");
    }
  }
  else if (blessing < 0)
  {
    mprint("You seem to lose energy, instead of gaining it!");
    level_drain(3, "reversed energy drain");
  }
  else if (level->site[x][y].locchar == ALTAR)
  {
    mprint("The altar collapses in on itself....");
    level->site[x][y].locchar = ABYSS;
    level->site[x][y].p_locf = L_ABYSS;
    lset(x, y, CHANGED);
    if (!player.patron)
    {
      mprint("You drain some theurgic energy from the altar....");
      gain_experience(40);
      player.hp += 20;
      player.pow += 2;
    }
    if (level->site[x][y].aux == player.patron)
    {
      mprint("Your deity is enraged.");
      mprint("You are struck by godsfire.");
      p_damage(player.hp - 1, UNSTOPPABLE, "godsfire");
      mprint("You feel atheistic.");
      player.patron = -1;
      player.rank[PRIESTHOOD] = 0;
    }
    else
    {
      mprint("You feel the wrath of a god....");
      p_damage(random_range(player.level * 10), UNSTOPPABLE, "divine wrath");
      if (player.patron != 0)
      {
        mprint("Your deity doesn't seem to mind your action, though.");
        gain_experience(100);
      }
    }
  }
  else
  {
    mprint("You drain some energy from the ambient megaflow.");
    player.hp++;
  }
}

void sanctuary()
{
  if (level->environment == E_TEMPLE)
    mprint("Odd, the spell has no effect. I wonder why.");
  else
  {
    mprint("You're standing on sacred ground!");
    player.sx = player.x;
    player.sy = player.y;
  }
}

void shadowform()
{
  /* WDT HACK: this fix might work, but it seems like the immunity
   * will be FAR too short.  It's obviously better than the old 
   * situation, though... */
  if (!player.status[SHADOWFORM])
  {
    mprint("You feel like a shadow.");
    player.immunity[NORMAL_DAMAGE]++;
    player.immunity[ACID]++;
    player.immunity[THEFT]++;
    player.immunity[INFECTION]++;
    player.status[SHADOWFORM] += player.level;
  }
  else
  {
    mprint("You feel even more shadowy.");
    player.status[SHADOWFORM] += player.level;
  }
}

void illuminate(int blessing)
{
  int r = level->site[player.x][player.y].roomnumber;
  if (blessing > -1)
  {
    if (r > ROOMBASE)
    {
      if (loc_statusp(player.x, player.y, LIT))
        mprint("A glow surrounds you.");
      else
      {
        mprint("The room lights up!");
        player.status[ILLUMINATION] += blessing + 3;
        spreadroomlight(player.x,
                        player.y,
                        level->site[player.x][player.y].roomnumber);
      }
    }
    else
      mprint("You see a faint glimmer of light which quickly fades.");
  }
  else
  {
    if (r > ROOMBASE)
    {
      if (!loc_statusp(player.x, player.y, LIT))
        mprint("Nothing much happens.");
      else
      {
        mprint("The room darkens!");
        spreadroomdark(player.x,
                       player.y,
                       level->site[player.x][player.y].roomnumber);
      }
    }
    else
      mprint("The gloom thickens for a moment.");
  }
}

void drain_life(int amount)
{
  amount = abs(amount);
  mprint("You feel cold!");
  if (p_immune(NEGENERGY))
    mprint("... but the feeling quickly fades.");
  else
  {
    if (random_range(2))
    {
      mprint("The coldness spreads throughout your body...");
      player.str -= amount;
      player.con -= amount;
      if ((player.str < 3) || (player.con < 3))
      {
        mprint("You suffer a fatal heart attack!!!");
        player.hp = 0;
        strcpy(Str2, "a coronary");
        p_death(Str2);
      }
    }
    else
    {
      mprint("The coldness saps your very soul...");
      strcpy(Str2, "soul destruction");
      level_drain(amount, Str2);
    }
  }
}

void inflict_fear(int x, int y)
{
  struct monster *m;
  if ((player.x == x) && (player.y == y))
  {
    mprint("You shudder with otherworldly dread.");
    if (player.immunity[FEAR] > 0)
      mprint("You brace up and face your fear like a hero!");
    else
    {
      mprint("You panic!");
      player.status[AFRAID] += 10;
    }
  }
  else if ((m = level->site[x][y].creature) != NULL)
  {
    if (m->uniqueness == COMMON)
    {
      strcpy(Str2, "The ");
      strcat(Str2, m->monstring);
    }
    else
      strcpy(Str2, m->monstring);
    m->speed = max(2, m->speed - 1);
    if (m_immunityp(m, FEAR))
      strcat(Str2, "seems enraged!");
    else
    {
      strcat(Str2, "is terrorized!");
      m_dropstuff(m);
      if (m_statusp(m, MOBILE))
        m->movef = M_MOVE_SCAREDY;
    }
  }
  else
    mprint("A thrill of fear tickles your spine ... and passes.");
}

/*Turns on deflection status for the player */
void deflection(int blessing)
{
  if (blessing > -1)
  {
    mprint("You feel buffered.");
    player.status[DEFLECTION] = blessing + random_range(6);
  }
  else
  {
    mprint("You feel vulnerable");
    player.status[VULNERABLE] += random_range(6) - blessing;
  }
}
