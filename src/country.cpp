/* omega copyright (C) by Laurence Raphael Brothers, 1987,1988,1989 */
/* country.c */
/* load_country(), and all load_ functions for places which are */
/* accessible from the country and don't have their own files */

#include "glob.h"

/* loads the countryside level from the data file */
void load_country()
{
	int i, j;
	unsigned char site;

	FILE *fd;

	strcpy(Str3, Omegalib);
	strcat(Str3, "country.dat");
	fd = checkfopen(Str3, "rb");
	site = cryptkey("country.dat");

	for (j = 0; j < LENGTH; j++)
	{
		for (i = 0; i < WIDTH; i++)
		{
			site = getc(fd) ^ site;
			Country[i][j].aux = 0;
			Country[i][j].status = 0;
			switch (site)
			{
			case (PASS & 0xff):
				Country[i][j].base_terrain_type = PASS;
				Country[i][j].current_terrain_type = MOUNTAINS;
				break;
			case (CASTLE & 0xff):
				Country[i][j].base_terrain_type = CASTLE;
				Country[i][j].current_terrain_type = MOUNTAINS;
				break;
			case (STARPEAK & 0xff):
				Country[i][j].base_terrain_type = STARPEAK;
				Country[i][j].current_terrain_type = MOUNTAINS;
				break;
			case (CAVES & 0xff):
				Country[i][j].base_terrain_type = CAVES;
				Country[i][j].current_terrain_type = MOUNTAINS;
				break;
			case (VOLCANO & 0xff):
				Country[i][j].base_terrain_type = VOLCANO;
				Country[i][j].current_terrain_type = MOUNTAINS;
				break;
			case (DRAGONLAIR & 0xff):
				Country[i][j].base_terrain_type = DRAGONLAIR;
				Country[i][j].current_terrain_type = DESERT;
				break;
			case (MAGIC_ISLE & 0xff):
				Country[i][j].base_terrain_type = MAGIC_ISLE;
				Country[i][j].current_terrain_type = CHAOS_SEA;
				break;
			case ('W'):
				Country[i][j].base_terrain_type = WEREWOLF_DEN;
				Country[i][j].current_terrain_type = PLAINS;
				break;
			case 'a':
			case 'b':
			case 'c':
			case 'd':
			case 'e':
			case 'f':
				Country[i][j].current_terrain_type =
						Country[i][j].base_terrain_type = VILLAGE;
				Country[i][j].aux = 1 + site - 'a';
				break;
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
				Country[i][j].current_terrain_type =
						Country[i][j].base_terrain_type = TEMPLE;
				Country[i][j].aux = site - '0';
				break;
			case (PLAINS & 0xff):
				Country[i][j].current_terrain_type =
						Country[i][j].base_terrain_type = PLAINS;
				break;
			case (TUNDRA & 0xff):
				Country[i][j].current_terrain_type =
						Country[i][j].base_terrain_type = TUNDRA;
				break;
			case (ROAD & 0xff):
				Country[i][j].current_terrain_type =
						Country[i][j].base_terrain_type = ROAD;
				break;
			case (MOUNTAINS & 0xff):
				Country[i][j].current_terrain_type =
						Country[i][j].base_terrain_type = MOUNTAINS;
				break;
			case (RIVER & 0xff):
				Country[i][j].current_terrain_type =
						Country[i][j].base_terrain_type = RIVER;
				break;
			case (CITY & 0xff):
				Country[i][j].current_terrain_type =
						Country[i][j].base_terrain_type = CITY;
				break;
			case (FOREST & 0xff):
				Country[i][j].current_terrain_type =
						Country[i][j].base_terrain_type = FOREST;
				break;
			case (JUNGLE & 0xff):
				Country[i][j].current_terrain_type =
						Country[i][j].base_terrain_type = JUNGLE;
				break;
			case (SWAMP & 0xff):
				Country[i][j].current_terrain_type =
						Country[i][j].base_terrain_type = SWAMP;
				break;
			case (DESERT & 0xff):
				Country[i][j].current_terrain_type =
						Country[i][j].base_terrain_type = DESERT;
				break;
			case (CHAOS_SEA & 0xff):
				Country[i][j].current_terrain_type =
						Country[i][j].base_terrain_type = CHAOS_SEA;
				break;
			}
		}
		site = getc(fd) ^ site;
	}
	fclose(fd);
}

/* loads the dragon's lair into Level*/
void load_dlair(int empty, int populate)
{
	int i, j;
	char site;

	FILE *fd;

	if (empty)
	{
		mprint("The Lair is now devoid of inhabitants and treasure.");
		morewait();
	}

	if (!populate)
		empty = TRUE;
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
	level->environment = E_DLAIR;
	strcpy(Str3, Omegalib);
	strcat(Str3, "dlair.dat");
	fd = checkfopen(Str3, "rb");
	site = cryptkey("dlair.dat");
	for (j = 0; j < LENGTH; j++)
	{
		for (i = 0; i < WIDTH; i++)
		{
			level->site[i][j].lstatus = 0;
			if (i < 48)
				level->site[i][j].roomnumber = RS_CAVERN;
			else
				level->site[i][j].roomnumber = RS_DRAGONLORD;
			level->site[i][j].p_locf = L_NO_OP;
			site = getc(fd) ^ site;
			switch (site)
			{
			case 'D':
				level->site[i][j].locchar = FLOOR;
				if (!empty)
				{
					make_site_monster(i, j, DRAGON_LORD);
					level->site[i][j].creature->specialf = M_SP_LAIR;
				}
				break;
			case 'd':
				level->site[i][j].locchar = FLOOR;
				if (!empty)
				{
					make_site_monster(i, j, DRAGON); /* elite dragons, actually */
					level->site[i][j].creature->specialf = M_SP_LAIR;
					level->site[i][j].creature->hit *= 2;
					level->site[i][j].creature->dmg *= 2;
				}
				break;
			case 'W':
				level->site[i][j].locchar = FLOOR;
				if (!empty)
					make_site_monster(i, j, KING_WYV);
				break;
			case 'M':
				level->site[i][j].locchar = FLOOR;
				if (!empty)
					make_site_monster(i, j, RANDOM);
				break;
			case 'S':
				level->site[i][j].locchar = FLOOR;
				level->site[i][j].showchar = WALL;
				if (!empty)
					lset(i, j, SECRET);
				level->site[i][j].roomnumber = RS_SECRETPASSAGE;
				break;
			case '$':
				level->site[i][j].locchar = FLOOR;
				if (!empty)
					make_site_treasure(i, j, 10);
				break;
			case 's':
				level->site[i][j].locchar = FLOOR;
				level->site[i][j].p_locf = L_TRAP_SIREN;
				break;
			case '7':
				if (!empty)
					level->site[i][j].locchar = PORTCULLIS;
				else
					level->site[i][j].locchar = FLOOR;
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
				if (!empty)
					level->site[i][j].p_locf = L_PORTCULLIS_TRAP;
				break;
			case 'X':
				level->site[i][j].locchar = FLOOR;
				level->site[i][j].p_locf = L_TACTICAL_EXIT;
				break;
			case '#':
				level->site[i][j].locchar = WALL;
				level->site[i][j].aux = 150;
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

/* loads the star peak into Level*/
void load_speak(int empty, int populate)
{
	int i, j, safe = player.alignment > 0;
	char site;

	FILE *fd;

	if (empty)
	{
		mprint("The peak is now devoid of inhabitants and treasure.");
		morewait();
	}

	if (!populate)
		empty = TRUE;

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
	level->environment = E_STARPEAK;
	strcpy(Str3, Omegalib);
	strcat(Str3, "speak.dat");
	fd = checkfopen(Str3, "rb");
	site = cryptkey("speak.dat");
	for (j = 0; j < LENGTH; j++)
	{
		for (i = 0; i < WIDTH; i++)
		{
			level->site[i][j].lstatus = 0;
			level->site[i][j].roomnumber = RS_STARPEAK;
			level->site[i][j].p_locf = L_NO_OP;
			site = getc(fd) ^ site;
			switch (site)
			{
			case 'S':
				level->site[i][j].locchar = FLOOR;
				level->site[i][j].showchar = WALL;
				lset(i, j, SECRET);
				level->site[i][j].roomnumber = RS_SECRETPASSAGE;
				break;
			case 'L':
				level->site[i][j].locchar = FLOOR;
				if (!empty)
				{
					make_site_monster(i, j, LAWBRINGER);
					if (safe)
						m_status_reset(level->site[i][j].creature, HOSTILE);
				}
				break;
			case 's':
				level->site[i][j].locchar = FLOOR;
				if (!empty)
				{
					make_site_monster(i, j, SERV_LAW); /* servant of law */
					if (safe)
						m_status_reset(level->site[i][j].creature, HOSTILE);
				}
				break;
			case 'M':
				level->site[i][j].locchar = FLOOR;
				if (!empty)
				{
					make_site_monster(i, j, -1);
					if (safe)
						m_status_reset(level->site[i][j].creature, HOSTILE);
				}
				break;
			case '$':
				level->site[i][j].locchar = FLOOR;
				if (!empty)
					make_site_treasure(i, j, 10);
				break;
			case '7':
				if (!empty)
					level->site[i][j].locchar = PORTCULLIS;
				else
					level->site[i][j].locchar = FLOOR;
				level->site[i][j].p_locf = L_PORTCULLIS;
				break;
			case 'R':
				level->site[i][j].locchar = FLOOR;
				level->site[i][j].p_locf = L_RAISE_PORTCULLIS;
				break;
			case '-':
				level->site[i][j].locchar = CLOSED_DOOR;
				break;
			case '|':
				level->site[i][j].locchar = OPEN_DOOR;
				break;
			case 'p':
				level->site[i][j].locchar = FLOOR;
				level->site[i][j].p_locf = L_PORTCULLIS;
				break;
			case 'T':
				level->site[i][j].locchar = FLOOR;
				if (!empty)
					level->site[i][j].p_locf = L_PORTCULLIS_TRAP;
				break;
			case 'X':
				level->site[i][j].locchar = FLOOR;
				level->site[i][j].p_locf = L_TACTICAL_EXIT;
				break;
			case '#':
				level->site[i][j].locchar = WALL;
				level->site[i][j].aux = 150;
				break;
			case '4':
				level->site[i][j].locchar = RUBBLE;
				level->site[i][j].p_locf = L_RUBBLE;
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

/* loads the magic isle into Level*/
void load_misle(int empty, int populate)
{
	int i, j;
	char site;

	FILE *fd;

	if (empty)
	{
		mprint("The isle is now devoid of inhabitants and treasure.");
		morewait();
	}

	if (!populate)
		empty = TRUE;

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
	level->environment = E_MAGIC_ISLE;
	strcpy(Str3, Omegalib);
	strcat(Str3, "misle.dat");
	fd = checkfopen(Str3, "rb");
	site = cryptkey("misle.dat");
	for (j = 0; j < LENGTH; j++)
	{
		for (i = 0; i < WIDTH; i++)
		{
			level->site[i][j].lstatus = 0;
			level->site[i][j].roomnumber = RS_MAGIC_ISLE;
			level->site[i][j].p_locf = L_NO_OP;
			site = getc(fd) ^ site;
			switch (site)
			{
			case 'E':
				level->site[i][j].locchar = FLOOR;
				if (!empty)
					make_site_monster(i, j, EATER); /* eater of magic */
				break;
			case 'm':
				level->site[i][j].locchar = FLOOR;
				if (!empty)
					make_site_monster(i, j, MIL_PRIEST); /* militant priest */
				break;
			case 'n':
				level->site[i][j].locchar = FLOOR;
				if (!empty)
					make_site_monster(i, j, NAZGUL);
				break;
			case 'X':
				level->site[i][j].locchar = FLOOR;
				level->site[i][j].p_locf = L_TACTICAL_EXIT;
				break;
			case '#':
				level->site[i][j].locchar = WALL;
				level->site[i][j].aux = 150;
				break;
			case '4':
				level->site[i][j].locchar = RUBBLE;
				level->site[i][j].p_locf = L_RUBBLE;
				break;
			case '~':
				level->site[i][j].locchar = WATER;
				level->site[i][j].p_locf = L_CHAOS;
				break;
			case '=':
				level->site[i][j].locchar = WATER;
				level->site[i][j].p_locf = L_MAGIC_POOL;
				break;
			case '-':
				level->site[i][j].locchar = CLOSED_DOOR;
				break;
			case '|':
				level->site[i][j].locchar = OPEN_DOOR;
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

/* loads the magic isle into Level*/
void load_werewolf_den(int empty, int populate)
{
	int i, j;
	char site;

	FILE *fd;

	if (empty)
	{
		mprint("The isle is now devoid of inhabitants and treasure.");
		morewait();
	}

	if (!populate)
		empty = TRUE;

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
	level->environment = E_WEREWOLF_DEN;
	strcpy(Str3, Omegalib);
	strcat(Str3, "wereden.dat");
	fd = checkfopen(Str3, "rb");
	site = cryptkey("wereden.dat");
	for (j = 0; j < LENGTH; j++)
	{
		for (i = 0; i < WIDTH; i++)
		{
			level->site[i][j].lstatus = 0;
			lset(i, j, SEEN);
			level->site[i][j].roomnumber = RS_MAGIC_ISLE;
			level->site[i][j].p_locf = L_NO_OP;
			site = getc(fd) ^ site;
			switch (site)
			{
			case 'E':
				level->site[i][j].locchar = FLOOR;
				if (!empty)
					make_site_monster(i, j, EATER); /* eater of magic */
				break;
			case 'm':
				level->site[i][j].locchar = FLOOR;
				if (!empty)
					make_site_monster(i, j, MIL_PRIEST); /* militant priest */
				break;
			case 'n':
				level->site[i][j].locchar = FLOOR;
				if (!empty)
					make_site_monster(i, j, NAZGUL);
				break;
			case 'X':
				level->site[i][j].locchar = FLOOR;
				level->site[i][j].p_locf = L_TACTICAL_EXIT;
				break;
			case '#':
				level->site[i][j].locchar = WALL;
				level->site[i][j].aux = 150;
				break;
			case '4':
				level->site[i][j].locchar = RUBBLE;
				level->site[i][j].p_locf = L_RUBBLE;
				break;
			case '~':
				level->site[i][j].locchar = WATER;
				level->site[i][j].p_locf = L_CHAOS;
				break;
			case '=':
				level->site[i][j].locchar = WATER;
				level->site[i][j].p_locf = L_MAGIC_POOL;
				break;
			case '-':
				level->site[i][j].locchar = CLOSED_DOOR;
				break;
			case '|':
				level->site[i][j].locchar = OPEN_DOOR;
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

/* loads a temple into Level*/
void load_temple(int deity, int populate)
{
	int i, j;
	char site;
	Monsterlist* ml;
	FILE *fd;

	/* WDT HACK: I don't know why this is wrong.  Shrug.  David Givens
   * suggested removing it, and he has more experience with Omega
   * than I, so... */
	/*  initrand(Current_Environment, deity); */ /* FIXED! 12/30/98 */
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
	level->environment = E_TEMPLE;
	strcpy(Str3, Omegalib);
	strcat(Str3, "temple.dat");
	fd = checkfopen(Str3, "rb");
	site = cryptkey("temple.dat");
	for (j = 0; j < LENGTH; j++)
	{
		for (i = 0; i < WIDTH; i++)
		{
			switch (deity)
			{
			case ODIN:
				level->site[i][j].roomnumber = RS_ODIN;
				break;
			case SET:
				level->site[i][j].roomnumber = RS_SET;
				break;
			case HECATE:
				level->site[i][j].roomnumber = RS_HECATE;
				break;
			case ATHENA:
				level->site[i][j].roomnumber = RS_ATHENA;
				break;
			case DRUID:
				level->site[i][j].roomnumber = RS_DRUID;
				break;
			case DESTINY:
				level->site[i][j].roomnumber = RS_DESTINY;
				break;
			}
			site = getc(fd) ^ site;
			switch (site)
			{
			case '8':
				level->site[i][j].locchar = ALTAR;
				level->site[i][j].p_locf = L_ALTAR;
				level->site[i][j].aux = deity;
				break;
			case 'H':
				level->site[i][j].locchar = FLOOR;
				if (populate && (!player.patron ||
												 strcmp(player.name, Priest[player.patron]) ||
												 player.rank[PRIESTHOOD] != HIGHPRIEST))
					make_high_priest(i, j, deity);
				break;
			case 'S':
				level->site[i][j].locchar = FLOOR;
				if (!player.patron ||
						strcmp(player.name, Priest[player.patron]) ||
						player.rank[PRIESTHOOD] != HIGHPRIEST)
					lset(i, j, SECRET);
				break;
			case 'W':
				level->site[i][j].locchar = FLOOR;
				if (deity != player.patron && deity != DRUID)
					level->site[i][j].p_locf = L_TEMPLE_WARNING;
				break;
			case 'm':
				level->site[i][j].locchar = FLOOR;
				if (populate)
					make_site_monster(i, j, MIL_PRIEST); /* militant priest */
				break;
			case 'd':
				level->site[i][j].locchar = FLOOR;
				if (populate)
					make_site_monster(i, j, DOBERMAN); /* doberman death hound */
				break;
			case 'X':
				level->site[i][j].locchar = FLOOR;
				level->site[i][j].p_locf = L_TACTICAL_EXIT;
				break;
			case '#':
				if (deity != DRUID)
				{
					level->site[i][j].locchar = WALL;
					level->site[i][j].aux = 150;
				}
				else
				{
					level->site[i][j].locchar = HEDGE;
					level->site[i][j].p_locf = L_HEDGE;
				}
				break;
			case '.':
				level->site[i][j].locchar = FLOOR;
				break;
			case 'x':
				level->site[i][j].locchar = FLOOR;
				random_temple_site(i, j, deity, populate);
				break;
			case '?':
				if (deity != DESTINY)
					level->site[i][j].locchar = FLOOR;
				else
				{
					level->site[i][j].locchar = ABYSS;
					level->site[i][j].p_locf = L_ADEPT;
				}
				break;
			case '-':
				level->site[i][j].locchar = CLOSED_DOOR;
				break;
			case '|':
				level->site[i][j].locchar = OPEN_DOOR;
				break;
			}
		}
		site = getc(fd) ^ site;
	}
	/* Main Temple is peaceful for player of same sect,druids always peaceful. */
	if ((player.patron == deity) || (deity == DRUID))
		for (ml = level->mlist; ml != NULL; ml = ml->next)
			m_status_reset(ml->m, HOSTILE);
	fclose(fd);
	/*  initrand(-2, 0); */ /* FIXED! 12/30/98 */
}

void random_temple_site(int i, int j, int deity, int populate)
{
	switch (random_range(12))
	{
	case 0:
		if (populate)
			make_site_monster(i, j, MEND_PRIEST);
		break; /* mendicant priest */
	case 1:
		level->site[i][j].locchar = WATER;
		level->site[i][j].p_locf = L_MAGIC_POOL;
	case 2:
		if (populate)
			make_site_monster(i, j, INNER_DEMON);
		break; /* inner circle demon */
	case 3:
		if (populate)
			make_site_monster(i, j, ANGEL);
		break; /* angel of apropriate sect */
	case 4:
		if (populate)
			make_site_monster(i, j, HIGH_ANGEL);
		break; /* high angel of apropriate sect */
	case 5:
		if (populate)
			make_site_monster(i, j, ARCHANGEL);
		break; /* archangel of apropriate sect */
	}
}

void make_high_priest(int i, int j, int deity)
{
	Monsterlist* ml = Monsterlist::create();
	pmt m = ((pmt)checkmalloc(sizeof(montype)));
	make_hiscore_npc(m, deity);
	m->x = i;
	m->y = j;
	level->site[i][j].creature = m;
	ml->m = m;
	ml->next = level->mlist;
	level->mlist = ml;
}
