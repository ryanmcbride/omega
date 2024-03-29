/* omega copyright (C) by Laurence Raphael Brothers, 1987,1988,1989 */
/* aux1.c */
/* auxiliary functions for those in com.c, also see aux2.c and aux3.c */

#include "glob.h"
#include <map>
#include <string>

/* check to see if too much tunneling has been done in this level */
void tunnelcheck()
{
  if ((level->depth == 0 && Current_Environment != E_DLAIR) ||
      Current_Environment == E_ASTRAL)
    return;
  level->tunnelled++;
  if ((level->tunnelled) > LENGTH / 4)
    mprint("Dust and stone fragments fall on you from overhead.");
  if ((level->tunnelled) > LENGTH / 2)
    mprint("You hear groaning and creaking noises.");
  if ((level->tunnelled) > 3 * LENGTH / 4)
    mprint("The floor trembles and you hear a loud grinding screech.");
  if ((level->tunnelled) > LENGTH)
  {
    mprint("With a scream of tortured stone, the entire dungeon caves in!!!");
    gain_experience(5000);
    if (player.status[SHADOWFORM])
    {
      change_environment(E_COUNTRYSIDE);
      static std::map<unsigned int, unsigned int> terrainMap = {
          {CASTLE, MOUNTAINS},
          {STARPEAK, MOUNTAINS},
          {CAVES, MOUNTAINS},
          {VOLCANO, MOUNTAINS},
          {DRAGONLAIR, DESERT},
          {MAGIC_ISLE, CHAOS_SEA},
      };
      if (terrainMap.count(Country[player.x][player.y].base_terrain_type) > 0)
      {
        Country[player.x][player.y].current_terrain_type =
            terrainMap[Country[player.x][player.y].base_terrain_type];
      }
      Country[player.x][player.y].base_terrain_type =
          Country[player.x][player.y].current_terrain_type;
      c_set(player.x, player.y, CHANGED);
      print1("In your shadowy state, you float back up to the surface.");
      return;
    }
    mprint("You are flattened into an unpleasant jellylike substance.");
    p_death("dungeon cave-in");
  }
}

/* displays a room's name */
void showroom(int i)
{
  std::string str1;
  std::string str2;
  switch (Current_Environment)
  {
  case E_MANSION:
    str2 = "A luxurious mansion: ";
    break;
  case E_HOUSE:
    str2 = "A house: ";
    break;
  case E_HOVEL:
    str2 = "A hovel: ";
    break;
  case E_CITY:
    str2 = "The City of Rampart";
    break;
  case E_VILLAGE:
    switch (Villagenum)
    {
    case 1:
      str2 = "The Village of Star View";
      break;
    case 2:
      str2 = "The Village of Woodmere";
      break;
    case 3:
      str2 = "The Village of Stormwatch";
      break;
    case 4:
      str2 = "The Village of Thaumaris";
      break;
    case 5:
      str2 = "The Village of Skorch";
      break;
    case 6:
      str2 = "The Village of Whorfen";
      break;
    }
    break;
  case E_CAVES:
    str2 = "The Goblin Caves: ";
    break;
  case E_CASTLE:
    str2 = "The Archmage's Castle: ";
    break;
  case E_ASTRAL:
    str2 = "The Astral Plane: ";
    break;
  case E_VOLCANO:
    str2 = "The Volcano: ";
    break;
  case E_SEWERS:
    str2 = "The Sewers: ";
    break;
  case E_TACTICAL_MAP:
    str2 = "The Tactical Map ";
    break;
  default:
    str2 = "";
    break;
  }
  if (Current_Environment == Current_Dungeon)
  {
    str1 = "Level " + std::to_string((int)level->depth);
    str1 += std::string(" (") + roomname(i) + ")";
  }
  else if (str2.length() == 0 || Current_Environment == E_MANSION ||
           Current_Environment == E_HOUSE || Current_Environment == E_HOVEL)
    str1 = roomname(i);
  str2 += str1;
  locprint(str2);
}

int player_on_sanctuary()
{
  if ((player.x == player.sx) &&
      (player.y == player.sy))
    return (TRUE);
  else
  {
    if (player.patron)
    {
      if ((level->site[player.x][player.y].locchar == ALTAR) &&
          (level->site[player.x][player.y].aux == player.patron))
        return (TRUE);
      else
        return (FALSE);
    }
    else
      return (FALSE);
  }
}

/* check a move attempt, maybe attack something, return TRUE if ok to move. */
/* x y is the proposed place to move to */
int p_moveable(int x, int y)
{
  setgamestatus(SKIP_MONSTERS);
  if (!inbounds(x, y))
    return (FALSE);
  else if (player.status[SHADOWFORM])
  {
    switch (level->site[x][y].p_locf)
    {
    case L_CHAOS:
    case L_ABYSS:
    case L_VOID:
      return confirmation();
    default:
      resetgamestatus(SKIP_MONSTERS);
      return (TRUE);
    }
  }
  else if (loc_statusp(x, y, SECRET))
  {
    if (!gamestatusp(FAST_MOVE))
      print3("Ouch!");
    return (FALSE);
  }
  else if (level->site[x][y].creature != NULL)
  {
    if (!gamestatusp(FAST_MOVE))
    {
      fight_monster(level->site[x][y].creature);
      resetgamestatus(SKIP_MONSTERS);
      return (FALSE);
    }
    else
      return (FALSE);
  }
  else if ((level->site[x][y].locchar == WALL) ||
           (level->site[x][y].locchar == STATUE) ||
           (level->site[x][y].locchar == PORTCULLIS) ||
           (level->site[x][y].locchar == CLOSED_DOOR) ||
           (gamestatusp(FAST_MOVE) &&
            ((level->site[x][y].locchar == HEDGE) ||
             (level->site[x][y].locchar == LAVA) ||
             (level->site[x][y].locchar == ABYSS) ||
             (level->site[x][y].locchar == VOID_CHAR) ||
             (level->site[x][y].locchar == FIRE) ||
             (level->site[x][y].locchar == WHIRLWIND) ||
             (level->site[x][y].locchar == WATER) ||
             (level->site[x][y].locchar == LIFT) ||
             (level->site[x][y].locchar == TRAP))))
  {
    if (!gamestatusp(FAST_MOVE))
      print3("Ouch!");
    return (FALSE);
  }
  else if (optionp(CONFIRM))
  {
    if ((level->site[x][y].locchar == HEDGE) ||
        (level->site[x][y].locchar == LAVA) ||
        (level->site[x][y].locchar == FIRE) ||
        (level->site[x][y].locchar == WHIRLWIND) ||
        (level->site[x][y].locchar == ABYSS) ||
        (level->site[x][y].locchar == VOID_CHAR) ||
        (level->site[x][y].locchar == WATER) ||
        (level->site[x][y].locchar == RUBBLE) ||
        (level->site[x][y].locchar == LIFT) ||
        (level->site[x][y].locchar == TRAP))
    {
      /* horses WILL go into water... */
      if (gamestatusp(MOUNTED))
      {
        if (level->site[x][y].locchar != WATER ||
            level->site[x][y].p_locf != L_WATER)
        {
          print1("You can't convince your steed to continue.");
          setgamestatus(SKIP_MONSTERS);
          return (FALSE);
        }
        else
          return (TRUE);
      }
      else if (confirmation())
        resetgamestatus(SKIP_MONSTERS);
      else
        setgamestatus(SKIP_MONSTERS);
      return (!gamestatusp(SKIP_MONSTERS));
    }
    else
    {
      resetgamestatus(SKIP_MONSTERS);
      return (TRUE);
    }
  }
  else
  {
    resetgamestatus(SKIP_MONSTERS);
    return (TRUE);
  }
}

/* check a move attempt in the countryside */
int p_country_moveable(int x, int y)
{
  if (!inbounds(x, y))
    return (FALSE);
  else if (optionp(CONFIRM))
  {
    if ((Country[x][y].current_terrain_type == CHAOS_SEA) ||
        (Country[x][y].current_terrain_type == MOUNTAINS))
      return (confirmation());
    else
      return (TRUE);
  }
  else
    return (TRUE);
}

/* search once particular spot */
void searchat(int x, int y)
{
  int i;
  if (inbounds(x, y) && (random_range(3) || player.status[ALERT]))
  {
    if (loc_statusp(x, y, SECRET))
    {
      lreset(x, y, SECRET);
      lset(x, y, CHANGED);
      if ((level->site[x][y].locchar == OPEN_DOOR) ||
          (level->site[x][y].locchar == CLOSED_DOOR))
      {
        mprint("You find a secret door!");
        for (i = 0; i <= 8; i++)
        { /* FIXED! 12/25/98 */
          lset(x + Dirs[0][i], y + Dirs[1][i], STOPS);
          lset(x + Dirs[0][i], y + Dirs[1][i], CHANGED);
        }
      }
      else
        mprint("You find a secret passage!");
      drawvision(player.x, player.y);
    }
    if ((level->site[x][y].p_locf >= TRAP_BASE) &&
        (level->site[x][y].locchar != TRAP) &&
        (level->site[x][y].p_locf <= TRAP_BASE + NUMTRAPS))
    {
      level->site[x][y].locchar = TRAP;
      lset(x, y, CHANGED);
      mprint("You find a trap!");
      drawvision(player.x, player.y);
      resetgamestatus(FAST_MOVE);
    }
  }
}

/* This is to be called whenever anything might change player performance in
   melee, such as changing weapon, statistics, etc. */
void calc_melee()
{
  calc_weight();

  player.maxweight = (player.str * player.agi * 10);
  player.absorption = player.status[PROTECTION];
  player.defense = 2 * statmod(player.agi) + (player.level / 2);
  player.hit = player.level + statmod(player.dex) + 1;
  player.dmg = statmod(player.str) + 3;
  player.speed = 5 - min(4, (statmod(player.agi) / 2));
  if (player.status[HASTED] > 0)
    player.speed = player.speed / 2;
  if (player.status[SLOWED] > 0)
    player.speed = player.speed * 2;
  if (player.itemweight > 0)
    switch (player.maxweight / player.itemweight)
    {
    case 0:
      player.speed += 6;
      break;
    case 1:
      player.speed += 3;
      break;
    case 2:
      player.speed += 2;
      break;
    case 3:
      player.speed += 1;
      break;
    }

  if (player.status[ACCURATE])
    player.hit += 20;
  if (player.status[HERO])
    player.hit += player.dex;
  if (player.status[HERO])
    player.dmg += player.str;
  if (player.status[HERO])
    player.defense += player.agi;
  if (player.status[HERO])
    player.speed = player.speed / 2;

  player.speed = max(1, min(25, player.speed));

  if (gamestatusp(MOUNTED))
  {
    player.speed = 3;
    player.hit += 10;
    player.dmg += 10;
  }

  /* weapon */
  /* have to check for used since it could be a 2h weapon just carried
     in one hand */
  if (player.possessions[O_WEAPON_HAND] != NULL)
    if (player.possessions[O_WEAPON_HAND]->used &&
        ((player.possessions[O_WEAPON_HAND]->objchar == WEAPON) ||
         (player.possessions[O_WEAPON_HAND]->objchar == MISSILEWEAPON)))
    {
      player.hit +=
          player.possessions[O_WEAPON_HAND]->hit +
          player.possessions[O_WEAPON_HAND]->plus;
      player.dmg +=
          player.possessions[O_WEAPON_HAND]->dmg +
          player.possessions[O_WEAPON_HAND]->plus;
    }

  /* shield or defensive weapon */
  if (player.possessions[O_SHIELD] != NULL)
  {
    player.defense +=
        player.possessions[O_SHIELD]->aux +
        player.possessions[O_SHIELD]->plus;
  }

  /* armor */
  if (player.possessions[O_ARMOR] != NULL)
  {
    player.absorption += player.possessions[O_ARMOR]->dmg;
    player.defense +=
        player.possessions[O_ARMOR]->plus -
        player.possessions[O_ARMOR]->aux;
  }

  if (strlen(player.meleestr) > 2 * maneuvers())
    default_maneuvers();
  comwinprint();
  showflags();
  dataprint();
}

/* player attacks monster m */
void fight_monster(Monster *m)
{
  int hitmod = 0;
  int reallyfight = TRUE;

  if (player.status[AFRAID])
  {
    print3("You are much too afraid to fight!");
    reallyfight = FALSE;
  }
  else if (player_on_sanctuary())
  {
    print3("You restrain yourself from desecrating this holy place.");
    reallyfight = FALSE;
  }
  else if (player.status[SHADOWFORM])
  {
    print3("Your attack has no effect in your shadowy state.");
    reallyfight = FALSE;
  }
  else if ((player.status[BERSERK] < 1) && (!m_statusp(m, HOSTILE)))
  {
    if (optionp(BELLICOSE))
      reallyfight = TRUE;
    else
      reallyfight = confirmation();
  }
  else
    reallyfight = TRUE;

  if (reallyfight)
  {

    if (Lunarity == 1)
      hitmod += player.level;
    else if (Lunarity == -1)
      hitmod -= (player.level / 2);

    if (!m->attacked)
      player.alignment -= 2; /* chaotic action */
    m_status_set(m, AWAKE);
    m_status_set(m, HOSTILE);
    m->attacked = TRUE;
    player.hit += hitmod;
    tacplayer(m);
    player.hit -= hitmod;
  }
}

/* Attempt to break an object o */
int damage_item(Object *o)
{
  int i;
  /* special case -- break star gem */
  if (o->id == ARTIFACTID + 21)
  {
    print1("The Star Gem shatters into a million glistening shards....");
    if (Current_Environment == E_STARPEAK)
    {
      if (!gamestatusp(KILLED_LAWBRINGER))
        print2("You hear an agonizing scream of anguish and despair.");
      morewait();
      print1("A raging torrent of energy escapes in an explosion of magic!");
      print2("The energy flows to the apex of Star Peak where there is");
      morewait();
      clearmsg();
      print1("an enormous explosion!");
      morewait();
      annihilate(1);
      print3("You seem to gain strength in the chaotic glare of magic!");
      player.str = max(player.str, player.maxstr + 5); /* FIXED! 12/25/98 */
      player.pow = max(player.pow, player.maxpow + 5); /* ditto */
      player.alignment -= 200;
      dispose_lost_objects(1, o);
    }
    else
    {
      morewait();
      print1("The shards coalesce back together again, and vanish");
      print2("with a muted giggle.");
      dispose_lost_objects(1, o);
      Objects[o->id].uniqueness = UNIQUE_UNMADE; /* FIXED! 12/30/98 */
      /* WDT HACK: the above is correct only if UNIQUE_UNMADE means that
       * the artifact hasn't been generated yet.  (Clearly, Omega is a
       * little buggy in that regard with respect to artifacts in general
       * -- it's almost trivial to force two identical artefacts to be
       * generated right now.) */
    }
    return 1;
  }
  else
  {
    if (o->fragility < random_range(30))
    {
      if (o->objchar == STICK)
      {
        std::string str = "Your " + (o->blessing >= 0 ? o->truename : o->cursestr) + " explodes!";
        print1(str);
        morewait();
        if (o->charge < 1)
          nprint1(" Fzzz... Out of Power... Oh well...");
        else
        {
          nprint1(" Ka-Blamm!!!");
          /* general case. Some sticks will eventually do special things */
          morewait();
          manastorm(player.x, player.y, o->charge * o->level * 10);
          dispose_lost_objects(1, o);
        }
        return 1;
      }
      else if ((o->blessing > 0) && (o->level > random_range(10)))
      {
        std::string str = std::string("Your ") + itemid(o) + " glows strongly.";
        print1(str);
        return 0;
      }
      else if ((o->blessing < -1) && (o->level > random_range(10)))
      {
        std::string str = std::string("You hear an evil giggle from your ") + itemid(o);
        print1(str);
        return 0;
      }
      else if (o->plus > 0)
      {
        std::string str = std::string("Your ") + itemid(o) + " glows and then fades.";
        print1(str);
        o->plus--;
        return 0;
      }
      else
      {
        if (o->blessing > 0)
          print1("You hear a faint despairing cry!");
        else if (o->blessing < 0)
          print1("You hear an agonized scream!");
        std::string str = std::string("Your ") + itemid(o) + " shatters in a thousand lost fragments!";
        print2(str);
        morewait();
        dispose_lost_objects(1, o);
        return 1;
      }
    }
    return 0;
  }
}

/* do dmg points of damage of type dtype, from source fromstring */
void p_damage(int dmg, int dtype, std::string fromstring)
{
  if (!p_immune(dtype))
  {
    if (gamestatusp(FAST_MOVE))
    {
      drawvision(player.x, player.y);
      resetgamestatus(FAST_MOVE);
    }
    if (dtype == NORMAL_DAMAGE)
      player.hp -= max(1, (dmg - player.absorption));
    else
      player.hp -= dmg;
    if (player.hp < 1)
      p_death(fromstring);
  }
  else
    mprint("You resist the effects!");
  dataprint();
}

/* game over, you lose! */
void p_death(std::string fromstring)
{
  player.hp = -1;
  print3("You died!");
  morewait();
  display_death(fromstring);
#ifdef SAVE_LEVELS
  kill_all_levels();
#endif
  endgraf();
  exit(0);
}

/* move the cursor around, like for firing a wand, sets x and y to target */
void setspot(int *x, int *y)
{
  char c = ' ';
  mprint("Targeting.... ? for help");
  omshowcursor(*x, *y);
  while ((c != '.') && (c != ESCAPE))
  {
    c = lgetc();
    switch (c)
    {
    case 'h':
    case '4':
      movecursor(x, y, -1, 0);
      break;
    case 'j':
    case '2':
      movecursor(x, y, 0, 1);
      break;
    case 'k':
    case '8':
      movecursor(x, y, 0, -1);
      break;
    case 'l':
    case '6':
      movecursor(x, y, 1, 0);
      break;
    case 'b':
    case '1':
      movecursor(x, y, -1, 1);
      break;
    case 'n':
    case '3':
      movecursor(x, y, 1, 1);
      break;
    case 'y':
    case '7':
      movecursor(x, y, -1, -1);
      break;
    case 'u':
    case '9':
      movecursor(x, y, 1, -1);
      break;
    case '?':
      clearmsg();
      mprint("Use vi keys or numeric keypad to move cursor to target.");
      mprint("Hit the '.' key when done, or ESCAPE to abort.");
      break;
    }
  }
  if (c == ESCAPE)
    *x = *y = ABORT;
  screencheck(player.y);
}

/* get a direction: return index into Dirs array corresponding to direction */
int getdir()
{
  while (1)
  {
    mprint("Select direction [hjklyubn, ESCAPE to quit]: ");
    switch (mgetc())
    {
    case '4':
    case 'h':
    case 'H':
      return (5);
    case '2':
    case 'j':
    case 'J':
      return (6);
    case '8':
    case 'k':
    case 'K':
      return (7);
    case '6':
    case 'l':
    case 'L':
      return (4);
    case '7':
    case 'y':
    case 'Y':
      return (3);
    case '9':
    case 'u':
    case 'U':
      return (1);
    case '1':
    case 'b':
    case 'B':
      return (2);
    case '3':
    case 'n':
    case 'N':
      return (0);
    case ESCAPE:
      return (ABORT);
    default:
      print3("That's not a direction! ");
    }
  }
}

/* functions describes monster m's state for examine function */
char *mstatus_string(Monster *m)
{
  if (m_statusp(m, M_INVISIBLE) && !player.status[TRUESIGHT])
    strcpy(Str2, "Some invisible creature");
  else if (m->uniqueness == COMMON)
  {
    if (m->hp < Monsters[m->id].hp / 3)
      strcpy(Str2, "a grievously injured ");
    else if (m->hp < Monsters[m->id].hp / 2)
      strcpy(Str2, "a severely injured ");
    else if (m->hp < Monsters[m->id].hp)
      strcpy(Str2, "an injured ");
    else
      strcpy(Str2, getarticle(m->monstring));
    if (m->level > Monsters[m->id].level)
    {
      strcat(Str2, " (level ");
      strcat(Str2, wordnum(m->level + 1 - Monsters[m->id].level));
      strcat(Str2, ") ");
    }
    strcat(Str2, m->monstring);
  }
  else
  {
    strcpy(Str2, m->monstring);
    if (m->hp < Monsters[m->id].hp / 3)
      strcat(Str2, " who is grievously injured ");
    else if (m->hp < Monsters[m->id].hp / 2)
      strcat(Str2, " who is severely injured ");
    else if (m->hp < Monsters[m->id].hp)
      strcat(Str2, " who is injured ");
  }
  return (Str2);
}

/* for the examine function */
void describe_player()
{
  if (player.hp < (player.maxhp / 5))
    print1("A grievously injured ");
  else if (player.hp < (player.maxhp / 2))
    print1("A seriously wounded ");
  else if (player.hp < player.maxhp)
    print1("A somewhat bruised ");
  else
    print1("A fit ");

  if (player.status[SHADOWFORM])
    nprint1("shadow");
  else
    nprint1(levelname(player.level));
  nprint1(" named ");
  nprint1(player.name);
  if (gamestatusp(MOUNTED))
    nprint1(" (riding a horse.)");
}

/* access to player experience... */
/* share out experience among guild memberships */
void gain_experience(int amount)
{
  int i, count = 0, share;
  player.xp += (long)amount;
  gain_level(); /* actually, check to see if should gain level */
  for (i = 0; i < NUMRANKS; i++)
    if (player.guildxp[i] > 0)
      count++;
  share = amount / (max(count, 1));
  for (i = 0; i < NUMRANKS; i++)
    if (player.guildxp[i] > 0)
      player.guildxp[i] += share;
}

/* try to hit a monster in an adjacent space. If there are none
   return FALSE. Note if you're berserk you get to attack ALL
   adjacent monsters! */
int goberserk()
{
  int wentberserk = FALSE, i;
  char meleestr[80];
  strcpy(meleestr, player.meleestr);
  strcpy(player.meleestr, "lLlClH");
  for (i = 0; i < 8; i++)
    if (level->site[player.x + Dirs[0][i]][player.y + Dirs[1][i]].creature != NULL)
    {
      wentberserk = TRUE;
      fight_monster(level->site[player.x + Dirs[0][i]][player.y + Dirs[1][i]].creature);
      morewait();
    }
  strcpy(player.meleestr, meleestr);
  return (wentberserk);
}

/* identifies a trap for examine() by its aux value */
char *trapid(int trapno)
{
  switch (trapno)
  {
  case L_TRAP_SIREN:
    return ("A siren trap");
  case L_TRAP_DART:
    return ("A dart trap");
  case L_TRAP_PIT:
    return ("A pit");
  case L_TRAP_SNARE:
    return ("A snare");
  case L_TRAP_BLADE:
    return ("A blade trap");
  case L_TRAP_FIRE:
    return ("A fire trap");
  case L_TRAP_TELEPORT:
    return ("A teleport trap");
  case L_TRAP_DISINTEGRATE:
    return ("A disintegration trap");
  case L_TRAP_DOOR:
    return ("A trap door");
  case L_TRAP_MANADRAIN:
    return ("A manadrain trap");
  case L_TRAP_ACID:
    return ("An acid shower trap");
  case L_TRAP_SLEEP_GAS:
    return ("A sleep gas trap");
  case L_TRAP_ABYSS:
    return ("A concealed entrance to the abyss");
  default:
    return ("A completely inoperative trap.");
  }
}

/* checks current food status of player, every hour, and when food is eaten */
void foodcheck()
{
  if (player.food > 48)
  {
    print3("You vomit up your huge meal.");
    player.food = 12;
  }
  else if (player.food == 30)
    print3("Time for a smackerel of something.");
  else if (player.food == 20)
    print3("You feel hungry.");
  else if (player.food == 12)
    print3("You are ravenously hungry.");
  else if (player.food == 3)
  {
    print3("You feel weak.");
    if (gamestatusp(FAST_MOVE))
    {
      drawvision(player.x, player.y);
      resetgamestatus(FAST_MOVE);
    }
  }
  else if (player.food < 0)
  {
    if (gamestatusp(FAST_MOVE))
    {
      drawvision(player.x, player.y);
      resetgamestatus(FAST_MOVE);
    }
    print3("You're starving!");
    p_damage(-5 * player.food, UNSTOPPABLE, "starvation");
  }
  showflags();
}

/* see whether room should be illuminated */
void roomcheck()
{
  static int oldroomno = -1;
#ifdef MSDOS_SUPPORTED_ANTIQUE
  static int oldlevel = -1;
#else
  static Level *oldlevel = NULL;
#endif
  int roomno = level->site[player.x][player.y].roomnumber;

  if ((roomno == RS_CAVERN) ||
      (roomno == RS_SEWER_DUCT) ||
      (roomno == RS_KITCHEN) ||
      (roomno == RS_BATHROOM) ||
      (roomno == RS_BEDROOM) ||
      (roomno == RS_DININGROOM) ||
      (roomno == RS_CLOSET) ||
      (roomno > ROOMBASE))
    if ((!loc_statusp(player.x, player.y, LIT)) &&
        (!player.status[BLINDED]) &&
        (player.status[ILLUMINATION] || (difficulty() < 6)))
    {
      showroom(level->site[player.x][player.y].roomnumber);
      spreadroomlight(player.x, player.y, roomno);
      levelrefresh();
    }
  if ((oldroomno != roomno) ||
#ifdef MSDOS_SUPPORTED_ANTIQUE
      (oldlevel != level->depth))
  {
#else
      (oldlevel != level))
  {
#endif
    showroom(roomno);
    oldroomno = roomno;
#ifdef MSDOS_SUPPORTED_ANTIQUE
    oldlevel = level->depth;
#else
    oldlevel = level;
#endif
  }
}

/* ask for mercy */
void surrender(Monster *m)
{
  int i;
  long bestitem, bestvalue;

  switch (random_range(4))
  {
  case 0:
    print1("You grovel at the monster's feet...");
    break;
  case 1:
    print1("You cry 'uncle'!");
    break;
  case 2:
    print1("You beg for mercy.");
    break;
  case 3:
    print1("You yield to the monster.");
    break;
  }
  if (m->id == GUARD)
  {
    if (m_statusp(m, HOSTILE))
      monster_talk(m);
    else
    {
      print2("The guard (bored): Have you broken a law? [yn] ");
      if (ynq2() == 'y')
      {
        print2("The guard grabs you, and drags you to court.");
        morewait();
        send_to_jail();
      }
      else
        print2("Then don't bother me. Scat!");
    }
  }
  else if ((m->talkf == M_NO_OP) ||
           (m->talkf == M_TALK_STUPID))
    print3("Your plea is ignored.");
  else
  {
    morewait();
    print1("Your surrender is accepted.");
    if (player.cash > 0)
      nprint1(" All your gold is taken....");
    player.cash = 0;
    bestvalue = 0;
    bestitem = ABORT;
    for (i = 1; i < MAXITEMS; i++)
      if (player.possessions[i] != NULL)
        if (bestvalue < true_item_value(player.possessions[i]))
        {
          bestitem = i;
          bestvalue = true_item_value(player.possessions[i]);
        }
    if (bestitem != ABORT)
    {
      print2("You also give away your best item... ");
      nprint2(itemid(player.possessions[bestitem]));
      nprint2(".");
      morewait();
      givemonster(m, player.possessions[bestitem]);
      morewait(); /* msgs come from givemonster */
      conform_unused_object(player.possessions[bestitem]);
      player.possessions[bestitem] = NULL;
    }
    print2("You feel less experienced... ");
    player.xp = max(0, player.xp - m->xpv);
    nprint2("The monster seems more experienced!");
    m->level = (min(10, m->level + 1));
    m->hp += m->level * 20;
    m->hit += m->level;
    m->dmg += m->level;
    m->ac += m->level;
    m->xpv += m->level * 10;
    morewait();
    clearmsg();
    if ((m->talkf == M_TALK_EVIL) && random_range(10))
    {
      print1("It continues to attack you, laughing evilly!");
      m_status_set(m, HOSTILE);
      m_status_reset(m, GREEDY);
    }
    else if (m->id == HORNET || m->id == GUARD)
      print1("It continues to attack you. ");
    else
    {
      print1("The monster leaves, chuckling to itself....");
      m_teleport(m);
    }
  }
  dataprint();
}

/* threaten a monster */
void threaten(Monster *m)
{
  char response;
  switch (random_range(4))
  {
  case 0:
    mprint("You demand that your opponent surrender!");
    break;
  case 1:
    mprint("You threaten to do bodily harm to it.");
    break;
  case 2:
    mprint("You attempt to bluster it into submission.");
    break;
  case 3:
    mprint("You try to cow it with your awesome presence.");
    break;
  }
  morewait(); /* FIXED! 12/25/98 */
  if (!m_statusp(m, HOSTILE))
  {
    print3("You only annoy it with your futile demand.");
    m_status_set(m, HOSTILE);
  }
  else if (((m->level * 2 > player.level) && (m->hp > player.dmg)) ||
           (m->uniqueness != COMMON))
    print1("It sneers contemptuously at you.");
  else if ((m->talkf != M_TALK_GREEDY) &&
           (m->talkf != M_TALK_HUNGRY) &&
           (m->talkf != M_TALK_EVIL) &&
           (m->talkf != M_TALK_MAN) &&
           (m->talkf != M_TALK_BEG) &&
           (m->talkf != M_TALK_THIEF) &&
           (m->talkf != M_TALK_MERCHANT) &&
           (m->talkf != M_TALK_IM))
    print1("Your demand is ignored");
  else
  {
    print1("It yields to your mercy.");
    player.alignment += 3;
    print2("Kill it, rob it, or free it? [krf] ");
    do
      response = (char)mcigetc();
    while ((response != 'k') && (response != 'r') && (response != 'f'));
    if (response == 'k')
    {
      m_death(m);
      print2("You treacherous rogue!");
      player.alignment -= 13;
    }
    else if (response == 'r')
    {
      player.alignment -= 2;
      print2("It drops its treasure and flees.");
      m_dropstuff(m);
      m->hp = -1;
      level->site[m->x][m->y].creature = NULL;
      putspot(m->x, m->y, getspot(m->x, m->y, FALSE));
    }
    else
    {
      player.alignment += 2;
      print2("'If you love something set it free ... '");
      if (random_range(100) == 13)
      {
        morewait();
        print2("'...If it doesn't come back, hunt it down and kill it.'");
      }
      print3("It departs with a renewed sense of its own mortality.");
      m->hp = -1;
      level->site[m->x][m->y].creature = NULL;
      putspot(m->x, m->y, getspot(m->x, m->y, FALSE));
    }
  }
}

/* name of the player's experience level */
char *levelname(int level)
{
  switch (level)
  {
  case 0:
    strcpy(Str3, "neophyte");
    break;
  case 1:
    strcpy(Str3, "beginner");
    break;
  case 2:
    strcpy(Str3, "tourist");
    break;
  case 3:
    strcpy(Str3, "traveller");
    break;
  case 4:
    strcpy(Str3, "wayfarer");
    break;
  case 5:
    strcpy(Str3, "peregrinator");
    break;
  case 6:
    strcpy(Str3, "wanderer");
    break;
  case 7:
    strcpy(Str3, "hunter");
    break;
  case 8:
    strcpy(Str3, "scout");
    break;
  case 9:
    strcpy(Str3, "trailblazer");
    break;
  case 10:
    strcpy(Str3, "discoverer");
    break;
  case 11:
    strcpy(Str3, "explorer");
    break;
  case 12:
    strcpy(Str3, "senior explorer");
    break;
  case 13:
    strcpy(Str3, "ranger");
    break;
  case 14:
    strcpy(Str3, "ranger captain");
    break;
  case 15:
    strcpy(Str3, "ranger knight");
    break;
  case 16:
    strcpy(Str3, "adventurer");
    break;
  case 17:
    strcpy(Str3, "experienced adventurer");
    break;
  case 18:
    strcpy(Str3, "skilled adventurer");
    break;
  case 19:
    strcpy(Str3, "master adventurer");
    break;
  case 20:
    strcpy(Str3, "hero");
    break;
  case 21:
    strcpy(Str3, "superhero");
    break;
  case 22:
    strcpy(Str3, "demigod");
    break;
  default:
    if (level < 100)
    {
      strcpy(Str3, "Order ");
      Str3[6] = ((level / 10) - 2) + '0';
      Str3[7] = 0;
      strcat(Str3, " Master of Omega");
    }
    else
      strcpy(Str3, "Ultimate Master of Omega");
    break;
  }
  return (Str3);
}
