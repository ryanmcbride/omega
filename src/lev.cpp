/* omega copyright (c) 1987,1988,1989 by Laurence Raphael Brothers */
/* lev.c */

#include "glob.h"

/* Functions dealing with dungeon and country levels aside from actual
level structure generation */

/* monsters for tactical encounters */
void make_country_monsters(Symbol terrain)
{
  Monsterlist *tml = NULL;
  Monsterlist *ml = NULL;
  int plains[10] =
      {BUNNY, BUNNY, HORNET, QUAIL, HAWK, DEER, WOLF, LION, BRIGAND, RANDOM};
  /*    {BUNNY,BUNNY,BLACKSNAKE,HAWK,IMPALA,WOLF,LION,BRIGAND,RANDOM};*/
  /* DG changed (WDT: I'd like to see a blacksnake). */
  int forest[10] =
      {BUNNY, QUAIL, HAWK, BADGER, DEER, DEER, WOLF, BEAR, BRIGAND, RANDOM};
  int jungle[10] =
      {ANTEATER, PARROT, MAMBA, ANT, ANT, HYENA, HYENA, ELEPHANT, LION, RANDOM};
  int river[10] =
      {QUAIL, TROUT, TROUT, MANOWAR, BASS, BASS, CROC, CROC, BRIGAND, RANDOM};
  int swamp[10] =
      {BASS, BASS, CROC, CROC, BOGTHING, ANT, ANT, RANDOM, RANDOM, RANDOM};
  int desert[10] =
      {HAWK, HAWK, CAMEL, CAMEL, HYENA, HYENA, LION, LION, RANDOM, RANDOM};
  int tundra[10] =
      {WOLF, WOLF, BEAR, BEAR, DEER, DEER, RANDOM, RANDOM, RANDOM, RANDOM};
  int mountain[10] =
      {BUNNY, SHEEP, WOLF, WOLF, HAWK, HAWK, HAWK, RANDOM, RANDOM, RANDOM};
  int *monsters, i, nummonsters;

  nummonsters = (random_range(5) + 1) * (random_range(3) + 1);

  if (terrain == PLAINS)
    monsters = plains;
  else if (terrain == FOREST)
    monsters = forest;
  else if (terrain == JUNGLE)
    monsters = jungle;
  else if (terrain == RIVER)
    monsters = river;
  else if (terrain == SWAMP)
    monsters = swamp;
  else if (terrain == MOUNTAINS ||
           terrain == PASS ||
           terrain == VOLCANO)
    monsters = mountain;
  else if (terrain == DESERT)
    monsters = desert;
  else if (terrain == TUNDRA)
    monsters = tundra;
  else
    monsters = NULL;

  for (i = 0; i < nummonsters; i++)
  {
    tml = Monsterlist::create();
    tml->m = Monster::create();
    if (monsters == NULL)
      tml->m =
          m_create(random_range(WIDTH), random_range(LENGTH), TRUE, difficulty());
    else
    {
      tml->m = make_creature(*(monsters + random_range(10)));
      tml->m->x = random_range(WIDTH);
      tml->m->y = random_range(LENGTH);
    }
    level->site[tml->m->x][tml->m->y].creature = tml->m;
    tml->m->sense = WIDTH;
    if (m_statusp(tml->m, ONLYSWIM))
    {
      level->site[tml->m->x][tml->m->y].locchar = WATER;
      level->site[tml->m->x][tml->m->y].p_locf = L_WATER;
      lset(tml->m->x, tml->m->y, CHANGED);
    }

    tml->next = ml;
    ml = tml;
  }
  level->mlist = ml;
}

/* monstertype is more or less Current_Dungeon */
/* The caves and sewers get harder as you penetrate them; the castle
is completely random, but also gets harder as it is explored;
the astral and the volcano just stay hard... */
void populate_level(int monstertype)
{
  Monsterlist *head = NULL;
  Monsterlist *tml = NULL;
  int i, j, k, monsterid, nummonsters = (random_range(difficulty() / 3) + 1) * 3 + 8;

  if (monstertype == E_CASTLE)
    nummonsters += 10;
  else if (monstertype == E_ASTRAL)
    nummonsters += 10;
  else if (monstertype == E_VOLCANO)
    nummonsters += 20;

  head = tml = Monsterlist::create();

  for (k = 0; k < nummonsters; k++)
  {

    findspace(&i, &j, -1);

    switch (monstertype)
    {
    case E_CAVES:
      if (level->depth * 10 + random_range(100) > 150)
        monsterid = GOBLIN_SHAMAN;
      else if (level->depth * 10 + random_range(100) > 100)
        monsterid = GOBLIN_CHIEF; /* Goblin Chieftain */
      else if (random_range(100) > 50)
        monsterid = GOBLIN;
      else
        monsterid = RANDOM; /* IE, random monster */
      break;
    case E_SEWERS:
      if (!random_range(3))
        monsterid = -1;
      else
        switch (random_range(level->depth + 3))
        {
        case 0:
          monsterid = SEWER_RAT;
          break;
        case 1:
          monsterid = AGGRAVATOR;
          break; /* aggravator fungus */
        case 2:
          monsterid = BLIPPER;
          break; /* blipper rat */
        case 3:
          monsterid = NIGHT_GAUNT;
          break;
        case 4:
          monsterid = NASTY;
          break; /* transparent nasty */
        case 5:
          monsterid = MURK;
          break; /* murk fungus */
        case 6:
          monsterid = CATOBLEPAS;
          break;
        case 7:
          monsterid = ACID_CLOUD;
          break;
        case 8:
          monsterid = DENEBIAN;
          break; /* denebian slime devil */
        case 9:
          monsterid = CROC;
          break; /* giant crocodile */
        case 10:
          monsterid = TESLA;
          break; /* tesla monster */
        case 11:
          monsterid = SHADOW;
          break; /* shadow spirit */
        case 12:
          monsterid = BOGTHING;
          break; /* bogthing */
        case 13:
          monsterid = WATER_ELEM;
          break; /* water elemental */
        case 14:
          monsterid = TRITON;
          break;
        case 15:
          monsterid = ROUS;
          break;
        default:
          monsterid = RANDOM;
          break; /* whatever seems good */
        }
      break;
    case E_ASTRAL:
      if (random_range(2)) /* random astral creatures */
        switch (random_range(12))
        {
        case 0:
          monsterid = THOUGHTFORM;
          break;
        case 1:
          monsterid = FUZZY;
          break; /* astral fuzzy */
        case 2:
          monsterid = BAN_SIDHE;
          break;
        case 3:
          monsterid = GRUE;
          break; /* astral grue */
        case 4:
          monsterid = SHADOW;
          break; /* shadow spirit */
        case 5:
          monsterid = ASTRAL_VAMP;
          break; /* astral vampire */
        case 6:
          monsterid = MANABURST;
          break;
        case 7:
          monsterid = RAKSHASA;
          break;
        case 8:
          monsterid = ILL_FIEND;
          break; /* illusory fiend */
        case 9:
          monsterid = MIRRORMAST;
          break; /* mirror master */
        case 10:
          monsterid = ELDER_GRUE;
          break; /* elder etheric grue */
        case 11:
          monsterid = SHADOW_SLAY;
          break; /* shadow slayer */
        }
      else if (random_range(2) && (level->depth == 1)) /* plane of earth */
        monsterid = EARTH_ELEM;                        /* earth elemental */
      else if (random_range(2) && (level->depth == 2)) /* plane of air */
        monsterid = AIR_ELEM;                          /* air elemental */
      else if (random_range(2) && (level->depth == 3)) /* plane of water */
        monsterid = WATER_ELEM;                        /* water elemental */
      else if (random_range(2) && (level->depth == 4)) /* plane of fire */
        monsterid = FIRE_ELEM;                         /* fire elemental */
      else if (random_range(2) && (level->depth == 5)) /* deep astral */
        switch (random_range(12))
        {
        case 0:
          monsterid = NIGHT_GAUNT;
          break;
        case 1:
          monsterid = SERV_LAW;
          break; /* servant of law */
        case 2:
          monsterid = SERV_CHAOS;
          break; /* servant of chaos */
        case 3:
          monsterid = FROST_DEMON;
          break; /* lesser frost demon */
        case 4:
          monsterid = OUTER_DEMON;
          break; /* outer circle demon */
        case 5:
          monsterid = DEMON_SERP;
          break; /* demon serpent */
        case 6:
          monsterid = ANGEL;
          break;
        case 7:
          monsterid = INNER_DEMON;
          break; /* inner circle demon */
        case 8:
          monsterid = FDEMON_L;
          break; /* frost demon lord */
        case 9:
          monsterid = HIGH_ANGEL;
          break;
        case 10:
          monsterid = DEMON_PRINCE;
          break; /* prime circle demon */
        case 11:
          monsterid = ARCHANGEL;
          break;
        }
      else
        monsterid = RANDOM;
      break;
    case E_VOLCANO:
      if (random_range(2))
      {
        do
          monsterid = random_range(ML10 - ML4) + ML4;
        while (Monsters[monsterid].uniqueness != COMMON);
      }
      else
        switch (random_range(level->depth / 2 + 2))
        { /* evil & fire creatures */
        case 0:
          monsterid = HAUNT;
          break;
        case 1:
          monsterid = INCUBUS;
          break;
        case 2:
          monsterid = DRAGONETTE;
          break;
        case 3:
          monsterid = FROST_DEMON;
          break;
        case 4:
          monsterid = SPECTRE;
          break;
        case 5:
          monsterid = LAVA_WORM;
          break;
        case 6:
          monsterid = FIRE_ELEM;
          break;
        case 7:
          monsterid = LICHE;
          break;
        case 8:
          monsterid = RAKSHASA;
          break;
        case 9:
          monsterid = DEMON_SERP;
          break;
        case 10:
          monsterid = NAZGUL;
          break;
        case 11:
          monsterid = FLAME_DEV;
          break;
        case 12:
          monsterid = LOATHLY;
          break;
        case 13:
          monsterid = ZOMBIE;
          break;
        case 14:
          monsterid = INNER_DEMON;
          break;
        case 15:
          monsterid = BAD_FAIRY;
          break;
        case 16:
          monsterid = DRAGON;
          break;
        case 17:
          monsterid = FDEMON_L;
          break;
        case 18:
          monsterid = SHADOW_SLAY;
          break;
        case 19:
          monsterid = DEATHSTAR;
          break;
        case 20:
          monsterid = VAMP_LORD;
          break;
        case 21:
          monsterid = DEMON_PRINCE;
          break;
        default:
          monsterid = RANDOM;
          break;
        }
      break;
    case E_CASTLE:
      if (random_range(4) == 1)
      {
        if (difficulty() < 5)
          monsterid = ENCHANTOR;
        else if (difficulty() < 6)
          monsterid = NECROMANCER;
        else if (difficulty() < 8)
          monsterid = FIRE_ELEM;
        else
          monsterid = THAUMATURGIST;
      }
      else
        monsterid = RANDOM;
      break;

    default:
      monsterid = RANDOM;
      break;
    }

    assert(RANDOM == -1); /* WDT: the following test slightly assumes
                           * this. */
    if (monsterid > RANDOM)
      level->site[i][j].creature = make_creature(monsterid);
    else
      level->site[i][j].creature = m_create(i, j, TRUE, difficulty());

    level->site[i][j].creature->x = i;
    level->site[i][j].creature->y = j;

    if (m_statusp(level->site[i][j].creature, ONLYSWIM))
    {
      level->site[i][j].locchar = WATER;
      level->site[i][j].p_locf = L_WATER;
      lset(i, j, CHANGED);
    }

    tml->next = Monsterlist::create();
    tml->next->m = level->site[i][j].creature;
    tml = tml->next;
  }

  if (level->mlist == NULL)
  {
    tml->next = NULL;
    level->mlist = head->next;
  }
  else
  {
    tml->next = level->mlist;
    level->mlist = head->next;
  }
}

/* Add a wandering monster possibly */
void wandercheck()
{
  int x, y;
  Monsterlist *tml;
  if (random_range(MaxDungeonLevels) < difficulty())
  {
    findspace(&x, &y, -1);
    tml = Monsterlist::create();
    tml->next = level->mlist;
    tml->m = level->site[x][y].creature = m_create(x, y, WANDERING, difficulty());
    level->mlist = tml;
  }
}

/* call make_creature and place created monster on level->mlist and Level */
void make_site_monster(int i, int j, int mid)
{
  Monsterlist *ml = Monsterlist::create();
  Monster *m;
  if (mid > -1)
    level->site[i][j].creature = (m = make_creature(mid));
  else
    level->site[i][j].creature = (m = m_create(i, j, WANDERING, difficulty()));
  m->x = i;
  m->y = j;
  ml->m = m;
  ml->next = level->mlist;
  level->mlist = ml;
}

/* make and return an appropriate monster for the level and depth*/
/* called by populate_level, doesn't actually add to mlist for some reason*/
/* eventually to be more intelligent */
Monster *m_create(int x, int y, int kind, int level)
{
  Monster *newmonster;
  int monster_range;
  int mid;

  switch (level)
  {
  case 0:
    monster_range = ML1;
    break;
  case 1:
    monster_range = ML2;
    break;
  case 2:
    monster_range = ML3;
    break;
  case 3:
    monster_range = ML4;
    break;
  case 4:
    monster_range = ML5;
    break;
  case 5:
    monster_range = ML6;
    break;
  case 6:
    monster_range = ML7;
    break;
  case 7:
    monster_range = ML8;
    break;
  case 8:
    monster_range = ML9;
    break;
  case 9:
    monster_range = ML10;
    break;
  default:
    monster_range = NUMMONSTERS;
    break;
  }

  do
    mid = random_range(monster_range);
  while (Monsters[mid].uniqueness != COMMON);
  newmonster = make_creature(mid);

  /* no duplicates of unique monsters */
  if (kind == WANDERING)
    m_status_set(newmonster, WANDERING);
  newmonster->x = x;
  newmonster->y = y;
  return (newmonster);
}

/* make creature # mid, totally random if mid == -1 */
/* make creature allocates space for the creature */
Monster *make_creature(int mid)
{
  Monster *newmonster = Monster::create();
  Object *ob;
  int i, treasures;

  if (mid == -1)
    mid = random_range(ML9);
  *newmonster = Monsters[mid];
  if ((mid == ANGEL) || (mid == HIGH_ANGEL) || (mid == ARCHANGEL))
  {
    /* aux1 field of an angel is its deity */
    if (Current_Environment == E_TEMPLE)
      newmonster->aux1 = Country[LastCountryLocX][LastCountryLocY].aux;
    else
      newmonster->aux1 = random_range(6) + 1;
    strcpy(Str3, Monsters[mid].monstring);
    switch (newmonster->aux1)
    {
    case ODIN:
      strcat(Str3, " of Odin");
      break;
    case SET:
      strcat(Str3, " of Set");
      break;
    case HECATE:
      strcat(Str3, " of Hecate");
      break;
    case ATHENA:
      strcat(Str3, " of Athena");
      break;
    case DESTINY:
      strcat(Str3, " of Destiny");
      break;
    case DRUID:
      strcat(Str3, " of the Balance");
      break;
    }
    newmonster->monstring = salloc(Str3);
  }
  else if (mid == ZERO_NPC || mid == WEREHUMAN)
  {
    /* generic 0th level human, or a were-human */
    newmonster->monstring = mantype();
    strcpy(Str1, "dead ");
    strcat(Str1, newmonster->monstring);
    newmonster->corpsestr = salloc(Str1);
  }
  else if ((newmonster->monchar & 0xff) == '!')
  {
    /* the nymph/satyr and incubus/succubus */
    if (player.preference == 'f' ||
        (player.preference != 'm' && random_range(2)))
    {
      newmonster->monchar = 'n' | CLR(RED);
      newmonster->monstring = "nymph";
      newmonster->corpsestr = "dead nymph";
    }
    else
    {
      newmonster->monchar = 's' | CLR(RED);
      newmonster->monstring = "satyr";
      newmonster->corpsestr = "dead satyr";
    }
    if (newmonster->id == INCUBUS)
    {
      if ((newmonster->monchar & 0xff) == 'n')
        newmonster->corpsestr = "dead succubus";
      else
        newmonster->corpsestr = "dead incubus";
    }
  }
  if (mid == NPC)
    make_log_npc(newmonster);
  else if (mid == HISCORE_NPC)
    make_hiscore_npc(newmonster, random_range(15));
  else
  {
    if (newmonster->sleep < random_range(100))
      m_status_set(newmonster, AWAKE);
    if (newmonster->startthing > -1 &&
        Objects[newmonster->startthing].uniqueness <= UNIQUE_MADE)
    {
      ob = Object::create();
      *ob = Objects[newmonster->startthing];
      m_pickup(newmonster, ob);
    }
    treasures = random_range(newmonster->treasure);
    for (i = 0; i < treasures; i++)
    {
      do
      {
        ob = Object::create_object(newmonster->level);
        if (ob->uniqueness != COMMON)
        {
          Objects[ob->id].uniqueness = UNIQUE_UNMADE;
          delete ob;
          ob = NULL;
        }
      } while (!ob);
      m_pickup(newmonster, ob);
    }
  }
  newmonster->click = (Tick + 1) % 50;
  return (newmonster);
}

/* drop treasures randomly onto level */
void stock_level()
{
  int i, j, k, numtreasures = 2 * random_range(difficulty() / 4) + 4;

  /* put cash anywhere, including walls, put other treasures only on floor */
  for (k = 0; k < numtreasures + 10; k++)
  {
    do
    {
      i = random_range(WIDTH);
      j = random_range(LENGTH);
    } while (level->site[i][j].locchar != FLOOR);
    make_site_treasure(i, j, difficulty());
    i = random_range(WIDTH);
    j = random_range(LENGTH);
    level->site[i][j].things = Objectlist::create();
    level->site[i][j].things->thing = Object::makeCash(difficulty());
    level->site[i][j].things->next = NULL;
    /* caves have more random cash strewn around */
    if (Current_Dungeon == E_CAVES)
    {
      i = random_range(WIDTH);
      j = random_range(LENGTH);
      level->site[i][j].things = Objectlist::create();
      level->site[i][j].things->thing = Object::makeCash(difficulty());
      level->site[i][j].things->next = NULL;
      i = random_range(WIDTH);
      j = random_range(LENGTH);
      level->site[i][j].things = Objectlist::create();
      level->site[i][j].things->thing = Object::makeCash(difficulty());
      level->site[i][j].things->next = NULL;
    }
  }
}

/* make a new object (of at most level itemlevel) at site i,j on level*/
void make_site_treasure(int i, int j, int itemlevel)
{
  Objectlist *tmp = Objectlist::create();
  tmp->thing = Object::create_object(itemlevel);
  tmp->next = level->site[i][j].things;
  level->site[i][j].things = tmp;
}

/* make a specific new object at site i,j on level*/
void make_specific_treasure(int i, int j, int itemid)
{
  Objectlist *tmp;
  if (Objects[itemid].uniqueness == UNIQUE_TAKEN)
    return;
  tmp = Objectlist::create();
  tmp->thing = Object::create();
  *(tmp->thing) = Objects[itemid];
  tmp->next = level->site[i][j].things;
  level->site[i][j].things = tmp;
}

#ifndef MSDOS_SUPPORTED_ANTIQUE
/* returns a "level of difficulty" based on current environment
   and depth in dungeon. Is somewhat arbitrary. value between 1 and 10.
   May not actually represent real difficulty, but instead level
   of items, monsters encountered.    */
int difficulty()
{
  int depth = 1;
  if (level != NULL)
    depth = level->depth;
  switch (Current_Environment)
  {
  case E_COUNTRYSIDE:
    return (7);
  case E_CITY:
    return (3);
  case E_VILLAGE:
    return (1);
  case E_TACTICAL_MAP:
    return (7);
  case E_SEWERS:
    return (depth / 6) + 3;
  case E_CASTLE:
    return (depth / 4) + 4;
  case E_CAVES:
    return (depth / 3) + 1;
  case E_VOLCANO:
    return (depth / 4) + 5;
  case E_ASTRAL:
    return (8);
  case E_ARENA:
    return (5);
  case E_HOVEL:
    return (3);
  case E_MANSION:
    return (7);
  case E_HOUSE:
    return (5);
  case E_DLAIR:
    return (9);
  case E_ABYSS:
    return (10);
  case E_STARPEAK:
    return (9);
  case E_CIRCLE:
    return (8);
  case E_MAGIC_ISLE:
    return (8);
  case E_TEMPLE:
    return (8);
  default:
    return (3);
  }
}
#endif
