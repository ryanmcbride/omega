/* omega copyright (c) 1987,1988,1989 by Laurence Raphael Brothers */
/* env.c */
/* some load_* routines for special environments */

#include "glob.h"

/* loads the arena level into Level*/
void load_arena()
{
  int i, j;
  char site;
  pob box = ((pob)checkmalloc(sizeof(objtype)));
  FILE *fd;

  *box = Objects[THINGID + 0];

  tempLevel = level;
  if (ok_to_free(tempLevel))
  {
#ifndef SAVE_LEVELS
    free_level(tempLevel);
#endif
    tempLevel = NULL;
  }
#ifndef SAVE_LEVELS
  level = ((Level*)checkmalloc(sizeof(Level)));
#else
  msdos_changelevel(TempLevel, 0, -1);
  Level = &TheLevel;
#endif
  clear_level(level);
  level->environment = E_ARENA;
  strcpy(Str3, Omegalib);
  strcat(Str3, "arena.dat");
  fd = checkfopen(Str3, "rb");
  site = cryptkey("arena.dat");
  for (j = 0; j < LENGTH; j++)
  {
    for (i = 0; i < WIDTH; i++)
    {
      level->site[i][j].lstatus = SEEN + LIT;
      level->site[i][j].roomnumber = RS_ARENA;
      site = getc(fd) ^ site;
      level->site[i][j].p_locf = L_NO_OP;
      switch (site)
      {
      case 'P':
        level->site[i][j].locchar = PORTCULLIS;
        level->site[i][j].p_locf = L_PORTCULLIS;
        break;
      case 'X':
        level->site[i][j].locchar = FLOOR;
        level->site[i][j].p_locf = L_ARENA_EXIT;
        break;
      case '#':
        level->site[i][j].locchar = WALL;
        break;
      case '.':
        level->site[i][j].locchar = FLOOR;
        break;
      }
      level->site[i][j].showchar = level->site[i][j].locchar;
    }
    site = getc(fd) ^ site;
  }
  fclose(fd);
  level->site[60][7].creature = Arena_Monster;
  Arena_Monster->x = 60;
  Arena_Monster->y = 7;
  Arena_Monster->sense = 50;
  m_pickup(Arena_Monster, box);
  m_status_set(Arena_Monster, AWAKE);
  level->mlist = (Monsterlist*)checkmalloc(sizeof(Monsterlist));
  level->mlist->m = Arena_Monster;
  level->mlist->next = NULL;
  /* hehehehe cackled the dungeon master.... */
  print2("Your opponent holds the only way you can leave!");
  Arena_Monster->hp += Arena_Monster->level * 10;
  Arena_Monster->hit += Arena_Monster->hit;
  Arena_Monster->dmg += Arena_Monster->dmg / 2;
}

/* loads the sorcereror's circle into Level*/
void load_circle(int populate)
{
  int i, j;
  int safe = (player.rank[CIRCLE] > 0);
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
#ifndef SAVE_LEVELS
  level = ((Level*)checkmalloc(sizeof(Level)));
#else
  msdos_changelevel(TempLevel, 0, -1);
  Level = &TheLevel;
#endif
  clear_level(level);
  level->environment = E_CIRCLE;
  strcpy(Str3, Omegalib);
  strcat(Str3, "circle.dat");
  fd = checkfopen(Str3, "rb");
  site = cryptkey("circle.dat");
  for (j = 0; j < LENGTH; j++)
  {
    for (i = 0; i < WIDTH; i++)
    {
      level->site[i][j].lstatus = 0;
      level->site[i][j].roomnumber = RS_CIRCLE;
      level->site[i][j].p_locf = L_NO_OP;
      site = getc(fd) ^ site;
      switch (site)
      {
      case 'P':
        level->site[i][j].locchar = FLOOR;
        if (populate)
        {
          make_prime(i, j); /* prime sorceror */
          level->site[i][j].creature->specialf = M_SP_PRIME;
          if (!safe)
            m_status_set(level->site[i][j].creature, HOSTILE);
        }
        break;
      case 'D':
        level->site[i][j].locchar = FLOOR;
        if (populate)
        {
          make_site_monster(i, j, DEMON_PRINCE); /* prime circle demon */
          if (safe)
            m_status_reset(level->site[i][j].creature, HOSTILE);
          level->site[i][j].creature->specialf = M_SP_COURT;
        }
        break;
      case 's':
        level->site[i][j].locchar = FLOOR;
        if (populate)
        {
          make_site_monster(i, j, SERV_CHAOS); /* servant of chaos */
          level->site[i][j].creature->specialf = M_SP_COURT;
          if (safe)
            m_status_reset(level->site[i][j].creature, HOSTILE);
        }
        break;
      case 'e':
        level->site[i][j].locchar = FLOOR;
        if (populate)
        {
          make_site_monster(i, j, ENCHANTOR); /* enchanter */
          level->site[i][j].creature->specialf = M_SP_COURT;
          if (safe)
            m_status_reset(level->site[i][j].creature, HOSTILE);
        }
        break;
      case 'n':
        level->site[i][j].locchar = FLOOR;
        if (populate)
        {
          make_site_monster(i, j, NECROMANCER); /* necromancer */
          level->site[i][j].creature->specialf = M_SP_COURT;
          if (safe)
            m_status_reset(level->site[i][j].creature, HOSTILE);
        }
        break;
      case 'T':
        level->site[i][j].locchar = FLOOR;
        if (populate)
        {
          make_site_monster(i, j, THAUMATURGIST); /* High Thaumaturgist */
          level->site[i][j].creature->specialf = M_SP_COURT;
          if (safe)
            m_status_reset(level->site[i][j].creature, HOSTILE);
        }
        break;
      case '#':
        level->site[i][j].locchar = WALL;
        level->site[i][j].aux = 1000;
        break;
      case 'L':
        level->site[i][j].locchar = FLOOR;
        level->site[i][j].p_locf = L_CIRCLE_LIBRARY;
        break;
      case '?':
        level->site[i][j].locchar = FLOOR;
        level->site[i][j].p_locf = L_TOME1;
        break;
      case '!':
        level->site[i][j].locchar = FLOOR;
        level->site[i][j].p_locf = L_TOME2;
        break;
      case 'S':
        level->site[i][j].locchar = FLOOR;
        lset(i, j, SECRET);
        break;
      case '.':
        level->site[i][j].locchar = FLOOR;
        break;
      case '-':
        level->site[i][j].locchar = CLOSED_DOOR;
        break;
      }
    }
    site = getc(fd) ^ site;
  }
  fclose(fd);
}

/* make the prime sorceror */
void make_prime(int i, int j)
{
  Monsterlist* ml = ((Monsterlist*)checkmalloc(sizeof(Monsterlist)));
  pmt m = ((pmt)checkmalloc(sizeof(montype)));
  pol ol;
  pob o;
  make_hiscore_npc(m, 10); /* 10 is index for prime */
  m->x = i;
  m->y = j;
  level->site[i][j].creature = m;
  ml->m = m;
  ml->next = level->mlist;
  level->mlist = ml;

  if (Objects[ARTIFACTID + 21].uniqueness != UNIQUE_TAKEN)
  {
    ol = ((pol)checkmalloc(sizeof(oltype)));
    o = ((pob)checkmalloc(sizeof(objtype)));
    *o = Objects[ARTIFACTID + 21];
    ol->thing = o;
    ol->next = NULL;
    m->possessions = ol;
  }
}

/* loads the court of the archmage into Level*/
void load_court(int populate)
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
#ifndef SAVE_LEVELS
  level = ((Level*)checkmalloc(sizeof(Level)));
#else
  msdos_changelevel(TempLevel, 0, -1);
  Level = &TheLevel;
#endif
  clear_level(level);
  level->environment = E_COURT;
  strcpy(Str3, Omegalib);
  strcat(Str3, "court.dat");
  fd = checkfopen(Str3, "rb");
  site = cryptkey("court.dat");
  for (j = 0; j < LENGTH; j++)
  {
    for (i = 0; i < WIDTH; i++)
    {
      level->site[i][j].lstatus = 0;
      level->site[i][j].roomnumber = RS_COURT;
      level->site[i][j].p_locf = L_NO_OP;
      site = getc(fd) ^ site;
      switch (site)
      {
      case '5':
        level->site[i][j].locchar = CHAIR;
        level->site[i][j].p_locf = L_THRONE;
        if (populate)
        {
          make_specific_treasure(i, j, ARTIFACTID + 22);
          make_archmage(i, j);
          m_status_reset(level->site[i][j].creature, HOSTILE);
          m_status_reset(level->site[i][j].creature, MOBILE);
        }
        break;
      case 'e':
        level->site[i][j].locchar = FLOOR;
        if (populate)
        {
          make_site_monster(i, j, ENCHANTOR); /* enchanter */
          m_status_reset(level->site[i][j].creature, HOSTILE);
          level->site[i][j].creature->specialf = M_SP_COURT;
        }
        break;
      case 'n':
        level->site[i][j].locchar = FLOOR;
        if (populate)
        {
          make_site_monster(i, j, NECROMANCER); /* necromancer */
          m_status_reset(level->site[i][j].creature, HOSTILE);
          level->site[i][j].creature->specialf = M_SP_COURT;
        }
        break;
      case 'T':
        level->site[i][j].locchar = FLOOR;
        if (populate)
        {
          make_site_monster(i, j, THAUMATURGIST); /* High Thaumaturgist */
          m_status_reset(level->site[i][j].creature, HOSTILE);
          level->site[i][j].creature->specialf = M_SP_COURT;
        }
        break;
      case '#':
        level->site[i][j].locchar = WALL;
        level->site[i][j].aux = 1000;
        break;
      case 'G':
        level->site[i][j].locchar = FLOOR;
        level->site[i][j].locchar = FLOOR;
        if (populate)
        {
          make_site_monster(i, j, GUARD); /* guard */
          m_status_reset(level->site[i][j].creature, HOSTILE);
        }
        break;
      case '<':
        level->site[i][j].locchar = STAIRS_UP;
        level->site[i][j].p_locf = L_ESCALATOR;
        break;
      case '.':
        level->site[i][j].locchar = FLOOR;
        break;
      }
    }
    site = getc(fd) ^ site;
  }
  fclose(fd);
}

/* make the archmage */
void make_archmage(int i, int j)
{
  Monsterlist* ml = ((Monsterlist*)checkmalloc(sizeof(Monsterlist)));
  pmt m = ((pmt)checkmalloc(sizeof(montype)));
  make_hiscore_npc(m, 9); /* 9 is index for archmage */
  m->x = i;
  m->y = j;
  level->site[i][j].creature = m;
  ml->m = m;
  ml->next = level->mlist;
  level->mlist = ml;
  m->specialf = M_SP_COURT;
}
