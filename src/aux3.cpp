/* omega copyright (C) by Laurence Raphael Brothers, 1987,1988,1989 */
/* aux3.c */
/* some functions called by com.c, also see aux1.c, aux2.c */
/* This is a real grab bag file. It contains functions used by
   aux1.c and omega.c, as well as elsewhere. It is mainly here so aux1.c
   and aux2.c are not huge */

#include "glob.h"
#include <map>

/* check every ten minutes */
void tenminute_check()
{
  if (Time % 60 == 0)
    hourly_check();
  else
  {
    if (Current_Environment == Current_Dungeon)
      wandercheck();
    minute_status_check();
    tenminute_status_check();
    if ((player.status[DISEASED] < 1) && (player.hp < player.maxhp))
      player.hp = min(player.maxhp, player.hp + player.level + 1);
    if (Current_Environment != E_COUNTRYSIDE && Current_Environment != E_ABYSS)
      indoors_random_event();
  }
}

/* hourly check is same as ten_minutely check except food is also
   checked, and since time moves in hours out of doors, also
   outdoors_random_event is possible */
void hourly_check()
{
  player.food--;
  foodcheck();
  if (hour() == 0)
  { /* midnight, a new day */
    moon_check();
    Date++;
  }
  torch_check();
  if (Current_Environment == Current_Dungeon)
    wandercheck();
  minute_status_check();
  tenminute_status_check();
  if ((player.status[DISEASED] == 0) && (player.hp < player.maxhp))
    player.hp = min(player.maxhp, player.hp + player.level + 1);
  if (Current_Environment != E_COUNTRYSIDE && Current_Environment != E_ABYSS)
    indoors_random_event();
}

void indoors_random_event()
{
  Monsterlist *ml;
  Objectlist *ol;
  switch (random_range(1000))
  {
  case 0:
    print3("You feel an unexplainable elation.");
    morewait();
    break;
  case 1:
    print3("You hear a distant rumbling.");
    morewait();
    break;
  case 2:
    print3("You realize your fly is open.");
    morewait();
    break;
  case 3:
    print3("You have a sudden craving for a pecan twirl.");
    morewait();
    break;
  case 4:
    print3("A mysterious healing flux settles over the level.");
    morewait();
    for (ml = level->mlist; ml != NULL; ml = ml->next)
      if (ml->m->hp > 0)
        ml->m->hp = Monsters[ml->m->id].hp;
    player.hp = max(player.hp, player.maxhp);
    break;
  case 5:
    print3("You discover an itch just where you can't scratch it.");
    morewait();
    break;
  case 6:
    print3("A cosmic ray strikes!");
    p_damage(10, UNSTOPPABLE, "a cosmic ray");
    morewait();
    break;
  case 7:
    print3("You catch your second wind....");
    player.maxhp++;
    player.hp = max(player.hp, player.maxhp);
    player.mana = max(player.mana, calcmana());
    morewait();
    break;
  case 8:
    print3("You find some spare change in a hidden pocket.");
    morewait();
    player.cash += player.level * player.level + 1;
    break;
  case 9:
    print3("You feel strangely lucky.");
    morewait();
    break;
  case 10:
    print3("You trip over something hidden in a shadow...");
    morewait();
    ol = Objectlist::create();
    ol->thing = Object::create_object(difficulty()); /* FIXED!  12/30/98 */
    assert(ol->thing);                               /* WDT I want to make sure... */
    ol->next = level->site[player.x][player.y].things;
    level->site[player.x][player.y].things = ol;
    pickup();
    break;
  case 11:
    print3("A mysterious voice echoes all around you....");
    morewait();
    hint();
    morewait();
    break;
  case 12:
    if (Balance > 0)
    {
      print3("You get word of the failure of your bank!");
      Balance = 0;
    }
    else
      print3("You feel lucky.");
    break;
  case 13:
    if (Balance > 0)
    {
      print3("You get word of a bank error in your favor!");
      Balance += 5000;
    }
    else
      print3("You feel unlucky.");
    break;
  }
  dataprint();
  showflags();
}

void outdoors_random_event()
{
  int num, i, j;
  Object *ob;

  switch (random_range(300))
  {
  case 0:
    if (Country[player.x][player.y].current_terrain_type == TUNDRA)
      mprint("It begins to snow. Heavily.");
    else if (Country[player.x][player.y].current_terrain_type == DESERT)
      mprint("A sandstorm swirls around you.");
    else
    {
      if ((Date > 75) && (Date < 330))
        mprint("You are drenched by a sudden downpour!");
      else
        mprint("It begins to snow. Heavily.");
    }
    morewait();
    mprint("Due to the inclement weather conditions, you have become lost.");
    morewait();
    Precipitation += random_range(12) + 1;
    setgamestatus(LOST);
    break;
  case 1:
    mprint("You enter a field of brightly colored flowers...");
    mprint("Wow, man! These are some pretty poppies...");
    morewait();
    mprint("poppies...");
    morewait();
    mprint("poppies...");
    morewait();
    print3("You become somewhat disoriented...");
    setgamestatus(LOST);
    break;
  case 2:
    mprint("You discover a sprig of athelas growing lonely in the wild.");
    morewait();
    mprint("Using your herbalist lore you cook a cake of lembas....");
    morewait();
    ob = Object::create("wafer of lembas");
    gain_item(ob);
    break;
  case 3:
    if (Precipitation > 0)
    {
      mprint("You are struck by a bolt of lightning!");
      p_damage(random_range(25), ELECTRICITY, "a lightning strike");
      morewait();
    }
    else
      mprint("You feel static cling");
    break;
  case 4:
    mprint("You find a fast-food establishment.");
    morewait();
    l_commandant();
    break;
  case 5:
    mprint("A weird howling tornado hits from out of the West!");
    morewait();
    mprint("You've been caught in a chaos storm!");
    morewait();
    num = random_range(300);
    if (num < 10)
    {
      mprint("Your cell-structure was disrupted!");
      p_damage(random_range(100), UNSTOPPABLE, "a chaos storm");
      morewait();
    }
    else if (num < 20)
    {
      mprint("The chaos storm warps your frame!");
      morewait();
      mprint("Your statistical entropy has been maximized.");
      morewait();
      mprint("You feel average...");
      morewait();
      toggle_item_use(TRUE); /* FIXED! 12/30/98 */
      player.str = player.maxstr = player.con = player.maxcon =
          player.dex = player.maxdex = player.agi = player.maxagi =
              player.iq = player.maxiq = player.pow = player.maxpow =
                  ((player.maxstr + player.maxcon + player.maxdex + player.maxagi +
                    player.maxiq + player.maxpow + 12) /
                   6);
      toggle_item_use(FALSE); /* FIXED! 12/30/98 */
    }
    else if (num < 30)
    {
      mprint("Your entire body glows with an eerie flickering light.");
      morewait();
      toggle_item_use(TRUE); /* FIXED! 12/30/98 */
      for (i = 1; i < MAXITEMS; i++)
        if (player.possessions[i] != NULL)
        {
          player.possessions[i]->plus++;
          if (player.possessions[i]->objchar == STICK)
            player.possessions[i]->charge += 10;
          player.possessions[i]->blessing += 10;
        }
      toggle_item_use(FALSE); /* FIXED! 12/30/98 */
      cleanse(1);
      mprint("You feel filled with energy!");
      morewait();
      player.maxpow += 5;
      player.pow += 5;
      player.mana = player.maxmana = calcmana() * 5;
      mprint("You also feel weaker. Paradoxical, no?");
      morewait();
      player.con -= 5;
      player.maxcon -= 5;
      if (player.con < 3)
        p_death("congestive heart failure");
    }
    else if (num < 40)
    {
      mprint("Your entire body glows black.");
      morewait();
      dispel(-1);
      dispel(-1);
      player.pow -= 10;
      player.mana = 0;
    }
    else if (num < 60)
    {
      mprint("The storm deposits you in a strange place....");
      morewait();
      player.x = random_range(WIDTH);
      player.y = random_range(LENGTH);
      screencheck(player.y);
    }
    else if (num < 70)
    {
      mprint("A tendril of the storm condenses and falls into your hands.");
      morewait();
      ob = Object::create();
      ob->make_artifact(-1);
      gain_item(ob);
    }
    else if (num < 80)
    {
      if (gamestatusp(MOUNTED))
      {
        mprint("Your horse screams as he is transformed into an");
        morewait();
        mprint("imaginary unseen dead tortoise.");
        morewait();
        mprint("You are now on foot.");
        morewait();
        resetgamestatus(MOUNTED);
      }
      else
      {
        mprint("You notice you are riding a horse. Odd. Very odd....");
        morewait();
        mprint("Now that's a horse of a different color!");
        morewait();
        setgamestatus(MOUNTED);
      }
    }
    else if (num < 90)
    {
      mprint("You feel imbued with godlike power....");
      morewait();
      wish(1);
    }
    else if (num < 100)
    {
      mprint("The chaos storm has wiped your memory!");
      morewait();
      mprint("You feel extraordinarily naive....");
      morewait();
      mprint("You can't remember a thing! Not even your name.");
      morewait();
      player.xp = 0;
      player.level = 0;
      for (i = 0; i < NUMRANKS; i++)
        player.rank[i] = 0;
      for (i = 0; i < NUMSPELLS; i++)
        Spells[i].known = FALSE;
      rename_player();
    }
    else
    {
      mprint("You survive the chaos storm relatively unscathed.");
      morewait();
      mprint("It was a learning experience.");
      morewait();
      gain_experience(1000);
    }
    break;
  case 6:
  case 7:
  case 8:
  case 9:
  case 10:
    mprint("An encounter!");
    morewait();
    change_environment(E_TACTICAL_MAP);
    break;
  case 11:
    mprint("You find a Traveller's Aid station with maps of the local area.");
    morewait();
    if (gamestatusp(LOST))
    {
      resetgamestatus(LOST);
      mprint("You know where you are now.");
    }
    for (i = player.x - 5; i < player.x + 6; i++)
      for (j = player.y - 5; j < player.y + 6; j++)
        if (inbounds(i, j))
        {
          c_set(i, j, SEEN);
          if (Country[i][j].current_terrain_type !=
              Country[i][j].base_terrain_type)
          {
            c_set(i, j, CHANGED);
            Country[i][j].current_terrain_type =
                Country[i][j].base_terrain_type;
          }
        }
    show_screen();
    break;
  case 12:
    if (!gamestatusp(MOUNTED))
    {
      mprint("You develop blisters....");
      p_damage(1, UNSTOPPABLE, "blisters");
    }
    break;
  case 13:
    mprint("You discover an itch just where you can't scratch it.");
    break;
  case 14:
    mprint("A cosmic ray strikes!");
    morewait();
    p_damage(10, UNSTOPPABLE, "a cosmic ray");
    break;
  case 15:
    mprint("You feel strangely lucky.");
    break;
  case 16:
    mprint("The west wind carries with it a weird echoing voice....");
    morewait();
    hint();
    morewait();
    break;
  }
  dataprint();
  showflags();
}

char getlocation()
{
  char c = '\0';

  menuprint(" (enter location [HCL]) ");
  showmenu();
  while (c == '\0')
    switch (c = ((char)mcigetc()))
    {
    case 'h':
      menuprint(" High.");
      break;
    case 'c':
      menuprint(" Center.");
      break;
    case 'l':
      menuprint(" Low.");
      break;
    default:
      c = '\0';
      break;
    }
  showmenu();
  return (c - 'a' + 'A');
}

/* chance for player to resist magic somehow */
/* hostile_magic ranges in power from 0 (weak) to 10 (strong) */
int magic_resist(int hostile_magic)
{
  if ((player.rank[COLLEGE] + player.rank[CIRCLE] > 0) &&
      (player.level / 2 + random_range(20) >
       hostile_magic + random_range(20)))
  {
    if (player.mana > hostile_magic * hostile_magic)
    {
      mprint("Thinking fast, you defend youself with a counterspell!");
      player.mana -= hostile_magic * hostile_magic;
      dataprint();
      return (TRUE);
    }
  }
  if (player.level / 4 + player.status[PROTECTION] + random_range(20) >
      hostile_magic + random_range(30))
  {
    mprint("You resist the spell!");
    return (TRUE);
  }
  else
    return (FALSE);
}

void terrain_check(int takestime)
{
  int faster = 0;

  if (player.patron == DRUID)
  {
    faster = 1;
    switch (random_range(32))
    {
    case 0:
      print2("Along the many paths of nature...");
      break;
    case 1:
      print2("You move swiftly through the wilderness.");
      break;
    }
  }
  else if (gamestatusp(MOUNTED))
  {
    faster = 1;
    switch (random_range(32))
    {
    case 0:
    case 1:
      print2("Clippity Clop.");
      break;
    case 2:
      print2("....my spurs go jingle jangle jingle....");
      break;
    case 3:
      print2("....as I go riding merrily along....");
      break;
    }
  }
  else if (player.possessions[O_BOOTS] &&
           player.possessions[O_BOOTS]->usef == I_BOOTS_7LEAGUE)
  {
    takestime = 0;
    switch (random_range(32))
    {
    case 0:
      print2("Boingg!");
      break;
    case 1:
      print2("Whooosh!");
      break;
    case 2:
      print2("Over hill, over dale....");
      break;
    case 3:
      print2("...able to leap over 7 leagues in a single bound....");
      break;
    }
  }
  else if (player.status[SHADOWFORM])
  {
    faster = 1;
    switch (random_range(32))
    {
    case 0:
      print2("As swift as a shadow.");
      break;
    case 1:
      print2("\"I walk through the trees...\"");
      break;
    }
  }
  else
    switch (random_range(32))
    {
    case 0:
      print2("Trudge. Trudge.");
      break;
    case 1:
      print2("The road goes ever onward....");
      break;
    }
  auto ttype = Country[player.x][player.y].current_terrain_type;
  if (ttype == RIVER)
  {
    if ((player.y < 6) && (player.x > 20))
      locprint("Star Lake.");
    else if (player.y < 41)
    {
      if (player.x < 10)
        locprint("Aerie River.");
      else
        locprint("The Great Flood.");
    }
    else if (player.x < 42)
      locprint("The Swamp Runs.");
    else
      locprint("River Greenshriek.");
    if (takestime)
    {
      Time += 60;
      hourly_check();
      Time += 60;
      hourly_check();
      Time += 60;
      hourly_check();
    }
  }
  else if (ttype == ROAD)
  {
    locprint("A well-maintained road.");
    if (takestime)
    {
      Time += 60;
      hourly_check();
    }
  }
  else if (ttype == PLAINS)
  {
    locprint("A rippling sea of grass.");
    if (takestime)
    {
      Time += 60;
      hourly_check();
      if (!faster)
      {
        Time += 60;
        hourly_check();
      }
    }
  }
  else if (ttype == TUNDRA)
  {
    locprint("The Great Northern Wastes.");
    if (takestime)
    {
      Time += 60;
      hourly_check();
      if (!faster)
      {
        Time += 60;
        hourly_check();
      }
    }
  }
  else if (ttype == FOREST)
  {
    if (player.y < 10)
      locprint("The Deepwood.");
    else if (player.y < 18)
      locprint("The Forest of Erelon.");
    else if (player.y < 46)
      locprint("The Great Forest.");
    if (takestime)
    {
      Time += 60;
      hourly_check();
      if (player.rank[PRIESTHOOD] == 0 || player.patron != DRUID)
      {
        Time += 60;
        hourly_check();
        if (!faster)
        {
          Time += 60;
          hourly_check();
        }
      }
    }
  }
  else if (ttype == JUNGLE)
  {
    locprint("Greenshriek Jungle.");
    if (takestime)
    {
      Time += 60;
      hourly_check();
      Time += 60;
      hourly_check();
      if (!faster)
      {
        Time += 60;
        hourly_check();
        Time += 60;
        hourly_check();
      }
    }
  }
  else if (ttype == DESERT)
  {
    locprint("The Waste of Time.");
    if (takestime)
    {
      Time += 60;
      hourly_check();
      Time += 60;
      hourly_check();
      if (!faster)
      {
        Time += 60;
        hourly_check();
        Time += 60;
        hourly_check();
      }
    }
  }
  else if (ttype == MOUNTAINS)
  {
    if ((player.y < 9) && (player.x < 12))
      locprint("The Magic Mountains");
    else if ((player.y < 9) && (player.y > 2) && (player.x < 40))
      locprint("The Peaks of the Fist.");
    else if (player.x < 52)
      locprint("The Rift Mountains.");
    else
      locprint("Borderland Mountains.");
    if (takestime)
    {
      Time += 60;
      hourly_check();
      Time += 60;
      hourly_check();
      Time += 60;
      hourly_check();
      Time += 60;
      hourly_check();
      Time += 60;
      hourly_check();
      if (!faster)
      {
        Time += 60;
        hourly_check();
        Time += 60;
        hourly_check();
        Time += 60;
        hourly_check();
      }
    }
  }
  else if (ttype == PASS)
  {
    locprint("A hidden pass.");
    if (takestime)
    {
      Time += 60;
      hourly_check();
    }
  }
  else if (ttype == CHAOS_SEA)
  {
    locprint("The Sea of Chaos.");
    if (takestime)
    {
      Time += 60;
      hourly_check();
    }
    mprint("You have entered the sea of chaos...");
    morewait();
    l_chaos();
  }
  else if (ttype == SWAMP)
  {
    locprint("The Loathly Swamp.");
    if (takestime)
    {
      Time += 60;
      hourly_check();
      Time += 60;
      hourly_check();
      Time += 60;
      hourly_check();
      Time += 60;
      hourly_check();
      Time += 60;
      hourly_check();
      Time += 60;
      hourly_check();
      if (!faster)
      {
        Time += 60;
        hourly_check();
        Time += 60;
        hourly_check();
      }
    }
  }
  else if (ttype == CITY)
  {
    if (gamestatusp(LOST))
    {
      resetgamestatus(LOST);
      mprint("Well, I guess you know where you are now....");
    }
    locprint("Outside Rampart, the city.");
  }
  else if (ttype == VILLAGE)
  {
    if (gamestatusp(LOST))
    {
      resetgamestatus(LOST);
      mprint("The village guards let you know where you are....");
    }
    locprint("Outside a small village.");
  }
  else if (ttype == CAVES)
  {
    locprint("A deserted hillside.");
    if (takestime)
    {
      Time += 60;
      hourly_check();
    }
    mprint("You notice a concealed entrance into the hill.");
  }
  else if (ttype == CASTLE)
  {
    locprint("Near a fortified castle.");
    if (takestime)
    {
      Time += 60;
      hourly_check();
    }
    mprint("The castle is hewn from solid granite. The drawbridge is down.");
  }
  else if (ttype == TEMPLE)
  {
    switch (Country[player.x][player.y].aux)
    {
    case ODIN:
      locprint("A rough-hewn granite temple.");
      break;
    case SET:
      locprint("A black pyramidal temple made of sandstone.");
      break;
    case ATHENA:
      locprint("A classical marble-columned temple.");
      break;
    case HECATE:
      locprint("A temple of ebony adorned with ivory.");
      break;
    case DRUID:
      locprint("A temple formed of living trees.");
      break;
    case DESTINY:
      locprint("A temple of some mysterious blue crystal.");
      break;
    }
    if (takestime)
    {
      Time += 60;
      hourly_check();
    }
    mprint("You notice an entrance conveniently at hand.");
  }
  else if (ttype == MAGIC_ISLE)
  {
    locprint("A strange island in the midst of the Sea of Chaos.");
    if (takestime)
    {
      Time += 60;
      hourly_check();
    }
    mprint("There is a narrow causeway to the island from here.");
  }
  else if (ttype == STARPEAK)
  {
    locprint("Star Peak.");
    if (takestime)
    {
      Time += 60;
      hourly_check();
    }
    mprint("The top of the mountain seems to glow with a allochroous aura.");
  }
  else if (ttype == DRAGONLAIR)
  {
    locprint("A rocky chasm.");
    if (takestime)
    {
      Time += 60;
      hourly_check();
    }
    mprint("You are at a cave entrance from which you see the glint of gold.");
  }
  else if (ttype == VOLCANO)
  {
    locprint("HellWell Volcano.");
    if (takestime)
    {
      Time += 60;
      hourly_check();
    }
    mprint("A shimmer of heat lightning plays about the crater rim.");
  }
  else
  {
    locprint("I haven't any idea where you are!!!");
  }
  outdoors_random_event();
}

void countrysearch()
{
  int x, y;
  Time += 60;
  hourly_check();
  for (x = player.x - 1; x < player.x + 2; x++)
    for (y = player.y - 1; y < player.y + 2; y++)
      if (inbounds(x, y))
      {
        if (Country[x][y].current_terrain_type !=
            Country[x][y].base_terrain_type)
        {
          clearmsg();
          mprint("Your search was fruitful!");
          Country[x][y].current_terrain_type = Country[x][y].base_terrain_type;
          c_set(x, y, CHANGED);
          mprint("You discovered:");
          mprint(countryid(Country[x][y].base_terrain_type));
        }
      }
}

std::string countryid(Symbol terrain)
{
  std::string str;
  std::map<unsigned char, std::string> countryMap = {
      {MOUNTAINS & 0xff, "Almost impassable mountains"},
      {PLAINS & 0xff, "Seemingly endless plains"},
      {TUNDRA & 0xff, "A frosty stretch of tundra"},
      {ROAD & 0xff, "A paved highway"},
      {PASS & 0xff, "A secret mountain pass"},
      {RIVER & 0xff, "A rolling river"},
      {CITY & 0xff, "The city of Rampart"},
      {VILLAGE & 0xff, "A rural village"},
      {FOREST & 0xff, "A verdant forest"},
      {JUNGLE & 0xff, "A densely overgrown jungle"},
      {SWAMP & 0xff, "A swampy fen"},
      {VOLCANO & 0xff, "A huge active volcano"},
      {CASTLE & 0xff, "An imposing castle"},
      {STARPEAK & 0xff, "A mysterious mountain."},
      {DRAGONLAIR & 0xff, "A cavern filled with treasure."},
      {MAGIC_ISLE & 0xff, "An island emanating magic."},
      {CAVES & 0xff, "A hidden cave entrance"},
      {TEMPLE & 0xff, "A neoclassical temple"},
      {DESERT & 0xff, "A sere desert"},
      {CHAOS_SEA & 0xff, "The Sea of Chaos"},
  };
  if (countryMap.count(terrain) > 0)
    return countryMap[terrain];

  return "I have no idea.";
}

static char *sitenames[] = {/* alphabetical listing */
                            "alchemist", "arena", "armorer", "bank", "brothel", "casino", "castle",
                            "city gates", "collegium magii", "condo", "department of public works",
                            "diner", "explorers' club", "fast food", "gymnasium", "healer", "hospice",
                            "les crapuleux", "library", "mercenary guild", "oracle", "order of paladins",
                            "pawn shop", "sorcerors' guild ", "tavern", "temple", "thieves' guild"};

static int sitenums[] = {/* the order matches sitenames[] */
                         L_ALCHEMIST, L_ARENA, L_ARMORER, L_BANK, L_BROTHEL, L_CASINO, L_CASTLE,
                         L_COUNTRYSIDE, L_COLLEGE, L_CONDO, L_DPW, L_DINER, L_CLUB, L_COMMANDANT,
                         L_GYM, L_HEALER, L_CHARITY, L_CRAP, L_LIBRARY, L_MERC_GUILD, L_ORACLE,
                         L_ORDER, L_PAWN_SHOP, L_SORCERORS, L_TAVERN, L_TEMPLE, L_THIEVES_GUILD};

void showknownsites(int first, int last)
{
  int i, printed = FALSE;

  menuclear();
  menuprint("\nPossible Sites:\n");
  for (i = first; i <= last; i++)
    if (CitySiteList[sitenums[i] - CITYSITEBASE][0])
    {
      printed = TRUE;
      menuprint(sitenames[i]);
      menuprint("\n");
    }
  if (!printed)
    menuprint("\nNo known sites match that prefix!");
  showmenu();
}

int parsecitysite()
{
  int first, last, pos;
  char byte, prefix[80];
  int found = 0;
  int f, l;

  first = 0;
  last = NUMCITYSITES - 1;
  pos = 0;
  print2("");
  do
  {
    byte = mgetc();
    if (byte == BACKSPACE || byte == DELETE)
    {
      if (pos > 0)
      {
        prefix[--pos] = '\0';
        byte = prefix[pos - 1];
        f = first;
        while (f >= 0 && !strncmp(prefix, sitenames[f], pos))
        {
          if (CitySiteList[sitenums[f] - CITYSITEBASE][0])
            first = f;
          f--;
        }
        l = last;
        while (l < NUMCITYSITES && !strncmp(prefix, sitenames[l], pos))
        {
          if (CitySiteList[sitenums[l] - CITYSITEBASE][0])
            last = l;
          l++;
        }
        if (found)
          found = 0;
        print2(prefix);
      }
      if (pos == 0)
      {
        first = 0;
        last = NUMCITYSITES - 1;
        found = 0;
        print2("");
      }
    }
    else if (byte == ESCAPE)
    {
      xredraw();
      return ABORT;
    }
    else if (byte == '?')
      showknownsites(first, last);
    else if (byte != '\n')
    {
      if (byte >= 'A' && byte <= 'Z')
        byte += 'a' - 'A';
      if (found)
        continue;
      f = first;
      l = last;
      while (f < NUMCITYSITES &&
             (!CitySiteList[sitenums[f] - CITYSITEBASE][0] ||
              strlen(sitenames[f]) < pos || sitenames[f][pos] < byte))
        f++;
      while (l >= 0 && (!CitySiteList[sitenums[l] - CITYSITEBASE][0] ||
                        strlen(sitenames[l]) < pos || sitenames[l][pos] > byte))
        l--;
      if (l < f)
        continue;
      prefix[pos++] = byte;
      prefix[pos] = '\0';
      nprint2(prefix + pos - 1);
      first = f;
      last = l;
      if (first == last && !found)
      { /* unique name */
        found = 1;
        nprint2(sitenames[first] + pos);
      }
    }
  } while (byte != '\n');
  xredraw();
  if (found)
    return sitenums[first] - CITYSITEBASE;
  else
  {
    print3("That is an ambiguous abbreviation!");
    return ABORT;
  }
}

/* are there hostile monsters within 2 moves? */
int hostilemonstersnear()
{
  int i, j, hostile = FALSE;

  for (i = player.x - 2; ((i < player.x + 3) && (!hostile)); i++)
    for (j = player.y - 2; ((j < player.y + 3) && (!hostile)); j++)
      if (inbounds(i, j))
        if (level->site[i][j].creature != NULL)
          hostile = m_statusp(level->site[i][j].creature, HOSTILE);

  return (hostile);
}

/* random effects from some of stones in villages */
/* if alignment of stone is alignment of player, gets done sooner */
int stonecheck(int alignment)
{
  int *stone, match = FALSE, cycle = FALSE, i;

  if (alignment == 1)
  {
    stone = &Lawstone;
    match = player.alignment > 0;
  }
  else if (alignment == -1)
  {
    stone = &Chaostone;
    match = player.alignment < 0;
  }
  else
  {
    stone = &Mindstone;
    match = FALSE;
  }
  *stone += random_range(4) + (match ? random_range(4) : 0);
  switch ((*stone)++)
  {
  case 0:
  case 2:
  case 4:
  case 6:
  case 8:
  case 10:
  case 12:
  case 14:
  case 16:
  case 18:
  case 20:
  case 22:
  case 24:
  case 26:
  case 28:
  case 30:
  case 32:
  case 34:
  case 36:
  case 38:
  case 40:
    print1("The stone glows grey.");
    print2("Not much seems to happen this time.");
    (*stone)--;
    break;
  case 1:
    print1("The stone glows black");
    print2("A burden has been removed from your shoulders.....");
    print3("Your pack has disintegrated!");
    for (i = 0; i < MAXPACK; i++)
      if (player.pack[i] != NULL)
      {
        delete player.pack[i];
        player.pack[i] = NULL;
      }
    player.packptr = 0;
    break;
  case 3:
    print1("The stone glows microwave");
    print2("A vortex of antimana spins about you!");
    morewait();
    dispel(-1);
    break;
  case 5:
    print1("The stone glows infrared");
    print2("A portal opens nearby and an obviously confused monster appears!");
    summon(-1, -1);
    morewait();
    break;
  case 7:
    print1("The stone glows brick red");
    print2("A gold piece falls from the heavens into your money pouch!");
    player.cash++;
    break;
  case 9:
    print1("The stone glows cherry red");
    print2("A flush of warmth spreads through your body.");
    augment(1);
    break;
  case 11:
    print1("The stone glows orange");
    print2("A flux of energy blasts you!");
    manastorm(player.x, player.y, random_range(player.maxhp) + 1);
    break;
  case 13:
    print1("The stone glows lemon yellow");
    print2("You're surrounded by enemies! You begin to foam at the mouth.");
    player.status[BERSERK] += 10;
    break;
  case 15:
    print1("The stone glows yellow");
    print2("Oh no! The DREADED AQUAE MORTIS!");
    morewait();
    print2("No, wait, it's just your imagination.");
    break;
  case 17:
    print1("The stone glows chartreuse");
    print2("Your joints stiffen up.");
    player.agi -= 3;
    break;
  case 19:
    print1("The stone glows green");
    print2("You come down with an acute case of Advanced Leprosy.");
    player.status[DISEASED] = 1100;
    player.hp = 1;
    player.dex -= 5;
    break;
  case 21:
    print1("The stone glows forest green");
    print2("You feel wonderful!");
    player.status[HERO] += 10;
    break;
  case 23:
    print1("The stone glows cyan");
    print2("You feel a strange twisting sensation....");
    morewait();
    strategic_teleport(-1);
    break;
  case 25:
    print1("The stone glows blue");
    morewait();
    print1("You feel a tingle of an unearthly intuition:");
    morewait();
    hint();
    break;
  case 27:
    print1("The stone glows navy blue");
    print2("A sudden shock of knowledge overcomes you.");
    morewait();
    clearmsg();
    identify(1);
    knowledge(1);
    break;
  case 29:
    print1("The stone glows blue-violet");
    print2("You feel forgetful.");
    for (i = 0; i < NUMSPELLS; i++)
      if (Spells[i].known)
      {
        Spells[i].known = FALSE;
        break;
      }
    break;
  case 31:
    print1("The stone glows violet");
    morewait();
    acquire(0);
    break;
  case 33:
    print1("The stone glows deep purple");
    print2("You vanish.");
    player.status[INVISIBLE] += 10;
    break;
  case 35:
    print1("The stone glows ultraviolet");
    print2("All your hair rises up on end.... A bolt of lightning hits you!");
    p_damage(random_range(player.maxhp), ELECTRICITY, "mystic lightning");
    break;
  case 37:
    print1("The stone glows roentgen");
    print2("You feel more experienced.");
    gain_experience((player.level + 1) * 250);
    break;
  case 39:
    print1("The stone glows gamma");
    print2("Your left hand shines silvery, and your right emits a golden aura.");
    morewait();
    enchant(1);
    bless(1);
    print3("Your hands stop glowing.");
    break;
  case 41:
  case 42:
  case 43:
  case 44:
  case 45:
  case 46:
  case 47:
  case 48:
  case 49:
    print1("The stone glows cosmic!");
    print2("The stone's energy field quiets for a moment...");
    *stone = 50;
    cycle = TRUE;
    break;
  default:
    print1("The stone glows polka-dot (?!?!?!?)");
    print2("You feel a strange twisting sensation....");
    morewait();
    *stone = 0;
    strategic_teleport(-1);
    break;
  }
  calc_melee();
  return (cycle);
}

void alert_guards()
{
  int foundguard = FALSE;
  Monsterlist *ml;
  int suppress = 0;
  for (ml = level->mlist; ml != NULL; ml = ml->next)
    if (((ml->m->id == GUARD) ||
         ((ml->m->id == HISCORE_NPC) && (ml->m->aux2 == 15))) && /*justiciar*/
        (ml->m->hp > 0))
    {
      foundguard = TRUE;
      m_status_set(ml->m, AWAKE);
      m_status_set(ml->m, HOSTILE);
    }
  if (foundguard)
  {
    mprint("You hear a whistle and the sound of running feet!");
    if (Current_Environment == E_CITY)
      level->site[40][60].p_locf = L_NO_OP; /* pacify_guards restores this */
  }
  if ((!foundguard) && (Current_Environment == E_CITY) &&
      !gamestatusp(DESTROYED_ORDER))
  {
    suppress = gamestatusp(SUPPRESS_PRINTING);
    resetgamestatus(SUPPRESS_PRINTING);
    print2("The last member of the Order of Paladins dies....");
    morewait();
    gain_experience(1000);
    player.alignment -= 250;
    if (!gamestatusp(KILLED_LAWBRINGER))
    {
      print1("A chime sounds from far away.... The sound grows stronger....");
      print2("Suddenly the great shadowy form of the LawBringer appears over");
      print3("the city. He points his finger at you....");
      morewait();
      print1("\"Cursed art thou, minion of chaos! May thy strength fail thee");
      print2("in thy hour of need!\" You feel an unearthly shiver as the");
      print3("LawBringer waves his palm across the city skies....");
      morewait();
      player.str /= 2;
      dataprint();
      print1("You hear a bell tolling, and eerie moans all around you....");
      print2("Suddenly, the image of the LawBringer is gone.");
      print3("You hear a guardsman's whistle in the distance!");
      morewait();
      resurrect_guards();
    }
    else
    {
      print1("The Order's magical defenses have dropped, and the");
      print2("Legions of Chaos strike....");
      morewait();
      print1("The city shakes! An earthquake has struck!");
      print2("Cracks open in the street, and a chasm engulfs the Order HQ!");
      print3("Flames lick across the sky and you hear wild laughter....");
      morewait();
      gain_experience(5000);
      destroy_order();
    }
  }
  if (suppress)
    resetgamestatus(SUPPRESS_PRINTING);
}

/* can only occur when player is in city, so OK to use Level */
void destroy_order()
{
  int i, j;
  setgamestatus(DESTROYED_ORDER);
  if (level != City)
    print1("Zounds! A Serious Mistake!");
  else
    for (i = 35; i < 46; i++)
      for (j = 60; j < 63; j++)
      {
        if (i == 40 && (j == 60 || j == 61))
        {
          lreset(i, j, SECRET);
          level->site[i][j].locchar = FLOOR;
          level->site[i][j].p_locf = L_NO_OP;
          lset(i, j, CHANGED);
        }
        else
        {
          level->site[i][j].locchar = RUBBLE;
          level->site[i][j].p_locf = L_RUBBLE;
          lset(i, j, CHANGED);
        }
        if (level->site[i][j].creature != NULL)
        {
          level->site[i][j].creature->hp = -1;
          level->site[i][j].creature = NULL;
        }
        make_site_monster(i, j, GHOST);
        level->site[i][j].creature->monstring = "ghost of a Paladin";
        m_status_set(level->site[i][j].creature, HOSTILE);
      }
}

int maneuvers()
{
  int m;

  m = 2 + player.level / 7;
  if (player.rank[ARENA])
    m++;
  if (player.status[HASTED])
    m *= 2;
  if (player.status[SLOWED])
    m /= 2;
  m = min(8, max(1, m));

  return (m);
}

/* for when haste runs out, etc. */
void default_maneuvers()
{
  int i;
  morewait();
  clearmsg();
  print1("Warning, resetting your combat options to the default.");
  print2("Use the 'F' command to select which options you prefer.");
  morewait();
  for (i = 0; i < maneuvers(); i += 2)
  {
    player.meleestr[i * 2] = 'A';
    player.meleestr[(i * 2) + 1] = 'C';
    player.meleestr[(i + 1) * 2] = 'B';
    player.meleestr[((i + 1) * 2) + 1] = 'C';
  }
  player.meleestr[maneuvers() * 2] = 0;
}
