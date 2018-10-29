/* omega copyright (C) by Laurence Raphael Brothers, 1987,1988,1989 */
/* village.c */
/* some functions to make the village levels */

#include "glob.h"

/* loads the village level into Level*/
void load_village(int villagenum, int populate)
{
  int i, j;
  char site;

  FILE *fd;

  tempLevel = level;
  if (ok_to_free(tempLevel))
  {
#ifndef SAVE_LEVELS
    free_level(tempLevel);
#endif
    tempLevel = NULL;
  }

  initrand(Current_Environment, villagenum);

  assign_village_function(0, 0, TRUE);

#ifndef SAVE_LEVELS
  level = ((Level*)checkmalloc(sizeof(Level)));
#else
  msdos_changelevel(TempLevel, 0, -1);
  Level = &TheLevel;
#endif
  clear_level(level);
  level->environment = E_VILLAGE;
  strcpy(Str3, Omegalib);
  switch (villagenum)
  {
  case 1:
    strcat(Str3, "village1.dat");
    break;
  case 2:
    strcat(Str3, "village2.dat");
    break;
  case 3:
    strcat(Str3, "village3.dat");
    break;
  case 4:
    strcat(Str3, "village4.dat");
    break;
  case 5:
    strcat(Str3, "village5.dat");
    break;
  case 6:
    strcat(Str3, "village6.dat");
    break;
  }
  site = cryptkey("village.dat");
  fd = checkfopen(Str3, "rb");
  for (j = 0; j < LENGTH; j++)
  {
    for (i = 0; i < WIDTH; i++)
    {
      lset(i, j, SEEN);
      site = getc(fd) ^ site;
      level->site[i][j].p_locf = L_NO_OP;
      switch (site)
      {
      case 'f':
        level->site[i][j].locchar = FLOOR;
        if (populate)
          make_food_bin(i, j);
        break;
      case 'g':
        level->site[i][j].locchar = FLOOR;
        level->site[i][j].p_locf = L_GRANARY;
        break;
      case 'h':
        level->site[i][j].locchar = FLOOR;
        if (populate)
          make_horse(i, j);
        break;
      case 'S':
        level->site[i][j].locchar = FLOOR;
        level->site[i][j].p_locf = L_STABLES;
        break;
      case 'H':
        level->site[i][j].locchar = FLOOR;
        if (populate)
          make_merchant(i, j);
        break;
      case 'C':
        level->site[i][j].locchar = FLOOR;
        level->site[i][j].p_locf = L_COMMONS;
        break;
      case 's':
        level->site[i][j].locchar = FLOOR;
        if (populate)
          make_sheep(i, j);
        break;
      case 'x':
        assign_village_function(i, j, FALSE);
        break;
      case 'X':
        level->site[i][j].locchar = FLOOR;
        level->site[i][j].p_locf = L_COUNTRYSIDE;
        break;
      case 'G':
        level->site[i][j].locchar = FLOOR;
        if (populate)
        {
          make_guard(i, j);
          level->site[i][j].creature->aux1 = i;
          level->site[i][j].creature->aux2 = j;
        }
        break;
      case '^':
        level->site[i][j].locchar = FLOOR;
        level->site[i][j].p_locf = L_TRAP_SIREN;
        break;
      case '"':
        level->site[i][j].locchar = HEDGE;
        level->site[i][j].p_locf = L_HEDGE;
        break;
      case '~':
        level->site[i][j].locchar = WATER;
        level->site[i][j].p_locf = L_WATER;
        break;
      case '+':
        level->site[i][j].locchar = WATER;
        level->site[i][j].p_locf = L_CHAOS;
        break;
      case '\'':
        level->site[i][j].locchar = HEDGE;
        level->site[i][j].p_locf = L_TRIFID;
        break;
      case '!':
        special_village_site(i, j, villagenum);
        break;
      case '#':
        level->site[i][j].locchar = WALL;
        level->site[i][j].aux = 100;
        break;
      case '.':
        level->site[i][j].locchar = FLOOR;
        break;
      case '-':
        level->site[i][j].locchar = CLOSED_DOOR;
        break;
      case '1':
        level->site[i][j].locchar = STATUE;
        break;
      }
      if (loc_statusp(i, j, SECRET))
        level->site[i][j].showchar = WALL;
      else
        level->site[i][j].showchar = level->site[i][j].locchar;
    }
    site = getc(fd) ^ site;
  }
  fclose(fd);
  initrand(E_RESTORE, 0);
}

void make_guard(int i, int j)
{
  Monsterlist* tml = ((Monsterlist*)(checkmalloc(sizeof(Monsterlist))));
  tml->m = (level->site[i][j].creature = make_creature(GUARD));
  tml->m->x = i;
  tml->m->y = j;
  tml->next = level->mlist;
  level->mlist = tml;
}

void make_sheep(int i, int j)
{
  Monsterlist* tml = ((Monsterlist*)(checkmalloc(sizeof(Monsterlist))));
  tml->m = (level->site[i][j].creature = make_creature(SHEEP));
  tml->m->x = i;
  tml->m->y = j;
  tml->next = level->mlist;
  level->mlist = tml;
}

void make_food_bin(int i, int j)
{
  Objectlist* tol;
  int k;

  for (k = 0; k < 10; k++)
  {
    tol = ((Objectlist*)checkmalloc(sizeof(Objectlist)));
    tol->thing = ((pob)checkmalloc(sizeof(objtype)));
    make_food(tol->thing, 15); /* grain */
    tol->next = level->site[i][j].things;
    level->site[i][j].things = tol;
  }
}

void make_horse(int i, int j)
{
  Monsterlist* tml = ((Monsterlist*)(checkmalloc(sizeof(Monsterlist))));
  tml->m = (level->site[i][j].creature = make_creature(HORSE));
  tml->m->x = i;
  tml->m->y = j;
  tml->next = level->mlist;
  level->mlist = tml;
}

void make_merchant(int i, int j)
{
  Monsterlist* tml = ((Monsterlist*)(checkmalloc(sizeof(Monsterlist))));
  tml->m = (level->site[i][j].creature = make_creature(MERCHANT));
  tml->m->x = i;
  tml->m->y = j;
  tml->next = level->mlist;
  level->mlist = tml;
}

void assign_village_function(int x, int y, int setup)
{
  static int next = 0;
  static int permutation[24]; /* number of x's in village map */
  int i, j, k;

  if (setup)
  {
    next = 0;
    for (i = 0; i < 24; i++)
      permutation[i] = i;
    for (i = 0; i < 24; i++)
    {
      j = permutation[i];
      k = random_range(24);
      permutation[i] = permutation[k];
      permutation[k] = j;
    }
  }
  else
  {

    lset(x, y + 1, STOPS);
    lset(x + 1, y, STOPS);
    lset(x - 1, y, STOPS);
    lset(x, y - 1, STOPS);
    lset(x, y, STOPS);

    switch (permutation[next++])
    {
    case 0:
      level->site[x][y].locchar = OPEN_DOOR;
      level->site[x][y].p_locf = L_ARMORER;
      break;
    case 1:
      level->site[x][y].locchar = OPEN_DOOR;
      level->site[x][y].p_locf = L_HEALER;
      break;
    case 2:
      level->site[x][y].locchar = OPEN_DOOR;
      level->site[x][y].p_locf = L_TAVERN;
      break;
    case 3:
      level->site[x][y].locchar = OPEN_DOOR;
      level->site[x][y].p_locf = L_COMMANDANT;
      break;
    case 4:
      level->site[x][y].locchar = OPEN_DOOR;
      level->site[x][y].p_locf = L_CARTOGRAPHER;
      break;
    default:
      level->site[x][y].locchar = CLOSED_DOOR;
      if (random_range(2))
        level->site[x][y].aux = LOCKED;
      if (random_range(2))
        level->site[x][y].p_locf = L_HOVEL;
      else
        level->site[x][y].p_locf = L_HOUSE;
      break;
    }
  }
}

void special_village_site(int i, int j, int villagenum)
{
  if (villagenum == 1)
  {
    level->site[i][j].locchar = ALTAR;
    level->site[i][j].p_locf = L_LAWSTONE;
  }
  if (villagenum == 2)
  {
    level->site[i][j].locchar = ALTAR;
    level->site[i][j].p_locf = L_BALANCESTONE;
  }
  else if (villagenum == 3)
  {
    level->site[i][j].locchar = ALTAR;
    level->site[i][j].p_locf = L_CHAOSTONE;
  }
  else if (villagenum == 4)
  {
    level->site[i][j].locchar = ALTAR;
    level->site[i][j].p_locf = L_MINDSTONE;
  }
  else if (villagenum == 5)
  {
    level->site[i][j].locchar = ALTAR;
    level->site[i][j].p_locf = L_SACRIFICESTONE;
  }
  else if (villagenum == 6)
  {
    level->site[i][j].locchar = ALTAR;
    level->site[i][j].p_locf = L_VOIDSTONE;
  }
}
