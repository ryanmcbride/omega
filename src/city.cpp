/* omega copyright (C) by Laurence Raphael Brothers, 1987,1988,1989 */
/* city.c */
/* some functions to make the city level */

#include "glob.h"

/* loads the city level */
void load_city(int populate)
{
  int i, j;
  Monsterlist* ml;
  char site;

  FILE *fd;

  initrand(E_CITY, 0);

  strcpy(Str3, Omegalib);
  strcat(Str3, "city.dat");
  fd = checkfopen(Str3, "rb");
  site = cryptkey("city.dat");

  tempLevel = level;
  if (ok_to_free(tempLevel))
  {
#ifndef SAVE_LEVELS
    tempLevel->free();
#endif
    tempLevel = NULL;
  }
#ifndef SAVE_LEVELS
  level = Level::create();
#else
  msdos_changelevel(TempLevel, 0, -1);
  Level = &TheLevel;
#endif
  clear_level(level);
  level->depth = 0;
  level->environment = E_CITY;
  for (j = 0; j < LENGTH; j++)
  {
    for (i = 0; i < WIDTH; i++)
    {
      lset(i, j, SEEN);
      site = getc(fd) ^ site;
      switch (site)
      {
      case 'g':
        level->site[i][j].locchar = FLOOR;
        level->site[i][j].p_locf = L_GARDEN;
        break;
      case 'y':
        level->site[i][j].locchar = FLOOR;
        level->site[i][j].p_locf = L_CEMETARY;
        break;
      case 'x':
        assign_city_function(i, j);
        break;
      case 't':
        level->site[i][j].locchar = FLOOR;
        level->site[i][j].p_locf = L_TEMPLE;
        CitySiteList[L_TEMPLE - CITYSITEBASE][0] = TRUE;
        CitySiteList[L_TEMPLE - CITYSITEBASE][1] = i;
        CitySiteList[L_TEMPLE - CITYSITEBASE][2] = j;
        break;
      case 'T':
        level->site[i][j].locchar = FLOOR;
        level->site[i][j].p_locf = L_PORTCULLIS_TRAP;
        level->site[i][j].aux = NOCITYMOVE;
        break;
      case 'R':
        level->site[i][j].locchar = FLOOR;
        level->site[i][j].p_locf = L_RAISE_PORTCULLIS;
        level->site[i][j].aux = NOCITYMOVE;
        break;
      case '7':
        level->site[i][j].locchar = FLOOR;
        level->site[i][j].p_locf = L_PORTCULLIS;
        level->site[i][j].aux = NOCITYMOVE;
        break;
      case 'C':
        level->site[i][j].locchar = OPEN_DOOR;
        level->site[i][j].p_locf = L_COLLEGE;
        CitySiteList[L_COLLEGE - CITYSITEBASE][0] = TRUE;
        CitySiteList[L_COLLEGE - CITYSITEBASE][1] = i;
        CitySiteList[L_COLLEGE - CITYSITEBASE][2] = j;
        break;
      case 's':
        level->site[i][j].locchar = OPEN_DOOR;
        level->site[i][j].p_locf = L_SORCERORS;
        CitySiteList[L_SORCERORS - CITYSITEBASE][0] = TRUE;
        CitySiteList[L_SORCERORS - CITYSITEBASE][1] = i;
        CitySiteList[L_SORCERORS - CITYSITEBASE][2] = j;
        break;
      case 'M':
        level->site[i][j].locchar = OPEN_DOOR;
        level->site[i][j].p_locf = L_MERC_GUILD;
        CitySiteList[L_MERC_GUILD - CITYSITEBASE][0] = TRUE;
        CitySiteList[L_MERC_GUILD - CITYSITEBASE][1] = i;
        CitySiteList[L_MERC_GUILD - CITYSITEBASE][2] = j;
        break;
      case 'c':
        level->site[i][j].locchar = OPEN_DOOR;
        level->site[i][j].p_locf = L_CASTLE;
        CitySiteList[L_CASTLE - CITYSITEBASE][0] = TRUE;
        CitySiteList[L_CASTLE - CITYSITEBASE][1] = i;
        CitySiteList[L_CASTLE - CITYSITEBASE][2] = j;
        break;
      case '?':
        mazesite(i, j, populate);
        break;
      case 'P':
        level->site[i][j].locchar = OPEN_DOOR;
        level->site[i][j].p_locf = L_ORDER;
        CitySiteList[L_ORDER - CITYSITEBASE][0] = TRUE;
        CitySiteList[L_ORDER - CITYSITEBASE][1] = i;
        CitySiteList[L_ORDER - CITYSITEBASE][2] = j;
        break;
      case 'H':
        level->site[i][j].locchar = OPEN_DOOR;
        level->site[i][j].p_locf = L_CHARITY;
        CitySiteList[L_CHARITY - CITYSITEBASE][0] = TRUE;
        CitySiteList[L_CHARITY - CITYSITEBASE][1] = i;
        CitySiteList[L_CHARITY - CITYSITEBASE][2] = j;
        break;
      case 'j':
        level->site[i][j].locchar = FLOOR;
        if (populate)
          make_justiciar(i, j);
        break;
      case 'J':
        level->site[i][j].locchar = CLOSED_DOOR;
        level->site[i][j].p_locf = L_JAIL;
        break;
      case 'A':
        level->site[i][j].locchar = OPEN_DOOR;
        level->site[i][j].p_locf = L_ARENA;
        CitySiteList[L_ARENA - CITYSITEBASE][0] = TRUE;
        CitySiteList[L_ARENA - CITYSITEBASE][1] = i;
        CitySiteList[L_ARENA - CITYSITEBASE][2] = j;
        break;
      case 'B':
        level->site[i][j].locchar = OPEN_DOOR;
        level->site[i][j].p_locf = L_BANK;
        CitySiteList[L_BANK - CITYSITEBASE][0] = TRUE;
        CitySiteList[L_BANK - CITYSITEBASE][1] = i;
        CitySiteList[L_BANK - CITYSITEBASE][2] = j;
        lset(i, j + 1, STOPS);
        lset(i + 1, j, STOPS);
        lset(i - 1, j, STOPS);
        lset(i, j - 1, STOPS);
        break;
      case 'X':
        level->site[i][j].locchar = FLOOR;
        level->site[i][j].p_locf = L_COUNTRYSIDE;
        CitySiteList[L_COUNTRYSIDE - CITYSITEBASE][0] = TRUE;
        CitySiteList[L_COUNTRYSIDE - CITYSITEBASE][1] = i;
        CitySiteList[L_COUNTRYSIDE - CITYSITEBASE][2] = j;
        break;
      case 'v':
        level->site[i][j].locchar = FLOOR;
        level->site[i][j].p_locf = L_VAULT;
        level->site[i][j].aux = NOCITYMOVE;
        lset(i, j, SECRET);
        break;
      case 'S':
        level->site[i][j].locchar = FLOOR;
        level->site[i][j].aux = NOCITYMOVE;
        lset(i, j, SECRET);
        break;
      case 'G':
        level->site[i][j].locchar = FLOOR;
        if (populate)
        {
          make_site_monster(i, j, GUARD);
          level->site[i][j].creature->aux1 = i;
          level->site[i][j].creature->aux2 = j;
        }
        break;
      case 'u':
        level->site[i][j].locchar = FLOOR;
        if (populate)
          make_minor_undead(i, j);
        break;
      case 'U':
        level->site[i][j].locchar = FLOOR;
        if (populate)
          make_major_undead(i, j);
        break;
      case 'V':
        level->site[i][j].showchar = WALL;
        level->site[i][j].locchar = FLOOR;
        level->site[i][j].p_locf = L_VAULT;
        if (populate)
          make_site_treasure(i, j, 5);
        level->site[i][j].aux = NOCITYMOVE;
        lset(i, j, SECRET);
        break;
      case '%':
        level->site[i][j].showchar = WALL;
        level->site[i][j].locchar = FLOOR;
        level->site[i][j].p_locf = L_TRAP_SIREN;
        if (populate)
          make_site_treasure(i, j, 5);
        level->site[i][j].aux = NOCITYMOVE;
        lset(i, j, SECRET);
        break;
      case '$':
        level->site[i][j].locchar = FLOOR;
        if (populate)
          make_site_treasure(i, j, 5);
        break;
      case '2':
        level->site[i][j].locchar = ALTAR;
        level->site[i][j].p_locf = L_ALTAR;
        level->site[i][j].aux = ODIN;
        break;
      case '3':
        level->site[i][j].locchar = ALTAR;
        level->site[i][j].p_locf = L_ALTAR;
        level->site[i][j].aux = SET;
        break;
      case '4':
        level->site[i][j].locchar = ALTAR;
        level->site[i][j].p_locf = L_ALTAR;
        level->site[i][j].aux = ATHENA;
        break;
      case '5':
        level->site[i][j].locchar = ALTAR;
        level->site[i][j].p_locf = L_ALTAR;
        level->site[i][j].aux = HECATE;
        break;
      case '6':
        level->site[i][j].locchar = ALTAR;
        level->site[i][j].p_locf = L_ALTAR;
        level->site[i][j].aux = DESTINY;
        break;
      case '^':
        level->site[i][j].showchar = WALL;
        level->site[i][j].locchar = FLOOR;
        level->site[i][j].p_locf = TRAP_BASE + random_range(NUMTRAPS);
        lset(i, j, SECRET);
        break;
      case '"':
        level->site[i][j].locchar = HEDGE;
        break;
      case '~':
        level->site[i][j].locchar = WATER;
        level->site[i][j].p_locf = L_WATER;
        break;
      case '=':
        level->site[i][j].locchar = WATER;
        level->site[i][j].p_locf = L_MAGIC_POOL;
        break;
      case '*':
        level->site[i][j].locchar = WALL;
        level->site[i][j].aux = 10;
        break;
      case '#':
        level->site[i][j].locchar = WALL;
        level->site[i][j].aux = 500;
        break;
      case '.':
        level->site[i][j].locchar = FLOOR;
        break;
      case ',':
        level->site[i][j].showchar = WALL;
        level->site[i][j].locchar = FLOOR;
        level->site[i][j].aux = NOCITYMOVE;
        lset(i, j, SECRET);
        break;
      case '-':
        level->site[i][j].locchar = CLOSED_DOOR;
        break;
      case '1':
        level->site[i][j].locchar = STATUE;
        break;
      default:
        printf("\nOops... missed a case: '%c'   \n", site);
        morewait();
      }

      if (loc_statusp(i, j, SEEN))
      {
        if (loc_statusp(i, j, SECRET))
          level->site[i][j].showchar = WALL;
        else
          level->site[i][j].showchar = level->site[i][j].locchar;
      }
    }
    site = getc(fd) ^ site;
  }
  City = level;

  /* make all city monsters asleep, and shorten their wakeup range to 2 */
  /* to prevent players from being molested by vicious monsters on */
  /* the streets */
  for (ml = level->mlist; ml != NULL; ml = ml->next)
  {
    m_status_reset(ml->m, AWAKE);
    ml->m->wakeup = 2;
  }
  fclose(fd);
  initrand(E_RESTORE, 0);
}

void assign_city_function(int x, int y)
{
  static int setup = 0;
  static int next = 0;
  static int permutation[64]; /* number of x's in city map */
  int i, j, k, l;

  level->site[x][y].aux = TRUE;

  lset(x, y + 1, STOPS);
  lset(x + 1, y, STOPS);
  lset(x - 1, y, STOPS);
  lset(x, y - 1, STOPS);
  lset(x, y, STOPS); /* FIXED! 12/30/98 */

  if (setup == 0)
  {
    setup = 1;
    for (i = 0; i < 64; i++)
      permutation[i] = i;
    for (i = 0; i < 500; i++)
    {
      j = random_range(64);
      k = random_range(64);
      l = permutation[j];
      permutation[j] = permutation[k];
      permutation[k] = l;
    }
  }
  if (next > 63)
  { /* in case someone changes the no. of x's */
    level->site[x][y].locchar = CLOSED_DOOR;
    level->site[x][y].p_locf = L_HOUSE;
    if (random_range(5))
      level->site[x][y].aux = LOCKED;
  }
  else
    switch (permutation[next])
    {
    case 0:
      level->site[x][y].locchar = OPEN_DOOR;
      level->site[x][y].p_locf = L_ARMORER;
      CitySiteList[L_ARMORER - CITYSITEBASE][1] = x;
      CitySiteList[L_ARMORER - CITYSITEBASE][2] = y;
      break;
    case 1:
      level->site[x][y].locchar = OPEN_DOOR;
      level->site[x][y].p_locf = L_CLUB;
      CitySiteList[L_CLUB - CITYSITEBASE][1] = x;
      CitySiteList[L_CLUB - CITYSITEBASE][2] = y;
      break;
    case 2:
      level->site[x][y].locchar = OPEN_DOOR;
      level->site[x][y].p_locf = L_GYM;
      CitySiteList[L_GYM - CITYSITEBASE][1] = x;
      CitySiteList[L_GYM - CITYSITEBASE][2] = y;
      break;
    case 3:
      level->site[x][y].locchar = CLOSED_DOOR;
      level->site[x][y].p_locf = L_THIEVES_GUILD;
      CitySiteList[L_THIEVES_GUILD - CITYSITEBASE][1] = x;
      CitySiteList[L_THIEVES_GUILD - CITYSITEBASE][2] = y;
      break;
    case 4:
      level->site[x][y].locchar = OPEN_DOOR;
      level->site[x][y].p_locf = L_HEALER;
      CitySiteList[L_HEALER - CITYSITEBASE][1] = x;
      CitySiteList[L_HEALER - CITYSITEBASE][2] = y;
      break;
    case 5:
      level->site[x][y].locchar = OPEN_DOOR;
      level->site[x][y].p_locf = L_CASINO;
      CitySiteList[L_CASINO - CITYSITEBASE][1] = x;
      CitySiteList[L_CASINO - CITYSITEBASE][2] = y;
      break;
    case 7:
      level->site[x][y].locchar = OPEN_DOOR;
      level->site[x][y].p_locf = L_DINER;
      CitySiteList[L_DINER - CITYSITEBASE][1] = x;
      CitySiteList[L_DINER - CITYSITEBASE][2] = y;
      break;
    case 8:
      level->site[x][y].locchar = OPEN_DOOR;
      level->site[x][y].p_locf = L_CRAP;
      CitySiteList[L_CRAP - CITYSITEBASE][1] = x;
      CitySiteList[L_CRAP - CITYSITEBASE][2] = y;
      break;
    case 6:
    case 9:
    case 20:
      level->site[x][y].locchar = OPEN_DOOR;
      level->site[x][y].p_locf = L_COMMANDANT;
      CitySiteList[L_COMMANDANT - CITYSITEBASE][1] = x;
      CitySiteList[L_COMMANDANT - CITYSITEBASE][2] = y;
      break;
    case 21:
      level->site[x][y].locchar = OPEN_DOOR;
      level->site[x][y].p_locf = L_TAVERN;
      CitySiteList[L_TAVERN - CITYSITEBASE][1] = x;
      CitySiteList[L_TAVERN - CITYSITEBASE][2] = y;
      break;
    case 10:
      level->site[x][y].locchar = OPEN_DOOR;
      level->site[x][y].p_locf = L_ALCHEMIST;
      CitySiteList[L_ALCHEMIST - CITYSITEBASE][1] = x;
      CitySiteList[L_ALCHEMIST - CITYSITEBASE][2] = y;
      break;
    case 11:
      level->site[x][y].locchar = OPEN_DOOR;
      level->site[x][y].p_locf = L_DPW;
      CitySiteList[L_DPW - CITYSITEBASE][1] = x;
      CitySiteList[L_DPW - CITYSITEBASE][2] = y;
      break;
    case 12:
      level->site[x][y].locchar = OPEN_DOOR;
      level->site[x][y].p_locf = L_LIBRARY;
      CitySiteList[L_LIBRARY - CITYSITEBASE][1] = x;
      CitySiteList[L_LIBRARY - CITYSITEBASE][2] = y;
      break;
    case 13:
      level->site[x][y].locchar = OPEN_DOOR;
      level->site[x][y].p_locf = L_PAWN_SHOP;
      CitySiteList[L_PAWN_SHOP - CITYSITEBASE][1] = x;
      CitySiteList[L_PAWN_SHOP - CITYSITEBASE][2] = y;
      break;
    case 14:
      level->site[x][y].locchar = OPEN_DOOR;
      level->site[x][y].p_locf = L_CONDO;
      CitySiteList[L_CONDO - CITYSITEBASE][1] = x;
      CitySiteList[L_CONDO - CITYSITEBASE][2] = y;
      break;
    case 15:
      level->site[x][y].locchar = CLOSED_DOOR;
      level->site[x][y].p_locf = L_BROTHEL;
      CitySiteList[L_BROTHEL - CITYSITEBASE][1] = x;
      CitySiteList[L_BROTHEL - CITYSITEBASE][2] = y;
      break;
    default:
      level->site[x][y].locchar = CLOSED_DOOR;
      switch (random_range(6))
      {
      case 0:
        level->site[x][y].p_locf = L_HOVEL;
        break;
      case 1:
      case 2:
      case 3:
      case 4:
        level->site[x][y].p_locf = L_HOUSE;
        break;
      case 5:
        level->site[x][y].p_locf = L_MANSION;
        break;
      }
      if (random_range(5))
        level->site[x][y].aux = LOCKED;
      break;
    }
  next++;
}

/* makes a hiscore npc for mansions */
void make_justiciar(int i, int j)
{
  Monsterlist* ml = Monsterlist::create();
  ml->m = ((pmt)checkmalloc(sizeof(montype)));
  *(ml->m) = Monsters[NPC];
  make_hiscore_npc(ml->m, 15);
  ml->m->x = i;
  ml->m->y = j;
  level->site[i][j].creature = ml->m;
  ml->m->click = (Tick + 1) % 60;
  ml->next = level->mlist;
  level->mlist = ml;
  m_status_reset(ml->m, AWAKE);
}

/* loads the city level */
void resurrect_guards()
{
  int i, j;
  char site;

  FILE *fd;

  strcpy(Str3, Omegalib);
  strcat(Str3, "city.dat");
  fd = checkfopen(Str3, "rb");
  site = cryptkey("city.dat");
  for (j = 0; j < LENGTH; j++)
  {
    for (i = 0; i < WIDTH; i++)
    {
      site = getc(fd) ^ site;
      if (site == 'G')
      {
        make_site_monster(i, j, GUARD);
        level->site[i][j].creature->monstring = "undead guardsman";
        level->site[i][j].creature->meleef = M_MELEE_SPIRIT;
        level->site[i][j].creature->movef = M_MOVE_SPIRIT;
        level->site[i][j].creature->strikef = M_STRIKE_MISSILE;
        level->site[i][j].creature->immunity = EVERYTHING - pow2(NORMAL_DAMAGE);
        level->site[i][j].creature->hp *= 2;
        level->site[i][j].creature->hit *= 2;
        level->site[i][j].creature->dmg *= 2;
        level->site[i][j].creature->ac *= 2;
        m_status_set(level->site[i][j].creature, HOSTILE);
        m_status_set(level->site[i][j].creature, AWAKE);
      }
    }
    site = getc(fd) ^ site;
  }
  fclose(fd);
}

void mazesite(int i, int j, int populate)
{
  static FILE *fd = NULL;
  static int k = 0;
  static char site;
  if (fd == NULL)
  {
    strcpy(Str2, Omegalib);
    strcpy(Str4, "maze .dat");
    Str4[4] = '1' + random_range(4);
    strcat(Str2, Str4);
    fd = checkfopen(Str2, "rb");
    site = cryptkey("mazes");
  }
  site = getc(fd) ^ site;
  k++;
  if (k == 286)
    fclose(fd);
  switch (site)
  {
  case '"':
    level->site[i][j].locchar = HEDGE;
    if (random_range(10))
      level->site[i][j].p_locf = L_HEDGE;
    else
      level->site[i][j].p_locf = L_TRIFID;
    break;
  case '-':
    level->site[i][j].locchar = CLOSED_DOOR;
    break;
  case '.':
    level->site[i][j].locchar = FLOOR;
    break;
  case '>':
    level->site[i][j].locchar = STAIRS_DOWN;
    level->site[i][j].p_locf = L_SEWER;
    break;
  case 'z':
    level->site[i][j].locchar = FLOOR;
    level->site[i][j].p_locf = L_MAZE;
    break;
  case 'O':
    level->site[i][j].locchar = OPEN_DOOR;
    level->site[i][j].p_locf = L_ORACLE;
    CitySiteList[L_ORACLE - CITYSITEBASE][1] = i;
    CitySiteList[L_ORACLE - CITYSITEBASE][2] = j;
    break;
  case '?':
    randommazesite(i, j, populate);
    break;
  }
  lreset(i, j, SEEN);
}

void randommazesite(int i, int j, int populate)
{
  switch (random_range(7))
  {
  case 0:
  case 1:
    level->site[i][j].locchar = FLOOR;
    level->site[i][j].p_locf = TRAP_BASE + random_range(NUMTRAPS);
    break;
  case 2:
  case 3:
    level->site[i][j].locchar = FLOOR;
    if (populate)
      make_site_monster(i, j, -1);
    break;
  case 4:
  case 5:
    level->site[i][j].locchar = FLOOR;
    if (populate)
      make_site_treasure(i, j, 5);
    break;
  default:
    level->site[i][j].locchar = FLOOR;
  }
}

/* undead are not hostile unless disturbed.... */
void make_minor_undead(int i, int j)
{
  int mid;
  if (random_range(2))
    mid = GHOST;
  else
    mid = HAUNT;
  make_site_monster(i, j, mid);
  m_status_reset(level->site[i][j].creature, AWAKE);
  m_status_reset(level->site[i][j].creature, HOSTILE);
}

/* undead are not hostile unless disturbed.... */
void make_major_undead(int i, int j)
{
  int mid;
  if (random_range(2))
    mid = LICHE; /* lich */
  else
    mid = VAMP_LORD; /*vampire lord*/
  make_site_monster(i, j, mid);
  m_status_reset(level->site[i][j].creature, AWAKE);
  m_status_reset(level->site[i][j].creature, HOSTILE);
}

static char jail[5][11] =
    {
        {'#', '#', '*', '#', '#', '*', '#', '#', '*', '#', '#'},
        {'#', '#', '*', '#', '#', '*', '#', '*', '#', '#', '#'},
        {'#', '#', 'T', '#', 'T', '#', 'T', '#', 'T', '#', '#'},
        {'#', '#', '7', '#', '7', '#', '7', '#', '7', '#', '#'},
        {'#', '#', 'R', '#', 'R', '#', 'R', '#', 'R', '#', '#'}};

/* fixes up the jail in case it has been munged by player action */
void repair_jail()
{
  int i, j;
  for (i = 0; i < 11; i++)
    for (j = 0; j < 5; j++)
    {
      switch (jail[j][i])
      {
      case '#':
        City->site[i + 35][j + 52].locchar = WALL;
        City->site[i + 35][j + 52].p_locf = L_NO_OP;
        City->site[i + 35][j + 52].aux = NOCITYMOVE;
        break;
      case '*':
        City->site[i + 35][j + 52].locchar = WALL;
        City->site[i + 35][j + 52].p_locf = L_NO_OP;
        City->site[i + 35][j + 52].aux = 10;
        break;
      case 'T':
        City->site[i + 35][j + 52].locchar = FLOOR;
        City->site[i + 35][j + 52].p_locf = L_PORTCULLIS_TRAP;
        City->site[i + 35][j + 52].aux = NOCITYMOVE;
        break;
      case '7':
        City->site[i + 35][j + 52].locchar = FLOOR;
        City->site[i + 35][j + 52].p_locf = L_PORTCULLIS;
        City->site[i + 35][j + 52].aux = NOCITYMOVE;
        break;
      case 'R':
        City->site[i + 35][j + 52].locchar = FLOOR;
        City->site[i + 35][j + 52].p_locf = L_RAISE_PORTCULLIS;
        City->site[i + 35][j + 52].aux = NOCITYMOVE;
        break;
      }
      lreset(i + 35, j + 52, CHANGED);
    }
}
