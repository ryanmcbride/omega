/* omega copyright (C) by Laurence Raphael Brothers, 1987,1988,1989 */
/* site1.c */
/* 1st half of site functions and aux functions to them */

#ifndef MSDOS_SUPPORTED_ANTIQUE
#include <unistd.h>
#endif

#include "glob.h"

/* the bank; can be broken into (!) */
void l_bank()
{
	int done = FALSE, valid = FALSE;
	long amount;
	char response;
	char passwd[64];
	print1("First Bank of Omega: Autoteller Carrel.");

	if (gamestatusp(BANK_BROKEN))
		print2("You see a damaged autoteller.");
	else
	{
		print2("The proximity sensor activates the autoteller as you approach.");
		morewait();
		clearmsg();
		while (!done)
		{
			print1("Current Balance: ");
			mlongprint(Balance);
			nprint1("Au. ");
			nprint1(" Enter command (? for help) > ");
			response = mgetc();
			if (response == '?')
			{
				menuclear();
				menuprint("?: This List.\n");
				if (strcmp(Password, "") == 0)
					menuprint("O: Open an account.\n");
				else
				{
					menuprint("P: Enter password.\n");
					menuprint("D: Deposit.\n");
					menuprint("W: Withdraw\n");
				}
				menuprint("X: eXit\n");
				showmenu();
				morewait();
				xredraw();
				continue;
			}
			else if ((response == 'P') && (strcmp(Password, "") != 0))
			{
				clearmsg();
				print1("Password: ");
				strcpy(passwd, msgscanstring());
				valid = (strcmp(passwd, Password) == 0);
				if (!valid)
				{
					done = TRUE;
					menuclear();
					menuprint("Alert! Alert! Invalid Password!\n");
					menuprint("The police are being summoned!\n");
					menuprint("Please wait for the police to arrive....\n\n");
					menuprint("----Hit space bar to continue----\n");
					showmenu();
					response = menugetc();
					if (response == ' ')
					{
						player.alignment += 5;
						xredraw();
						print1("Ah ha! Trying to rob the bank, eh?");
						print2("Take him away, boys!");
						morewait();
						send_to_jail();
					}
					else
					{
						player.alignment -= 5;
						menuclear();
						sleep(4);
						menuprint("^@^@^@^@^@00AD1203BC0F0000FFFFFFFFFFFF\n");
						menuprint("Interrupt in _get_space. Illegal Character.\n");
						showmenu();
						sleep(4);
						menuprint("Aborting _police_alert.....\n");
						menuprint("Attempting reboot.....\n");
						showmenu();
						sleep(4);
						menuprint("Warning: Illegal shmop at _count_cash.\n");
						menuprint("Warning: Command Buffer NOT CLEARED\n");
						showmenu();
						sleep(4);
						menuprint("Reboot Complete. Execution Continuing.\n");
						menuprint("Withdrawing: 4294967297 Au.\n");
						menuprint("Warning: Arithmetic Overflow in _withdraw\n");
						showmenu();
						sleep(4);
						menuprint("Yo mama. Core dumped.\n");
						showmenu();
						sleep(4);
						xredraw();
						clearmsg();
						print1("The cash machine begins to spew gold pieces!");
						print2("You pick up your entire balance and then some!");
						player.cash += Balance + 1000 + random_range(3000);
						Balance = 0;
						setgamestatus(BANK_BROKEN);
					}
				}
				else
					print2("Password accepted. Working.");
			}
			else if ((response == 'D') && valid)
			{
				clearmsg();
				print1("Amount: ");
				amount = get_money(player.cash);
				if (amount < 1)
					print3("Transaction aborted.");
				else if (amount > player.cash)
					print3("Deposit too large -- transaction aborted.");
				else
				{
					print2("Transaction accomplished.");
					Balance += amount;
					player.cash -= amount;
				}
			}
			else if ((response == 'W') && valid)
			{
				clearmsg();
				print1("Amount: ");
				amount = get_money(Balance);
				if (amount < 1)
					print3("Transaction aborted.");
				else if (amount > Balance)
					print3("Withdrawal too large -- transaction aborted.");
				else
				{
					print2("Transaction accomplished.");
					Balance -= amount;
					player.cash += amount;
				}
			}
			else if (response == 'X')
			{
				clearmsg();
				print1("Bye!");
				done = TRUE;
			}
			else if ((response == 'O') && (strcmp(Password, "") == 0))
			{
				clearmsg();
				print1("Opening new account.");
				nprint1(" Please enter new password: ");
				strcpy(Password, msgscanstring());
				if (strcmp(Password, "") == 0)
				{
					print3("Illegal to use null password -- aborted.");
					done = TRUE;
				}
				else
				{
					print2("Password validated; account saved.");
					valid = TRUE;
				}
			}
			else
				print3(" Illegal command.");
			dataprint();
		}
	}
	xredraw();
}

void l_armorer()
{
	int done = FALSE;
	char action;
	if (hour() == 12)
		print3("Unfortunately, this is Julie's lunch hour -- try again later.");
	else if (nighttime())
		print3("It seems that Julie keeps regular business hours.");
	else
	{
		while (!done)
		{
			clearmsg();
			print1("Julie's: Buy Armor, Weapons, or Leave [a,w,ESCAPE] ");
			action = mgetc();
			if (action == ESCAPE)
				done = TRUE;
			else if (action == 'a')
				buyfromstock(ARMORID, 10);
			else if (action == 'w')
				buyfromstock(WEAPONID, 23);
		}
	}
	xredraw();
}

void buyfromstock(int base, int numitems)
{
	int i;
	char item;
	Object *newitem;

	print2("Purchase which item? [ESCAPE to quit] ");
	menuclear();
	for (i = 0; i < numitems; i++)
	{
		std::string str = " :";
		str[0] = i + 'a';
		str += Objects[base + i].objstr;
		menuprint(str);
		menuprint("\n");
	}
	showmenu();
	item = ' ';
	while ((item != ESCAPE) &&
		   ((item < 'a') || (item >= 'a' + numitems)))
		item = mgetc();
	if (item != ESCAPE)
	{
		i = item - 'a';
		newitem = Object::create();
		*newitem = Objects[base + i];
		newitem->known = 2;
		clearmsg();
		print1("I can let you have it for ");
		mlongprint(2 * true_item_value(newitem));
		nprint1("Au. Buy it? [yn] ");
		if (ynq1() == 'y')
		{
			if (player.cash < 2 * true_item_value(newitem))
			{
				print2("Why not try again some time you have the cash?");
				delete newitem;
			}
			else
			{
				player.cash -= 2 * true_item_value(newitem);
				dataprint();
				gain_item(newitem);
			}
		}
		else
			delete newitem;
	}
}

void l_club()
{
#define hinthour club_hinthour
	char response;

	print1("Rampart Explorers' Club.");
	if (!gamestatusp(CLUB_MEMBER))
	{
		if (player.level < 2)
			print3("Only reknowned adventurers need apply.");
		else
		{
			print2("Dues are 100Au. Pay it? [yn] ");
			if (ynq2() == 'y')
			{
				if (player.cash < 100)
					print3("Beat it, or we'll blackball you!");
				else
				{
					print1("Welcome to the club! You are taught the spell of Return.");
					print2("When cast on the first level of a dungeon it");
					morewait();
					clearmsg();
					print1("will transport you down to the lowest level");
					print2("you have explored, and vice versa.");
					Spells[S_RETURN].known = TRUE;
					player.cash -= 100;
					setgamestatus(CLUB_MEMBER);
				}
			}
			else
				print2("OK, but you're missing out on our benefits....");
		}
	}
	else
	{
		print2("Shop at the club store or listen for rumors [sl] ");
		do
			response = (char)mcigetc();
		while ((response != 's') && (response != 'l') && (response != ESCAPE));
		if (response == 'l')
		{
			if (hinthour == hour())
				print2("You don't hear anything useful.");
			else
			{
				print1("You overhear a conversation....");
				hint();
				hinthour = hour();
			}
		}
		else if (response == 's')
		{
			buyfromstock(THINGID + 7, 2);
			xredraw();
		}
		else if (response == ESCAPE)
			print2("Be seeing you, old chap!");
	}
}
#undef hinthour

void l_gym()
{
	int done = TRUE;
	int trained = 0;
	clearmsg();
	do
	{
		print1("The Rampart Gymnasium");
		if ((Gymcredit > 0) || (player.rank[ARENA]))
		{
			nprint1("-- Credit: ");
			mlongprint(Gymcredit);
			nprint1("Au.");
		}
		done = FALSE;
		menuclear();
		menuprint("Train for 2000 Au. Choose:\n");
		menuprint("\na: work out in the weight room");
		menuprint("\nb: use our gymnastics equipment");
		menuprint("\nc: take our new anaerobics course");
		menuprint("\nd: enroll in dance lessons.");
		menuprint("\nESCAPE: Leave this place.");
		showmenu();
		switch (mgetc())
		{
		case 'a':
			gymtrain(&(player.maxstr), &(player.str));
			break;
		case 'b':
			gymtrain(&(player.maxdex), &(player.dex));
			break;
		case 'c':
			gymtrain(&(player.maxcon), &(player.con));
			break;
		case 'd':
			gymtrain(&(player.maxagi), &(player.agi));
			break;
		case ESCAPE:
			clearmsg();
			if (trained == 0)
				print1("Well, it's your body you're depriving!");
			else if (trained < 3)
				print1("You towel yourself off, and find the exit.");
			else
				print1("A refreshing bath, and you're on your way.");
			done = TRUE;
			break;
		default:
			trained--;
			break;
		}
		trained++;
	} while (!done);
	xredraw();
	calc_melee();
}

void l_healer()
{
	print1("Rampart Healers. Member RMA.");
	morewait();
	clearmsg();
	print1("a: Heal injuries (50 crowns)");
	print2("b: Cure disease (250 crowns)");
	print3("ESCAPE: Leave these antiseptic alcoves.");
	switch ((char)mcigetc())
	{
	case 'a':
		healforpay();
		break;
	case 'b':
		cureforpay();
		break;
	default:
		print3("OK, but suppose you have Acute Satyriasis?");
		break;
	}
}

void statue_random(int x, int y)
{
	Object *item;
	int i, j;
	switch (random_range(difficulty() + 3) - 1)
	{
	default:
		l_statue_wake();
		break;
	case 0:
		print1("The statue crumbles with a clatter of gravel.");
		level->site[x][y].locchar = RUBBLE;
		level->site[x][y].p_locf = L_RUBBLE;
		plotspot(x, y, TRUE);
		lset(x, y, CHANGED);
		break;
	case 1:
		print1("The statue stoutly resists your attack.");
		break;
	case 2:
		print1("The statue crumbles with a clatter of gravel.");
		level->site[x][y].locchar = RUBBLE;
		level->site[x][y].p_locf = L_RUBBLE;
		plotspot(x, y, TRUE);
		lset(x, y, CHANGED);
		make_site_treasure(x, y, difficulty());
		break;
	case 3:
		print1("The statue hits you back!");
		p_damage(random_range(difficulty() * 5), UNSTOPPABLE, "a statue");
		break;
	case 4:
		print1("The statue looks slightly pained. It speaks:");
		morewait();
		clearmsg();
		hint();
		break;
	case 5:
		if ((Current_Environment == Current_Dungeon) ||
			(Current_Environment == E_CITY))
		{
			print1("You hear the whirr of some mechanism.");
			print2("The statue glides smoothly into the floor!");
			/* WDT HACK: I shouldn't be making this choice on a level
			 * where no stairs can be (or perhaps I should, and I should
			 * implement a bonus level!). */
			level->site[x][y].locchar = STAIRS_DOWN;
			level->site[x][y].p_locf = L_NO_OP;
			lset(x, y, CHANGED | STOPS);
		}
		break;
	case 6:
		print1("The statue was covered with contact cement!");
		print2("You can't move....");
		player.status[IMMOBILE] += random_range(6) + 2;
		break;
	case 7:
		print1("A strange radiation emanates from the statue!");
		dispel(-1);
		break;
	case 8: /* I think this is particularly evil. Heh heh. */
		if (player.possessions[O_WEAPON_HAND] != NULL)
		{
			print1("Your weapon sinks deeply into the statue and is sucked away!");
			item = player.possessions[O_WEAPON_HAND];
			conform_lost_object(player.possessions[O_WEAPON_HAND]);
			item->blessing = -1 - abs(item->blessing);
			drop_at(x, y, item);
		}
		break;
	case 9:
		print1("The statue extends an arm. Beams of light illuminate the level!");
		for (i = 0; i < WIDTH; i++)
			for (j = 0; j < LENGTH; j++)
			{
				lset(i, j, SEEN);
				if (loc_statusp(i, j, SECRET))
				{
					lreset(i, j, SECRET);
					lset(i, j, CHANGED);
				}
			}
		show_screen();
		break;
	}
}

void l_statue_wake()
{
	int i;
	int x = player.x, y = player.y;
	for (i = 0; i < 9; i++)
		wake_statue(x + Dirs[0][i], y + Dirs[1][i], TRUE);
}

void wake_statue(int x, int y, int first)
{
	int i;
	Monsterlist *tml;
	if (level->site[x][y].locchar == STATUE)
	{
		if (!first)
			mprint("Another statue awakens!");
		else
			mprint("A statue springs to life!");
		level->site[x][y].locchar = FLOOR;
		lset(x, y, CHANGED);
		tml = Monsterlist::create();
		tml->m =
			(level->site[x][y].creature = m_create(x, y, 0, difficulty() + 1));
		m_status_set(level->site[x][y].creature, HOSTILE);
		tml->next = level->mlist;
		level->mlist = tml;
		for (i = 0; i < 8; i++)
			wake_statue(x + Dirs[0][i], y + Dirs[1][i], FALSE);
	}
}

void l_casino()
{
	int i, done = FALSE, a, b, c, match;
	char response;
	print1("Rampart Mithril Nugget Casino.");
	if (random_range(10) == 1)
		print2("Casino closed due to Grand Jury investigation.");
	else
	{
		while (!done)
		{
			morewait();
			clearmsg();
			print1("a: Drop 100Au in the slots.");
			print2("b: Risk 1000Au  at roulette.");
			print3("ESCAPE: Leave this green baize hall.");
			response = (char)mcigetc();
			if (response == 'a')
			{
				if (player.cash < 100)
					print3("No credit, jerk.");
				else
				{
					player.cash -= 100;
					dataprint();
					for (i = 0; i < 20; i++)
					{
						if (i == 19)
							sleep(1);
						else
							usleep(250000);
						a = random_range(10);
						b = random_range(10);
						c = random_range(10);
						clearmsg1();
						mprint(slotstr(a));
						mprint(slotstr(b));
						mprint(slotstr(c));
					}
					if (winnings > 0)
						do
						{
							a = random_range(10);
							b = random_range(10);
							c = random_range(10);
						} while ((a == b) || (a == c) || (b == c));
					else
					{
						a = random_range(10);
						b = random_range(10);
						c = random_range(10);
					}
					clearmsg();
					mprint(slotstr(a));
					mprint(slotstr(b));
					mprint(slotstr(c));
					if ((a == b) && (a == c))
					{
						print3("Jackpot Winner!");
						winnings += (a + 2) * (b + 2) * (c + 2) * 5;
						player.cash += (a + 2) * (b + 2) * (c + 2) * 5;
						dataprint();
					}
					else if (a == b)
					{
						print3("Winner!");
						player.cash += (a + 2) * (b + 2) * 5;
						dataprint();
						winnings += (a + 2) * (b + 2) * 5;
					}
					else if (a == c)
					{
						print3("Winner!");
						player.cash += (a + 2) * (c + 2) * 5;
						dataprint();
						winnings += (a + 2) * (c + 2) * 5;
					}
					else if (c == b)
					{
						print3("Winner!");
						player.cash += (c + 2) * (b + 2) * 5;
						dataprint();
						winnings += (c + 2) * (b + 2) * 5;
					}
					else
					{
						print3("Loser!");
						winnings -= 100;
					}
				}
			}
			else if (response == 'b')
			{
				if (player.cash < 1000)
					mprint("No credit, jerk.");
				else
				{
					player.cash -= 1000;
					dataprint();
					print1("Red or Black? [rb]");
					do
						response = (char)mcigetc();
					while ((response != 'r') && (response != 'b'));
					match = (response == 'r' ? 0 : 1);
					for (i = 0; i < 20; i++)
					{
						if (i == 19)
							sleep(1);
						else
							usleep(250000);
						a = random_range(37);
						b = a % 2;
						if (a == 0)
							print1(" 0 ");
						else if (a == 1)
							print1(" 0 - 0 ");
						else
						{
							(b == 0) ? print1("Red ") : print1("Black ");
							mnumprint(a - 1);
						}
					}
					if (winnings > 0)
						do
						{
							a = random_range(37);
							b = a % 2;
						} while (b == match);
					else
					{
						a = random_range(37);
						b = a % 2;
					}
					if (a == 0)
						print1(" 0 ");
					else if (a == 1)
						print1(" 0 - 0 ");
					else
					{
						(b == 0) ? print1("Red ") : print1("Black ");
						mnumprint(a - 1);
					}
					if ((a > 1) && (b == match))
					{
						print3(" Winner!");
						winnings += 1000;
						player.cash += 2000;
						dataprint();
					}
					else
					{
						print3(" Loser!");
						winnings -= 1000;
						dataprint();
					}
				}
			}
			else if (response == ESCAPE)
				done = TRUE;
		}
	}
}

void l_commandant()
{
	int num;
	Object *food;
	print1("Commandant Sonder's Rampart-fried Lyzzard partes. Open 24 hrs.");
	print2("Buy a bucket! Only 5 Au. Make a purchase? [yn] ");
	if (ynq2() == 'y')
	{
		clearmsg();
		print1("How many? ");
		num = (int)parsenum();
		if (num < 1)
			print3("Cute. Real cute.");
		else if (num * 5 > player.cash)
			print3("No handouts here, mac!");
		else
		{
			player.cash -= num * 5;
			food = Object::create();
			*food = Objects[FOODID + 0]; /* food ration */
			food->number = num;
			if (num == 1)
				print2("There you go, mac! One Lyzzard Bucket, coming up.");
			else
				print2("A passel of Lyzzard Buckets, for your pleasure.");
			morewait();
			gain_item(food);
		}
	}
	else
		print2("Don't blame the Commandant if you starve!");
}

void l_diner()
{
	print1("The Rampart Diner. All you can eat, 25Au.");
	print2("Place an order? [yn] ");
	if (ynq2() == 'y')
	{
		if (player.cash < 25)
			mprint("TANSTAAFL! Now git!");
		else
		{
			player.cash -= 25;
			dataprint();
			player.food = 44;
			foodcheck();
		}
	}
}

void l_crap()
{
	print1("Les Crapeuleaux. (****) ");
	if ((hour() < 17) || (hour() > 23))
		print2("So sorry, we are closed 'til the morrow...");
	else
	{
		print2("May I take your order? [yn] ");
		if (ynq2() == 'y')
		{
			if (player.cash < 1000)
				print2("So sorry, you have not the funds for dinner.");
			else
			{
				print2("Hope you enjoyed your tres expensive meal, m'sieur...");
				player.cash -= 1000;
				dataprint();
				player.food += 8;
				foodcheck();
			}
		}
	}
}

void l_tavern()
{
#define hinthour tavern_hinthour
	char response;
	print1("The Centaur and Nymph -- J. Riley, prop.");
	if (nighttime())
	{
		menuclear();
		menuprint("Riley says: Whataya have?\n\n");
		menuprint("a: Pint of Riley's ultra-dark 1Au\n");
		menuprint("b: Shot of Tullimore Dew 10Au\n");
		menuprint("c: Round for the House. 100Au\n");
		menuprint("d: Bed and Breakfast. 25Au\n");
		menuprint("ESCAPE: Leave this comfortable haven.\n");
		showmenu();
		do
			response = (char)mcigetc();
		while ((response != 'a') &&
			   (response != 'b') &&
			   (response != 'c') &&
			   (response != 'd') &&
			   (response != ESCAPE));
		switch (response)
		{
		case 'a':
			if (player.cash < 1)
				print2("Aw hell, have one on me.");
			else
			{
				player.cash -= 1;
				dataprint();
				if (hinthour != hour())
				{
					if (random_range(3))
					{
						print1("You overhear a rumor...");
						hint();
					}
					else
						print1("You don't hear much of interest.");
					hinthour = hour();
				}
				else
					print1("You just hear the same conversations again.");
			}
			break;
		case 'b':
			if (player.cash < 10)
				print2("I don't serve the Dew on no tab, buddy!");
			else
			{
				player.cash -= 10;
				print1("Ahhhhh....");
				if (player.status[POISONED] || player.status[DISEASED])
					print2("Phew! That's, er, smooth stuff!");
				player.status[POISONED] = 0;
				player.status[DISEASED] = 0;
				showflags();
			}
			break;
		case 'c':
			if (player.cash < 100)
			{
				print1("Whatta feeb!");
				print2("Outta my establishment.... Now!");
				p_damage(random_range(20), UNSTOPPABLE, "Riley's right cross");
				morewait();
			}
			else
			{
				player.cash -= 100;
				dataprint();
				print1("'What a guy!'");
				morewait();
				print2("'Hey, thanks, fella.'");
				morewait();
				print3("'Make mine a double...'");
				morewait();
				clearmsg();
				switch (random_range(4))
				{
				case 0:
					print1("'You're a real pal. Say, have you heard.... ");
					hint();
					break;
				case 1:
					print1("A wandering priest of Dionysus blesses you...");
					if ((player.patron == ODIN) || (player.patron == ATHENA))
						player.alignment++;
					else if ((player.patron == HECATE) || (player.patron == SET))
						player.alignment--;
					else if (player.alignment > 0)
						player.alignment--;
					else
						player.alignment++;
					break;
				case 2:
					print1("A thirsty bard promises to put your name in a song!");
					gain_experience(20);
					break;
				case 3:
					print1("Riley draws you a shot of his 'special reserve'");
					print2("Drink it [yn]?");
					if (ynq2() == 'y')
					{
						if (player.con < random_range(20))
						{
							print1("<cough> Quite a kick!");
							print2("You feel a fiery warmth in your tummy....");
							player.con++;
							player.maxcon++;
						}
						else
							print2("You toss it back nonchalantly.");
					}
				}
			}
			break;
		case 'd':
			if (player.cash < 25)
				print2("Pay in advance, mac!");
			else
			{
				player.cash -= 25;
				print2("How about a shot o' the dew for a nightcap?");
				morewait();
				Time += (6 + random_range(4)) * 60;
				player.status[POISONED] = 0;
				player.status[DISEASED] = 0;
				player.food = 40;
				/* reduce temporary stat gains to max stat levels */
				toggle_item_use(TRUE);
				player.str = min(player.str, player.maxstr);
				player.con = min(player.con, player.maxcon);
				player.agi = min(player.agi, player.maxagi);
				player.dex = min(player.dex, player.maxdex);
				player.iq = min(player.iq, player.maxiq);
				player.pow = min(player.pow, player.maxpow);
				toggle_item_use(FALSE);
				timeprint();
				dataprint();
				showflags();
				print1("The next day.....");
				if (hour() > 10)
					print2("Oh my! You overslept!");
			}
			break;
		default:
			print2("So? Just looking? Go on!");
			break;
		}
	}
	else
		print2("The pub don't open til dark, fella.");
	xredraw();
}
#undef hinthour

void l_alchemist()
{
	int i, done = FALSE, mlevel;
	char response;
	Object *obj;
	print1("Ambrosias' Potions et cie.");
	if (nighttime())
		print2("Ambrosias doesn't seem to be in right now.");
	else
		while (!done)
		{
			morewait();
			clearmsg();
			print1("a: Sell monster components.");
			print2("b: Pay for transformation.");
			print3("ESCAPE: Leave this place.");
			response = (char)mcigetc();
			if (response == 'a')
			{
				clearmsg();
				done = TRUE;
				i = getitem(CORPSE);
				if ((i != ABORT) && (player.possessions[i] != NULL))
				{
					obj = player.possessions[i];
					if (Monsters[obj->charge].transformid == -1)
					{
						print1("I don't want such a thing.");
						if (obj->basevalue > 0)
							print2("You might be able to sell it to someone else, though.");
					}
					else
					{
						clearmsg();
						print1("I'll give you ");
						mnumprint(obj->basevalue / 3);
						nprint1("Au for it. Take it? [yn] ");
						if (ynq1() == 'y')
						{
							player.cash += (obj->basevalue / 3);
							conform_lost_objects(1, obj);
						}
						else
							print2("Well, keep the smelly old thing, then!");
					}
				}
				else
					print2("So nu?");
			}
			else if (response == 'b')
			{
				clearmsg();
				done = TRUE;
				i = getitem(CORPSE);
				if ((i != ABORT) && (player.possessions[i] != NULL))
				{
					obj = player.possessions[i];
					if (Monsters[obj->charge].transformid == -1)
						print1("Oy vey! You want me to transform such a thing?");
					else
					{
						mlevel = Monsters[obj->charge].level;
						print1("It'll cost you ");
						mnumprint(max(10, obj->basevalue * 2));
						nprint1("Au for the transformation. Pay it? [yn] ");
						if (ynq1() == 'y')
						{
							if (player.cash < max(10, obj->basevalue * 2))
								print2("You can't afford it!");
							else
							{
								print1("Voila! A tap of the Philosopher's Stone...");
								player.cash -= max(10, obj->basevalue * 2);
								*obj = Objects[Monsters[obj->charge].transformid];
								if ((obj->id >= STICKID) && (obj->id < STICKID + NUMSTICKS))
									obj->charge = 20;
								if (obj->plus == 0)
									obj->plus = mlevel;
								if (obj->blessing == 0)
									obj->blessing = 1;
							}
						}
						else
							print2("I don't need your business, anyhow.");
					}
				}
				else
					print2("So nu?");
			}
			else if (response == ESCAPE)
				done = TRUE;
		}
}

void l_dpw()
{
	print1("Rampart Department of Public Works.");
	if (Date - LastDay < 7)
		print2("G'wan! Get a job!");
	else if (player.cash < 100)
	{
		print2("Do you want to go on the dole? [yn] ");
		if (ynq2() == 'y')
		{
			print1("Well, ok, but spend it wisely.");
			morewait();
			print1("Please enter your name for our records:");
			strcpy(Str1, msgscanstring());
			if (Str1[0] >= 'a' && Str1[0] <= 'z')
				Str1[0] += 'A' - 'a';
			if (Str1[0] == '\0')
				print1("Maybe you should come back when you've learned to write.");
			else if (strcmp(player.name, Str1) != 0)
			{
				print3("Aha! Welfare Fraud! It's off to gaol for you, lout!");
				morewait();
				send_to_jail();
			}
			else
			{
				print2("Here's your handout, layabout!");
				LastDay = Date;
				player.cash = 99;
				dataprint();
			}
		}
	}
	else
		print2("You're too well off for us to help you!");
}

void l_library()
{
	char response;
	int studied = FALSE;
	int done = FALSE, fee = 1000;
	print1("Rampart Public Library.");
	if (nighttime())
		print2("CLOSED");
	else
	{
		morewait();
		print1("Library Research Fee: 1000Au.");
		if (player.maxiq < 18)
		{
			print2("The Rampart student aid system has arranged a grant!");
			morewait();
			clearmsg();
			print1("Your revised fee is: ");
			mnumprint(fee = max(50, 1000 - (18 - player.maxiq) * 125));
			nprint1("Au.");
		}
		morewait();
		while (!done)
		{
			print1("Pay the fee? [yn] ");
			if (ynq1() == 'y')
			{
				if (player.cash < fee)
				{
					print2("No payee, No studee.");
					done = TRUE;
				}
				else
				{
					player.cash -= fee;
					do
					{
						studied = TRUE;
						dataprint();
						menuclear();
						menuprint("Peruse a scroll:\n");
						menuprint("a: Omegan Theology\n");
						menuprint("b: Guide to Rampart\n");
						menuprint("c: High Magick\n");
						menuprint("d: Odd Uncatalogued Document\n");
						menuprint("e: Attempt Advanced Research\n");
						menuprint("ESCAPE: Leave this font of learning.\n");
						showmenu();
						response = (char)mcigetc();
						if (response == 'a')
						{
							print1("You unfurl an ancient, yellowing scroll...");
							morewait();
							theologyfile();
						}
						else if (response == 'b')
						{
							print1("You unroll a slick four-color document...");
							morewait();
							cityguidefile();
						}
						else if (response == 'c')
						{
							print1("This scroll is written in a strange magical script...");
							morewait();
							wishfile();
						}
						else if (response == 'd')
						{
							print1("You find a strange document, obviously misfiled");
							print2("under the heading 'acrylic fungus painting technique'");
							morewait();
							adeptfile();
						}
						else if (response == 'e')
						{
							if (random_range(30) > player.iq)
							{
								print2("You feel more knowledgeable!");
								player.iq++;
								player.maxiq++;
								dataprint();
								if (player.maxiq < 19 &&
									fee != max(50, 1000 - (18 - player.maxiq) * 125))
								{
									morewait();
									clearmsg();
									print1("Your revised fee is: ");
									mnumprint(fee = max(50, 1000 - (18 - player.maxiq) * 125));
									nprint1("Au.");
									morewait();
								}
							}
							else
							{
								clearmsg1();
								print1("You find advice in an ancient tome: ");
								morewait();
								hint();
								morewait();
							}
						}
						else if (response == ESCAPE)
						{
							done = TRUE;
							print1("That was an expensive browse...");
						}
						else
							studied = FALSE;
					} while (!studied);
				}
				xredraw();
			}
			else
			{
				done = TRUE;
				if (studied)
					print2("Come back anytime we're open, 7am to 8pm.");
				else
					print2("You philistine!");
			}
		}
	}
}

void l_pawn_shop()
{
	int i, j, k, limit, number, done = FALSE;
	char item, action;

	if (nighttime())
		print1("Shop Closed: Have a Nice (K)Night");
	else
	{
		limit = min(5, Date - Pawndate);
		Pawndate = Date;
		for (k = 0; k < limit; k++)
		{
			if (Pawnitems[0] != NULL)
			{
				if (Objects[Pawnitems[0]->id].uniqueness > UNIQUE_UNMADE)
					Objects[Pawnitems[0]->id].uniqueness = UNIQUE_UNMADE;
				/* could turn up anywhere, really :) */
				delete Pawnitems[0];
				Pawnitems[0] = NULL;
			}
			for (i = 0; i < PAWNITEMS - 1; i++)
				Pawnitems[i] = Pawnitems[i + 1];
			Pawnitems[PAWNITEMS - 1] = NULL;
			for (i = 0; i < PAWNITEMS; i++)
				if (Pawnitems[i] == NULL)
					do
					{
						if (Pawnitems[i] != NULL)
							delete Pawnitems[i];
						Pawnitems[i] = Object::create_object(5);
						Pawnitems[i]->known = 2;
					} while ((Pawnitems[i]->objchar == CASH) ||
							 (Pawnitems[i]->objchar == ARTIFACT) ||
							 (true_item_value(Pawnitems[i]) <= 0));
		}
		while (!done)
		{
			print1("Knight's Pawn Shop:");
			print2("Buy item, Sell item, sell Pack contents, Leave [b,s,p,ESCAPE] ");
			menuclear();
			for (i = 0; i < PAWNITEMS; i++)
				if (Pawnitems[i] != NULL)
				{
					std::string str = " :";
					str[0] = i + 'a';
					str += itemid(Pawnitems[i]);
					menuprint(str);
					menuprint("\n");
				}
			showmenu();
			action = (char)mcigetc();
			if (action == ESCAPE)
				done = TRUE;
			else if (action == 'b')
			{
				print2("Purchase which item? [ESCAPE to quit] ");
				item = ' ';
				while ((item != ESCAPE) &&
					   ((item < 'a') || (item >= 'a' + PAWNITEMS)))
					item = (char)mcigetc();
				if (item != ESCAPE)
				{
					i = item - 'a';
					if (Pawnitems[i] == NULL)
						print3("No such item!");
					else if (true_item_value(Pawnitems[i]) <= 0)
					{
						print1("Hmm, how did that junk get on my shelves?");
						print2("I'll just remove it.");
						delete Pawnitems[i];
						Pawnitems[i] = NULL;
					}
					else
					{
						clearmsg();
						print1("The low, low, cost is: ");
						mlongprint(Pawnitems[i]->number * true_item_value(Pawnitems[i]));
						nprint1(" Buy it? [ynq] ");
						if (ynq1() == 'y')
						{
							if (player.cash <
								Pawnitems[i]->number *
									true_item_value(Pawnitems[i]))
							{
								print2("No credit! Gwan, Beat it!");
								morewait();
							}
							else
							{
								player.cash -=
									Pawnitems[i]->number *
									true_item_value(Pawnitems[i]);
								Objects[Pawnitems[i]->id].known = 1;
								gain_item(Pawnitems[i]);
								Pawnitems[i] = NULL;
							}
						}
					}
				}
			}
			else if (action == 's')
			{
				menuclear();
				print2("Sell which item: ");
				i = getitem(NULL_ITEM);
				if ((i != ABORT) && (player.possessions[i] != NULL))
				{
					if (cursed(player.possessions[i]))
					{
						print1("No loans on cursed items! I been burned before....");
						morewait();
					}
					else if (true_item_value(player.possessions[i]) <= 0)
					{
						print1("That looks like a worthless piece of junk to me.");
						morewait();
					}
					else
					{
						clearmsg();
						print1("You can get ");
						mlongprint(item_value(player.possessions[i]) / 2);
						nprint1("Au each. Sell [yn]? ");
						if (ynq1() == 'y')
						{
							number = getnumber(player.possessions[i]->number);
							if ((number >= player.possessions[i]->number) &&
								player.possessions[i]->used)
							{
								player.possessions[i]->used = FALSE;
								player.possessions[i]->item_use();
							}
							player.cash += number * item_value(player.possessions[i]) / 2;
							delete Pawnitems[0];
							for (j = 0; j < PAWNITEMS - 1; j++)
								Pawnitems[j] = Pawnitems[j + 1];
							Pawnitems[PAWNITEMS - 1] = Object::create();
							*(Pawnitems[PAWNITEMS - 1]) = *(player.possessions[i]);
							Pawnitems[PAWNITEMS - 1]->number = number;
							Pawnitems[PAWNITEMS - 1]->known = 2;
							dispose_lost_objects(number, player.possessions[i]);
							dataprint();
						}
					}
				}
			}
			else if (action == 'p')
			{
				for (i = 0; i < player.packptr; i++)
				{
					if (player.pack[i]->blessing > -1 &&
						true_item_value(player.pack[i]) > 0)
					{
						clearmsg();
						print1("Sell ");
						nprint1(itemid(player.pack[i]));
						nprint1(" for ");
						mlongprint(item_value(player.pack[i]) / 2);
						nprint1("Au each? [yn] ");
						if (ynq1() == 'y')
						{
							number = getnumber(player.pack[i]->number);
							if (number > 0)
							{
								player.cash += number * item_value(player.pack[i]) / 2;
								delete Pawnitems[0];
								for (j = 0; j < PAWNITEMS - 1; j++)
									Pawnitems[j] = Pawnitems[j + 1];
								Pawnitems[PAWNITEMS - 1] = Object::create();
								*(Pawnitems[PAWNITEMS - 1]) = *(player.pack[i]);
								Pawnitems[PAWNITEMS - 1]->number = number;
								Pawnitems[PAWNITEMS - 1]->known = 2;
								player.pack[i]->number -= number;
								if (player.pack[i]->number < 1)
								{
									delete player.pack[i];
									player.pack[i] = NULL;
								}
								dataprint();
							}
						}
					}
				}
				fixpack();
			}
		}
	}
	calc_melee();
	xredraw();
}
