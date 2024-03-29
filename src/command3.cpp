/* omega copyright (C) by Laurence Raphael Brothers, 1987,1988,1989 */
/* command3.c */

/* This file contains some more top level command functions
   called from command1.c */

#ifndef MSDOS_SUPPORTED_ANTIQUE
#include <pwd.h>
#include <unistd.h>
#endif

#include "glob.h"
#include "date.h"
#include <map>
#include <functional>
#include <string>

/* look at some spot */
void examine()
{
  Objectlist* ol;
  int x = player.x, y = player.y, drewmenu = FALSE;

  clearmsg();

  /* WDT HACK: I'm not sure I buy that one shouldn't be able to examine
   * when one is blind.  However, the 'right' way to do it is certainly
   * too difficult (I would expect to be able to examine only the items
   * I actually recall).  So, for now I'll use David Given's compromise.
   * 12/30/98
   */
  if (player.status[BLINDED] > 0)
  {
    mprint("You're blind - you can't examine things.");
    return;
  }
  setgamestatus(SKIP_MONSTERS);
  mprint("Examine --");
  setspot(&x, &y);
  if (inbounds(x, y))
  {
    clearmsg();
    if (Current_Environment == E_COUNTRYSIDE)
    {
      if (!c_statusp(x, y, SEEN))
        print3("How should I know what that is?");
      else
      {
        mprint("That terrain is:");
        mprint(countryid(Country[x][y].current_terrain_type));
      }
    }
    else if (!view_los_p(player.x, player.y, x, y))
      print3("I refuse to examine something I can't see.");
    else
    {
      clearmsg();
      if (level->site[x][y].creature != NULL)
        mprint(mstatus_string(level->site[x][y].creature));
      else if ((player.x == x) && (player.y == y))
        describe_player();
      if (loc_statusp(x, y, SECRET))
        print2("An age-worn stone wall.");
      else{
        auto lc = level->site[x][y].locchar;
        if(lc == SPACE){
          print2("An infinite void.");
        } else if (lc == PORTCULLIS){
          print2("A heavy steel portcullis");
        } else if (lc == ABYSS) {
          print2("An entrance to the infinite abyss");
        } else if (lc == FLOOR){
          if (Current_Dungeon == Current_Environment)
            print2("A dirty stone floor.");
          else
            print2("The ground.");
        } else if (lc == WALL){
          if (level->site[x][y].aux == 0)
            print2("A totally impervious wall.");
          else if (level->site[x][y].aux < 10)
            print2("A pitted concrete wall.");
          else if (level->site[x][y].aux < 30)
            print2("An age-worn sandstone wall.");
          else if (level->site[x][y].aux < 50)
            print2("A smooth basalt wall.");
          else if (level->site[x][y].aux < 70)
            print2("A solid granite wall.");
          else if (level->site[x][y].aux < 90)
            print2("A wall of steel.");
          else if (level->site[x][y].aux < 210)
          {
            if (Current_Environment == E_CITY)
              print2("A thick wall of Rampart bluestone");
            else
              print2("A magically reinforced wall.");
          }
          else
            print2("An almost totally impervious wall.");
        } else if (lc == RUBBLE){
          print2("A dangerous-looking pile of rubble.");
        } else if (lc == SAFE){
          print2("A steel safe inset into the floor.");
        } else if (lc ==  CLOSED_DOOR){
          print2("A solid oaken door, now closed.");
        } else if (lc == OPEN_DOOR){
          print2("A solid oaken door, now open.");
        } else if (lc ==  STATUE){
          print2("A strange-looking statue.");
        } else if (lc == STAIRS_UP){
          print2("A stairway leading up.");
        } else if (lc == STAIRS_DOWN){
          print2("A stairway leading down....");
        } else if (lc == TRAP){
          print2(trapid(level->site[x][y].p_locf));
        } else if (lc == HEDGE){
          if (level->site[x][y].p_locf == L_EARTH_STATION)
            print2("A weird fibrillation of oozing tendrils.");
          else
            print2("A brambly, thorny hedge.");
        } else if (lc == LAVA){
          print2("A bubbling pool of lava.");
        } else if (lc == LIFT){
          print2("A strange glowing disk.");
        } else if (lc == ALTAR){
          print2("An (un?)holy altar.");
        } else if (lc == CHAIR){
          print2("A chair.");
        } else if (lc == WHIRLWIND){
          print2("A strange cyclonic electrical storm.");
        } else if (lc == WATER){
          if (level->site[x][y].p_locf == L_WATER)
            print2("A deep pool of water.");
          else if (level->site[x][y].p_locf == L_CHAOS)
            print2("A pool of primal chaos.");
          else if (level->site[x][y].p_locf == L_WATER_STATION)
            print2("A bubbling pool of acid.");
          else
            print2("An eerie pool of water.");
        } else if (lc == FIRE){
          print2("A curtain of fire.");
        } else {
          print2("Wow, I haven't the faintest idea!");
        }
      }
      
      if ((ol = level->site[x][y].things) != NULL && !loc_statusp(x, y, SECRET))
      {
        if (ol->next == NULL)
          print3(itemid(ol->thing));
        else
        {
          drewmenu = TRUE;
          menuclear();
          menuprint("Things on floor:\n");
          while (ol != NULL)
          {
            menuprint("\n");
            menuprint(itemid(ol->thing));
            ol = ol->next;
          }
          showmenu();
        }
      }
      morewait();
      sign_print(x, y, TRUE);
    }
  }
  if (drewmenu)
    xredraw();
}

void help()
{
  char c;
  char filestr[80];
  FILE *in, *out;
  int n;

  clearmsg();
  print1("Please enter the letter indicating what topic you want help on.");
  menuclear();
  menuprint("a: Overview\n");
  menuprint("b: Characters\n");
  menuprint("c: Inventories\n");
  menuprint("d: Movement\n");
  menuprint("e: Combat\n");
  menuprint("f: Bugs\n");
  menuprint("g: Magic\n");
  menuprint("h: The Countryside\n");
  menuprint("i: The Screen Display\n");
  menuprint("j: Saving and Restoring\n");
  menuprint("k: Options Settings\n");
  menuprint("l: Dungeon/City/Other Command List\n");
  menuprint("m: Countryside Command List\n");
#if !defined(MSDOS) && !defined(AMIGA)
  menuprint("n: Everything\n");
#endif
  menuprint("ESCAPE: Forget the whole thing.");
  showmenu();
  do
    c = (char)mcigetc();
#if defined(MSDOS) || defined(AMIGA)
  while ((c < 'a' || c > 'm') && c != ESCAPE);
  if (c != ESCAPE)
  {
    sprintf(filestr, "%shelp%d.txt", Omegalib, c + 1 - 'a');
    displayfile(filestr);
  }
#else
  while ((c < 'a' || c > 'n') && c != ESCAPE);
  if (c == 'n')
  {
    print1("Trying to copy all help files to ./omega.doc ");
    nprint1("Confirm [yn]");
    if (ynq1() == 'y')
    {
      change_to_user_perms();
      out = checkfopen("omega.doc", "w");
      print2("Copying");
      for (n = 1; n <= 13; n++)
      {
        nprint2(".");
        sprintf(Str1, "%shelp%d.txt", Omegalib, n);
        in = checkfopen(Str1, "r");
        while (fgets(Str1, STRING_LEN, in))
          fputs(Str1, out);
        fclose(in);
      }
      fclose(out);
      change_to_game_perms();
      nprint2(" Done.");
    }
  }
  else if (c != ESCAPE)
  {
    sprintf(filestr, "%shelp%d.txt", Omegalib, c + 1 - 'a');
    print1("Display help file, or Copy help file to file in wd. [dc] ");
    do
      c = (char)mcigetc();
    while ((c != 'd') && (c != 'c') && (c != ESCAPE));
    if (c == 'd')
      displayfile(filestr);
    else if (c == 'c')
      copyfile(filestr);
  }
#endif
  xredraw();
}

void version()
{
  setgamestatus(SKIP_MONSTERS);
  print3(VERSIONSTRING);
  nprint3(":");
  nprint3(" Last Edited: ");
  nprint3(LAST_OMEGA_EDIT_DATE);
}

void fire()
{
  int index, x1, y1, x2, y2;
  Object* obj;
  Monster *m;

  clearmsg();

  print1("Fire/Throw --");
  index = getitem(NULL_ITEM);
  if (index == ABORT)
    setgamestatus(SKIP_MONSTERS);
  else if (index == CASHVALUE)
    print3("Can't fire money at something!");
  else if (cursed(player.possessions[index]) &&
           player.possessions[index]->used)
    print3("You can't seem to get rid of it!");
  /* load a crossbow */
  else if ((player.possessions[O_WEAPON_HAND] != NULL) &&
           (*player.possessions[O_WEAPON_HAND] == "crossbow") &&
           (player.possessions[O_WEAPON_HAND]->aux != LOADED) &&
           (*player.possessions[index] == "bolt"))
  {
    mprint("You crank back the crossbow and load a bolt.");
    player.possessions[O_WEAPON_HAND]->aux = LOADED;
  }
  else
  {
    if (player.possessions[index]->used)
    {
      player.possessions[index]->used = FALSE;
      player.possessions[index]->item_use();
    }
    obj = player.possessions[index];
    x1 = x2 = player.x;
    y1 = y2 = player.y;
    setspot(&x2, &y2);
    if ((x2 == player.x) && (y2 == player.y))
      mprint("You practice juggling for a moment or two.");
    else
    {
      do_object_los(obj->objchar, &x1, &y1, x2, y2);
      if ((m = level->site[x1][y1].creature) != NULL)
      {
        if (obj->dmg == 0)
        {
          if (m->treasure > 0)
          { /* the monster can have treasure/objects */
            mprint("Your gift is caught!");
            givemonster(m, split_item(1, obj));
            conform_lost_objects(1, obj);
          }
          else
          {
            mprint("Your thrown offering is ignored.");
            setgamestatus(SUPPRESS_PRINTING);
            p_drop_at(x1, y1, 1, obj);
            resetgamestatus(SUPPRESS_PRINTING);
            conform_lost_objects(1, obj);
          }
        }
        else if (obj->aux == I_SCYTHE)
        {
          mprint("It isn't very aerodynamic... you miss.");
          setgamestatus(SUPPRESS_PRINTING);
          p_drop_at(x1, y1, 1, obj);
          resetgamestatus(SUPPRESS_PRINTING);
          conform_lost_objects(1, obj);
        }
        else if (hitp(player.hit, m->ac))
        { /* ok already, hit the damn thing */
          weapon_use(2 * statmod(player.str), obj, m);
          if ((*obj == "arrow" || *obj == "bolt") &&
              !random_range(4))
            dispose_lost_objects(1, obj);
          else
          {
            setgamestatus(SUPPRESS_PRINTING);
            p_drop_at(x1, y1, 1, obj);
            resetgamestatus(SUPPRESS_PRINTING);
            conform_lost_objects(1, obj);
          }
        }
        else
        {
          mprint("You miss it.");
          setgamestatus(SUPPRESS_PRINTING);
          p_drop_at(x1, y1, 1, obj);
          resetgamestatus(SUPPRESS_PRINTING);
          conform_lost_objects(1, obj);
        }
      }
      else
      {
        setgamestatus(SUPPRESS_PRINTING);
        p_drop_at(x1, y1, 1, obj);
        resetgamestatus(SUPPRESS_PRINTING);
        conform_lost_objects(1, obj);
        plotspot(x1, y1, TRUE);
      }
    }
  }
}

void quit(int)
{
  clearmsg();
  change_to_game_perms();
  mprint("Quit: Are you sure? [yn] ");
  if (ynq() == 'y')
  {
    if (player.rank[ADEPT] == 0)
      display_quit();
    else
      display_bigwin();
#ifdef SAVE_LEVELS
    kill_all_levels();
#endif
    endgraf();
    exit(0);
  }
  else
    resetgamestatus(SKIP_MONSTERS);
}

/* rest in 10 second segments so if woken up by monster won't
die automatically.... */
void nap()
{
  static int naptime;
  if (gamestatusp(FAST_MOVE))
  {
    if (naptime-- < 1)
    {
      clearmsg();
      mprint("Yawn. You wake up.");
      resetgamestatus(FAST_MOVE);
      drawvision(player.x, player.y);
    }
  }
  else
  {
    clearmsg();
    mprint("Rest for how long? (in minutes) ");
    naptime = (int)parsenum();
    if (naptime > 600)
    {
      print3("You can only sleep up to 10 hours (600 minutes)");
      naptime = 3600;
    }
    else
      naptime *= 6;
    if (naptime > 1)
    {
      clearmsg();
      setgamestatus(FAST_MOVE);
      mprint("Resting.... ");
    }
  }
}

void charid()
{
  char id;
  int countryside = FALSE;
  char cstr[80];

  clearmsg();
  mprint("Character to identify: ");
  id = mgetc();
  if (Current_Environment == E_COUNTRYSIDE)
  {
    countryside = TRUE;
    auto s = countryid(id);
    if (s == "I have no idea.")
      countryside = FALSE;
    else
      mprint(s);
  }
  if (!countryside)
  {
    if ((id >= 'a' && id <= 'z') || (id >= 'A' && id <= 'Z') || id == '@')
      mprint("A monster or NPC -- examine (x) to find out exactly.");
    else
    {
      static std::multimap<char, std::string> lookMap = {
          {SPACE & 0xff, " : An airless void (if seen) or unknown region (if unseen)"},
          {WALL & 0xff, " : An (impenetrable?) wall"},
          {OPEN_DOOR & 0xff, " : An open door"},
          {CLOSED_DOOR & 0xff, " : A closed (possibly locked) door"},
          {LAVA & 0xff, " : A pool of lava"},
          {HEDGE & 0xff, " : A dense hedge"},
          {WATER & 0xff, " : A deep body of water"},
          {FIRE & 0xff, " : A curtain of fire"},
          {TRAP & 0xff, " : An uncovered trap"},
          {STAIRS_UP & 0xff, " : A stairway leading up"},
          {STAIRS_DOWN & 0xff, " : A stairway leading down"},
          {FLOOR & 0xff, " : The dungeon floor"},
          {PORTCULLIS & 0xff, " : A heavy steel portcullis"},
          {ABYSS & 0xff, " : An entrance to the infinite abyss"},
          {PLAYER & 0xff, " : You, the player"},
          {CORPSE & 0xff, " : The remains of some creature"},
          {THING & 0xff, " : Some random miscellaneous object"},
          {SAFE & 0xff, " : A steel safe inset into the floor"},
          {RUBBLE & 0xff, " : A dangerous-looking pile of rubble"},
          {STATUE & 0xff, " : A statue"},
          {ALTAR & 0xff, " : A (un?)holy altar"},
          {CASH & 0xff, " : Bills, specie, gems: cash"},
          {PILE & 0xff, " : A pile of objects"},
          {FOOD & 0xff, " : Something edible"},
          {WEAPON & 0xff, " : Some kind of weapon"},
          {MISSILEWEAPON & 0xff, " : Some kind of missile weapon"},
          {SCROLL & 0xff, " : Something readable"},
          {POTION & 0xff, " : Something drinkable"},
          {ARMOR & 0xff, " : A suit of armor"},
          {SHIELD & 0xff, " : A shield"},
          {CLOAK & 0xff, " : A cloak"},
          {BOOTS & 0xff, " : A pair of boots"},
          {STICK & 0xff, " : A stick"},
          {RING & 0xff, " : A ring"},
          {ARTIFACT & 0xff, " : An artifact"},
          {CHAIR & 0xff, " : A chair"},
          {WHIRLWIND & 0xff, " : A whirlwind"},
      };
      if (lookMap.count(id) <= 0)
      {
        mprint("That character is unused.");
      }
      else
      {
        auto result = lookMap.equal_range(id);
        std::string out;
        for (auto it = result.first; it != result.second; it++){
          out += it->second;
        }
        mprint(out);
      }
    }
  }
}

void wizard()
{
  char *lname;
#ifndef MSDOS_SUPPORTED_ANTIQUE
  struct passwd *dastuff;
#endif

  setgamestatus(SKIP_MONSTERS);
  if (gamestatusp(CHEATED))
    mprint("You're already in wizard mode!");
  else
  {
    clearmsg();
    mprint("Really try to enter wizard mode? [yn] ");
    if (ynq() == 'y')
    {
      lname = getlogin();
#ifndef MSDOS_SUPPORTED_ANTIQUE
      if (!lname || strlen(lname) == 0)
      {
        dastuff = getpwuid(getuid());
        lname = dastuff->pw_name;
      }
#endif
      if (strcmp(lname, WIZARD) == 0)
      {
        setgamestatus(CHEATED);
        mprint("Wizard mode set.");
      }
      else
      {
        mprint("There is a shrieking sound, as of reality being distorted.");
        strcpy(Str1, WIZARD);
        strcat(Str1, ", the Wizard of Omega appears before you....");
        if (Str1[0] >= 'a' && Str1[0] <= 'z')
          Str1[0] += 'A' - 'a'; /* capitalise 1st letter */
        mprint(Str1);
        mprint("'Do not meddle in the affairs of Wizards --");
        if (random_range(2))
          mprint("it makes them soggy and hard to light.'");
        else
          mprint("for they are subtle, and swift to anger!'");
      }
    }
  }
}

/* Jump, that is */
void vault()
{
  int x = player.x, y = player.y, jumper = 0;

  clearmsg();

  if (player.possessions[O_BOOTS] != NULL)
    if (player.possessions[O_BOOTS]->usef == I_BOOTS_JUMPING)
      jumper = 2;
  if (player.status[IMMOBILE] > 0)
  {
    resetgamestatus(FAST_MOVE);
    print3("You are unable to move");
  }
  else
  {
    setgamestatus(SKIP_MONSTERS);
    mprint("Jump where?");
    setspot(&x, &y);
    if (!los_p(player.x, player.y, x, y))
      print3("The way is obstructed.");
    else if (player.itemweight > player.maxweight)
      print3("You are too burdened to jump anywhere.");
    else if (distance(x, y, player.x, player.y) >
             max(2, statmod(player.agi) + 2) + jumper)
      print3("The jump is too far for you.");
    else if (level->site[x][y].creature != NULL)
      print3("You can't jump on another creature.");
    else if (!p_moveable(x, y))
      print3("You can't jump there.");
    else
    {
      resetgamestatus(SKIP_MONSTERS);
      player.x = x;
      player.y = y;
      if ((!jumper) && (random_range(30) > player.agi))
      {
        mprint("Oops -- took a tumble.");
        setgamestatus(SKIP_PLAYER);
        p_damage((player.itemweight / 250), UNSTOPPABLE, "clumsiness");
      }
      p_movefunction(level->site[player.x][player.y].p_locf);
      if (Current_Environment != E_COUNTRYSIDE)
        if ((level->site[player.x][player.y].things != NULL) &&
            (optionp(PICKUP)))
          pickup();
    }
  }
}

/* Sets sequence of combat maneuvers. */
void tacoptions()
{
  int actionsleft, done, place;
  char defatt, *attstr, *defstr; /* for the default setting */
  int draw_again = 1;

  setgamestatus(SKIP_MONSTERS);

  done = FALSE;
  actionsleft = maneuvers();
  place = 0;
  do
  {
    if (draw_again)
    {
      menuclear();
      menuprint("Enter a combat maneuvers sequence.\n");
      menuprint("? for help, ! for default, backspace to start again,\n");
      menuprint(" RETURN to save sequence\n");
      showmenu();
      draw_again = 0;
    }
    clearmsg();
    mprint("Maneuvers Left:");
    mnumprint(actionsleft);
    switch (mgetc())
    {
    case '?':
      combat_help();
      draw_again = 1;
      break;
    case 'a':
    case 'A':
      if (actionsleft < 1)
        print3("No more maneuvers!");
      else
      {
        if (player.possessions[O_WEAPON_HAND] == NULL)
        {
          player.meleestr[place] = 'C';
          menuprint("\nPunch:");
        }
        else if (player.possessions[O_WEAPON_HAND]->type == THRUSTING)
        {
          player.meleestr[place] = 'T';
          menuprint("\nThrust:");
        }
        else if (player.possessions[O_WEAPON_HAND]->type == STRIKING)
        {
          player.meleestr[place] = 'C';
          menuprint("\nStrike:");
        }
        else
        {
          menuprint("\nCut:");
          player.meleestr[place] = 'C';
        }
        place++;
        player.meleestr[place] = getlocation();
        place++;
        actionsleft--;
      }
      break;
    case 'b':
    case 'B':
      if (actionsleft < 1)
        print3("No more maneuvers!");
      else
      {
        player.meleestr[place] = 'B';
        if (player.possessions[O_WEAPON_HAND] == NULL)
          menuprint("\nDodge (from):");
        else if (player.possessions[O_WEAPON_HAND]->type == THRUSTING)
          menuprint("\nParry:");
        else
          menuprint("\nBlock:");
        place++;
        player.meleestr[place] = getlocation();
        place++;
        actionsleft--;
      }
      break;
    case 'l':
    case 'L':
      if (actionsleft < 2)
        print3("Not enough maneuvers to lunge!");
      else
      {
        if (player.possessions[O_WEAPON_HAND] != NULL)
        {
          if (player.possessions[O_WEAPON_HAND]->type != MISSILE)
          {
            menuprint("\nLunge:");
            player.meleestr[place] = 'L';
            place++;
            player.meleestr[place] = getlocation();
            place++;
            actionsleft -= 2;
          }
          else
          {
            print3("Can't lunge with a missile weapon!");
            morewait();
          }
        }
        else
        {
          print3("Can't lunge without a weapon!");
          morewait();
        }
      }
      break;
    case 'r':
    case 'R':
      if (actionsleft < 2)
        print3("Not enough maneuvers to riposte!");
      else
      {
        if (player.possessions[O_WEAPON_HAND] != NULL)
        {
          if (player.possessions[O_WEAPON_HAND]->type == THRUSTING)
          {
            player.meleestr[place++] = 'R';
            menuprint("\nRiposte:");
            player.meleestr[place++] = getlocation();
            actionsleft -= 2;
          }
          else
          {
            print3("Can't riposte without a thrusting weapon!");
            morewait();
          }
        }
        else
        {
          print3("Can't riposte without a thrusting weapon!");
          morewait();
        }
      }
      break;
    case BACKSPACE:
    case DELETE:
      place = 0;
      actionsleft = maneuvers();
      draw_again = 1;
      break;
    case '!':
      if (player.possessions[O_WEAPON_HAND] == NULL)
      {
        defatt = 'C';
        attstr = "Punch";
      }
      else if (player.possessions[O_WEAPON_HAND]->type == THRUSTING)
      {
        defatt = 'T';
        attstr = "Thrust";
      }
      else if (player.possessions[O_WEAPON_HAND]->type == STRIKING)
      {
        defatt = 'C';
        attstr = "Strike";
      }
      else
      {
        defatt = 'C';
        attstr = "Cut";
      }
      if (player.possessions[O_WEAPON_HAND] == NULL)
        defstr = "Dodge";
      else if (player.possessions[O_WEAPON_HAND]->type == THRUSTING)
        defstr = "Parry";
      else
        defstr = "Block";
      menuclear();
      menuprint("Enter a combat maneuvers sequence.\n");
      menuprint("? for help, ! for default, backspace to start again,\n");
      menuprint(" RETURN to save sequence\n\n");
      for (place = 0; place < maneuvers(); place++)
        if (place & 1)
        { /* every 2nd time around */
          player.meleestr[place * 2] = 'B';
          player.meleestr[(place * 2) + 1] = 'C';
          menuprint(defstr);
          menuprint(" Center.\n");
        }
        else
        {
          player.meleestr[place * 2] = defatt;
          player.meleestr[(place * 2) + 1] = 'C';
          menuprint(attstr);
          menuprint(" Center.\n");
        }
      actionsleft = 0;
      showmenu();
      player.meleestr[place * 2] = '\0';
      break;
    case RETURN:
    case LINEFEED:
    case ESCAPE:
      done = TRUE;
      break;
    }
    /*    if (actionsleft < 1) morewait(); */ /* FIXED 12/30/98 */
  } while (!done);
  xredraw();
  player.meleestr[place] = 0;
}

/* Do the Artful Dodger trick */
void pickpocket()
{
  int dx, dy, index = 0;
  Monster *m;

  clearmsg();

  mprint("Pickpocketing --");

  index = getdir();

  if (index == ABORT)
    setgamestatus(SKIP_MONSTERS);
  else
  {
    dx = Dirs[0][index];
    dy = Dirs[1][index];

    if ((!inbounds(player.x + dx, player.y + dy)) ||
        (level->site[player.x + dx][player.y + dy].creature == NULL))
    {
      print3("There's nothing there to steal from!!!");
      setgamestatus(SKIP_MONSTERS);
    }
    else
    {
      m = level->site[player.x + dx][player.y + dy].creature;
      if (m->id == GUARD)
      {
        mprint("Trying to steal from a guardsman, eh?");
        mprint("Not a clever idea.");
        if (player.cash > 0)
        {
          mprint("As a punitive fine, the guard takes all your money.");
          player.cash = 0;
          dataprint();
        }
        else
        {
          mprint("The guardsman places you under arrest.");
          morewait();
          send_to_jail();
        }
      }
      else if (m->possessions == NULL)
      {
        mprint("You couldn't find anything worth taking!");
        mprint("But you managed to annoy it...");
        m_status_set(m, HOSTILE);
      }
      else if (player.dex * 5 + player.rank[THIEVES] * 20 + random_range(100) >
               random_range(100) + m->level * 20)
      {
        mprint("You successfully complete your crime!");
        mprint("You stole:");
        mprint(itemid(m->possessions->thing));
        player.alignment--;
        gain_experience(m->level * m->level);
        gain_item(m->possessions->thing);
        m->possessions = m->possessions->next;
      }
    }
  }
}

void rename_player()
{
  setgamestatus(SKIP_MONSTERS);
  clearmsg();
  mprint("Rename Character: ");
  strcpy(Str1, msgscanstring());
  if (strlen(Str1) == 0)
    mprint(player.name);
  else
  {
    if (Str1[0] >= 'a' && Str1[0] <= 'z')
      Str1[0] += 'A' - 'a';
    strcpy(player.name, Str1);
  }
  sprintf(Str1, "Henceforth, you shall be known as %s", player.name);
  print2(Str1);
}

void abortshadowform()
{
  setgamestatus(SKIP_MONSTERS);
  if (player.status[SHADOWFORM] && (player.status[SHADOWFORM] < 1000))
  {
    mprint("You abort your spell of Shadow Form.");
    player.immunity[NORMAL_DAMAGE]--;
    player.immunity[ACID]--;
    player.immunity[THEFT]--;
    player.immunity[INFECTION]--;
    mprint("You feel less shadowy now.");
    player.status[SHADOWFORM] = 0;
  }
}

void tunnel()
{
  int dir, ox, oy, aux;

  clearmsg();
  mprint("Tunnel -- ");
  dir = getdir();
  if (dir == ABORT)
    setgamestatus(SKIP_MONSTERS);
  else
  {
    ox = player.x + Dirs[0][dir];
    oy = player.y + Dirs[1][dir];
    if (loc_statusp(ox, oy, SECRET))
      mprint("You have no success as yet.");
    else if (level->site[ox][oy].locchar != WALL)
    {
      print3("You can't tunnel through that!");
      setgamestatus(SKIP_MONSTERS);
    }
    else
    {
      aux = level->site[ox][oy].aux;
      if (random_range(20) == 1)
      {
        if (player.possessions[O_WEAPON_HAND] == NULL)
        {
          mprint("Ouch! broke a fingernail...");
          p_damage(player.str / 6, UNSTOPPABLE, "a broken fingernail");
        }
        else if ((player.possessions[O_WEAPON_HAND]->type == THRUSTING) ||
                 ((player.possessions[O_WEAPON_HAND]->type != STRIKING) &&
                  (player.possessions[O_WEAPON_HAND]->fragility <
                   random_range(20))))
        {
          mprint("Clang! Uh oh...");
          (void)damage_item(player.possessions[O_WEAPON_HAND]);
        }
        else
          mprint("Your digging implement shows no sign of breaking.");
      }
      if (player.possessions[O_WEAPON_HAND] == NULL)
      {
        if ((aux > 0) && ((player.str / 3) + random_range(100) > aux))
        {
          mprint("You carve a tunnel through the stone!");
          tunnelcheck();
          level->site[ox][oy].locchar = RUBBLE;
          level->site[ox][oy].p_locf = L_RUBBLE;
          lset(ox, oy, CHANGED);
        }
        else
          mprint("No joy.");
      }
      else if (player.possessions[O_WEAPON_HAND]->type == THRUSTING)
      {
        if ((aux > 0) &&
            (player.possessions[O_WEAPON_HAND]->dmg * 2 + random_range(100) >
             aux))
        {
          mprint("You carve a tunnel through the stone!");
          tunnelcheck();
          level->site[ox][oy].locchar = RUBBLE;
          level->site[ox][oy].p_locf = L_RUBBLE;
          lset(ox, oy, CHANGED);
        }
        else
          mprint("No luck.");
      }
      else if ((aux > 0) &&
               (player.possessions[O_WEAPON_HAND]->dmg + random_range(100) > aux))
      {
        mprint("You carve a tunnel through the stone!");
        tunnelcheck();
        level->site[ox][oy].locchar = RUBBLE;
        level->site[ox][oy].p_locf = L_RUBBLE;
        lset(ox, oy, CHANGED);
      }
      else
        mprint("You have no success as yet.");
    }
  }
}

void hunt(Symbol terrain)
{
  int fertility = 0;
  std::map<unsigned int, std::function<void()>> huntMap = {
      {SWAMP, []() { mprint("You hesitate to hunt for food in the marshy wasteland."); }},
      {VOLCANO, []() { mprint("There is nothing alive here (or so it seems)"); }},
      {CASTLE, []() { mprint("There is nothing alive here (or so it seems)"); }},
      {TEMPLE, []() { mprint("There is nothing alive here (or so it seems)"); }},
      {CAVES, []() { mprint("There is nothing alive here (or so it seems)"); }},
      {STARPEAK, []() { mprint("There is nothing alive here (or so it seems)"); }},
      {MAGIC_ISLE, []() { mprint("There is nothing alive here (or so it seems)"); }},
      {DRAGONLAIR, []() { mprint("There is nothing alive here (or so it seems)"); }},
      {VILLAGE, []() { mprint("You can find no food here; perhaps if you went inside...."); }},
      {CITY, []() { mprint("You can find no food here; perhaps if you went inside...."); }},
      {ROAD, []() { mprint("You feel it would be a better idea to hunt off the road."); }},
      {CHAOS_SEA, []() { mprint("Food in the Sea of Chaos? Go on!"); }},
      {DESERT, [&]() {
         mprint("You wander off into the trackless desert in search of food...");
         Time += 100;
         hourly_check();
         fertility = 10;
       }},
      {JUNGLE, [&]() {
         mprint("You search the lush and verdant jungle for game....");
         Time += 100;
         hourly_check();
         fertility = 80;
       }},
      {PLAINS, [&]() {
         mprint("You set off through the tall grass; the game is afoot.");
         Time += 100;
         hourly_check();
         fertility = 50;
       }},
      {TUNDRA, [&]() {
         mprint("You blaze a trail through the frozen wasteland....");
         Time += 100;
         hourly_check();
         fertility = 30;
       }},
      {FOREST, [&]() {
         mprint("You try to follow the many tracks through the forest loam....");
         Time += 100;
         hourly_check();
         fertility = 70;
       }},
      {MOUNTAINS, [&]() {
         mprint("You search the cliff walls looking for something to eat....");
         Time += 100;
         hourly_check();
         fertility = 30;
       }},
      {PASS, [&]() {
         mprint("You search the cliff walls looking for something to eat....");
         Time += 100;
         hourly_check();
         fertility = 30;
       }},
      {RIVER, [&]() {
         mprint("The halcyon river is your hopeful food source...");
         Time += 100;
         hourly_check();
         fertility = 80;
       }},
  };
  if(huntMap.count(terrain) > 0){
    huntMap[terrain]();
  }
  if (((Date % 360 < 60) || (Date % 360 > 300)) &&
      (terrain != DESERT) &&
      (terrain != JUNGLE))
  {
    mprint("The cold weather impedes your hunt....");
    fertility = fertility / 2;
  }
  if (fertility > random_range(100))
  {
    mprint("You have an encounter...");
    change_environment(E_TACTICAL_MAP);
  }
  else
    mprint("Your hunt is fruitless.");
}

void dismount_steed()
{
  Monsterlist* ml;
  if (!gamestatusp(MOUNTED))
    print3("You're on foot already!");
  else if (Current_Environment == E_COUNTRYSIDE)
  {
    mprint("If you leave your steed here he will wander away!");
    mprint("Do it anyway? [yn] ");
    if (ynq() == 'y')
      resetgamestatus(MOUNTED);
  }
  else
  {
    resetgamestatus(MOUNTED);
    ;
    ml = Monsterlist::create();
    ml->m = Monster::create();
    *(ml->m) = Monsters[HORSE];
    ml->m->x = player.x;
    ml->m->y = player.y;
    ml->m->status = MOBILE + SWIMMING;
    ml->next = level->mlist;
    level->site[player.x][player.y].creature = ml->m;
    level->mlist = ml;
  }
  calc_melee();
}

void city_move()
{
  int site, x = player.x, y = player.y, toggle = FALSE;
  clearmsg();
  if (Current_Environment != E_CITY)
  {
    print3("This command only works in the city!");
    setgamestatus(SKIP_MONSTERS);
  }
  else if (player.status[IMMOBILE] > 0)
    print3("You can't even move!");
  else if (hostilemonstersnear())
  {
    setgamestatus(SKIP_MONSTERS);
    print3("You can't move this way with hostile monsters around!");
  }
  else if (level->site[player.x][player.y].aux == NOCITYMOVE)
    print3("You can't use the 'M' command from this location.");
  else
  {
    print1("Move to which establishment [? for help, ESCAPE to quit]");
    site = parsecitysite();
    if (site != ABORT)
    {
      mprint("You're on your way...");
      morewait();
      while ((x != CitySiteList[site][1]) || (y != CitySiteList[site][2]))
      {
        toggle = !toggle;
        if (toggle)
        {
          Time++;
          if (Time % 10 == 0)
            tenminute_check();
          else
            minute_status_check();
        }
        x += sign(CitySiteList[site][1] - x);
        y += sign(CitySiteList[site][2] - y);
        screencheck(y);
        omshowcursor(x, y);
      }
      player.x = x;
      player.y = y;
      screencheck(player.y);
      mprint("Made it!");
      drawvision(player.x, player.y);
      morewait();
      p_movefunction(level->site[x][y].p_locf);
    }
  }
}

void frobgamestatus()
{
  char response;
  long num;
  mprint("Set or Reset or Forget it [s,r,ESCAPE]:");
  do
    response = (char)mcigetc();
  while ((response != 'r') && (response != 's') && (response != ESCAPE));
  if (response != ESCAPE)
  {
    mprint("Enter log2 of flag:");
    num = (int)parsenum();
    if (num > -1)
    {
      num = pow2(num);
      if (num == CHEATED)
      {
        mprint("Can't alter Wizard flag.");
        return;
      }
      if (response == 's')
        setgamestatus(num);
      else
        resetgamestatus(num);
      mprint("Done....");
    }
  }
}
