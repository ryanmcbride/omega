/* omega copyright (C) by Laurence Raphael Brothers, 1987,1988,1989 */
/* guild2.c */
/* L_ functions  */

/* These functions implement the various guilds. */
/* They are all l_ functions since they are basically activated*/
/* at some site or other. */

#include "glob.h"

void l_thieves_guild()
{
	int fee, count, i, number, done = FALSE, dues = 1000;
	char c, action;
	Object* lockpick;
	print1("You have penetrated to the Lair of the Thieves' Guild.");
	if (!nighttime())
		print2("There aren't any thieves around in the daytime.");
	else
	{
		if ((player.rank[THIEVES] == TMASTER) &&
				(player.level > Shadowlordlevel) &&
				find_and_remove_item(THINGID + 16, -1))
		{
			print2("You nicked the Justiciar's Badge!");
			morewait();
			print1("The Badge is put in a place of honor in the Guild Hall.");
			print2("You are now the Shadowlord of the Thieves' Guild!");
			morewait();
			print1("Who says there's no honor among thieves?");
			strcpy(Shadowlord, player.name);
			Shadowlordlevel = player.level;
			morewait();
			Shadowlordbehavior = fixnpc(4);
			save_hiscore_npc(7);
			clearmsg();
			print1("You learn the Spell of Shadowform.");
			Spells[S_SHADOWFORM].known = TRUE;
			morewait();
			clearmsg();
			player.rank[THIEVES] = SHADOWLORD;
			player.maxagi += 2;
			player.maxdex += 2;
			player.agi += 2;
			player.dex += 2;
		}
		while (!done)
		{
			menuclear();
			if (player.rank[THIEVES] == 0)
				menuprint("a: Join the Thieves' Guild.\n");
			else
				menuprint("b: Raise your Guild rank.\n");
			menuprint("c: Get an item identified.\n");
			if (player.rank[THIEVES] > 0)
				menuprint("d: Fence an item.\n");
			menuprint("ESCAPE: Leave this Den of Iniquity.");
			showmenu();
			action = mgetc();
			if (action == ESCAPE)
				done = TRUE;
			else if (action == 'a')
			{
				done = TRUE;
				if (player.rank[THIEVES] > 0)
					print2("You are already a member!");
				else if (player.alignment > 10)
					print2("You are too lawful to be a thief!");
				else
				{
					dues += dues * (12 - player.dex) / 9;
					dues += player.alignment * 5;
					dues = max(100, dues);
					clearmsg();
					mprint("Dues are");
					mnumprint(dues);
					mprint(" Au. Pay it? [yn] ");
					if (ynq1() == 'y')
					{
						if (player.cash < dues)
						{
							print1("You can't cheat the Thieves' Guild!");
							print2("... but the Thieves' Guild can cheat you....");
							player.cash = 0;
						}
						else
						{
							print1("Shadowlord ");
							nprint1(Shadowlord);
							print2("enters your name into the roll of the Guild.");
							morewait();
							clearmsg();
							print1("As a special bonus, you get a free lockpick.");
							print2("You are taught the spell of Object Detection.");
							morewait();
							Spells[S_OBJ_DET].known = TRUE;
							lockpick = Object::create("thieve's pick");
							gain_item(lockpick);
							player.cash -= dues;
							dataprint();
							player.guildxp[THIEVES] = 1;
							player.rank[THIEVES] = TMEMBER;
							player.maxdex++;
							player.dex++;
							player.agi++;
							player.maxagi++;
						}
					}
				}
			}
			else if (action == 'b')
			{
				if (player.rank[THIEVES] == 0)
					print2("You are not even a member!");
				else if (player.rank[THIEVES] == SHADOWLORD)
					print2("You can't get any higher than this!");
				else if (player.rank[THIEVES] == TMASTER)
				{
					if (player.level <= Shadowlordlevel)
						print2("You are not experienced enough to advance.");
					else
						print2("You must bring back the Justiciar's Badge!");
				}
				else if (player.rank[THIEVES] == THIEF)
				{
					if (player.guildxp[THIEVES] < 4000)
						print2("You are not experienced enough to advance.");
					else
					{
						print1("You are now a Master Thief of the Guild!");
						print2("You are taught the Spell of Apportation.");
						morewait();
						print1("To advance to the next level you must return with");
						print2("the badge of the Justiciar (cursed be his name).");
						morewait();
						clearmsg();
						print1("The Justiciar's office is just south of the gaol.");
						Spells[S_APPORT].known = TRUE;
						player.rank[THIEVES] = TMASTER;
						player.maxagi++;
						player.maxdex++;
						player.agi++;
						player.dex++;
					}
				}
				else if (player.rank[THIEVES] == ATHIEF)
				{
					if (player.guildxp[THIEVES] < 1500)
						print2("You are not experienced enough to advance.");
					else
					{
						print1("You are now a ranking Thief of the Guild!");
						print2("You learn the Spell of Invisibility.");
						Spells[S_INVISIBLE].known = TRUE;
						player.rank[THIEVES] = THIEF;
						player.agi++;
						player.maxagi++;
					}
				}
				else if (player.rank[THIEVES] == TMEMBER)
				{
					if (player.guildxp[THIEVES] < 400)
						print2("You are not experienced enough to advance.");
					else
					{
						print1("You are now an Apprentice Thief!");
						print2("You are taught the Spell of Levitation.");
						Spells[S_LEVITATE].known = TRUE;
						player.rank[THIEVES] = ATHIEF;
						player.dex++;
						player.maxdex++;
					}
				}
			}
			else if (action == 'c')
			{
				if (player.rank[THIEVES] == 0)
				{
					print1("RTG, Inc, Appraisers. Identification Fee: 50Au/item.");
					fee = 50;
				}
				else
				{
					fee = 5;
					print1("The fee is 5Au per item.");
				}
				print2("Identify one item, or all possessions? [ip] ");
				if ((char)mcigetc() == 'i')
				{
					if (player.cash < fee)
						print2("Try again when you have the cash.");
					else
					{
						player.cash -= fee;
						dataprint();
						identify(0);
					}
				}
				else
				{
					count = 0;
					for (i = 1; i < MAXITEMS; i++)
						if (player.possessions[i] != NULL)
							if (player.possessions[i]->known < 2)
								count++;
					for (i = 0; i < player.packptr; i++)
						if (player.pack[i] != NULL)
							if (player.pack[i]->known < 2)
								count++;
					clearmsg();
					print1("The fee will be: ");
					mnumprint(max(count * fee, fee));
					nprint1("Au. Pay it? [yn] ");
					if (ynq1() == 'y')
						if (player.cash < max(count * fee, fee))
							print2("Try again when you have the cash.");
						else
						{
							player.cash -= max(count * fee, fee);
							dataprint();
							identify(1);
						}
				}
			}
			else if (action == 'd')
			{
				if (player.rank[THIEVES] == 0)
					print2("Fence? Who said anything about a fence?");
				else
				{
					print1("Fence one item or go through pack? [ip] ");
					if ((char)mcigetc() == 'i')
					{
						i = getitem(NULL_ITEM);
						if ((i == ABORT) || (player.possessions[i] == NULL))
							print2("Huh, Is this some kind of set-up?");
						else if (player.possessions[i]->blessing < 0)
							print2("I don't want to buy a cursed item!");
						else
						{
							clearmsg();
							print1("I'll give you ");
							mlongprint(2 * item_value(player.possessions[i]) / 3);
							nprint1("Au each. OK? [yn] ");
							if (ynq1() == 'y')
							{
								number = getnumber(player.possessions[i]->number);
								if ((number >= player.possessions[i]->number) &&
										player.possessions[i]->used)
								{
									player.possessions[i]->used = FALSE;
									item_use(player.possessions[i]);
								}
								player.cash += number * 2 * item_value(player.possessions[i]) / 3;
								/* Fenced artifacts could turn up anywhere, really... */
								if (Objects[player.possessions[i]->id].uniqueness >
										UNIQUE_UNMADE)
									Objects[player.possessions[i]->id].uniqueness = UNIQUE_UNMADE;
								dispose_lost_objects(number, player.possessions[i]);
								dataprint();
							}
							else
								print2("Hey, gimme a break, it was a fair price!");
						}
					}
					else
					{
						for (i = 0; i < player.packptr; i++)
						{
							if (player.pack[i]->blessing > -1)
							{
								clearmsg();
								print1("Sell ");
								nprint1(itemid(player.pack[i]));
								nprint1(" for ");
								mlongprint(2 * item_value(player.pack[i]) / 3);
								nprint1("Au each? [ynq] ");
								if ((c = ynq1()) == 'y')
								{
									number = getnumber(player.pack[i]->number);
									player.cash += 2 * number * item_value(player.pack[i]) / 3;
									player.pack[i]->number -= number;
									if (player.pack[i]->number < 1)
									{
										/* Fenced an artifact?  You just might see it again. */
										if (Objects[player.pack[i]->id].uniqueness > UNIQUE_UNMADE)
											Objects[player.pack[i]->id].uniqueness = UNIQUE_UNMADE;
										delete player.pack[i];
										player.pack[i] = NULL;
									}
									dataprint();
								}
								else if (c == 'q')
									break;
							}
						}
						fixpack();
					}
				}
			}
		}
	}
	xredraw();
}

void l_college()
{
	char action;
	int done = FALSE, enrolled = FALSE;
	print1("The Collegium Magii. Founded 16937, AOF.");
	if (nighttime())
		print2("The Registration desk is closed at night....");
	else
	{
		while (!done)
		{
			if ((player.rank[COLLEGE] == MAGE) &&
					(player.level > Archmagelevel) &&
					find_and_remove_item(CORPSEID, EATER))
			{
				print1("You brought back the heart of the Eater of Magic!");
				morewait();
				print1("The Heart is sent to the labs for analysis.");
				print2("The Board of Trustees appoints you Archmage!");
				morewait();
				clearmsg();
				strcpy(Archmage, player.name);
				Archmagelevel = player.level;
				player.rank[COLLEGE] = ARCHMAGE;
				player.maxiq += 5;
				player.iq += 5;
				player.maxpow += 5;
				player.pow += 5;
				morewait();
				Archmagebehavior = fixnpc(4);
				save_hiscore_npc(9);
			}
			menuclear();
			menuprint("May we help you?\n\n");
			menuprint("a: Enroll in the College.\n");
			menuprint("b: Raise your College rank.\n");
			menuprint("c: Do spell research.\n");
			menuprint("ESCAPE: Leave these hallowed halls.\n");
			showmenu();
			action = mgetc();
			if (action == ESCAPE)
				done = TRUE;
			else if (action == 'a')
			{
				if (player.rank[COLLEGE] > 0)
					print2("You are already enrolled!");
				else if (player.iq < 13)
					print2("Your low IQ renders you incapable of being educated.");
				else if (player.rank[CIRCLE] > 0)
					print2("Sorcery and our Magic are rather incompatable, no?");
				else
				{
					if (player.iq > 17)
					{
						print2("You are given a scholarship!");
						morewait();
						enrolled = TRUE;
					}
					else
					{
						print1("Tuition is 1000Au. ");
						nprint1("Pay it? [yn] ");
						if (ynq1() == 'y')
						{
							if (player.cash < 1000)
								print2("You don't have the funds!");
							else
							{
								player.cash -= 1000;
								enrolled = TRUE;
								dataprint();
							}
						}
					}
					if (enrolled)
					{
						print1("Archmage ");
						nprint1(Archmage);
						nprint1(" greets you and congratulates you on your acceptance.");
						print2("You are now enrolled in the Collegium Magii!");
						morewait();
						print1("You are now a Novice.");
						print2("You may research 1 spell, for your intro class.");
						Spellsleft = 1;
						player.rank[COLLEGE] = INITIATE;
						player.guildxp[COLLEGE] = 1;
						player.maxiq += 1;
						player.iq += 1;
						player.maxpow += 1;
						player.pow += 1;
					}
				}
			}
			else if (action == 'b')
			{
				if (player.rank[COLLEGE] == 0)
					print2("You have not even been initiated, yet!");
				else if (player.rank[COLLEGE] == ARCHMAGE)
					print2("You are at the pinnacle of mastery in the Collegium.");
				else if (player.rank[COLLEGE] == MAGE)
				{
					if (player.level <= Archmagelevel)
						print2("You are not experienced enough to advance.");
					else
						print2("You must return with the heart of the Eater of Magic!");
				}
				else if (player.rank[COLLEGE] == PRECEPTOR)
				{
					if (player.guildxp[COLLEGE] < 4000)
						print2("You are not experienced enough to advance.");
					else
					{
						print1("You are now a Mage of the Collegium Magii!");
						print2("You may research 6 spells for postdoctoral research.");
						Spellsleft += 6;
						morewait();
						print1("To become Archmage, you must return with the");
						print2("heart of the Eater of Magic");
						morewait();
						clearmsg();
						print1("The Eater may be found on a desert isle somewhere.");
						player.rank[COLLEGE] = MAGE;
						player.maxiq += 2;
						player.iq += 2;
						player.maxpow += 2;
						player.pow += 2;
					}
				}
				else if (player.rank[COLLEGE] == STUDENT)
				{
					if (player.guildxp[COLLEGE] < 1500)
						print2("You are not experienced enough to advance.");
					else
					{
						print1("You are now a Preceptor of the Collegium Magii!");
						print2("You are taught the basics of ritual magic.");
						morewait();
						clearmsg();
						print1("Your position allows you to research 4 spells.");
						Spellsleft += 4;
						Spells[S_RITUAL].known = TRUE;
						player.rank[COLLEGE] = PRECEPTOR;
						player.maxiq += 1;
						player.iq += 1;
						player.maxpow += 1;
						player.pow += 1;
					}
				}
				else if (player.rank[COLLEGE] == NOVICE)
				{
					if (player.guildxp[COLLEGE] < 400)
						print2("You are not experienced enough to advance.");
					else
					{
						print1("You are now a Student at the Collegium Magii!");
						print2("You are taught the spell of identification.");
						morewait();
						clearmsg();
						print1("Thesis research credit is 2 spells.");
						Spellsleft += 2;
						Spells[S_IDENTIFY].known = TRUE;
						player.rank[COLLEGE] = STUDENT;
						player.maxiq += 1;
						player.iq += 1;
						player.maxpow += 1;
						player.pow += 1;
					}
				}
			}
			else if (action == 'c')
			{
				clearmsg();
				if (Spellsleft > 0)
				{
					print1("Research permitted: ");
					mnumprint(Spellsleft);
					nprint1(" Spells.");
					morewait();
				}
				if (Spellsleft < 1)
				{
					print1("Extracurricular Lab fee: 2000 Au. ");
					nprint1("Pay it? [yn] ");
					if (ynq1() == 'y')
					{
						if (player.cash < 2000)
							print1("Try again when you have the cash.");
						else
						{
							player.cash -= 2000;
							dataprint();
							Spellsleft = 1;
						}
					}
				}
				if (Spellsleft > 0)
				{
					learnspell(0);
					Spellsleft--;
				}
			}
		}
	}
	xredraw();
}

void l_sorcerors()
{
	char action;
	int done = FALSE, fee = 3000;
	long total;
	print1("The Circle of Sorcerors.");
	if (player.rank[CIRCLE] == -1)
	{
		print2("Fool! Didn't we tell you to go away?");
		player.mana = 0;
		dataprint();
	}
	else
		while (!done)
		{
			if ((player.rank[CIRCLE] == HIGHSORCEROR) &&
					(player.level > Primelevel) &&
					find_and_remove_item(CORPSEID, LAWBRINGER))
			{
				print2("You obtained the Crown of the Lawgiver!");
				morewait();
				print1("The Crown is ritually sacrificed to the Lords of Chaos.");
				print2("You are now the Prime Sorceror of the Inner Circle!");
				strcpy(Prime, player.name);
				Primelevel = player.level;
				morewait();
				Primebehavior = fixnpc(4);
				save_hiscore_npc(10);
				clearmsg();
				print1("You learn the Spell of Disintegration!");
				morewait();
				clearmsg();
				Spells[S_DISINTEGRATE].known = TRUE;
				player.rank[CIRCLE] = PRIME;
				player.maxpow += 10;
				player.pow += 10;
			}
			menuclear();
			menuprint("May we help you?\n\n");
			menuprint("a: Become an Initiate of the Circle.\n");
			menuprint("b: Raise your rank in the Circle.\n");
			menuprint("c: Restore mana points\n");
			menuprint("ESCAPE: Leave these Chambers of Power.\n");
			showmenu();
			action = mgetc();
			if (action == ESCAPE)
				done = TRUE;
			else if (action == 'a')
			{
				if (player.rank[CIRCLE] > 0)
					print2("You are already an initiate!");
				else if (player.alignment > 0)
					print2("You may not join -- you reek of Law!");
				else if (player.rank[COLLEGE] != 0)
					print2("Foolish Mage!  You don't have the right attitude to Power!");
				else
				{
					fee += player.alignment * 100;
					fee += fee * (12 - player.pow) / 9;
					fee = max(100, fee);
					clearmsg();
					mprint("For you, there is an initiation fee of");
					mnumprint(fee);
					mprint(" Au.");
					print2("Pay it? [yn] ");
					if (ynq2() == 'y')
					{
						if (player.cash < fee)
							print3("Try again when you have the cash!");
						else
						{
							print1("Prime Sorceror ");
							nprint1(Prime);
							print2("conducts your initiation into the circle of novices.");
							morewait();
							clearmsg();
							print1("You learn the Spell of Magic Missiles.");
							Spells[S_MISSILE].known = TRUE;
							player.cash -= fee;
							dataprint();
							player.rank[CIRCLE] = INITIATE;
							player.guildxp[CIRCLE] = 1;
							player.maxpow++;
							player.pow++;
						}
					}
				}
			}
			else if (action == 'b')
			{
				if (player.rank[CIRCLE] == 0)
					print2("You have not even been initiated, yet!");
				else if (player.alignment > -1)
				{
					print1("Ahh! You have grown too lawful!!!");
					print2("You are hereby blackballed from the Circle!");
					player.rank[CIRCLE] = -1;
					morewait();
					clearmsg();
					print1("A pox upon thee!");
					if (!player.immunity[INFECTION])
						player.status[DISEASED] += 100;
					print2("And a curse on your possessions!");
					morewait();
					clearmsg();
					acquire(-1);
					clearmsg();
					enchant(-1);
					bless(-1);
					print3("Die, false sorceror!");
					p_damage(25, UNSTOPPABLE, "a sorceror's curse");
					done = TRUE;
				}
				else if (player.rank[CIRCLE] == PRIME)
					print2("You are at the pinnacle of mastery in the Circle.");
				else if (player.rank[CIRCLE] == HIGHSORCEROR)
				{
					if (player.level <= Primelevel)
						print2("You are not experienced enough to advance.");
					else
						print2("You must return with the Crown of the LawBringer!");
				}
				else if (player.rank[CIRCLE] == SORCEROR)
				{
					if (player.guildxp[CIRCLE] < 4000)
						print2("You are not experienced enough to advance.");
					else
					{
						print1("You are now a High Sorceror of the Inner Circle!");
						print2("You learn the Spell of Disruption!");
						morewait();
						clearmsg();
						print1("To advance you must return with the LawBringer's Crown!");
						print2("The LawBringer resides on Star Peak.");
						Spells[S_DISRUPT].known = TRUE;
						player.rank[CIRCLE] = HIGHSORCEROR;
						player.maxpow += 5;
						player.pow += 5;
					}
				}
				else if (player.rank[CIRCLE] == ENCHANTER)
				{
					if (player.guildxp[CIRCLE] < 1500)
						print2("You are not experienced enough to advance.");
					else
					{
						print1("You are now a member of the Circle of Sorcerors!");
						print2("You learn the Spell of Ball Lightning!");
						Spells[S_LBALL].known = TRUE;
						player.rank[CIRCLE] = SORCEROR;
						player.maxpow += 2;
						player.pow += 2;
					}
				}
				else if (player.rank[CIRCLE] == INITIATE)
				{
					if (player.guildxp[CIRCLE] < 400)
						print2("You are not experienced enough to advance.");
					else
					{
						print1("You are now a member of the Circle of Enchanters!");
						print2("You learn the Spell of Firebolts.");
						Spells[S_FIREBOLT].known = TRUE;
						player.rank[CIRCLE] = ENCHANTER;
						player.maxpow += 2;
						player.pow += 2;
					}
				}
			}
			else if (action == 'c')
			{
				done = TRUE;
				fee = player.level * 100;
				if (player.rank[CIRCLE])
					fee = fee / 2;
				clearmsg();
				print1("That will be: ");
				mnumprint(fee);
				nprint1("Au. Pay it? [yn] ");
				if (ynq1() == 'y')
				{
					if (player.cash < fee)
						print2("Begone, deadbeat, or face the wrath of the Circle!");
					else
					{
						player.cash -= fee;
						total = calcmana();
						while (player.mana < total)
						{
							player.mana++;
							dataprint();
						}
						print2("Have a sorcerous day, now!");
					}
				}
				else
					print2("Be seeing you!");
			}
		}
	xredraw();
}

void l_order()
{
	Object* newitem;
	Monsterlist* ml;
	print1("The Headquarters of the Order of Paladins.");
	morewait();
	if ((player.rank[ORDER] == PALADIN) &&
			(player.level > Justiciarlevel) &&
			gamestatusp(GAVE_STARGEM) &&
			player.alignment > 300)
	{
		print1("You have succeeded in your quest!");
		morewait();
		print1("The previous Justiciar steps down in your favor.");
		print2("You are now the Justiciar of Rampart and the Order!");
		strcpy(Justiciar, player.name);
		for (ml = level->mlist; ml && (ml->m->id != HISCORE_NPC ||
																	 ml->m->aux2 != 15);
				 ml = ml->next)
			/* just scan for current Justicar */;
		if (ml)
		{
			level->site[ml->m->x][ml->m->y].creature = NULL;
			erase_monster(ml->m);
			ml->m->hp = -1; /* signals "death" -- no credit to player, though */
		}
		Justiciarlevel = player.level;
		morewait();
		Justiciarbehavior = fixnpc(4);
		save_hiscore_npc(15);
		clearmsg();
		print1("You are awarded a blessed shield of deflection!");
		morewait();
		newitem = Object::create("shield of deflection");
		newitem->blessing = 9;
		gain_item(newitem);
		morewait();
		player.rank[ORDER] = JUSTICIAR;
		player.maxstr += 5;
		player.str += 5;
		player.maxpow += 5;
		player.pow += 5;
	}
	if (player.alignment < 1)
	{
		if (player.rank[ORDER] > 0)
		{
			print1("You have been tainted by chaos!");
			print2("You are stripped of your rank in the Order!");
			morewait();
			player.rank[ORDER] = -1;
			send_to_jail();
		}
		else
			print1("Get thee hence, minion of chaos!");
	}
	else if (player.rank[ORDER] == -1)
		print1("Thee again?  Get thee hence, minion of chaos!");
	else if (player.rank[ORDER] == 0)
	{
		if (player.rank[ARENA] != 0)
			print1("We do not accept bloodstained gladiators into our Order.");
		else if (player.rank[LEGION] != 0)
			print1("Go back to your barracks, mercenary!");
		else
		{
			print1("Dost thou wish to join our Order? [yn] ");
			if (ynq1() == 'y')
			{
				print1("Justiciar ");
				nprint1(Justiciar);
				nprint1(" welcomes you to the Order.");
				print2("'Mayest thou always follow the sublime path of Law.'");
				morewait();
				print1("You are now a Gallant in the Order.");
				print2("You are given a horse and a blessed spear.");
				morewait();
				player.rank[ORDER] = GALLANT;
				player.guildxp[ORDER] = 1;
				setgamestatus(MOUNTED);
				newitem = Object::create("spear");
				newitem->blessing = 9;
				newitem->plus = 1;
				newitem->known = 2;
				gain_item(newitem);
			}
		}
	}
	else
	{
		print1("'Welcome back, Paladin.'");
		if (!gamestatusp(MOUNTED))
		{
			print2("You are given a new steed.");
			setgamestatus(MOUNTED);
		}
		morewait();
		clearmsg();
		if ((player.hp < player.maxhp) || (player.status[DISEASED]) ||
				(player.status[POISONED]))
			print1("Your wounds are treated by a medic.");
		cleanse(0);
		player.hp = player.maxhp;
		player.food = 40;
		print2("You get a hot meal from the refectory.");
		morewait();
		clearmsg();
		if (player.rank[ORDER] == PALADIN)
		{
			if (player.level <= Justiciarlevel)
				print2("You are not experienced enough to advance.");
			else if (player.alignment < 300)
				print2("You are not sufficiently Lawful as yet to advance.");
			else
				print2("You must give the Star Gem to the LawBringer.");
		}
		else if (player.rank[ORDER] == CHEVALIER)
		{
			if (player.guildxp[ORDER] < 4000)
				print2("You are not experienced enough to advance.");
			else if (player.alignment < 200)
				print2("You are not sufficiently Lawful as yet to advance.");
			else
			{
				print1("You are made a Paladin of the Order!");
				print2("You learn the Spell of Heroism and get Mithril Plate!");
				morewait();
				newitem = Object::create("mithril plate armor");
				newitem->blessing = 9;
				newitem->known = 2;
				gain_item(newitem);
				morewait();
				clearmsg();
				print1("To advance you must rescue the Star Gem and return it");
				print2("to its owner, the LawBringer, who resides on Star Peak.");
				morewait();
				print1("The Star Gem was stolen by the cursed Prime Sorceror,");
				print2("whose headquarters may be found beyond the Astral Plane.");
				morewait();
				print1("The Oracle will send you to the Astral Plane if you");
				print2("prove yourself worthy to her.");
				morewait();
				Spells[S_HERO].known = TRUE;
				player.rank[ORDER] = PALADIN;
			}
		}
		else if (player.rank[ORDER] == GUARDIAN)
		{
			if (player.guildxp[ORDER] < 1500)
				print2("You are not experienced enough to advance.");
			else if (player.alignment < 125)
				print2("You are not yet sufficiently Lawful to advance.");
			else
			{
				player.rank[ORDER] = CHEVALIER;
				print1("You are made a Chevalier of the Order!");
				print2("You are given a Mace of Disruption!");
				morewait();
				clearmsg();
				newitem = Object::create("mace of disruption");
				newitem->known = 2;
				gain_item(newitem);
			}
		}
		else if (player.rank[ORDER] == GALLANT)
		{
			if (player.guildxp[ORDER] < 400)
				print2("You are not experienced enough to advance.");
			else if (player.alignment < 50)
				print2("You are not Lawful enough to advance.");
			else
			{
				print1("You are made a Guardian of the Order of Paladins!");
				print2("You are given a Holy Hand Grenade (of Antioch).");
				morewait();
				print1("You hear a nasal monotone in the distance....");
				print2("'...and the number of thy counting shall be 3...'");
				morewait();
				clearmsg();
				player.rank[ORDER] = GUARDIAN;
				newitem = Object::create("Holy Hand-Grenade of Antioch");
				newitem->known = 2;
				gain_item(newitem);
			}
		}
	}
}
