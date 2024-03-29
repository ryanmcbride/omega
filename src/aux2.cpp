/* omega copyright (C) by Laurence Raphael Brothers, 1987,1988,1989 */
/* aux2.c */
/* some functions called by ocom.c, also see aux1.c and aux3.c*/
/* This is a real grab bag file. It contains functions used by
   aux1.c and omega.c, as well as elsewhere. It is mainly here so aux1.c
   and aux3.c are not huge */

#include "glob.h"
#include <map>

/* Player stats like str, agi, etc give modifications to various abilities
   chances to do things, etc. Positive is good, negative bad. */
int statmod(int stat)
{
  return ((stat - 10) / 2);
}

/* effects of hitting */
void p_hit(Monster *m, int dmg, int dtype)
{
  int dmult;

  /* chance for critical hit..., 3/10 */
  switch (random_range(10))
  {
  case 0:
    if (random_range(100) < player.level)
    {
      strcpy(Str3, "You annihilate ");
      dmult = 1000;
    }
    else
    {
      strcpy(Str3, "You blast ");
      dmult = 5;
    }
    break;
  case 1:
  case 2:
    strcpy(Str3, "You smash ");
    dmult = 2;
    break;

  default:
    dmult = 1;
    if (random_range(10))
      strcpy(Str3, "You hit ");
    else
      switch (random_range(4))
      {
      case 0:
        strcpy(Str3, "You damage ");
        break;
      case 1:
        strcpy(Str3, "You inflict bodily harm on ");
        break;
      case 2:
        strcpy(Str3, "You injure ");
        break;
      case 3:
        strcpy(Str3, "You molest ");
        break;
      }
    break;
  }
  if (Lunarity == 1)
    dmult = dmult * 2;
  else if (Lunarity == -1)
    dmult = dmult / 2;
  if (m->uniqueness == COMMON)
    strcat(Str3, "the ");
  strcat(Str3, m->monstring);
  strcat(Str3, ". ");
  if (Verbosity != TERSE)
    mprint(Str3);
  else
    mprint("You hit it.");
  m_damage(m, dmult * random_range(dmg), dtype);
  if ((Verbosity != TERSE) && (random_range(10) == 3) && (m->hp > 0))
    mprint("It laughs at the injury and fights on!");
}

/* and effects of missing */
void player_miss(Monster *m, int dtype)
{
  if (random_range(30) == 1) /* fumble 1 in 30 */
    p_fumble(dtype);
  else
  {
    if (Verbosity != TERSE)
    {
      if (random_range(10))
        strcpy(Str3, "You miss ");
      else
        switch (random_range(4))
        {
        case 0:
          strcpy(Str3, "You flail lamely at ");
          break;
        case 1:
          strcpy(Str3, "You only amuse ");
          break;
        case 2:
          strcpy(Str3, "You fail to even come close to ");
          break;
        case 3:
          strcpy(Str3, "You totally avoid contact with ");
          break;
        }
      if (m->uniqueness == COMMON)
        strcat(Str3, "the ");
      strcat(Str3, m->monstring);
      strcat(Str3, ". ");
      mprint(Str3);
    }
    else
      mprint("You missed it.");
  }
}

/* oh nooooo, a fumble.... */
void p_fumble(int dtype)
{
  mprint("Ooops! You fumbled....");
  switch (random_range(10))
  {
  case 0:
  case 1:
  case 2:
  case 3:
  case 4:
  case 5:
    drop_weapon();
    break;
  case 6:
  case 7:
  case 8:
    break_weapon();
    break;
  case 9:
    mprint("Oh No! You hit yourself!");
    p_damage(player.dmg, dtype, "stupidity");
    break;
  }
}

/* try to drop a weapon (from fumbling) */
void drop_weapon()
{
  if (player.possessions[O_WEAPON_HAND] != NULL)
  {
    std::string str = std::string("You dropped your ") + player.possessions[O_WEAPON_HAND]->objstr;
    mprint(str);
    morewait();
    p_drop_at(player.x, player.y, 1, player.possessions[O_WEAPON_HAND]);
    conform_lost_objects(1, player.possessions[O_WEAPON_HAND]);
  }
  else
    mprint("You feel fortunate.");
}

/* try to break a weapon (from fumbling) */
void break_weapon()
{
  if (player.possessions[O_WEAPON_HAND] != NULL)
  {
    std::string str = std::string("Your ") + itemid(player.possessions[O_WEAPON_HAND]) + " vibrates in your hand....";
    mprint(str);
    (void)damage_item(player.possessions[O_WEAPON_HAND]);
    morewait();
  }
}

/* hooray */
void p_win()
{
  morewait();
  clearmsg();
  print1("You won!");
  morewait();
  display_win();
  endgraf();
  exit(0);
}

/* handle a h,j,k,l, etc., to change x and y by dx and dy */
/* for targeting in dungeon */
void movecursor(int *x, int *y, int dx, int dy)
{
  if (inbounds(*x + dx, *y + dy))
  {
    *x += dx;
    *y += dy;
    screencheck(*y);
  }
  omshowcursor(*x, *y);
}

/* is Player immune to damage type dtype */
int p_immune(int dtype)
{
  return (player.immunity[dtype] > 0);
}

/* deal with each possible stati -- values are per move */
/* this function is executed every move */
/* A value over 1000 indicates a permanent effect */
void minute_status_check()
{
  int i;

  if (player.status[HASTED] > 0)
  {
    if (player.status[HASTED] < 1000)
    {
      player.status[HASTED]--;
      if (player.status[HASTED] == 0)
      {
        mprint("The world speeds up.");
        calc_melee();
      }
    }
  }

  if (player.status[POISONED] > 0)
  {
    player.status[POISONED]--;
    p_damage(3, POISON, "poison");
    if (player.status[POISONED] == 0)
    {
      showflags();
      mprint("You feel better now.");
    }
  }

  if (player.immunity[UNSTOPPABLE] > 0)
  {
    for (i = 0; i < NUMIMMUNITIES; i++)
      player.immunity[i]--;
    if (player.immunity[UNSTOPPABLE] == 1)
      mprint("You feel vincible again.");
  }

  if (player.status[IMMOBILE] > 0)
  {
    player.status[IMMOBILE]--;
    if (player.status[IMMOBILE] == 0)
      mprint("You can move again.");
  }

  if (player.status[SLEPT] > 0)
  {
    player.status[SLEPT]--;
    if (player.status[SLEPT] == 0)
    {
      mprint("You woke up.");
    }
  }

  if (player.status[REGENERATING] > 0)
  {
    if ((player.hp < player.maxhp) && (player.mana > 0))
    {
      player.hp++;
      player.mana--;
      dataprint();
    }
    if (player.status[REGENERATING] < 1000)
    {
      player.status[REGENERATING]--;
      if (player.status[REGENERATING] == 0)
      {
        mprint("You feel less homeostatic.");
      }
    }
  }

  if (player.status[SLOWED] > 0)
  {
    if (player.status[SLOWED] < 1000)
    {
      player.status[SLOWED]--;
      if (player.status[SLOWED] == 0)
      {
        mprint("You feel quicker now.");
        calc_melee();
      }
    }
  }

  if (player.status[RETURNING] > 0)
  {
    player.status[RETURNING]--;
    if (player.status[RETURNING] == 10)
      mprint("Your return spell slowly hums towards activation...");
    else if (player.status[RETURNING] == 8)
      mprint("There is an electric tension in the air!");
    else if (player.status[RETURNING] == 5)
      mprint("A vortex of mana begins to form around you!");
    else if (player.status[RETURNING] == 1)
      mprint("Your surroundings start to warp and fade!");
    if (player.status[RETURNING] == 0)
      level_return();
  }

  if (player.status[AFRAID] > 0)
  {
    if (player.status[AFRAID] < 1000)
    {
      player.status[AFRAID]--;
      if (player.status[AFRAID] == 0)
      {
        mprint("You feel bolder now.");
      }
    }
  }
}

/* effect of gamma ray radiation... */
void moon_check()
{
  /* 24 day lunar cycle */
  Phase = (Phase + 1) % 24;
  phaseprint();
  Lunarity = 0;
  if (((player.patron == DRUID) && ((Phase / 2 == 3) || (Phase / 2 == 9))) ||
      ((player.alignment > 10) && (Phase / 2 == 6)) ||
      ((player.alignment < -10) && (Phase / 2 == 0)))
  {
    mprint("As the moon rises you feel unusually vital!");
    Lunarity = 1;
  }
  else if (((player.patron == DRUID) && ((Phase / 2 == 0) || (Phase / 2 == 6))) ||
           ((player.alignment > 10) && (Phase / 2 == 0)) ||
           ((player.alignment < -10) && (Phase / 2 == 6)))
  {
    mprint("The rise of the moon tokens a strange enervation!");
    Lunarity = -1;
  }
}

/* check 1/hour for torch to burn out if used */
void torch_check()
{
  int i;
  for (i = O_READY_HAND; i <= O_WEAPON_HAND; i++)
  {
    if (player.possessions[i] != NULL)
      if ((player.possessions[i]->id == THINGID + 8) && /*torch */
          (player.possessions[i]->aux > 0))
      {
        player.possessions[i]->aux--;
        if (player.possessions[i]->aux == 0)
        {
          mprint("Your torch goes out!!!");
          conform_unused_object(player.possessions[i]);
          if (player.possessions[i]->number > 1)
          {
            player.possessions[i]->number--;
            player.possessions[i]->aux = 6;
          }
          else
          {
            player.possessions[i]->usef = I_NO_OP;
            player.possessions[i]->cursestr =
                player.possessions[i]->truename =
                    player.possessions[i]->objstr = "burnt-out torch";
          }
        }
      }
  }
}

/* values are in multiples of ten minutes */
/* values over 1000 indicate a permanent effect */
void tenminute_status_check()
{
  if ((player.status[SHADOWFORM] > 0) && (player.status[SHADOWFORM] < 1000))
  {
    player.status[SHADOWFORM]--;
    if (player.status[SHADOWFORM] == 0)
    {
      player.immunity[NORMAL_DAMAGE]--;
      player.immunity[ACID]--;
      player.immunity[THEFT]--;
      player.immunity[INFECTION]--;
      mprint("You feel less shadowy now.");
    }
  }

  if ((player.status[ILLUMINATION] > 0) && (player.status[ILLUMINATION] < 1000))
  {
    player.status[ILLUMINATION]--;
    if (player.status[ILLUMINATION] == 0)
    {
      mprint("Your light goes out!");
    }
  }

  if ((player.status[VULNERABLE] > 0) && (player.status[VULNERABLE] < 1000))
  {
    player.status[VULNERABLE]--;
    if (player.status[VULNERABLE] == 0)
      mprint("You feel less endangered.");
  }

  if ((player.status[DEFLECTION] > 0) && (player.status[DEFLECTION] < 1000))
  {
    player.status[DEFLECTION]--;
    if (player.status[DEFLECTION] == 0)
      mprint("You feel less well defended.");
  }

  if ((player.status[ACCURATE] > 0) && (player.status[ACCURACY] < 1000))
  {
    player.status[ACCURATE]--;
    if (player.status[ACCURATE] == 0)
    {
      calc_melee();
      mprint("The bulls' eyes go away.");
    }
  }
  if ((player.status[HERO] > 0) && (player.status[HERO] < 1000))
  {
    player.status[HERO]--;
    if (player.status[HERO] == 0)
    {
      calc_melee();
      mprint("You feel less than super.");
    }
  }

  if ((player.status[LEVITATING] > 0) && (player.status[LEVITATING] < 1000))
  {
    player.status[LEVITATING]--;
    if (player.status[LEVITATING] == 0)
      mprint("You're no longer walking on air.");
  }

  if (player.status[DISEASED] > 0)
  {
    player.status[DISEASED]--;
    if (player.status[DISEASED] == 0)
    {
      showflags();
      mprint("You feel better now.");
    }
  }

  if ((player.status[INVISIBLE] > 0) && (player.status[INVISIBLE] < 1000))
  {
    player.status[INVISIBLE]--;
    if (player.status[INVISIBLE] == 0)
      mprint("You feel more opaque now.");
  }

  if ((player.status[BLINDED] > 0) && (player.status[BLINDED] < 1000))
  {
    player.status[BLINDED]--;
    if (player.status[BLINDED] == 0)
      mprint("You can see again.");
  }

  if ((player.status[TRUESIGHT] > 0) && (player.status[TRUESIGHT] < 1000))
  {
    player.status[TRUESIGHT]--;
    if (player.status[TRUESIGHT] == 0)
      mprint("You feel less keen now.");
  }

  if ((player.status[BERSERK] > 0) && (player.status[BERSERK] < 1000))
  {
    player.status[BERSERK]--;
    if (player.status[BERSERK] == 0)
      mprint("You stop foaming at the mouth.");
  }

  if ((player.status[ALERT] > 0) && (player.status[ALERT] < 1000))
  {
    player.status[ALERT]--;
    if (player.status[ALERT] == 0)
      mprint("You feel less alert now.");
  }

  if ((player.status[BREATHING] > 0) && (player.status[BREATHING] < 1000))
  {
    player.status[BREATHING]--;
    if (player.status[BREATHING] == 0)
      mprint("You feel somewhat congested.");
  }

  if ((player.status[DISPLACED] > 0) && (player.status[DISPLACED] < 1000))
  {
    player.status[DISPLACED]--;
    if (player.status[DISPLACED] == 0)
      mprint("You feel a sense of position.");
  }
  timeprint();
  dataprint();
}

/* Increase in level at appropriate experience gain */
void gain_level()
{
  int gained = FALSE;
  int hp_gain; /* FIXED! 12/30/98 */

  if (gamestatusp(SUPPRESS_PRINTING))
    return;
  while (expval(player.level + 1) <= player.xp)
  {
    if (!gained)
      morewait();
    gained = TRUE;
    player.level++;
    print1("You have attained a new experience level!");
    print2("You are now ");
    nprint2(getarticle(levelname(player.level)));
    nprint2(levelname(player.level));
    hp_gain = random_range(player.con) + 1; /* start fix 12/30/98 */
    if (player.hp < player.maxhp)
      player.hp += hp_gain * player.hp / player.maxhp;
    else if (player.hp < player.maxhp + hp_gain)
      player.hp = player.maxhp + hp_gain;
    /* else leave current hp alone */
    player.maxhp += hp_gain;
    player.maxmana = calcmana();
    /* If the character was given a bonus, let him keep it.  Otherwise
     * recharge him. */
    player.mana = max(player.mana, player.maxmana); /* end fix 12/30/98 */
    morewait();
  }
  if (gained)
    clearmsg();
  calc_melee();
}

/* experience requirements */
long expval(int plevel)
{
  switch (plevel)
  {
  case 0:
    return (0L);
  case 1:
    return (20L);
  case 2:
    return (50L);
  case 3:
    return (200L);
  case 4:
    return (500L);
  case 5:
    return (1000L);
  case 6:
    return (2000L);
  case 7:
    return (3000L);
  case 8:
    return (5000L);
  case 9:
    return (7000L);
  case 10:
    return (10000L);
  default:
    return ((plevel - 9) * 10000L);
  }
}

/* If an item is unidentified, it isn't worth much to those who would buy it */
long item_value(Object *item)
{
  if (item->known == 0)
  {
    if (item->objchar == THING)
      return (1);
    else
      return (true_item_value(item) / 10);
  }
  else if (item->known == 1)
  {
    if (item->objchar == THING)
      return (item->basevalue);
    else
      return (item->basevalue / 2);
  }
  else
    return (true_item_value(item));
}

/* figures value based on item base-value, charge, plus, and blessing */
long true_item_value(Object *item)
{
  long value = item->basevalue;

  if (item->objchar == THING)
    return (item->basevalue);
  else
  {
    if (item->objchar == STICK)
      value += value * item->charge / 20;
    if (item->plus > -1)
      value += value * item->plus / 4;
    else
      value /= -item->plus;
    if (item->blessing > 0)
      value *= 2;
    return ((long)value);
  }
}

/* kill off player if he isn't got the "breathing" status */
void p_drown()
{
  int attempts = 3, i;

  if (player.status[BREATHING] > 0)
    mprint("Your breathing is unaffected!");
  else
    while (player.possessions[O_ARMOR] ||
           player.itemweight > ((int)(player.maxweight / 2)))
    {
      menuclear();
      switch (attempts--)
      {
      case 3:
        print3("You try to hold your breath...");
        break;
      case 2:
        print3("You try to hold your breath... You choke...");
        break;
      case 1:
        print3("You try to hold your breath... You choke... Your lungs fill...");
        break;
      case 0:
        p_death("drowning");
      }
      morewait();
      menuprint("a: Drop an item.\n");
      menuprint("b: Bash an item.\n");
      menuprint("c: Drop your whole pack.\n");
      showmenu();
      switch (menugetc())
      {
      case 'a':
        drop();
        if (level->site[player.x][player.y].p_locf == L_WATER && level->site[player.x][player.y].things)
        {
          mprint("It sinks without a trace.");
          level->site[player.x][player.y].things->free();
          level->site[player.x][player.y].things = NULL;
        }
        break;
      case 'b':
        bash_item();
        break;
      case 'c':
        setgamestatus(SUPPRESS_PRINTING);
        for (i = 0; i < MAXPACK; i++)
        {
          if (player.pack[i] != NULL)
            if (level->site[player.x][player.y].p_locf != L_WATER)
              p_drop_at(player.x, player.y, player.pack[i]->number, player.pack[i]);
          delete player.pack[i];
          player.pack[i] = NULL;
        }
        if (level->site[player.x][player.y].p_locf == L_WATER)
          mprint("It sinks without a trace.");
        player.packptr = 0;
        resetgamestatus(SUPPRESS_PRINTING);
        calc_melee();
        break;
      }
    }
  show_screen();
  return;
}

/* the effect of some weapon on Monster m, with dmgmod a bonus to damage */
void weapon_use(int dmgmod, Object *weapon, Monster *m)
{
  int aux = (weapon == NULL ? -2 : weapon->aux); /* bare hands */
  switch (aux)
  {
  case -2:
    weapon_bare_hands(dmgmod, m);
    break;
  default:
  case I_NO_OP:
    weapon_normal_hit(dmgmod, weapon, m);
    break;
  case I_ACIDWHIP:
    weapon_acidwhip(dmgmod, weapon, m);
    break;
  case I_MJOLNIR:
    weapon_mjolnir(dmgmod, weapon, m);
    break;
  case I_TANGLE:
    weapon_tangle(dmgmod, weapon, m);
    break;
  case I_ARROW:
    weapon_arrow(dmgmod, weapon, m);
    break;
  case I_BOLT:
    weapon_bolt(dmgmod, weapon, m);
    break;
  case I_DEMONBLADE:
    weapon_demonblade(dmgmod, weapon, m);
    break;
  case I_LIGHTSABRE:
    weapon_lightsabre(dmgmod, weapon, m);
    break;
  case I_MACE_DISRUPT:
    weapon_mace_disrupt(dmgmod, weapon, m);
    break;
  case I_VORPAL:
    weapon_vorpal(dmgmod, weapon, m);
    break;
  case I_DESECRATE:
    weapon_desecrate(dmgmod, weapon, m);
    break;
  case I_FIRESTAR:
    weapon_firestar(dmgmod, weapon, m);
    break;
  case I_DEFEND:
    weapon_defend(dmgmod, weapon, m);
    break;
  case I_VICTRIX:
    weapon_victrix(dmgmod, weapon, m);
    break;
  case I_SCYTHE:
    weapon_scythe(dmgmod, weapon, m);
    break;
  }
}

/* for printing actions in printactions above */
char *actionlocstr(char dir)
{
  switch (dir)
  {
  case 'L':
    strcpy(Str3, "low.");
    break;
  case 'C':
    strcpy(Str3, "center.");
    break;
  case 'H':
    strcpy(Str3, "high.");
    break;
  default:
    strcpy(Str3, "wildly.");
    break;
  }
  return (Str3);
}

/* execute player combat actions versus Monster m */
void tacplayer(Monster *m)
{
  int i = 0;
  std::string str;
  while (i < strlen(player.meleestr))
  {
    if (m->hp > 0)
    {
      switch (player.meleestr[i])
      {
      case 't':
      case 'T':
        if (player.possessions[O_WEAPON_HAND] == NULL)
          str = "You punch ";
        else
          str = "You thrust ";
        str += actionlocstr(player.meleestr[i + 1]);
        if (Verbosity == VERBOSE)
          mprint(str);
        if (player_hit(2 * statmod(player.dex), player.meleestr[i + 1], m))
          weapon_use(0, player.possessions[O_WEAPON_HAND], m);
        else
          player_miss(m, NORMAL_DAMAGE);
        break;
      case 'c':
      case 'C':
        if (player.possessions[O_WEAPON_HAND] == NULL)
          str = "You punch ";
        else if (player.possessions[O_WEAPON_HAND]->type == CUTTING)
          str = "You cut ";
        else if (player.possessions[O_WEAPON_HAND]->type == STRIKING)
          str = "You strike ";
        else
          str = "You attack ";
        str += actionlocstr(player.meleestr[i + 1]);
        if (Verbosity == VERBOSE)
          mprint(str);
        if (player_hit(0, player.meleestr[i + 1], m))
          weapon_use(2 * statmod(player.str),
                     player.possessions[O_WEAPON_HAND],
                     m);
        else
          player_miss(m, NORMAL_DAMAGE);
        break;
      case 'l':
      case 'L':
        str = "You lunge ";
        str += actionlocstr(player.meleestr[i + 1]);
        if (Verbosity == VERBOSE)
          mprint(str);
        if (player_hit(player.level + player.dex, player.meleestr[i + 1], m))
          weapon_use(player.level, player.possessions[O_WEAPON_HAND], m);
        else
          player_miss(m, NORMAL_DAMAGE);
        break;
      }
    }
    i += 2;
  }
}

/* checks to see if player hits with hitmod vs. Monster m at location hitloc */
int player_hit(int hitmod, char hitloc, Monster *m)
{
  int i = 0, blocks = FALSE, goodblocks = 0, hit;
  if (m->hp < 1)
  {
    mprint("Unfortunately, your opponent is already dead!");
    return (FALSE);
  }
  else
  {
    if (hitloc == 'X')
      hitloc = random_loc();

    transcribe_monster_actions(m);

    while (i < strlen(m->meleestr))
    {
      if ((m->meleestr[i] == 'B') || (m->meleestr[i] == 'R'))
      {
        blocks = TRUE;
        if (hitloc == m->meleestr[i + 1])
          goodblocks++;
      }
      i += 2;
    }

    if (!blocks)
      goodblocks = -1;
    hit = hitp(player.hit + hitmod, m->ac + goodblocks * 10);
    if ((!hit) && (goodblocks > 0))
    {
      std::string str;
      if (m->uniqueness == COMMON)
      {
        str = "The ";
        str += m->monstring;
      }
      else
        str = m->monstring;
      str += " blocks it!";
      if (Verbosity == VERBOSE)
        mprint(str);
    }
    return (hit);
  }
}

/* This function is used to undo all items temporarily, should
always be used in pairs with on being TRUE and FALSE, and may cause
anomalous stats and item-usage if used indiscriminately */

void toggle_item_use(int on)
{
  static int used[MAXITEMS];
  int i;
  setgamestatus(SUPPRESS_PRINTING);
  if (on)
    for (i = 0; i < MAXITEMS; i++)
    {
      used[i] = FALSE;
      if (player.possessions[i] != NULL)
      {
        if ((used[i] = player.possessions[i]->used) == TRUE)
        {
          player.possessions[i]->used = FALSE;
          player.possessions[i]->item_use();
        }
      }
    }
  else
  {
    for (i = 1; i < MAXITEMS; i++)
      if (used[i])
      {
        player.possessions[i]->used = TRUE;
        player.possessions[i]->item_use();
      }
    calc_melee();
    showflags();
    dataprint();
    timeprint();
  }
  resetgamestatus(SUPPRESS_PRINTING);
}

void enter_site(Symbol site)
{
  std::map<Symbol, unsigned int> siteMap = {
      {CITY, E_CITY},
      {VILLAGE, E_VILLAGE},
      {CAVES, E_CAVES},
      {CASTLE, E_CASTLE},
      {VOLCANO, E_VOLCANO},
      {TEMPLE, E_TEMPLE},
      {DRAGONLAIR, E_DLAIR},
      {STARPEAK, E_STARPEAK},
      {MAGIC_ISLE, E_MAGIC_ISLE},
      {WEREWOLF_DEN, E_WEREWOLF_DEN}};
  if (siteMap.count(site) > 0)
    change_environment(siteMap[site]);
  else
    print3("There's nothing to enter here!");
}

/* Switches context dungeon/countryside/city, etc */
void change_environment(char new_environment)
{
  int i, emerging = FALSE;

  player.sx = -1;
  player.sy = -1;        /* reset sanctuary if there was one */
  resetgamestatus(LOST); /* in case the player gets lost _on_ a site */

  resetgamestatus(FAST_MOVE);

  Last_Environment = Current_Environment;
  if (Last_Environment == E_COUNTRYSIDE)
  {
    LastCountryLocX = player.x;
    LastCountryLocY = player.y;
  }
  if (((Last_Environment == E_CITY) ||
       (Last_Environment == E_VILLAGE)) &&
      ((new_environment == E_MANSION) ||
       (new_environment == E_HOUSE) ||
       (new_environment == E_HOVEL) ||
       (new_environment == E_SEWERS) ||
       (new_environment == E_ARENA)))
  {
    LastTownLocX = player.x;
    LastTownLocY = player.y;
  }
  else if (((Last_Environment == E_MANSION) ||
            (Last_Environment == E_HOUSE) ||
            (Last_Environment == E_HOVEL) ||
            (Last_Environment == E_SEWERS) ||
            (Last_Environment == E_ARENA)) &&
           ((new_environment == E_CITY) ||
            (new_environment == E_VILLAGE)))
  {
    player.x = LastTownLocX;
    player.y = LastTownLocY;
    emerging = TRUE;
  }

  Current_Environment = new_environment;
  switch (new_environment)
  {
  case E_ARENA:
    LENGTH = 16;
    WIDTH = 64;
    player.x = 5;
    player.y = 7;
    setgamestatus(ARENA_MODE);
    load_arena();
    ScreenOffset = 0;
    show_screen();
    break;
  case E_ABYSS:
    LENGTH = 16;
    WIDTH = 64;
    player.x = 32;
    player.y = 15;
    load_abyss();
    abyss_file();
    lose_all_items();
    ScreenOffset = 0;
    show_screen();
    break;
  case E_CIRCLE:
    LENGTH = 16;
    WIDTH = 64;
    player.x = 32;
    player.y = 14;
    load_circle(TRUE);
    if (Objects[ARTIFACTID + 21].uniqueness == UNIQUE_TAKEN)
    {
      print1("A bemused voice says:");
      print2("'Why are you here? You already have the Star Gem!'");
      morewait();
    }
    else if (player.rank[CIRCLE] > 0)
    {
      print1("You hear the voice of the Prime Sorceror:");
      print2("'Congratulations on your attainment of the Circle's Demesne.'");
      morewait();
      print1("For the honor of the Circle, you may take the Star Gem");
      print2("and destroy it on the acme of Star Peak.");
      morewait();
      print1("Beware the foul LawBringer who resides there...");
      print2("By the way, some of the members of the Circle seem to");
      morewait();
      print1("have become a bit jealous of your success --");
      print2("I'd watch out for them too if I were you.");
      morewait();
    }
    else if (player.alignment > 0)
    {
      print1("A mysterious ghostly image materializes in front of you.");
      print2("It speaks: 'Greetings, fellow abider in Law. I am called");
      morewait();
      print1("The LawBringer. If you wish to advance our cause, obtain");
      print2("the mystic Star Gem and return it to me on Star Peak.");
      morewait();
      print1("Beware the power of the evil Circle of Sorcerors and the");
      print2("forces of Chaos which guard the gem.'");
      morewait();
      print1("The strange form fades slowly.");
      morewait();
    }
    ScreenOffset = 0;
    show_screen();
    break;
  case E_COURT:
    WIDTH = 64;
    LENGTH = 24;
    player.x = 32;
    player.y = 2;
    LastCountryLocX = 6;
    LastCountryLocY = 1;
    load_court(TRUE);
    ScreenOffset = 0;
    show_screen();
    break;
  case E_MANSION:
    WIDTH = 64;
    LENGTH = 16;
    load_house(E_MANSION, TRUE);
    player.y = 8;
    player.x = 2;
    ScreenOffset = 0;
    show_screen();
    break;
  case E_HOUSE:
    WIDTH = 64;
    LENGTH = 16;
    load_house(E_HOUSE, TRUE);
    player.y = 13;
    player.x = 2;
    ScreenOffset = 0;
    show_screen();
    break;
  case E_HOVEL:
    WIDTH = 64;
    LENGTH = 16;
    load_house(E_HOVEL, TRUE);
    player.y = 9;
    player.x = 2;
    ScreenOffset = 0;
    show_screen();
    break;
  case E_DLAIR:
    WIDTH = 64;
    LENGTH = 16;
    player.y = 9;
    player.x = 2;
    load_dlair(gamestatusp(KILLED_DRAGONLORD), TRUE);
    ScreenOffset = 0;
    show_screen();
    break;
  case E_STARPEAK:
    WIDTH = 64;
    LENGTH = 16;
    player.y = 9;
    player.x = 2;
    load_speak(gamestatusp(KILLED_LAWBRINGER), TRUE);
    ScreenOffset = 0;
    show_screen();
    break;
  case E_MAGIC_ISLE:
    WIDTH = 64;
    LENGTH = 16;
    player.y = 14;
    player.x = 62;
    load_misle(gamestatusp(KILLED_EATER), TRUE);
    ScreenOffset = 0;
    show_screen();
    break;
  case E_WEREWOLF_DEN:
    WIDTH = 64;
    LENGTH = 16;
    player.y = 14;
    player.x = 62;
    load_werewolf_den(gamestatusp(KILLED_EATER), TRUE);
    ScreenOffset = 0;
    show_screen();
    break;
  case E_TEMPLE:
    WIDTH = 64;
    LENGTH = 16;
    load_temple(Country[player.x][player.y].aux, TRUE);
    player.y = 15;
    player.x = 32;
    ScreenOffset = 0;
    show_screen();
    break;
  case E_CITY:
    WIDTH = 64;
    LENGTH = 64;
    if (emerging)
    {
      print1("You emerge onto the street.");
      emerging = FALSE;
    }
    else
    {
      print1("You pass through the massive gates of Rampart, the city.");
      player.x = 62;
      player.y = 21;
    }
    if (City == NULL)
      load_city(TRUE);
#ifdef SAVE_LEVELS
    else
      msdos_changelevel(Level, new_environment, 0);
#endif
    level = City;
    ScreenOffset = player.y - (ScreenLength / 2);
    show_screen();
    break;
  case E_VILLAGE:
    WIDTH = 64;
    LENGTH = 16;
    if (!emerging)
    {
      /* different villages per different locations */
      switch (Country[player.x][player.y].aux)
      {
      case 1:
        player.x = 0;
        player.y = 6;
        Villagenum = 1;
        break;
      default:
        print3("Very strange, a nonexistent village.");
      case 2:
        player.x = 39;
        player.y = 15;
        Villagenum = 2;
        break;
      case 3:
        player.x = 63;
        player.y = 8;
        Villagenum = 3;
        break;
      case 4:
        player.x = 32;
        player.y = 15;
        Villagenum = 4;
        break;
      case 5:
        player.x = 2;
        player.y = 8;
        Villagenum = 5;
        break;
      case 6:
        player.x = 2;
        player.y = 2;
        Villagenum = 6;
        break;
      }
    }
    if ((!emerging) || (tempLevel == NULL))
      load_village(Villagenum, TRUE);
    else if (tempLevel->environment != E_VILLAGE)
      load_village(Villagenum, TRUE);
#ifndef SAVE_LEVELS
    else
      level = tempLevel;
#else
    else
    {
      msdos_changelevel(Level, new_environment, 0);
      level = tempLevel;
    }
#endif
    if (emerging)
    {
      print1("You emerge onto the street.");
      emerging = FALSE;
    }
    else
      print1("You enter a small rural village.");
    ScreenOffset = 0;
    show_screen();
    break;
  case E_CAVES:
    WIDTH = 64;
    LENGTH = 64;
    print1("You enter a dark cleft in a hillside;");
    print2("You note signs of recent passage in the dirt nearby.");
    if (gamestatusp(MOUNTED))
    {
      morewait();
      print1("Seeing as you might not be coming back, you feel compelled");
      print2("to let your horse go, rather than keep him hobbled outside.");
      resetgamestatus(MOUNTED);
      calc_melee();
    }
    MaxDungeonLevels = CAVELEVELS;
    if (Current_Dungeon != E_CAVES)
    {
#ifdef SAVE_LEVELS
      msdos_changelevel(Level, 0, -1);
#endif
      free_dungeon();
      Dungeon = NULL;
      level = NULL;
      Current_Dungeon = E_CAVES;
    }
    change_level(0, 1, FALSE);
    break;
  case E_VOLCANO:
    WIDTH = 64;
    LENGTH = 64;
    print1("You pass down through the glowing crater.");
    if (gamestatusp(MOUNTED))
    {
      morewait();
      print1("Seeing as you might not be coming back, you feel compelled");
      print2("to let your horse go, rather than keep him hobbled outside.");
      resetgamestatus(MOUNTED);
      calc_melee();
    }
    MaxDungeonLevels = VOLCANOLEVELS;
    if (Current_Dungeon != E_VOLCANO)
    {
#ifdef SAVE_LEVELS
      msdos_changelevel(Level, 0, -1);
#endif
      free_dungeon();
      Dungeon = NULL;
      level = NULL;
      Current_Dungeon = E_VOLCANO;
    }
    change_level(0, 1, FALSE);
    break;
  case E_ASTRAL:
    WIDTH = 64;
    LENGTH = 64;
    print1("You are in a weird flickery maze.");
    if (gamestatusp(MOUNTED))
    {
      print2("Your horse doesn't seem to have made it....");
      resetgamestatus(MOUNTED);
      calc_melee();
    }
    MaxDungeonLevels = ASTRALLEVELS;
    if (Current_Dungeon != E_ASTRAL)
    {
#ifdef SAVE_LEVELS
      msdos_changelevel(Level, 0, -1);
#endif
      free_dungeon();
      Dungeon = NULL;
      level = NULL;
      Current_Dungeon = E_ASTRAL;
    }
    change_level(0, 1, FALSE);
    break;
  case E_CASTLE:
    WIDTH = 64;
    LENGTH = 64;
    print1("You cross the drawbridge. Strange forms move beneath the water.");
    if (gamestatusp(MOUNTED))
    {
      morewait();
      print1("Seeing as you might not be coming back, you feel compelled");
      print2("to let your horse go, rather than keep him hobbled outside.");
      resetgamestatus(MOUNTED);
    }
    MaxDungeonLevels = CASTLELEVELS;
    if (Current_Dungeon != E_CASTLE)
    {
#ifdef SAVE_LEVELS
      msdos_changelevel(Level, 0, -1);
#endif
      free_dungeon();
      Dungeon = NULL;
      level = NULL;
      Current_Dungeon = E_CASTLE;
    }
    change_level(0, 1, FALSE);
    break;
  case E_SEWERS:
    WIDTH = 64;
    LENGTH = 64;
    print1("You pry open a manhole and descend into the sewers below.");
    if (gamestatusp(MOUNTED))
    {
      print2("You horse waits patiently outside the sewer entrance....");
      dismount_steed();
    }
    MaxDungeonLevels = SEWERLEVELS;
    if (Current_Dungeon != E_SEWERS)
    {
#ifdef SAVE_LEVELS
      msdos_changelevel(Level, 0, -1);
#endif
      free_dungeon();
      Dungeon = NULL;
      level = NULL;
      Current_Dungeon = E_SEWERS;
    }
    change_level(0, 1, FALSE);
    break;
  case E_COUNTRYSIDE:
    WIDTH = 64;
    LENGTH = 64;
    print1("You return to the fresh air of the open countryside.");
    if (Last_Environment == E_CITY)
    {
      player.x = 27;
      player.y = 19;
    }
    else
    {
      player.x = LastCountryLocX;
      player.y = LastCountryLocY;
    }
    for (i = 0; i < 9; i++)
      c_set(player.x + Dirs[0][i], player.y + Dirs[1][i], SEEN);
    ScreenOffset = player.y - (ScreenLength / 2);
    show_screen();
    break;
  case E_TACTICAL_MAP:
    WIDTH = 64;
    LENGTH = 16;
    print1("You are now on the tactical screen; exit off any side to leave");
    make_country_screen(Country[player.x][player.y].current_terrain_type);
    make_country_monsters(Country[player.x][player.y].current_terrain_type);
    player.x = WIDTH / 2;
    player.y = LENGTH / 2;
    while (level->site[player.x][player.y].locchar == WATER)
    {
      if (player.y < LENGTH / 2 + 5)
        player.y++;
      else if (player.x > WIDTH / 2 - 10)
      {
        player.x--;
        player.y = LENGTH / 2 - 5;
      }
      else
      {
        level->site[player.x][player.y].locchar =
            level->site[player.x][player.y].showchar = FLOOR;
        level->site[player.x][player.y].p_locf = L_NO_OP;
      }
    }
    ScreenOffset = 0;
    show_screen();
    break;
  case E_NEVER_NEVER_LAND:
  default:
    print1("There must be some mistake. You don't look like Peter Pan.");
    print2("(But here you are in Never-Never Land)");
    ScreenOffset = player.y - (ScreenLength / 2);
    show_screen();
    break;
  }
  setlastxy(player.x, player.y);
  if (Current_Environment != E_COUNTRYSIDE)
    showroom(level->site[player.x][player.y].roomnumber);
  else
    terrain_check(FALSE);
}
