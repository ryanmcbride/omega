/* omega copyright (c) 1987,1988,1989 by Laurence Raphael Brothers */
/* mtalk.c */
/* monster talk functions */

#include "glob.h"

/* The druid's altar is in the northern forest */
void m_talk_druid(Monster* m)
{
  int i;
  Monsterlist* curr;

  if (!m_statusp(m, HOSTILE))
  {
    print1("The Archdruid raises a hand in greeting.");
    if (!gamestatusp(SPOKE_TO_DRUID))
    {
      setgamestatus(SPOKE_TO_DRUID);
      morewait();
      print1("The Archdruid congratulates you on reaching his sanctum.");
      print2("You feel competent.");
      morewait();
      gain_experience(300);
      if (player.patron == DRUID)
      {
        print1("The Archdruid conveys to you the wisdom of nature....");
        print2("You feel like a sage.");
        morewait();
        for (i = 0; i < NUMRANKS; i++)
        {
          if (player.guildxp[i] > 0)
            player.guildxp[i] += 300;
        }
      }
    }
    mprint("Do you request a ritual of neutralization? [yn] ");
    if (ynq() == 'y')
    {
      if (Phase / 2 == 6 || Phase / 2 == 0)
      { /* full or new moon */
        mprint("\"Unfortunately, I cannot perform a ritual of balance on");
        if (Phase / 2 == 6)
          mprint("this lawful day.\"");
        else
          mprint("this chaotic day.\"");
      }
      else if (Phase / 2 == 3 || Phase / 2 == 9)
      { /* half moon */
        mprint("You take part in today's holy celebration of balance...");
        player.alignment = 0;
        player.mana = calcmana();
        if (player.patron == DRUID)
          gain_experience(200); /* if a druid wants to spend 2 days */
        Time += 60;             /* celebrating for 1600 xp, why not? */
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
      }
      else
      {
        mprint("The ArchDruid conducts a sacred rite of balance...");
        if (player.patron == DRUID)
        {
          player.alignment = 0;
          player.mana = calcmana();
        }
        else
          player.alignment -= player.alignment * max(0, 10 - player.level) / 10;
        /* the higher level the character is, the more set in his/her ways */
        Time += 60;
        hourly_check();
      }
      dataprint();
    }
  }
  else
  {
    mprint("The ArchDruid looks at you and cries: 'Unclean! Unclean!'");
    disrupt(player.x, player.y, 100);
    mprint("This seems to have satiated his desire for vengeance.");
    mprint("'Have you learned your lesson?' The ArchDruid asks. [yn] ");
    if (ynq())
    {
      mprint("'I certainly hope so!' says the ArchDruid.");
      for (curr = level->mlist; curr; curr = curr->next)
        m_status_reset(curr->m, HOSTILE);
      m_vanish(m);
    }
    else
    {
      mprint("'Idiot.' mutters the ArchDruid.");
      p_damage(500, UNSTOPPABLE, "the ArchDruid's Vengeance");
    }
  }
}

void m_talk_silent(Monster* m)
{

  int reply = random_range(4);

  if (m->uniqueness == COMMON)
  {
    strcpy(Str2, "The ");
    strcat(Str2, m->monstring);
  }
  else
    strcpy(Str2, m->monstring);
  switch (reply)
  {
  case 0:
    strcat(Str2, " does not reply. ");
    break;
  case 1:
    strcat(Str2, " shrugs silently. ");
    break;
  case 2:
    strcat(Str2, " hold a finger to his mouth. ");
    break;
  case 3:
    strcat(Str2, " glares at you but says nothing. ");
    break;
  }
  mprint(Str2);
}

void m_talk_stupid(Monster* m)
{

  int reply = random_range(4);
  if (m->uniqueness == COMMON)
  {
    strcpy(Str2, "The ");
    strcat(Str2, m->monstring);
  }
  else
    strcpy(Str2, m->monstring);
  switch (reply)
  {
  case 0:
    strcat(Str2, " looks at you with mute incomprehension.");
    break;
  case 1:
    strcat(Str2, " growls menacingly and ignores you.");
    break;
  case 2:
    strcat(Str2, " does not seem to have heard you.");
    break;
  case 3:
    strcat(Str2, " tries to pretend it didn't hear you.");
    break;
  }
  mprint(Str2);
}

void m_talk_greedy(Monster* m)
{

  int reply = random_range(4);
  if (m->uniqueness == COMMON)
  {
    strcpy(Str2, "The ");
    strcat(Str2, m->monstring);
  }
  else
    strcpy(Str2, m->monstring);
  switch (reply)
  {
  case 0:
    strcat(Str2, " says: Give me a treasure.... ");
    break;
  case 1:
    strcat(Str2, " says: Stand and deliver, knave! ");
    break;
  case 2:
    strcat(Str2, " says: Your money or your life! ");
    break;
  case 3:
    strcat(Str2, " says: Yield or Die! ");
    break;
  }
  mprint(Str2);
}

void m_talk_hungry(Monster* m)
{

  int reply = random_range(4);
  if (m->uniqueness == COMMON)
  {
    strcpy(Str2, "The ");
    strcat(Str2, m->monstring);
  }
  else
    strcpy(Str2, m->monstring);
  switch (reply)
  {
  case 0:
    strcat(Str2, " says: I hunger, foolish adventurer! ");
    break;
  case 1:
    strcat(Str2, " drools menacingly at you. ");
    break;
  case 2:
    strcat(Str2, " says: You're invited to be lunch! ");
    break;
  case 3:
    strcat(Str2, " says: Feeed Meee! ");
    break;
  }
  mprint(Str2);
}

void m_talk_guard(Monster* m)
{
  if (m_statusp(m, HOSTILE))
  {
    print1("'Surrender in the name of the Law!'");
    print2("Do it? [yn] ");
    if (ynq2() == 'y')
    {
      player.alignment++;
      if (Current_Environment == E_CITY)
      {
        print1("Go directly to jail. Do not pass go, do not collect 200Au.");
        print2("You are taken to the city gaol.");
        morewait();
        send_to_jail();
        drawvision(player.x, player.y);
      }
      else
      {
        clearmsg();
        print1("Mollified, the guard disarms you and sends you away.");
        dispose_lost_objects(1, player.possessions[O_WEAPON_HAND]);
        pacify_guards();
      }
    }
    else
    {
      clearmsg();
      print1("All right, you criminal scum, you asked for it!");
    }
  }
  else if (player.rank[ORDER] > 0)
    print1("'Greetings comrade! May you always tread the paths of Law.'");
  else
    print1("Move it right along, stranger!");
}

void m_talk_mp(Monster* m)
{
  mprint("The mendicant priest asks you to spare some treasure for the needy");
}

void m_talk_titter(Monster* m)
{

  if (m->uniqueness == COMMON)
  {
    strcpy(Str2, "The ");
    strcat(Str2, m->monstring);
  }
  else
    strcpy(Str2, m->monstring);
  strcat(Str2, " titters obscenely at you.");
  mprint(Str2);
}

void m_talk_ninja(Monster* m)
{
  mprint("The black-garbed figure says apologetically:");
  mprint("'Situree simasita, wakarimasen.'");
}

void m_talk_thief(Monster* m)
{
  if (player.rank[THIEVES])
  {
    if (m->level == 2)
      m->monstring = "sneak thief";
    else
      m->monstring = "master thief";
    print1("The cloaked figure makes a gesture which you recognize...");
    print2("...the thieves' guild recognition signal!");
    print3("'Sorry, mate, thought you were a mark....'");
    morewait();
    m_vanish(m);
  }
  else
    m_talk_man(m);
}

void m_talk_assassin(Monster* m)
{
  m->monstring = "master assassin";
  print1("The ominous figure does not reply, but hands you an embossed card:");
  print2("'Guild of Assassins Ops are forbidden to converse with targets.'");
}

void m_talk_im(Monster* m)
{
  if (strcmp(m->monstring, "itinerant merchant") != 0)
  {
    m->monstring = "itinerant merchant";
  }
  if (m->possessions == NULL)
    mprint("The merchant says: Alas! I have nothing to sell!");
  else
  {
    m->possessions->thing->known = 2;
    clearmsg();
    mprint("I have a fine");
    mprint(itemid(m->possessions->thing));
    mprint("for only");
    mlongprint(max(10, 4 * true_item_value(m->possessions->thing)));
    mprint("Au.");
    mprint("Want it? [yn] ");
    if (ynq() == 'y')
    {
      if (player.cash < (max(10, 4 * true_item_value(m->possessions->thing))))
      {
        if (player.alignment > 10)
        {
          mprint("Well, I'll let you have it for what you've got.");
          player.cash = 0;
          gain_item(m->possessions->thing);
          m->possessions = NULL;
        }
        else
          mprint("Beat it, you deadbeat!");
      }
      else
      {
        mprint("Here you are. Have a good day.");
        player.cash -= max(10, (4 * item_value(m->possessions->thing)));
        gain_item(m->possessions->thing);
        m->possessions = NULL;
      }
    }
    else
      mprint("Well then, I must be off. Good day.");
    m_vanish(m);
  }
}

void m_talk_man(Monster* m)
{

  if (m->uniqueness == COMMON)
  {
    strcpy(Str2, "The ");
    strcat(Str2, m->monstring);
  }
  else
    strcpy(Str2, m->monstring);
  switch (random_range(5))
  {
  case 0:
    strcat(Str2, " asks you for the way home.");
    break;
  case 1:
    strcat(Str2, " wishes you a pleasant day.");
    break;
  case 2:
    strcat(Str2, " sneers at you contemptuously.");
    break;
  case 3:
    strcat(Str2, " smiles and nods.");
    break;
  case 4:
    strcat(Str2, " tells you a joke.");
    break;
  }
  mprint(Str2);
}

void m_talk_evil(Monster* m)
{

  if (m->uniqueness == COMMON)
  {
    strcpy(Str2, "The ");
    strcat(Str2, m->monstring);
  }
  else
    strcpy(Str2, m->monstring);
  switch (random_range(14))
  {
  case 0:
    strcat(Str2, " says: 'THERE CAN BE ONLY ONE!'");
    break;
  case 1:
    strcat(Str2, " says: 'Prepare to die, Buckwheat!'");
    break;
  case 2:
    strcat(Str2, " says: 'Time to die!'");
    break;
  case 3:
    strcat(Str2, " says: 'There will be no mercy.'");
    break;
  case 4:
    strcat(Str2, " insults your mother-in-law.");
    break;
  case 5:
    strcat(Str2, " says: 'Kurav tu ando mul!'");
  case 6:
    strcat(Str2, " says: '!va al infierno!'");
    break;
  case 7:
    strcat(Str2, " says: 'dame desu, nee.'");
    break;
  case 8:
    strcat(Str2, " spits on your rug and calls your cat a bastard.");
    break;
  case 9:
    strcat(Str2, " snickers malevolently and draws a weapon.");
    break;
  case 10:
    strcat(Str2, " sends 'rm -r *' to your shell!");
    break;
  case 11:
    strcat(Str2, " tweaks your nose and cackles evilly.");
    break;
  case 12:
    strcat(Str2, " thumbs you in the eyes.");
    break;
  case 13:
    strcat(Str2, " kicks you in the groin.");
    break;
  }
  mprint(Str2);
}

void m_talk_robot(Monster* m)
{
  if (m->uniqueness == COMMON)
  {
    strcpy(Str2, "The ");
    strcat(Str2, m->monstring);
  }
  else
    strcpy(Str2, m->monstring);
  switch (random_range(4))
  {
  case 0:
    strcat(Str2, " says: 'exterminate...Exterminate...EXTERMINATE!!!'");
    break;
  case 1:
    strcat(Str2, " says: 'Kill ... Crush ... Destroy'");
    break;
  case 2:
    strcat(Str2, " says: 'Danger -- Danger'");
    break;
  case 3:
    strcat(Str2, " says: 'Yo Mama -- core dumped.'");
    break;
  }
  mprint(Str2);
}

void m_talk_slithy(Monster* m)
{
  mprint("It can't talk -- it's too slithy!");
}

void m_talk_mimsy(Monster* m)
{
  mprint("It can't talk -- it's too mimsy!");
}

void m_talk_burble(Monster* m)
{

  if (m->uniqueness == COMMON)
  {
    strcpy(Str2, "The ");
    strcat(Str2, m->monstring);
  }
  else
    strcpy(Str2, m->monstring);
  strcat(Str2, " burbles hatefully at you.");
  mprint(Str2);
}

void m_talk_beg(Monster* m)
{
  if (m->uniqueness == COMMON)
  {
    strcpy(Str2, "The ");
    strcat(Str2, m->monstring);
  }
  else
    strcpy(Str2, m->monstring);
  strcat(Str2, " asks you for alms.");
  mprint(Str2);
}

void m_talk_hint(Monster* m)
{
  if (m->uniqueness == COMMON)
  {
    strcpy(Str2, "The ");
    strcat(Str2, m->monstring);
  }
  else
    strcpy(Str2, m->monstring);
  if (m_statusp(m, HOSTILE))
  {
    strcat(Str2, " only sneers at you. ");
    mprint(Str2);
  }
  else
  {
    strcat(Str2, " whispers in your ear: ");
    mprint(Str2);
    hint();
    m->talkf = M_TALK_SILENT;
  }
}

void m_talk_gf(Monster* m)
{
  mprint("The good fairy glints: Would you like a wish?");
  if (ynq() == 'y')
  {
    mprint("The good fairy glows: Are you sure?");
    if (ynq() == 'y')
    {
      mprint("The good fairy radiates: Really really sure?");
      if (ynq() == 'y')
      {
        mprint("The good fairy beams: I mean, like, sure as sure can be?");
        if (ynq() == 'y')
        {
          mprint("The good fairy dazzles: You don't want a wish, right?");
          if (ynq() == 'y')
            mprint("The good fairy laughs: I thought not.");
          else
            wish(0);
        }
      }
    }
  }
  mprint("In a flash of sweet-smelling light, the fairy vanishes....");
  player.hp = max(player.hp, player.maxhp);
  player.mana = max(player.mana, calcmana());
  mprint("You feel mellow.");
  m_vanish(m);
}

void m_talk_ef(Monster* m)
{
  mprint("The evil fairy roils: Eat my pixie dust!");
  mprint("She waves her black-glowing wand, which screams thinly....");
  m->movef = M_MOVE_SMART;
  m->meleef = M_MELEE_POISON;
  m->specialf = M_SP_THIEF;
  acquire(-1);
  bless(-1);
  sleep_player(m->level / 2);
  summon(-1, -1);
  summon(-1, -1);
  summon(-1, -1);
  summon(-1, -1);
}

void m_talk_seductor(Monster* m)
{
  if (m->uniqueness == COMMON)
  {
    strcpy(Str2, "The ");
    strcat(Str2, m->monstring);
  }
  else
    strcpy(Str2, m->monstring);
  if (player.preference == 'n')
  {
    strcat(Str2, " notices your disinterest and leaves with a pout.");
    mprint(Str2);
  }
  else
  {
    strcat(Str2, " beckons seductively...");
    mprint(Str2);
    mprint("Flee? [yn] ");
    if (ynq() == 'y')
    {
      mprint("You feel stupid.");
    }
    else
    {
      strcpy(Str2, "The ");
      strcat(Str2, m->monstring);
      strcat(Str2, " shows you a good time....");
      mprint(Str2);
      gain_experience(500);
      player.con++;
    }
  }
  m_vanish(m);
}

void m_talk_demonlover(Monster* m)
{
  if (m->uniqueness == COMMON)
  {
    strcpy(Str2, "The ");
    strcat(Str2, m->monstring);
  }
  else
    strcpy(Str2, m->monstring);
  if (player.preference == 'n')
  {
    strcat(Str2, " notices your disinterest and changes with a snarl...");
    mprint(Str2);
    morewait();
  }
  else
  {
    strcat(Str2, " beckons seductively...");
    mprint(Str2);
    mprint("Flee? [yn] ");
    if (ynq() == 'y')
      mprint("You feel fortunate....");
    else
    {
      if (m->uniqueness == COMMON)
      {
        strcpy(Str2, "The ");
        strcat(Str2, m->monstring);
      }
      else
        strcpy(Str2, m->monstring);
      strcat(Str2, " shows you a good time....");
      mprint(Str2);
      morewait();
      mprint("You feel your life energies draining...");
      level_drain(random_range(3) + 1, "a demon's kiss");
      morewait();
    }
  }
  m->talkf = M_TALK_EVIL;
  m->meleef = M_MELEE_SPIRIT;
  m->specialf = M_SP_DEMON;

  if ((m->monchar & 0xff) == 's')
  {
    m->monchar = 'I' | CLR(RED);
    m->monstring = "incubus";
  }
  else
  {
    m->monchar = 'S' | CLR(RED);
    m->monstring = "succubus";
  }
  if (m->uniqueness == COMMON)
  {
    strcpy(Str2, "The ");
    strcat(Str2, m->monstring);
  }
  else
    strcpy(Str2, m->monstring);
  strcat(Str2, " laughs insanely.");
  mprint(Str2);
  mprint("You now notice the fangs, claws, batwings...");
}

void m_talk_horse(Monster* m)
{
  if (m_statusp(m, HOSTILE))
    mprint("The horse neighs angrily at you.");
  else if (m_statusp(m, HUNGRY))
    mprint("The horse noses curiously at your pack.");
  else if (gamestatusp(MOUNTED))
    mprint("The horse and your steed don't seem to get along.");
  else if (Current_Environment == Current_Dungeon)
    mprint("The horse shies; maybe he doesn't like the dungeon air....");
  else
  {
    mprint("The horse lets you pat his nose. Want to ride him? [yn] ");
    if (ynq() == 'y')
    {
      m->hp = -1;
      level->site[m->x][m->y].creature = NULL;
      putspot(m->x, m->y, getspot(m->x, m->y, FALSE));
      setgamestatus(MOUNTED);
      calc_melee();
      mprint("You are now equitating!");
    }
  }
}

void m_talk_hyena(Monster* m)
{
  mprint("The hyena only laughs at you...");
}

void m_talk_parrot(Monster* m)
{
  mprint("Polly wanna cracker?");
}

void m_talk_servant(Monster* m)
{
  int target, x = player.x, y = player.y;
  if (m->id == SERV_LAW)
  {
    target = SERV_CHAOS;
    mprint("The Servant of Law pauses in thought for a moment.");
    mprint("You are asked: Are there any Servants of Chaos hereabouts? [yn] ");
  }
  else
  {
    target = SERV_LAW;
    mprint("The Servant of Chaos grins mischievously at you.");
    mprint("You are asked: Are there any Servants of Law hereabouts? [yn] ");
  }
  if (ynq() == 'y')
  {
    print1("Show me.");
    show_screen();
    drawmonsters(TRUE);
    setspot(&x, &y);
    if (level->site[x][y].creature != NULL)
    {
      if (level->site[x][y].creature->id == target)
      {
        mprint("The Servant launches itself towards its enemy.");
        mprint("In a blaze of combat, the Servants annihilate each other!");
        gain_experience(m->xpv);
        m_death(level->site[x][y].creature);
        level->site[m->x][m->y].creature = NULL;
        m->x = x;
        m->y = y;
        level->site[x][y].creature = m;
        m_death(level->site[x][y].creature);
      }
      else
        mprint("Right. Tell me about it. Idiot!");
    }
    else
      mprint("Right. Tell me about it. Idiot!");
  }
  else
    mprint("The servant shrugs and turns away.");
}

void m_talk_animal(Monster* m)
{
  if (m->uniqueness == COMMON)
  {
    strcpy(Str2, "The ");
    strcat(Str2, m->monstring);
  }
  else
    strcpy(Str2, m->monstring);
  mprint(Str2);
  mprint("shows you a scholarly paper by Dolittle, D. Vet.");
  mprint("which demonstrates that animals don't have speech centers");
  mprint("complex enough to communicate in higher languages.");
  mprint("It giggles softly to itself and takes back the paper.");
}

void m_talk_scream(Monster* m)
{
  mprint("A thinly echoing scream reaches your ears....");
  morewait();
  mprint("You feel doomed....");
  morewait();
  mprint("A bird appears and flies three times widdershins around your head.");
  summon(-1, QUAIL);
  m->talkf = M_TALK_EVIL;
}

void m_talk_archmage(Monster* m)
{
  if (m_statusp(m, HOSTILE))
  {
    mprint("The Archmage ignores your attempt at conversation");
    mprint("and concentrates on his spellcasting....");
  }
  else if (Current_Environment == E_COURT)
  {
    mprint("The Archmage congratulates you on getting this far.");
    mprint("He invites you to attempt the Throne of High Magic");
    mprint("but warns you that it is important to wield the Sceptre");
    mprint("before sitting on the throne.");
    if (level->site[m->x][m->y].p_locf == L_THRONE)
    {
      mprint("The Archmage smiles and makes an arcane gesture....");
      m_vanish(m);
    }
  }
  else
  {
    mprint("The Archmage tells you to find him again in his");
    mprint("Magical Court at the base of his castle in the mountains");
    mprint("of the far North-East; if you do he will give you some");
    mprint("important information.");
  }
}

void m_talk_merchant(Monster* m)
{
  if (!m_statusp(m, HOSTILE))
  {
    if (Current_Environment == E_VILLAGE)
    {
      mprint("The merchant asks you if you want to buy a horse for 250GP.");
      mprint("Pay the merchant? [yn] ");
      if (ynq() == 'y')
      {
        if (player.cash < 250)
          mprint("The merchant says: 'Come back when you've got the cash!'");
        else
        {
          player.cash -= 250;
          mprint("The merchant takes your money and tells you to select");
          mprint("any horse you want in the stables.");
          mprint("He says: 'You'll want to get to know him before trying to");
          mprint("ride him. By the way, food for the horse is not included.'");
          mprint("The merchant runs off toward the bank, cackling gleefully.");
          m_vanish(m);
        }
      }
      else
        mprint("The merchant tells you to stop wasting his time.");
    }
    else
    {
      mprint("The merchant tells you to visit his stables at his village");
      mprint("for a great deal on a horse.");
    }
  }
  else
  {
    mprint("The merchant ignores you and screams:");
    mprint("'Help! Help! I'm being oppressed!'");
  }
}

void m_talk_prime(Monster* m)
{
  if (!m_statusp(m, HOSTILE))
  {
    if (Current_Environment == E_CIRCLE)
    {
      print1("The Prime nods brusquely at you, removes a gem from his");
      print2("sleeve, places it on the floor, and vanishes wordlessly.");
      morewait();
      m_dropstuff(m);
      m_vanish(m);
    }
    else
    {
      print1("The Prime makes an intricate gesture, which leaves behind");
      print2("glowing blue sparks... He winks mischievously at you....");
      if (player.rank[CIRCLE] > 0)
      {
        morewait();
        print1("The blue sparks strike you! You feel enhanced!");
        print2("You feel more experienced....");
        player.pow += player.rank[CIRCLE];
        player.mana += calcmana();
        gain_experience(1000);
        m_vanish(m);
      }
    }
  }
  else
    m_talk_evil(m);
}

void m_talk_wereking(Monster *m)
{
  if (!m_statusp(m, HOSTILE))
  {
    switch (player.rank[WEREWOLF])
    {
    case 0:
      print1("You submissively appraoch the Werewolf King.");
      morewait();
      print2("Do you wish to join the Pack? [yn] ");
      if (ynq2() == 'y')
      {
        clearmsg();

        print1("He savagely attacks you...");
        morewait();
        nprint1(" until you are almost dead.");
        morewait();
        print1("The Werewolf King says \"If you survive...");
        morewait();
        print2("you will be stronger than ever.\"");
        morewait();
        clearmsg();
        player.cash = 1;
        player.rank[WEREWOLF] = PUP;
        player.guildxp[WEREWOLF] = 1;
        player.status[DISEASED] = 1100;
        player.str++;
        player.con++;
        player.maxstr++;
        player.maxcon++;
        player.hp = 1;
        player.maxhp *= 2;
        dataprint();
        showflags();
      }else{
        clearmsg();
        print1("He savagely attacks you...");
        m_status_set(m,HOSTILE);
      }
      break;
    case PUP:
      clearmsg();
      print1("The King smells your nethers");
      if (player.guildxp[WEREWOLF] < 400)
        print2("and decides that you're not ready to advance");
      else
      {
        print2("and decides you smell like a Delta wolf");
        morewait();
        clearmsg();
        print1("You're given a bloody heart to eat");
        player.rank[WEREWOLF] = DELTA;
        player.str++;
        player.maxstr++;
        player.maxcon++;
        player.con++;
        player.maxpow++;
        player.pow++;
        player.maxhp *= 1.5;
        player.hp = player.maxhp * 2;
        dataprint();
        showflags();
        dataprint();
        showflags();
      }
      break;
      case DELTA:
      clearmsg();
      print1("The King's hackles rise as he sniff's the air.");
      if (player.guildxp[WEREWOLF] < 1500)
        print2("You are too weak, go away!");
      else
      {
        print2("I'm impressed by your power");
        morewait();
        clearmsg();
        print1("You drink a potion of pure moonlight");
        player.rank[WEREWOLF] = BETA;
        player.str += 2;
        player.maxstr += 2;
        player.maxcon += 2;
        player.con += 2;
        player.maxpow += 2;
        player.pow += 2;
        player.maxhp *= 1.5;
        player.hp = player.maxhp * 2;
        dataprint();
        showflags();
      }
      break;
      case BETA:
      clearmsg();
      print1("The King's glares at you");
      if (player.guildxp[WEREWOLF] < 4000)
        print2("and then turns his back and ignores you");
      else
      {
        print2("You are truly an impressive beast");
        morewait();
        clearmsg();
        print1("The Kings carves a pentagram into your hand");
        player.rank[WEREWOLF] = ALPHA;
        player.str += 2;
        player.maxstr += 2;
        player.maxcon += 2;
        player.con += 2;
        player.maxpow += 2;
        player.pow += 2;
        player.maxhp *= 1.5;
        player.hp = player.maxhp * 2;
        dataprint();
        showflags();
      }
      break;
      case ALPHA:
      clearmsg();
      print1("The King seems agitated by your presense");
      if (player.guildxp[WEREWOLF] < 10000)
        print2("and glares angrily at you for a while");
      else
      {
        print2("You are a threat to my supremecy");
        morewait();
        clearmsg();
        print1("The Werewolf King attacks...");
        m_status_set(m,HOSTILE);
      }
      break;
    }
  }
  else
    m_talk_evil(m);
}