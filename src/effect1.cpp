/* omega copyright (C) by Laurence Raphael Brothers, 1987,1988,1989 */
/* effect1.c */

#include "glob.h"

/* enchant */
void enchant(int delta)
{
  int i, used = FALSE;
  long change_cash;

  if (delta < 0)
  {
    i = random_item();
    if (i == ABORT || player.possessions[i]->usef == I_NOTHING ||
        player.possessions[i]->usef == I_NO_OP ||
        player.possessions[i]->usef == I_NORMAL_ARMOR ||
        player.possessions[i]->usef == I_NORMAL_WEAPON ||
        player.possessions[i]->usef == I_NORMAL_SHIELD ||
        player.possessions[i]->objchar == FOOD ||
        player.possessions[i]->objchar == MISSILEWEAPON)
    {
      print1("You feel fortunate.");
      morewait();
    }
    else if (player.possessions[i]->blessing < 0 ||
             (player.possessions[i]->objchar == ARTIFACT && random_range(3)))
    {
      if (player.possessions[i]->uniqueness == COMMON)
        print1("Your ");
      nprint1(itemid(player.possessions[i]));
      nprint1(" glows, but the glow flickers out...");
      morewait();
    }
    else
    {
      used = (player.possessions[i]->used);
      if (used)
      {
        player.possessions[i]->used = FALSE;
        item_use(player.possessions[i]);
      }
      if (player.possessions[i]->uniqueness == COMMON)
        print1("Your ");
      nprint1(itemid(player.possessions[i]));
      nprint1(" radiates an aura of mundanity!");
      morewait();
      player.possessions[i]->plus = 0;
      player.possessions[i]->charge = -1;
      player.possessions[i]->usef = I_NOTHING;
      if (used)
      {
        player.possessions[i]->used = TRUE;
        item_use(player.possessions[i]);
      }
    }
  }
  else
  {
    i = getitem(CASH);
    if (i == ABORT)
    {
      print1("You feel unlucky.");
      morewait();
    }
    else if (i == CASHVALUE)
    {
      print1("You enchant your money.... What a concept!");
      change_cash = player.cash * (random_range(7) - 3) / 6;
      if (change_cash > 0)
        print2("Seems to have been a good idea!");
      else
        print2("Maybe it wasn't such a good idea....");
      player.cash += change_cash;
      morewait();
    }
    else if (player.possessions[i]->objchar == ARTIFACT)
    {
      if (player.possessions[i]->usef !=
          Objects[player.possessions[i]->id].usef)
      {
        print1("It re-acquires its magical aura!");
        player.possessions[i]->usef = Objects[player.possessions[i]->id].usef;
      }
      else
      {
        print1("The enchantment spell enfolds the ");
        nprint1(itemid(player.possessions[i]));
        print2("and the potent enchantment of the Artifact causes a backlash!");
        morewait();
        clearmsg();
        manastorm(player.x, player.y, player.possessions[i]->level * 5);
      }
    }
    else
    {
      if (player.possessions[i]->plus > random_range(20) + 1)
      {
        print1("Uh-oh, the force of the enchantment was too much!");
        print2("There is a loud explosion!");
        morewait();
        manastorm(player.x, player.y, player.possessions[i]->plus * 5);
        dispose_lost_objects(1, player.possessions[i]);
      }
      else
      {
        used = (player.possessions[i]->used);
        if (used)
        {
          setgamestatus(SUPPRESS_PRINTING);
          player.possessions[i]->used = FALSE;
          item_use(player.possessions[i]);
          resetgamestatus(SUPPRESS_PRINTING);
        }
        print1("The item shines!");
        morewait();
        player.possessions[i]->plus += delta + 1;
        if (player.possessions[i]->charge > -1)
          player.possessions[i]->charge +=
              ((delta + 1) * (random_range(10) + 1));
        if (used)
        {
          setgamestatus(SUPPRESS_PRINTING);
          player.possessions[i]->used = TRUE;
          item_use(player.possessions[i]);
          resetgamestatus(SUPPRESS_PRINTING);
        }
      }
    }
    calc_melee();
  }
}

/* bless */
void bless(int blessing)
{
  int index, used;

  if (blessing < 0)
  {
    index = random_item();
    if (index == ABORT)
    {
      print1("You feel fortunate.");
      morewait();
    }
    else
    {
      print1("A foul odor arises from ");
      if (player.possessions[index]->uniqueness == COMMON)
        nprint1("your ");
      nprint1(itemid(player.possessions[index]));
      morewait();
      used = (player.possessions[index]->used);
      if (used)
      {
        setgamestatus(SUPPRESS_PRINTING);
        player.possessions[index]->used = FALSE;
        item_use(player.possessions[index]);
        resetgamestatus(SUPPRESS_PRINTING);
      }
      player.possessions[index]->blessing -= 2;
      if (player.possessions[index]->blessing < 0)
        player.possessions[index]->plus =
            abs(player.possessions[index]->plus) - 1;
      if (used)
      {
        setgamestatus(SUPPRESS_PRINTING);
        player.possessions[index]->used = TRUE;
        item_use(player.possessions[index]);
        resetgamestatus(SUPPRESS_PRINTING);
      }
    }
  }
  else
  {
    index = getitem(NULL_ITEM);
    if (index == CASHVALUE)
    {
      print1("Blessing your money has no effect.");
      morewait();
    }
    else if (index != ABORT)
    {
      used = (player.possessions[index]->used == TRUE);
      if (used)
      {
        setgamestatus(SUPPRESS_PRINTING);
        player.possessions[index]->used = FALSE;
        item_use(player.possessions[index]);
        resetgamestatus(SUPPRESS_PRINTING);
      }
      print1("A pure white light surrounds the item... ");
      if (player.possessions[index]->blessing < 0 - (blessing + 1))
      {
        print2("which is evil enough to resist the effect of the blessing!");
        morewait();
      }
      else if (player.possessions[index]->blessing < -1)
      {
        print2("which disintegrates under the influence of the holy aura!");
        morewait();
        player.itemweight -= player.possessions[index]->weight;
        dispose_lost_objects(1, player.possessions[index]);
      }
      else if (player.possessions[index]->blessing < blessing + 1)
      {
        print2("which now seems affected by afflatus!");
        morewait();
        player.possessions[index]->blessing++;
        player.possessions[index]->plus =
            abs(player.possessions[index]->plus) + 1;
      }
      else
      {
        print2("The hierolux fades without any appreciable effect....");
        morewait();
      }
      if (used && (player.possessions[index] != NULL))
      {
        setgamestatus(SUPPRESS_PRINTING);
        player.possessions[index]->used = TRUE;
        item_use(player.possessions[index]);
        resetgamestatus(SUPPRESS_PRINTING);
      }
    }
  }
  calc_melee();
}

void heal(int amount)
{
  if (amount > -1)
  {
    mprint("You feel better.");
    if (player.hp < player.maxhp + amount)
    {
      player.hp += random_range(10 * amount) + 1;
      if (player.hp > player.maxhp)
        player.hp = player.maxhp + amount;
    }
    player.status[BLINDED] = 0;
  }
  else
  {
    mprint("You feel unwell.");
    player.hp -= random_range(10 * abs(amount) + 1);
    if (player.hp < 0)
      p_death("magical disruption");
  }
  dataprint();
}

void fbolt(int fx, int fy, int tx, int ty, int hit, int dmg)
{
  bolt(fx, fy, tx, ty, hit, dmg, FLAME);
}

void lbolt(int fx, int fy, int tx, int ty, int hit, int dmg)
{
  bolt(fx, fy, tx, ty, hit, dmg, ELECTRICITY);
}

/* Added 12/30/98 DG */
void icebolt(int fx, int fy, int tx, int ty, int hit, int dmg)
{
  bolt(fx, fy, tx, ty, hit, dmg, COLD);
}

void nbolt(int fx, int fy, int tx, int ty, int hit, int dmg)
{
  bolt(fx, fy, tx, ty, hit, dmg, NORMAL_DAMAGE);
}

/* from f to t */
void bolt(int fx, int fy, int tx, int ty, int hit, int dmg, int dtype)
{
  int xx, yy;
  Monster *target;
  Symbol boltchar;
  xx = fx;
  yy = fy;

  switch (dtype)
  {
  case FLAME:
    boltchar = ('*' | CLR(LIGHT_RED));
    break;
  case ELECTRICITY:
    boltchar = ('^' | CLR(LIGHT_BLUE));
    break;
  case NORMAL_DAMAGE:
    boltchar = ('!' | CLR(BROWN));
    break;
  case COLD:
    boltchar = ('o' | CLR(WHITE));
    break;
  default:
    assert(FALSE); /* this should never happen, right? WDT */
  }
  clearmsg();

  do_los(boltchar, &xx, &yy, tx, ty);

  if ((xx == player.x) && (yy == player.y))
  {
    if (player.status[DEFLECTION] > 0)
      mprint("The bolt just missed you!");
    else
    {
      switch (dtype)
      {
      case FLAME:
        mprint("You were blasted by a firebolt!");
        p_damage(random_range(dmg), dtype, "a firebolt");
        break;
      case ELECTRICITY:
        mprint("You were zapped by lightning!");
        p_damage(random_range(dmg), dtype, "a bolt of lightning");
        break;
      case NORMAL_DAMAGE:
        mprint("You were hit by a missile!");
        p_damage(random_range(dmg), dtype, "a missile");
        break;
      case COLD:
        mprint("You were hit by an icicle!");
        p_damage(random_range(dmg), dtype, "an icicle");
        break;
      }
    }
  }
  else if (NULL != (target = level->site[xx][yy].creature))
  {
    if (hitp(hit, target->ac))
    {
      if (target->uniqueness == COMMON)
      {
        strcpy(Str1, "The ");
        strcat(Str1, target->monstring);
      }
      else
        strcpy(Str1, target->monstring);
      switch (dtype)
      {
        /* WDT: these sentances really ought to be livened up.  Especially
         * in full verbose mode. */
      case FLAME:
        strcat(Str1, " was blasted by a firebolt!");
        break;
      case ELECTRICITY:
        strcat(Str1, " was zapped by lightning!");
        break;
      case NORMAL_DAMAGE:
        strcat(Str1, " was hit by a missile!");
        break;
      case COLD:
        strcat(Str1, " was hit by an icicle!");
        break;
      }
      mprint(Str1);
      m_status_set(target, HOSTILE);
      m_damage(target, random_range(dmg), dtype);
    }
    else
    {
      if (target->uniqueness == COMMON)
      {
        strcpy(Str1, "The ");
        strcat(Str1, target->monstring);
      }
      else
        strcpy(Str1, target->monstring);
      switch (dtype)
      {
      case FLAME:
        strcat(Str1, " was missed by a firebolt!");
        break;
      case ELECTRICITY:
        strcat(Str1, " was missed by lightning!");
        break;
      case NORMAL_DAMAGE:
        strcat(Str1, " was missed by a missile!");
        break;
      case COLD:
        strcat(Str1, " was missed by a flying icicle!");
        break;
      }
      mprint(Str1);
    }
  }
  else if (level->site[xx][yy].locchar == HEDGE)
    if (level->site[xx][yy].p_locf != L_TRIFID)
    {
      if ((dtype == FLAME) || (dtype == ELECTRICITY))
      {
        mprint("The hedge is blasted away!");
        level->site[xx][yy].p_locf = L_NO_OP;
        level->site[xx][yy].locchar = FLOOR;
        plotspot(xx, yy, TRUE);
        lset(xx, yy, CHANGED);
      }
      else
        mprint("The hedge is unaffected.");
    }
    else
      mprint("The trifid absorbs the energy and laughs!");
  else if (level->site[xx][yy].locchar == WATER)
    if (dtype == FLAME)
    {
      mprint("The water is vaporised!");
      level->site[xx][yy].p_locf = L_NO_OP;
      level->site[xx][yy].locchar = FLOOR;
      lset(xx, yy, CHANGED);
    }
}

void lball(int fx, int fy, int tx, int ty, int dmg)
{
  ball(fx, fy, tx, ty, dmg, ELECTRICITY);
}

void manastorm(int x, int y, int dmg)
{
  ball(x, y, x, y, dmg, UNSTOPPABLE);
}

void snowball(int fx, int fy, int tx, int ty, int dmg)
{
  ball(fx, fy, tx, ty, dmg, COLD);
}

void fball(int fx, int fy, int tx, int ty, int dmg)
{
  ball(fx, fy, tx, ty, dmg, FLAME);
}

/* from f to t */
void ball(int fx, int fy, int tx, int ty, int dmg, int dtype)
{
  int xx, yy, ex, ey, i;
  Monster *target;
  Symbol expchar = ('@' | CLR(LIGHT_PURPLE));

  xx = fx;
  yy = fy;

  switch (dtype)
  {
  case FLAME:
    expchar = ('*' | CLR(LIGHT_RED));
    break;
  case COLD:
    expchar = ('o' | CLR(WHITE));
    break;
  case ELECTRICITY:
    expchar = ('^' | CLR(LIGHT_BLUE));
    break;
  }

  do_los(expchar, &xx, &yy, tx, ty);
  draw_explosion(expchar, xx, yy);
  for (i = 0; i < 9; i++)
  {
    ex = xx + Dirs[0][i];
    ey = yy + Dirs[1][i];

    if ((ex == player.x) && (ey == player.y))
    {
      switch (dtype)
      {
      case FLAME:
        mprint("You were blasted by a fireball!");
        p_damage(random_range(dmg), FLAME, "a fireball");
        break;
      case COLD:
        mprint("You were blasted by a snowball!");
        p_damage(random_range(dmg), COLD, "a snowball");
        break;
      case ELECTRICITY:
        mprint("You were blasted by ball lightning!");
        p_damage(random_range(dmg), ELECTRICITY, "ball lightning");
        break;
      case UNSTOPPABLE:
        mprint("Oh No! Manastorm!");
        p_damage(random_range(dmg), UNSTOPPABLE, "a manastorm!");
        break;
      }
    }
    if (NULL != (target = level->site[ex][ey].creature))
    {
      if (los_p(player.x, player.y, target->x, target->y))
      {
        if (target->uniqueness == COMMON)
        {
          strcpy(Str1, "The ");
          strcat(Str1, target->monstring);
        }
        else
          strcpy(Str1, target->monstring);
        switch (dtype)
        {
        case FLAME:
          strcat(Str1, " was zorched by a fireball!");
          break;
        case COLD:
          strcat(Str1, " was blasted by a snowball!");
          break;
        case ELECTRICITY:
          strcat(Str1, " was zapped by ball lightning!");
          break;
        case UNSTOPPABLE:
          strcat(Str1, " was nuked by a manastorm!");
          break;
        }
        mprint(Str1);
      }
      m_status_set(target, HOSTILE);
      m_damage(target, random_range(dmg), dtype);
    }
    if (level->site[ex][ey].locchar == HEDGE)
      if (level->site[ex][ey].p_locf != L_TRIFID)
      {
        if ((dtype == FLAME) || (dtype == ELECTRICITY))
        {
          mprint("The hedge is blasted away!");
          level->site[ex][ey].p_locf = L_NO_OP;
          level->site[ex][ey].locchar = FLOOR;
          plotspot(ex, ey, TRUE);
          lset(ex, ey, CHANGED);
        }
        else
          mprint("The hedge is unaffected.");
      }
      else
        mprint("The trifid absorbs the energy and laughs!");
    else if (level->site[ex][ey].locchar == WATER)
      if (dtype == FLAME)
      {
        mprint("The water is vaporised!");
        level->site[ex][ey].p_locf = L_NO_OP;
        level->site[ex][ey].locchar = FLOOR;
        plotspot(ex, ey, TRUE);
        lset(ex, ey, CHANGED);
      }
  }
}

void mondet(int blessing)
{
  Monsterlist* ml;
  for (ml = level->mlist; ml != NULL; ml = ml->next)
    if (ml->m->hp > 0) /* FIXED 12/30/98 DG */
      if (blessing > -1)
        plotmon(ml->m);
      else
        putspot(random_range(WIDTH), random_range(LENGTH),
                Monsters[random_range(NUMMONSTERS)].monchar);
  levelrefresh();
  morewait();
  show_screen();
}

void objdet(int blessing)
{
  int i, j;
  for (i = 0; i < WIDTH; i++)
    for (j = 0; j < LENGTH; j++)
      if (level->site[i][j].things != NULL)
      {
        if (blessing < 0)
          putspot(random_range(WIDTH),
                  random_range(LENGTH),
                  level->site[i][j].things->thing->objchar);
        else
          putspot(i, j, level->site[i][j].things->thing->objchar);
      }
  levelrefresh();
  morewait();
  show_screen();
}

void identify(int blessing)
{
  int index;

  clearmsg();

  if (blessing == 0)
  {
    print1("Identify:");
    index = getitem(NULL_ITEM);
    if (index == CASHVALUE)
      print3("Your money is really money.");
    else if (index == ABORT)
      setgamestatus(SKIP_MONSTERS);
    else
    {
      if (player.possessions[index]->objchar == FOOD)
        player.possessions[index]->known = 1;
      else
      {
        player.possessions[index]->known = 2;
        Objects[player.possessions[index]->id].known = 1;
      }
      print1("Identified: ");
      mprint(itemid(player.possessions[index]));
    }
  }
  else if (blessing < 0)
  {
    print2("You feel forgetful.");
    for (index = 0; index < MAXITEMS; index++)
      if (player.possessions[index] != NULL)
      {
        player.possessions[index]->known = 0;
        Objects[player.possessions[index]->id].known = 0;
      }
  }
  else
  {
    print2("You feel encyclopaedic.");
    for (index = 0; index < MAXITEMS; index++)
      if (player.possessions[index] != NULL)
      {
        if (player.possessions[index]->objchar == FOOD)
          player.possessions[index]->known = 1;
        else
        {
          player.possessions[index]->known = 2;
          Objects[player.possessions[index]->id].known = 1;
        }
      }
    for (index = 0; index < player.packptr; index++)
      if (player.pack[index] != NULL)
      {
        if (player.pack[index]->objchar == FOOD)
          player.pack[index]->known = 1;
        else
        {
          player.pack[index]->known = 2;
          Objects[player.pack[index]->id].known = 1;
        }
      }
  }
  calc_melee();
}

/* returns index of random item, ABORT if player carrying none */
int random_item()
{
  int item = ABORT, tries = 0;
  int number = 0;

  for (tries = 0; tries < MAXITEMS; tries++)
    if (player.possessions[tries] != NULL)
    {
      number++;
      if (random_range(number) == 0)
        item = tries;
    }
  return (item);
}

/* various kinds of wishes */
void wish(int blessing)
{
  int i;
  char wishstr[80];
  clearmsg();
  print1("What do you wish for? ");
  if (blessing < 0)
    deathprint();
  else
    strcpy(wishstr, msgscanstring());
  if (blessing < 0 || strcmp(wishstr, "Death") == 0)
  {
    print2("As you wish, so shall it be.");
    p_death("a deathwish");
  }
  if (strcmp(wishstr, "Power") == 0)
  {
    print2("You feel a sudden surge of energy");
    player.mana = calcmana() * 10;
  }
  else if (strcmp(wishstr, "Skill") == 0)
  {
    print2("You feel more competent.");
    if (gamestatusp(CHEATED))
      gain_experience(10000);
    else
      gain_experience(min(10000, player.xp));
  }
  else if (strcmp(wishstr, "Wealth") == 0)
  {
    print2("You are submerged in shower of gold pieces!");
    player.cash += 10000;
  }
  else if (strcmp(wishstr, "Balance") == 0)
  {
    print2("You feel neutral.");
    player.alignment = 0;
  }
  else if (strcmp(wishstr, "Chaos") == 0)
  {
    print2("You feel chaotic.");
    player.alignment -= 25;
  }
  else if (strcmp(wishstr, "Law") == 0)
  {
    print2("You feel lawful.");
    player.alignment += 25;
  }
  else if (strcmp(wishstr, "Location") == 0)
    strategic_teleport(1);
  else if (strcmp(wishstr, "Knowledge") == 0)
  {
    print2("You feel more knowledgeable.");
    i = random_range(NUMSPELLS);
    if (Spells[i].known)
      Spells[i].powerdrain =
          (max(1, Spells[i].powerdrain / 2));
    else
      Spells[i].known = TRUE;
  }
  else if (strcmp(wishstr, "Health") == 0)
  {
    print2("You feel vigorous");
    player.hp = max(player.hp, player.maxhp);
    player.status[DISEASED] = 0;
    player.status[POISONED] = 0;
  }
  else if (strcmp(wishstr, "Destruction") == 0)
    annihilate(gamestatusp(CHEATED));
  else if (strcmp(wishstr, "Acquisition") == 0)
    acquire(gamestatusp(CHEATED));
  else if (strcmp(wishstr, "Summoning") == 0)
    summon(gamestatusp(CHEATED), -1);
  else if (strcmp(wishstr, "Stats") == 0 && gamestatusp(CHEATED))
  {
    player.str = player.maxstr = player.con = player.maxcon =
        player.agi = player.maxagi = player.dex = player.maxdex =
            player.iq = player.maxiq = player.pow = player.maxpow = 200;
    calc_melee();
  }
  else
    print2("You feel stupid.");
  dataprint();
  showflags();
}

/* gain for an item */
void acquire(int blessing)
{
  char otype;
  int index, id = ABORT;
  Object* newthing;

  if (blessing < 0)
  {
    index = random_item();
    if (index == ABORT)
      mprint("You feel fortunate.");
    else
    {
      print1("Smoke drifts out of your pack.... ");
      print2("Destroyed: ");
      nprint2(itemid(player.possessions[index]));
      morewait();
      dispose_lost_objects(1, player.possessions[index]);
    }
  }
  else
  {
    newthing = Object::create();
    newthing->id = -1;
    if (gamestatusp(CHEATED))
      print1("Acquire which kind of item: !?][}{)/=%%\\& ");
    else
      print1("Acquire which kind of item: !?][}{)/=%%\\ ");
    otype = mgetc();
    switch (otype)
    {
    case (POTION & 0xff):
      if (blessing > 0)
        id = itemlist(POTIONID, NUMPOTIONS);
      else
        id = random_range(NUMPOTIONS);
      if (id < 0)
        print2("You feel stupid.");
      else
        make_potion(newthing, id);
      break;
    case (SCROLL & 0xff):
      if (blessing > 0)
        id = itemlist(SCROLLID, NUMSCROLLS);
      else
        id = random_range(NUMSCROLLS);
      if (id < 0)
        print2("You feel stupid.");
      else
        make_scroll(newthing, id);
      break;
    case (RING & 0xff):
      if (blessing > 0)
        id = itemlist(RINGID, NUMRINGS);
      else
        id = random_range(NUMRINGS);
      if (id < 0)
        print2("You feel stupid.");
      else
        make_ring(newthing, id);
      break;
    case (STICK & 0xff):
      if (blessing > 0)
        id = itemlist(STICKID, NUMSTICKS);
      else
        id = random_range(NUMSTICKS);
      if (id < 0)
        print2("You feel stupid.");
      else
        make_stick(newthing, id);
      break;
    case (ARMOR & 0xff):
      if (blessing > 0)
        id = itemlist(ARMORID, NUMARMOR);
      else
        id = random_range(NUMARMOR);
      if (id < 0)
        print2("You feel stupid.");
      else
        make_armor(newthing, id);
      break;
    case (SHIELD & 0xff):
      if (blessing > 0)
        id = itemlist(SHIELDID, NUMSHIELDS);
      else
        id = random_range(NUMSHIELDS);
      if (id < 0)
        print2("You feel stupid.");
      else
        make_shield(newthing, id);
      break;
    case (WEAPON & 0xff):
      if (blessing > 0)
        id = itemlist(WEAPONID, NUMWEAPONS);
      else
        id = random_range(NUMWEAPONS);
      if (id < 0)
        print2("You feel stupid.");
      else
        Object::makeWeapon(id,newthing);
      break;
    case (BOOTS & 0xff):
      if (blessing > 0)
        id = itemlist(BOOTID, NUMBOOTS);
      else
        id = random_range(NUMBOOTS);
      if (id < 0)
        print2("You feel stupid.");
      else
        make_boots(newthing, id);
      break;
    case (CLOAK & 0xff):
      if (blessing > 0)
        id = itemlist(CLOAKID, NUMCLOAKS);
      else
        id = random_range(NUMCLOAKS);
      if (id < 0)
        print2("You feel stupid.");
      else
        make_cloak(newthing, id);
      break;
    case (FOOD & 0xff):
      if (blessing > 0)
        id = itemlist(FOODID, NUMFOODS);
      else
        id = random_range(NUMFOODS);
      if (id < 0)
        print2("You feel stupid.");
      else
        make_food(newthing, id);
      break;
    case (THING & 0xff):
      if (blessing > 0)
        id = itemlist(THINGID, NUMTHINGS);
      else
        id = random_range(NUMTHINGS);
      if (id < 0)
        print2("You feel stupid.");
      else
        make_thing(newthing, id);
      break;
    case (ARTIFACT & 0xff):
      if (gamestatusp(CHEATED))
        id = itemlist(ARTIFACTID, NUMARTIFACTS);
      else
        id = -1;
      if (id < 0)
        print2("You feel stupid.");
      else
        make_artifact(newthing, id);
      break;
    default:
      print2("You feel stupid.");
    }
    xredraw();
    if (id != ABORT)
    {
      if (blessing > 0)
      {
        newthing->known = 2;
        Objects[id].known = 1;
      }
      newthing->used = FALSE;
      gain_item(newthing);
    }
  }
}
