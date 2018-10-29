/* omega copyright (C) by Laurence Raphael Brothers, 1987,1988,1989 */
/* house.c */
/* some functions to make the house levels */

#include "glob.h"

/* loads the house level into Level*/
void load_house(int kind, int populate)
{
      int i, j;
      char site;
      int stops;

      FILE *fd;

      tempLevel = level;
      initrand(Current_Environment, player.x + player.y + hour() * 10);
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
      strcpy(Str3, Omegalib);
      switch (kind)
      {
      case E_HOUSE:
            strcat(Str3, "home1.dat");
            level->environment = E_HOUSE;
            site = cryptkey("home1.dat");
            break;
      case E_MANSION:
            strcat(Str3, "home2.dat");
            level->environment = E_MANSION;
            site = cryptkey("home2.dat");
            break;
      default:
      case E_HOVEL:
            strcat(Str3, "home3.dat");
            level->environment = E_HOVEL;
            site = cryptkey("home3.dat");
            break;
      }
      fd = checkfopen(Str3, "rb");
      stops = 0;
      for (j = 0; j < LENGTH; j++)
      {
            for (i = 0; i < WIDTH; i++)
            {
                  if (kind == E_HOVEL)
                        level->site[i][j].lstatus = SEEN;
                  else
                        level->site[i][j].lstatus = 0;
                  level->site[i][j].roomnumber = RS_CORRIDOR;
                  level->site[i][j].p_locf = L_NO_OP;
                  site = getc(fd) ^ site;
                  switch (site)
                  {
                  case 'N':
                        level->site[i][j].locchar = FLOOR;
                        level->site[i][j].roomnumber = RS_BEDROOM;
                        if (random_range(2) && populate)
                              make_house_npc(i, j);
                        break;
                  case 'H':
                        level->site[i][j].locchar = FLOOR;
                        level->site[i][j].roomnumber = RS_BEDROOM;
                        if (random_range(2) && populate)
                              make_mansion_npc(i, j);
                        break;
                  case 'D':
                        level->site[i][j].locchar = FLOOR;
                        level->site[i][j].roomnumber = RS_DININGROOM;
                        break;
                  case '.':
                        level->site[i][j].locchar = FLOOR;
                        if (stops)
                        {
                              lset(i, j, STOPS);
                              stops = 0;
                        }
                        break;
                  case 'c':
                        level->site[i][j].locchar = FLOOR;
                        level->site[i][j].roomnumber = RS_CLOSET;
                        break;
                  case 'G':
                        level->site[i][j].locchar = FLOOR;
                        level->site[i][j].roomnumber = RS_BATHROOM;
                        break;
                  case 'B':
                        level->site[i][j].locchar = FLOOR;
                        level->site[i][j].roomnumber = RS_BEDROOM;
                        break;
                  case 'K':
                        level->site[i][j].locchar = FLOOR;
                        level->site[i][j].roomnumber = RS_KITCHEN;
                        break;
                  case 'S':
                        level->site[i][j].locchar = FLOOR;
                        level->site[i][j].showchar = WALL;
                        lset(i, j, SECRET);
                        level->site[i][j].roomnumber = RS_SECRETPASSAGE;
                        break;
                  case '3':
                        level->site[i][j].locchar = SAFE;
                        level->site[i][j].showchar = WALL;
                        lset(i, j, SECRET);
                        level->site[i][j].p_locf = L_SAFE;
                        break;
                  case '^':
                        level->site[i][j].locchar = FLOOR;
                        level->site[i][j].p_locf = TRAP_BASE + random_range(NUMTRAPS);
                        break;
                  case 'P':
                        level->site[i][j].locchar = PORTCULLIS;
                        level->site[i][j].p_locf = L_PORTCULLIS;
                        break;
                  case 'R':
                        level->site[i][j].locchar = FLOOR;
                        level->site[i][j].p_locf = L_RAISE_PORTCULLIS;
                        break;
                  case 'p':
                        level->site[i][j].locchar = FLOOR;
                        level->site[i][j].p_locf = L_PORTCULLIS;
                        break;
                  case 'T':
                        level->site[i][j].locchar = FLOOR;
                        level->site[i][j].p_locf = L_PORTCULLIS_TRAP;
                        break;
                  case 'X':
                        level->site[i][j].locchar = FLOOR;
                        level->site[i][j].p_locf = L_HOUSE_EXIT;
                        stops = 1;
                        break;
                  case '#':
                        level->site[i][j].locchar = WALL;
                        switch (kind)
                        {
                        case E_HOVEL:
                              level->site[i][j].aux = 10;
                              break;
                        case E_HOUSE:
                              level->site[i][j].aux = 50;
                              break;
                        case E_MANSION:
                              level->site[i][j].aux = 150;
                              break;
                        }
                        break;
                  case '|':
                        level->site[i][j].locchar = OPEN_DOOR;
                        level->site[i][j].roomnumber = RS_CORRIDOR;
                        lset(i, j, STOPS);
                        break;
                  case '+':
                        level->site[i][j].locchar = CLOSED_DOOR;
                        level->site[i][j].roomnumber = RS_CORRIDOR;
                        level->site[i][j].aux = LOCKED;
                        lset(i, j, STOPS);
                        break;
                  case 'd':
                        level->site[i][j].locchar = FLOOR;
                        level->site[i][j].roomnumber = RS_CORRIDOR;
                        if (populate)
                              make_site_monster(i, j, DOBERMAN);
                        break;
                  case 'a':
                        level->site[i][j].locchar = FLOOR;
                        level->site[i][j].roomnumber = RS_CORRIDOR;
                        level->site[i][j].p_locf = L_TRAP_SIREN;
                        break;
                  case 'A':
                        level->site[i][j].locchar = FLOOR;
                        level->site[i][j].roomnumber = RS_CORRIDOR;
                        if (populate)
                              make_site_monster(i, j, AUTO_MINOR); /* automaton */
                        break;
                  }
                  level->site[i][j].showchar = ' ';
            }
            site = getc(fd) ^ site;
      }
      fclose(fd);
      initrand(E_RESTORE, 0);
}

/* makes a log npc for houses and hovels */
void make_house_npc(int i, int j)
{
      Monsterlist* ml = ((Monsterlist*)checkmalloc(sizeof(Monsterlist)));
      Object* ob;
      ml->m = ((pmt)checkmalloc(sizeof(montype)));
      *(ml->m) = Monsters[NPC];
      make_log_npc(ml->m);
      if (ml->m->id == NPC)
            mprint("You detect signs of life in this house.");
      else
            mprint("An eerie shiver runs down your spine as you enter....");
      /* if not == NPC, then we got a ghost off the npc list */
      ml->m->x = i;
      ml->m->y = j;
      level->site[i][j].creature = ml->m;
      ml->m->click = (Tick + 1) % 50;
      ml->next = level->mlist;
      level->mlist = ml;
      m_status_set(ml->m, HOSTILE);
      if (nighttime())
            m_status_reset(ml->m, AWAKE);
      else
            m_status_set(ml->m, AWAKE);
      if (ml->m->startthing > -1)
      {
            ob = ((Object*)checkmalloc(sizeof(Object)));
            *ob = Objects[ml->m->startthing];
            m_pickup(ml->m, ob);
      }
}

/* makes a hiscore npc for mansions */
void make_mansion_npc(int i, int j)
{
      Monsterlist* ml = ((Monsterlist*)checkmalloc(sizeof(Monsterlist)));
      ml->m = ((pmt)checkmalloc(sizeof(montype)));
      *(ml->m) = Monsters[NPC];
      make_hiscore_npc(ml->m, random_range(14) + 1);
      mprint("You detect signs of life in this house.");
      ml->m->x = i;
      ml->m->y = j;
      level->site[i][j].creature = ml->m;
      ml->m->click = (Tick + 1) % 50;
      ml->next = level->mlist;
      level->mlist = ml;
      m_status_set(ml->m, HOSTILE);
      if (nighttime())
            m_status_reset(ml->m, AWAKE);
      else
            m_status_set(ml->m, AWAKE);
}
