/* copyright (c) 1987,1988,1989 by Laurence Raphael Brothers */
/* utils.c */

/* Random utility functions called from all over */

#ifndef MSDOS_SUPPORTED_ANTIQUE
#include <sys/types.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#endif

#include "glob.h"

/* x and y on level? */
int inbounds(int x, int y)
{
  return ((x >= 0) && (y >= 0) && (x < WIDTH) && (y < LENGTH));
}

/* RANDFUNCTION is defined in odefs.h */
int random_range(int k)
{
  /*return( k==0 ? 0 : (int) RANDFUNCTION() % k ) ;*/
  return (k == 0 ? 0 : (int)((RANDFUNCTION() % 10000) * k) / 10000);
}

/* modify absolute y coord relative to which part of level we are on */
int screenmod(int y)
{
  return (y - ScreenOffset);
}

int offscreen(int y)
{
  return ((y < 0) ||
          (y < ScreenOffset) ||
          (y > ScreenOffset + ScreenLength - 1) ||
          (y > LENGTH));
}

/* always hit on a natural 0; never hit on a natural 19 */
int hitp(int hit, int ac)
{
  int roll = random_range(20);
  if (roll == 0)
    return (TRUE);
  else if (roll == 19)
    return (FALSE);
  else
    return ((roll < (hit - ac)) ? TRUE : FALSE);
}

/* number of moves from x1,y1 to x2,y2 */
int distance(int x1, int y1, int x2, int y2)
{
  return (max(abs(x2 - x1), abs(y2 - y1)));
}

/* can you shoot, or move monsters through a spot? */
int unblocked(int x, int y)
{
  if ((!inbounds(x, y)) ||
      (level->site[x][y].creature != NULL) ||
      (level->site[x][y].locchar == WALL) ||
      (level->site[x][y].locchar == PORTCULLIS) ||
      (level->site[x][y].locchar == STATUE) ||
      (level->site[x][y].locchar == HEDGE) ||
      (level->site[x][y].locchar == CLOSED_DOOR) ||
      loc_statusp(x, y, SECRET) ||
      ((x == player.x) && (y == player.y)))
    return (FALSE);
  else
    return (TRUE);
}

/* do monsters want to move through a spot */
int m_unblocked(Monster* m, int x, int y)
{
  if ((!inbounds(x, y)) || ((x == player.x) && (y == player.y)))
    return (FALSE);
  else if ((level->site[x][y].creature != NULL) ||
           (level->site[x][y].locchar == SPACE))
    return (FALSE);
  else if (m_statusp(m, ONLYSWIM))
    return (level->site[x][y].locchar == WATER);
  else if (loc_statusp(x, y, SECRET))
  {
    if (m->movef == M_MOVE_SMART)
    {
      if (los_p(x, y, player.x, player.y))
      {
        mprint("You see a secret door swing open!");
        lreset(x, y, SECRET);
        lset(x, y, CHANGED);
      }
      else
        mprint("You hear a door creak open, and then close again.");
      /* smart monsters would close secret doors behind them if the */
      /* player didn't see them using it */
      return (TRUE);
    }
    else
      return (m_statusp(m, INTANGIBLE));
  }
  else if ((level->site[x][y].locchar == FLOOR) ||
           (level->site[x][y].locchar == OPEN_DOOR))
    return (TRUE);
  else if ((level->site[x][y].locchar == PORTCULLIS) ||
           (level->site[x][y].locchar == WALL) ||
           (level->site[x][y].locchar == STATUE))
    return (m_statusp(m, INTANGIBLE));
  else if (level->site[x][y].locchar == WATER)
    return (m_statusp(m, SWIMMING) ||
            m_statusp(m, ONLYSWIM) ||
            m_statusp(m, INTANGIBLE) ||
            m_statusp(m, FLYING));
  else if (level->site[x][y].locchar == CLOSED_DOOR)
  {
    if (m->movef == M_MOVE_SMART)
    {
      mprint("You hear a door creak open.");
      level->site[x][y].locchar = OPEN_DOOR;
      lset(x, y, CHANGED);
      return (TRUE);
    }
    else if (random_range(m->dmg) > random_range(100))
    {
      mprint("You hear a door shattering.");
      level->site[x][y].locchar = RUBBLE;
      lset(x, y, CHANGED);
      return (TRUE);
    }
    else
      return (m_statusp(m, INTANGIBLE));
  }
  else if (level->site[x][y].locchar == LAVA)
    return ((m_immunityp(m, FLAME) &&
             m_statusp(m, SWIMMING)) ||
            m_statusp(m, INTANGIBLE) ||
            m_statusp(m, FLYING));
  else if (level->site[x][y].locchar == FIRE)
    return (m_statusp(m, INTANGIBLE) ||
            m_immunityp(m, FLAME));
  else if ((level->site[x][y].locchar == TRAP) ||
           (level->site[x][y].locchar == HEDGE) ||
           (level->site[x][y].locchar == ABYSS))
    return ((m->movef == M_MOVE_CONFUSED) ||
            m_statusp(m, INTANGIBLE) ||
            m_statusp(m, FLYING));
  else
    return (TRUE);
}

/* can you see through a spot? */
int view_unblocked(int x, int y)
{
  if (!inbounds(x, y))
    return (FALSE);
  else if ((level->site[x][y].locchar == WALL) ||
           (level->site[x][y].locchar == STATUE) ||
           (level->site[x][y].locchar == HEDGE) ||
           (level->site[x][y].locchar == FIRE) ||
           (level->site[x][y].locchar == CLOSED_DOOR) ||
           loc_statusp(x, y, SECRET))
    return (FALSE);
  else
    return (TRUE);
}

#ifndef MSDOS_SUPPORTED_ANTIQUE
/* 8 moves in Dirs */
void initdirs()
{
  Dirs[0][0] = 1;
  Dirs[0][1] = 1;
  Dirs[0][2] = -1;
  Dirs[0][3] = -1;
  Dirs[0][4] = 1;
  Dirs[0][5] = -1;
  Dirs[0][6] = 0;
  Dirs[0][7] = 0;
  Dirs[0][8] = 0;
  Dirs[1][0] = 1;
  Dirs[1][1] = -1;
  Dirs[1][2] = 1;
  Dirs[1][3] = -1;
  Dirs[1][4] = 0;
  Dirs[1][5] = 0;
  Dirs[1][6] = 1;
  Dirs[1][7] = -1;
  Dirs[1][8] = 0;
}
#endif

/* do_los moves pyx along a lineofsight from x1 to x2 */
/* x1 and x2 are pointers because as a side effect they are changed */
/* to the final location of the pyx */
void do_los(Symbol pyx, int* x1, int* y1, int x2, int y2)
{
  int dx, dy, ox, oy;
  int major, minor;
  int error, delta, step;
  int blocked;

  if (x2 - *x1 < 0)
    dx = 5;
  else if (x2 - *x1 > 0)
    dx = 4;
  else
    dx = -1;
  if (y2 - *y1 < 0)
    dy = 7;
  else if (y2 - *y1 > 0)
    dy = 6;
  else
    dy = -1;
  if (abs(x2 - *x1) > abs(y2 - *y1))
  {
    major = dx;
    minor = dy;
    step = abs(x2 - *x1);
    delta = 2 * abs(y2 - *y1);
  }
  else
  {
    major = dy;
    minor = dx;
    step = abs(y2 - *y1);
    delta = 2 * abs(x2 - *x1);
  }
  if (major == -1) /* x1,y2 already == x2,y2 */
    return;
  error = 0;
  do
  {
    ox = *x1;
    oy = *y1;
    *x1 += Dirs[0][major];
    *y1 += Dirs[1][major];
    error += delta;
    if (error > step)
    { /* don't need to check that minor >= 0 */
      *x1 += Dirs[0][minor];
      *y1 += Dirs[1][minor];
      error -= 2 * step;
    }
    blocked = !unblocked(*x1, *y1);
    if (error < 0 && (*x1 != x2 || *y1 != y2) && blocked)
    {
      *x1 -= Dirs[0][minor];
      *y1 -= Dirs[1][minor];
      error += 2 * step;
      blocked = !unblocked(*x1, *y1);
    }
    level->site[*x1][*y1].showchar = pyx;
    plotchar(pyx, *x1, *y1);
    plotspot(ox, oy, TRUE);
    usleep(50000);
  } while ((*x1 != x2 || *y1 != y2) && !blocked);
  plotspot(*x1, *y1, TRUE);
  levelrefresh();
}

/* This is the same as do_los, except we stop before hitting nonliving
obstructions */
void do_object_los(Symbol pyx, int* x1, int* y1, int x2, int y2)
{
  int dx, dy, ox, oy;
  int major, minor;
  int error, delta, step;
  int blocked;

  if (x2 - *x1 < 0)
    dx = 5;
  else if (x2 - *x1 > 0)
    dx = 4;
  else
    dx = -1;
  if (y2 - *y1 < 0)
    dy = 7;
  else if (y2 - *y1 > 0)
    dy = 6;
  else
    dy = -1;
  if (abs(x2 - *x1) > abs(y2 - *y1))
  {
    major = dx;
    minor = dy;
    step = abs(x2 - *x1);
    delta = 2 * abs(y2 - *y1);
  }
  else
  {
    major = dy;
    minor = dx;
    step = abs(y2 - *y1);
    delta = 2 * abs(x2 - *x1);
  }
  if (major == -1) /* x1,y2 already == x2,y2 */
    return;
  error = 0;
  do
  {
    ox = *x1;
    oy = *y1;
    *x1 += Dirs[0][major];
    *y1 += Dirs[1][major];
    error += delta;
    if (error > step)
    { /* don't need to check that minor >= 0 */
      *x1 += Dirs[0][minor];
      *y1 += Dirs[1][minor];
      error -= 2 * step;
    }
    blocked = !unblocked(*x1, *y1);
    if (error < 0 && (*x1 != x2 || *y1 != y2) && blocked)
    {
      *x1 -= Dirs[0][minor];
      *y1 -= Dirs[1][minor];
      error += 2 * step;
      blocked = !unblocked(*x1, *y1);
    }
    plotspot(ox, oy, TRUE);
    if (unblocked(*x1, *y1))
    {
      plotchar(pyx, *x1, *y1);
      level->site[*x1][*y1].showchar = pyx;
      usleep(50000);
    }
  } while ((*x1 != x2 || *y1 != y2) && !blocked);
  if (level->site[*x1][*y1].creature == NULL && blocked)
  {
    *x1 = ox;
    *y1 = oy;
  }
  plotspot(*x1, *y1, TRUE);
  levelrefresh();
}

/* los_p checks to see whether there is an unblocked los from x1,y1 to x2,y2 */
int los_p(int x1, int y1, int x2, int y2)
{
  int dx, dy;
  int major, minor;
  int error, delta, step;
  int blocked;

  if (x2 - x1 < 0)
    dx = 5;
  else if (x2 - x1 > 0)
    dx = 4;
  else
    dx = -1;
  if (y2 - y1 < 0)
    dy = 7;
  else if (y2 - y1 > 0)
    dy = 6;
  else
    dy = -1;
  if (abs(x2 - x1) > abs(y2 - y1))
  {
    major = dx;
    minor = dy;
    step = abs(x2 - x1);
    delta = 2 * abs(y2 - y1);
  }
  else
  {
    major = dy;
    minor = dx;
    step = abs(y2 - y1);
    delta = 2 * abs(x2 - x1);
  }
  if (major == -1) /* x1,y2 already == x2,y2 */
    return TRUE;
  error = 0;
  do
  {
    x1 += Dirs[0][major];
    y1 += Dirs[1][major];
    error += delta;
    if (error > step)
    { /* don't need to check that minor >= 0 */
      x1 += Dirs[0][minor];
      y1 += Dirs[1][minor];
      error -= 2 * step;
    }
    blocked = !unblocked(x1, y1);
    if (error < 0 && (x1 != x2 || y1 != y2) && blocked)
    {
      x1 -= Dirs[0][minor];
      y1 -= Dirs[1][minor];
      error += 2 * step;
      blocked = !unblocked(x1, y1);
    }
  } while ((x1 != x2 || y1 != y2) && !blocked);
  return ((x1 == x2) && (y1 == y2));
}

/* view_los_p sees through monsters */
int view_los_p(int x1, int y1, int x2, int y2)
{
  int dx, dy;
  int major, minor;
  int error, delta, step;
  int blocked;

  if (x2 - x1 < 0)
    dx = 5;
  else if (x2 - x1 > 0)
    dx = 4;
  else
    dx = -1;
  if (y2 - y1 < 0)
    dy = 7;
  else if (y2 - y1 > 0)
    dy = 6;
  else
    dy = -1;
  if (abs(x2 - x1) > abs(y2 - y1))
  {
    major = dx;
    minor = dy;
    step = abs(x2 - x1);
    delta = 2 * abs(y2 - y1);
  }
  else
  {
    major = dy;
    minor = dx;
    step = abs(y2 - y1);
    delta = 2 * abs(x2 - x1);
  }
  if (major == -1) /* x1,y2 already == x2,y2 */
    return TRUE;
  error = 0;
  do
  {
    x1 += Dirs[0][major];
    y1 += Dirs[1][major];
    error += delta;
    if (error > step)
    {
      x1 += Dirs[0][minor];
      y1 += Dirs[1][minor];
      error -= 2 * step;
    }
    blocked = !view_unblocked(x1, y1);
    if (error < 0 && (x1 != x2 || y1 != y2) && blocked)
    {
      x1 -= Dirs[0][minor];
      y1 -= Dirs[1][minor];
      error += 2 * step;
      blocked = !view_unblocked(x1, y1);
    }
  } while ((x1 != x2 || y1 != y2) && !blocked);
  return ((x1 == x2) && (y1 == y2));
}

#ifndef MSDOS_SUPPORTED_ANTIQUE
/* returns the command direction from the index into Dirs */
char inversedir(int dirindex)
{
  switch (dirindex)
  {
  case 0:
    return ('n');
  case 1:
    return ('u');
  case 2:
    return ('b');
  case 3:
    return ('y');
  case 4:
    return ('l');
  case 5:
    return ('h');
  case 6:
    return ('j');
  case 7:
    return ('k');
  default:
    return ('\0');
  }
}
#endif

long calc_points()
{
  int i;
  long points = 0;

  if (gamestatusp(SPOKE_TO_DRUID))
    points += 50;
  if (gamestatusp(COMPLETED_CAVES))
    points += 100;
  if (gamestatusp(COMPLETED_SEWERS))
    points += 200;
  if (gamestatusp(COMPLETED_CASTLE))
    points += 300;
  if (gamestatusp(COMPLETED_ASTRAL))
    points += 400;
  if (gamestatusp(COMPLETED_VOLCANO))
    points += 500;
  if (gamestatusp(KILLED_DRAGONLORD))
    points += 100;
  if (gamestatusp(KILLED_EATER))
    points += 100;
  if (gamestatusp(KILLED_LAWBRINGER))
    points += 100;

  points += player.xp / 50;

  points += player.cash / 500;

  for (i = 0; i < MAXITEMS; i++)
    if (player.possessions[i] != NULL)
      points += player.possessions[i]->level * (player.possessions[i]->known + 1);

  for (i = 0; i < MAXPACK; i++)
    if (player.pack[i] != NULL)
      points += player.pack[i]->level * (player.pack[i]->known + 1);

  for (i = 0; i < NUMRANKS; i++)
  {
    if (player.rank[i] == 5)
      points += 500;
    else
      points += 20 * player.rank[i];
  }

  if (player.hp < 1)
    points = (points / 2);

  else if (player.rank[ADEPT])
    points *= 10;

  return (points);
}

/* returns the 24 hour clock hour */
int hour()
{
  return ((int)(((Time + 720) / 60) % 24));
}

/* returns 0, 10, 20, 30, 40, or 50 */
int showminute()
{
  return ((int)((Time % 60) / 10) * 10);
}

/* returns the 12 hour clock hour */
int showhour()
{
  int showtime;
  if ((hour() == 0) || (hour() == 12))
    showtime = 12;
  else
    showtime = (hour() % 12);
  return (showtime);
}

/* nighttime is defined from 9 PM to 6AM */
int nighttime()
{
  return ((hour() > 20) || (hour() < 7));
}

char *getarticle(char* str)
{
  if ((str[0] == 'a') || (str[0] == 'A') ||
      (str[0] == 'e') || (str[0] == 'E') ||
      (str[0] == 'i') || (str[0] == 'I') ||
      (str[0] == 'o') || (str[0] == 'O') ||
      (str[0] == 'u') || (str[0] == 'U') ||
      (((str[0] == 'h') || (str[0] == 'H')) &&
       ((str[1] == 'i') || (str[1] == 'e'))))
    return ("an ");
  else
    return ("a ");
}

int day()
{
  return ((Date % 30) + 1);
}

char *ordinal(int number)
{
  if ((number == 11) || (number == 12) || (number == 13))
    return ("th");
  else
    switch (number % 10)
    {
    case 1:
      return ("st");
    case 2:
      return ("nd");
    case 3:
      return ("rd");
    default:
      return ("th");
    }
}

char *month()
{
  switch ((Date % 360) / 30)
  {
  case 0:
    return ("Freeze");
  case 1:
    return ("Ice");
  case 2:
    return ("Mud");
  case 3:
    return ("Storm");
  case 4:
    return ("Breeze");
  case 5:
    return ("Light");
  case 6:
    return ("Flame");
  case 7:
    return ("Broil");
  case 8:
    return ("Cool");
  case 9:
    return ("Haunt");
  case 10:
    return ("Chill");
  case 11:
    return ("Dark");
  case 12:
    return ("Twixt");
  default:
    return ("***Error***");
  }
}

/* WDT: code for the following two functions contributed by Sheldon 
 * Simms. */
/* finds floor space on level with buildaux not equal to baux,
sets x,y there. There must *be* floor space somewhere on level.... */
int spaceok(int i, int j, int baux)
{
  return ((level->site[i][j].locchar == FLOOR) &&
          (level->site[i][j].creature == NULL) &&
          (!loc_statusp(i, j, SECRET)) &&
          (level->site[i][j].buildaux != baux));
}

void findspace(int *x, int *y, int baux)
{
  int i, j, tog = TRUE, done = FALSE;

  do
  {
    i = random_range(WIDTH);
    j = random_range(LENGTH);
    if (spaceok(i, j, baux))
    {
      done = TRUE;
    }
    else
    {
      if (tog)
      {
        tog = !tog;
        while (1)
        {
          i++;
          if (i >= WIDTH)
            break;
          else if (spaceok(i, j, baux))
          {
            done = TRUE;
            break;
          }
        }
      }
      else
      {
        tog = !tog;
        while (1)
        {
          j++;
          if (j >= LENGTH)
            break;
          else if (spaceok(i, j, baux))
          {
            done = TRUE;
            break;
          }
        }
      }
    }
  } while (!done);
  *x = i;
  *y = j;
}

/* is prefix a prefix of s? */
int strprefix(char* prefix, char* s)
{
  int i = 0, matched = TRUE;
  if (strlen(prefix) > strlen(s))
    return (FALSE);
  else
  {
    while (matched && (i < strlen(prefix)))
    {
      matched = (prefix[i] == s[i]);
      i++;
    }
    return (matched);
  }
}

int confirmation()
{
  switch (random_range(4))
  {
  case 0:
    mprint("Are you sure? [yn] ");
    break;
  case 1:
    mprint("Certain about that? [yn] ");
    break;
  case 2:
    mprint("Do you really mean it? [yn] ");
    break;
  case 3:
    mprint("Confirm that, would you? [yn] ");
    break;
  }
  return (ynq() == 'y');
}

/* is character c a member of string s */
int strmem(char c, char *s)
{
  int i, found = FALSE;
  for (i = 0; ((i < strlen(s)) && (!found)); i++)
    found = (s[i] == c);
  return (found);
}

void calc_weight()
{
  int i, weight = 0;

  for (i = 1; i < MAXITEMS; i++)
    if (player.possessions[i] != NULL)
      weight += player.possessions[i]->weight *
                player.possessions[i]->number;
  if ((player.possessions[O_WEAPON_HAND] != NULL) &&
      (player.possessions[O_READY_HAND] == player.possessions[O_WEAPON_HAND]))
    weight -= player.possessions[O_READY_HAND]->weight *
              player.possessions[O_READY_HAND]->number;
  for (i = 0; i < MAXPACK; i++)
    if (player.pack[i] != NULL)
      weight += player.pack[i]->weight *
                player.pack[i]->number;
  player.itemweight = weight;
  dataprint();
}

/* returns true if its ok to get rid of a level */
int ok_to_free(Level* level)
{
  if (level == NULL)
    return (FALSE);
  else
    return ((level->environment != E_CITY) &&
            (level->environment != E_VILLAGE) &&
            (level->environment != Current_Dungeon));
}
Monster* Monster::create(){
  return new Monster;
}
Objectlist* Objectlist::create(){
  return new Objectlist;
}
void Objectlist::free(){
  auto pobjlist = this;
  Objectlist* tmp;
  while (pobjlist)
  {
    delete pobjlist->thing;
    tmp = pobjlist;
    pobjlist = pobjlist->next;
    delete tmp;
  }
}

Monsterlist* Monsterlist::create(){
  return new Monsterlist;
}
void Monsterlist::free(){
  Monsterlist* tmp;
  auto mlist = this;
  while (mlist)
  {
    mlist->m->possessions->free();
    tmp = mlist;
    delete tmp->m;
    mlist = mlist->next;
    delete tmp;
  }
}
  Level* Level::create(){
    return new Level;
  }
  void Level::free()
  {
    int i, j;
    auto level = this;
    level->mlist->free();
    for (i = 0; i < MAXWIDTH; i++)
    {
      for (j = 0; j < MAXLENGTH; j++)
      {
        if (level->site[i][j].things)
        {
          level->site[i][j].things->free();
          level->site[i][j].things = NULL;
        }
      }
    }
#ifndef SAVE_LEVELS
    delete level;
#endif
  }



/* alloc just enough string space for str, strcpy, and return pointer */
char *salloc(char* str)
{
  char *s = new char [strlen(str) + 1];
  strcpy(s, str);
  return (s);
}

#ifdef MSDOS
/* ****Moved here from another file**** */
/* reads a string from a file. If it is a line with more than 80 char's,
   then remainder of line to \n is consumed */
void filescanstring(fd, fstr)
    FILE *fd;
char *fstr;
{
  int i = -1;
  int byte = 'x';
  while ((i < 80) && (byte != '\n') && (byte != EOF))
  {
    i++;
    byte = fgetc(fd);
    fstr[i] = byte;
  }
  if (byte != '\n')
    while ((byte != '\n') && (byte != EOF))
      byte = fgetc(fd);
  fstr[i] = 0;
}
#endif

#ifdef MSDOS_SUPPORTED_ANTIQUE
/* ****Moved here from another file**** */
/* returns a "level of difficulty" based on current environment
   and depth in dungeon. Is somewhat arbitrary. value between 1 and 10.
   May not actually represent real difficulty, but instead level
   of items, monsters encountered.    */
int difficulty()
{
  int depth = 1;
  if (Level != NULL)
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

char cryptkey(char* fname)
{
  int pos, key = 0;

  for (pos = 0; fname[pos]; pos++)
    key += 3 * (fname[pos] - ' ');
  return (key & 0xff);
}

int game_uid;
int user_uid;

void init_perms()
{
#if (defined(BSD) || defined(SYSV)) && !defined(__DJGPP__)
  user_uid = getuid();
  game_uid = geteuid();
#endif
}

/*
#ifdef BSD
void setreuid(int, int);
#endif
*/

void change_to_user_perms()
{
#if (defined(BSD) || defined(SYSV)) && !defined(__EMX__) && !defined(__DJGPP__)
#ifdef BSD
  setreuid(game_uid, user_uid);
#else  /* SYSV */
  seteuid(user_uid);
#endif /* BSD */
#endif /* BSD || SYSV */
}

void change_to_game_perms()
{
#if (defined(BSD) || defined(SYSV)) && !defined(__EMX__) && !defined(__DJGPP__)
#ifdef BSD
  setreuid(user_uid, game_uid);
#else  /* SYSV */
  seteuid(game_uid);
#endif /* BSD */
#endif /* BSD || SYSV */
}

#ifdef NO_USLEEP
void usleep(int usecs)
{
  fd_set null;
  struct timeval timeout;

  FD_ZERO(&null);
  timeout.tv_usec = usecs;
  timeout.tv_sec = 0;
  select(0, &null, &null, &null, &timeout);
}
#endif
