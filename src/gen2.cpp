/* omega copyright (c) 1987,1988,1989 by Laurence Raphael Brothers */
/* gen2.c */
/* level generator functions */

#include "glob.h"
#include <map>
/* For each level, there should be one stairway going up and one down. 
fromlevel determines whether the player is placed on the up or the down
staircase. The aux value is currently unused elsewhere, but is set 
to the destination level. */

void make_stairs(int fromlevel)
{
  int i, j;
  /* no stairway out of astral */
  if (Current_Environment != E_ASTRAL)
  {
    findspace(&i, &j, -1);
    level->site[i][j].locchar = STAIRS_UP;
    level->site[i][j].aux = level->depth - 1;
    lset(i, j, STOPS);
    if (fromlevel >= 0 && fromlevel < level->depth)
    {
      player.x = i;
      player.y = j;
    }
  }
  if (level->depth < MaxDungeonLevels)
  {
    findspace(&i, &j, -1);
    level->site[i][j].locchar = STAIRS_DOWN;
    level->site[i][j].aux = level->depth + 1;
    lset(i, j, STOPS);
    if (fromlevel > level->depth)
    {
      player.x = i;
      player.y = j;
    }
  }
}

/* tactical map generating functions */

void make_country_screen(Symbol terrain)
{
  int i, j;
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
  level->environment = E_TACTICAL_MAP;
  level->generated = TRUE;
  std::map<unsigned char,std::function<void()>> terrainMap = {
    {FOREST,make_forest},
    {JUNGLE,make_jungle},
    {SWAMP,make_swamp},
    {RIVER,make_river},
    {MOUNTAINS,make_mountains},
    {PASS,make_mountains},
    {ROAD,make_road},
  };
  if(terrainMap.count(terrain)>0){
    terrainMap[terrain]();
  } else {
    make_plains();
  }
  if (nighttime())
  {
    print3("Night's gloom shrouds your sight.");
    for (i = 0; i < WIDTH; i++)
      for (j = 0; j < LENGTH; j++)
      {
        level->site[i][j].showchar = SPACE;
        level->site[i][j].lstatus = 0;
      }
  }
}

void make_general_map(char* terrain)
{
  int i, j;
  int size = strlen(terrain);
  char curr;

  for (i = 0; i < WIDTH; i++)
    for (j = 0; j < LENGTH; j++)
    {
      if ((i == 0 && j == 0) || !random_range(5))
        curr = terrain[random_range(size)];
      else if (j == 0 || (random_range(2) && i > 0))
        curr = level->site[i - 1][j].locchar & 0xff;
      else
        curr = level->site[i][j - 1].locchar & 0xff;
      if (curr == (FLOOR & 0xff))
      {
        level->site[i][j].locchar = level->site[i][j].showchar = FLOOR;
        level->site[i][j].p_locf = L_NO_OP;
      }
      if (curr == (HEDGE & 0xff))
      {
        level->site[i][j].locchar = level->site[i][j].showchar = HEDGE;
        level->site[i][j].p_locf = L_HEDGE;
      }
      if (curr == (WATER & 0xff))
      {
        level->site[i][j].locchar = level->site[i][j].showchar = WATER;
        level->site[i][j].p_locf = L_WATER;
      }
      if (curr == (RUBBLE & 0xff))
      {
        level->site[i][j].locchar = level->site[i][j].showchar = RUBBLE;
        level->site[i][j].p_locf = L_RUBBLE;
      }
      level->site[i][j].lstatus = SEEN + LIT;
      level->site[i][j].roomnumber = RS_COUNTRYSIDE;
      if ((i == 0) || (j == 0) || (i == WIDTH - 1) || (j == LENGTH - 1))
        level->site[i][j].p_locf = L_TACTICAL_EXIT;
    }
}

void make_plains()
{
  make_general_map(".");
}

void make_road()
{
  int x, y;
  make_general_map("\"\"~4....");
  for (x = WIDTH / 2 - 3; x <= WIDTH / 2 + 3; x++)
    for (y = 0; y < LENGTH; y++)
    {
      level->site[x][y].locchar = level->site[x][y].showchar = FLOOR;
      if (y != 0 && y != LENGTH - 1)
        level->site[x][y].p_locf = L_NO_OP;
    }
}

void make_forest()
{
  make_general_map("\".");
  straggle_corridor(0, random_range(LENGTH), WIDTH, random_range(LENGTH),
                    WATER, RS_COUNTRYSIDE);
}

void make_jungle()
{
  make_general_map("\"\".");
}

void make_river()
{
  int i, y, y1;
  make_general_map("\".......");
  y = random_range(LENGTH);
  y1 = random_range(LENGTH);
  straggle_corridor(0, y, WIDTH, y1, WATER, RS_COUNTRYSIDE);
  for (i = 0; i < 7; i++)
  {
    if (y > LENGTH / 2)
      y--;
    else
      y++;
    if (y1 > LENGTH / 2)
      y1--;
    else
      y1++;
    straggle_corridor(0, y, WIDTH, y1, WATER, RS_COUNTRYSIDE);
  }
}

void make_mountains()
{
  int i, x, y, x1, y1;
  make_general_map("4...");
  x = 0;
  y = random_range(LENGTH);
  x1 = WIDTH;
  y1 = random_range(LENGTH);
  straggle_corridor(x, y, x1, y1, WATER, RS_COUNTRYSIDE);
  for (i = 0; i < 7; i++)
  {
    x = random_range(WIDTH);
    x1 = random_range(WIDTH);
    y = 0;
    y1 = LENGTH;
    straggle_corridor(x, y, x1, y1, WATER, RS_COUNTRYSIDE);
  }
}

void make_swamp()
{
  make_general_map("~~\".");
}

/* builds a room. Then, for each successive room, sends off at least one
corridor which is guaranteed to connect up to another room, thus guaranteeing
fully connected level. */

void room_level()
{
  int i, fx, fy, tx, ty, t, l, e;
  char rsi;

  level->numrooms = random_range(8) + 9;

  do
  {
    t = random_range(LENGTH - 10) + 1;
    l = random_range(WIDTH - 10) + 1;
    e = 4 + random_range(5);
  } while ((level->site[l][t].roomnumber != RS_WALLSPACE) ||
           (level->site[l + e][t].roomnumber != RS_WALLSPACE) ||
           (level->site[l][t + e].roomnumber != RS_WALLSPACE) ||
           (level->site[l + e][t + e].roomnumber != RS_WALLSPACE));
  if (Current_Dungeon == E_SEWERS)
  {
    if (random_range(2))
      rsi = ROOMBASE + 25;
    else
      rsi = ROOMBASE + random_range(NUMROOMNAMES);
  }
  else
    rsi = ROOMBASE + random_range(NUMROOMNAMES);
  build_room(l, t, e, rsi, 1);

  for (i = 2; i <= level->numrooms; i++)
  {
    do
    {
      t = random_range(LENGTH - 10) + 1;
      l = random_range(WIDTH - 10) + 1;
      e = 4 + random_range(5);
    } while ((level->site[l][t].roomnumber != RS_WALLSPACE) ||
             (level->site[l + e][t].roomnumber != RS_WALLSPACE) ||
             (level->site[l][t + e].roomnumber != RS_WALLSPACE) ||
             (level->site[l + e][t + e].roomnumber != RS_WALLSPACE));
    if (Current_Dungeon == E_SEWERS)
    {
      if (random_range(2))
        rsi = ROOMBASE + 25;
      else
        rsi = ROOMBASE + random_range(NUMROOMNAMES);
    }
    else
      rsi = ROOMBASE + random_range(NUMROOMNAMES);
    build_room(l, t, e, rsi, i);

    /* corridor which is guaranteed to connect */
    findspace(&tx, &ty, i);

    /* figure out where to start corridor from */
    if ((ty <= t) && (tx <= l + e))
    {
      fx = l + 1 + random_range(e - 1);
      fy = t;
    }
    else if ((tx >= l + e) && (ty <= t + e))
    {
      fx = l + e;
      fy = t + 1 + random_range(e - 1);
    }
    else if ((ty >= t + e) && (tx >= l))
    {
      fx = l + 1 + random_range(e - 1);
      fy = t + e;
    }
    else
    {
      fx = l;
      fy = t + 1 + random_range(e - 1);
    }

    room_corridor(fx, fy, tx, ty, i);

    /* corridor which may not go anywhere */
    if (random_range(2))
    {
      findspace(&tx, &ty, i);
      if ((ty <= t) && (tx <= l + e))
      {
        fx = l + 1 + random_range(e - 1);
        fy = t;
      }
      else if ((tx >= l + e) && (ty <= t + e))
      {
        fx = l + e;
        fy = t + 1 + random_range(e - 1);
      }
      else if ((ty >= t + e) && (tx >= l))
      {
        fx = l + 1 + random_range(e - 1);
        fy = t + e;
      }
      else
      {
        fx = l;
        fy = t + 1 + random_range(e - 1);
      }
      room_corridor(fx, fy, tx, ty, i);
    }
  }

  if (Current_Dungeon == E_SEWERS)
  {
    if (level->depth == SEWERLEVELS)
    {
      findspace(&tx, &ty, -1);
      level->mlist = Monsterlist::create();
      level->mlist->next = NULL;
      level->mlist->m =
          level->site[tx][ty].creature =
              ((Monster*)make_creature(GREAT_WYRM)); /* The Great Wyrm */
      level->mlist->m->x = tx;
      level->mlist->m->y = ty;
    }
  }
  else if (Current_Environment == E_CASTLE)
  {
    if (level->depth == CASTLELEVELS)
    {
      findspace(&tx, &ty, -1);
      level->site[tx][ty].locchar = STAIRS_DOWN;
      level->site[tx][ty].p_locf = L_ENTER_COURT;
    }
  }
  else if (Current_Environment == E_VOLCANO)
  {
    if (level->depth == VOLCANOLEVELS && !gamestatusp(COMPLETED_VOLCANO))
    {
      findspace(&tx, &ty, -1);
      level->mlist = Monsterlist::create();
      level->mlist->next = NULL;
      level->mlist->m =
          level->site[tx][ty].creature =
              ((Monster*)make_creature(DEMON_EMP)); /* The demon emp */
      level->mlist->m->x = tx;
      level->mlist->m->y = ty;
    }
  }
}

/* goes from f to t unless it hits a site which is not a wall and doesn't
   have buildaux field == baux */
void room_corridor(int fx, int fy, int tx, int ty, int baux)
{
  int dx, dy, continuing = TRUE;

  dx = sign(tx - fx);
  dy = sign(ty - fy);

  makedoor(fx, fy);

  fx += dx;
  fy += dy;

  while (continuing)
  {
    level->site[fx][fy].locchar = FLOOR;
    level->site[fx][fy].roomnumber = RS_CORRIDOR;
    level->site[fx][fy].buildaux = baux;
    dx = sign(tx - fx);
    dy = sign(ty - fy);
    if ((dx != 0) && (dy != 0))
    {
      if (random_range(2))
        dx = 0;
      else if (random_range(2))
        dy = 0;
    }
    fx += dx;
    fy += dy;
    continuing = (((fx != tx) || (fy != ty)) &&
                  ((level->site[fx][fy].buildaux == 0) ||
                   (level->site[fx][fy].buildaux == baux)));
  }
  makedoor(fx, fy);
}

void maze_level()
{
  int i, j, tx, ty, mid;
  char rsi;
  if (Current_Environment == E_ASTRAL)
    switch (level->depth)
    {
    case 1:
      rsi = RS_EARTHPLANE;
      break;
    case 2:
      rsi = RS_AIRPLANE;
      break;
    case 3:
      rsi = RS_WATERPLANE;
      break;
    case 4:
      rsi = RS_FIREPLANE;
      break;
    case 5:
      rsi = RS_HIGHASTRAL;
      break;
    }
  else
    rsi = RS_VOLCANO;
  maze_corridor(random_range(WIDTH - 1) + 1,
                random_range(LENGTH - 1) + 1,
                random_range(WIDTH - 1) + 1,
                random_range(LENGTH - 1) + 1,
                rsi, 0);
  if (Current_Dungeon == E_ASTRAL)
  {
    for (i = 0; i < WIDTH; i++)
      for (j = 0; j < LENGTH; j++)
        if (level->site[i][j].locchar == WALL)
          switch (level->depth)
          {
          case 1:
            level->site[i][j].aux = 500;
            break;
          case 2:
            level->site[i][j].locchar = WHIRLWIND;
            level->site[i][j].p_locf = L_WHIRLWIND;
            break;
          case 3:
            level->site[i][j].locchar = WATER;
            level->site[i][j].p_locf = L_WATER;
            break;
          case 4:
            level->site[i][j].locchar = FIRE;
            level->site[i][j].p_locf = L_FIRE;
            break;
          case 5:
            level->site[i][j].locchar = ABYSS;
            level->site[i][j].p_locf = L_ABYSS;
            break;
          }
    switch (level->depth)
    {
    case 1:
      mid = LORD_EARTH;
      break; /* Elemental Lord of Earth */
    case 2:
      mid = LORD_AIR;
      break; /* Elemental Lord of Air */
    case 3:
      mid = LORD_WATER;
      break; /* Elemental Lord of Water */
    case 4:
      mid = LORD_FIRE;
      break; /* Elemental Lord of Fire */
    case 5:
      mid = ELEM_MASTER;
      break; /* Elemental Master */
    }
    if (level->depth == 5)
    {
      findspace(&tx, &ty, -1);
      level->site[tx][ty].p_locf = L_ENTER_CIRCLE;
      level->site[tx][ty].locchar = STAIRS_DOWN;
    }
    if (!gamestatusp(COMPLETED_ASTRAL))
    {
      findspace(&tx, &ty, -1);
      level->mlist = Monsterlist::create();
      level->mlist->next = NULL;
      level->mlist->m =
          level->site[tx][ty].creature =
              ((Monster*)make_creature(mid));
      level->mlist->m->x = tx;
      level->mlist->m->y = ty;
    }
  }
  else if (Current_Environment == E_VOLCANO)
  {
    if (level->depth == VOLCANOLEVELS && !gamestatusp(COMPLETED_VOLCANO))
    {
      findspace(&tx, &ty, -1);
      level->mlist = Monsterlist::create();
      level->mlist->next = NULL;
      level->mlist->m =
          level->site[tx][ty].creature =
              ((Monster*)make_creature(DEMON_EMP)); /* The demon emp */
      level->mlist->m->x = tx;
      level->mlist->m->y = ty;
    }
  }
}

/* keep drawing corridors recursively for 2^5 endpoints */
void maze_corridor(int fx, int fy, int tx, int ty, char rsi, char num)
{
  if (num < 6)
  {
    straggle_corridor(fx, fy, tx, ty, FLOOR, rsi);
    maze_corridor(tx, ty,
                  random_range(WIDTH - 1) + 1,
                  random_range(LENGTH - 1) + 1,
                  rsi, num + 1);
  }
}
