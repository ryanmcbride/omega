/* omega copyright (C) 1987,1988,1989 by Laurence Raphael Brothers */
/* itemf3.c */

/* mostly artifact and stick functions */

#include "glob.h"

/* amulet of the planes */
void i_planes(Object* o)
{
  if (player.mana < 1)
    print1("The amulet spits some multicolored sparks.");
  else
  {
    print1("You focus mana into the amulet....");
    player.mana = max(0, player.mana - 100);
    dataprint();
    morewait();
    strategic_teleport(1);
  }
}

/* the sceptre of high magic */
void i_sceptre(Object* o)
{
  if (HiMagicUse == Date)
    print1("The Sceptre makes a sort of dull 'thut' noise.");
  else if (Current_Environment == E_CIRCLE || Current_Environment == E_ASTRAL)
  {
    HiMagicUse = Date; /* WDT: this looks like it's a good place to use
                        * the batteries. */
    print1("The Sceptre warps strangely for a second, and then subsides.");
    morewait();
    print2("You smell ozone."); /* WDT: explain the battery use. */
  }
  else
  {
    HiMagicUse = Date;
    print1("With a shriek of tearing aether, a magic portal appears!");
    print2("Step through? [yn] ");
    if (ynq() == 'y')
      change_environment(E_COURT);
    print1("The sceptre seems to subside. You hear a high whine, as of");
    print2("capacitors beginning to recharge.");
    morewait();
  }
}

/* the star gem */
void i_stargem(Object* o)
{
  if (StarGemUse == Date)
  {
    print1("The Star Gem glints weakly as if to say:");
    print2("'You have used me overmuch.'");
    print3("and it vanishes a puff of regret.");
    Objects[o->id].uniqueness = UNIQUE_UNMADE;
    /* it's now out there, somewhere */
    dispose_lost_objects(1, o);
  }
  else
  {
    StarGemUse = Date;
    if (o->blessing < 1)
    {
      print1("The Star Gem shines brightly and emits a musical tone.");
      print2("You see a dark cloud roil away from it.");
      morewait();
      o->blessing = 10;
    }
    print1("The star gem flares with golden light!");
    morewait();
    if (player.status[ILLUMINATION] < 1000)
    {
      print1("Interesting, you seem to be permanently accompanied");
      print2("by a friendly lambent glow....");
      morewait();
      player.status[ILLUMINATION] = 1500;
    }
    print1("You suddenly find yourself whisked away by some unknown force!");
    morewait();
    setgamestatus(COMPLETED_ASTRAL);
    change_environment(E_COUNTRYSIDE);
    player.x = 61;
    player.y = 3;
    screencheck(3);
    drawvision(player.x, player.y);
    locprint("Star Peak");
    Country[player.x][player.y].current_terrain_type =
        Country[player.x][player.y].base_terrain_type;
    c_set(player.x, player.y, CHANGED);
    print2("The Star Gem's brilliance seems to fade.");
  }
}

/* wand of fear */
void i_fear(Object* o)
{
  int x = player.x, y = player.y;
  Objects[o->id].known = 1;
  o->known = max(1, o->known);
  setspot(&x, &y);
  if (o->blessing < 0)
  {
    x = player.x;
    y = player.y;
  }
  inflict_fear(x, y);
}

void i_juggernaut(Object* o)
{
  int d, x = player.x, y = player.y;
  int seen = 1, not_seen = 0;
  int tunneled = 0;

  print1("You activate the Juggernaut of Karnak!");
  if (!o->known)
  {
    print2("Uh, oh, it's coming this way!");
    p_death("the Juggernaut of Karnak");
  }
  else
  {
    d = getdir();
    if (d == ABORT)
      print2("You deactivate the Juggernaut before it escapes.");
    else
    {
      print1("Vroom! ");
      while (inbounds(x + Dirs[0][d], y + Dirs[1][d]))
      {
        x += Dirs[0][d];
        y += Dirs[1][d];
        if (!view_unblocked(x, y) || offscreen(y))
          seen = 0;
        if (level->site[x][y].locchar == WALL)
          tunneled++;
        if (level->site[x][y].locchar != WATER &&
            level->site[x][y].locchar != VOID_CHAR &&
            level->site[x][y].locchar != ABYSS &&
            level->site[x][y].locchar != SPACE &&
            level->site[x][y].locchar != LAVA)
        {
          level->site[x][y].locchar = FLOOR;
          level->site[x][y].p_locf = L_NO_OP;
        }
        lreset(x, y, SECRET);
        lset(x, y, CHANGED);
        if (level->site[x][y].creature != NULL)
        {
          if (seen)
            nprint1("Splat! ");
          else
            not_seen++;
          setgamestatus(SUPPRESS_PRINTING);
          m_death(level->site[x][y].creature);
          resetgamestatus(SUPPRESS_PRINTING);
        }
        plotspot(x, y, FALSE);
        omshowcursor(x, y);
      }
      if (not_seen > 6)
        print2("You hear many distant screams...");
      else if (not_seen > 3)
        print2("You hear several distant screams...");
      else if (not_seen > 1)
        print2("You hear a couple of distant screams...");
      else if (not_seen == 1)
        print2("You hear a distant scream...");
      gain_experience(1000);
      dispose_lost_objects(1, o);
      level->tunnelled += tunneled - 1;
      tunnelcheck();
    }
  }
}

void i_symbol(Object* o)
{
  int i;
  if (!o->known)
    print1("Nothing seems to happen.");
  /* if o->charge != 17, then symbol was stolen from own high priest! */
  else if ((o->aux != player.patron) || (o->charge != 17))
  {
    print1("You invoke the deity...");
    print2("...who for some reason seems rather annoyed at you...");
    print3("You are enveloped in Godsfire!");
    morewait();
    for (; player.hp > 1; player.hp--)
    {
      dataprint();
      morewait();
      for (i = 0; i < MAXITEMS; i++)
        if (player.possessions[i] != NULL)
          dispose_lost_objects(player.possessions[i]->number,
                               player.possessions[i]);
      player.mana = 0;
    }
  }
  else if (SymbolUseHour == hour())
  {
    print1("Your deity frowns upon this profligate use of power...");
    print2("Shazam! A bolt of Godsfire! Your symbol shatters!");
    dispose_lost_objects(1, o);
    player.hp = 1;
    dataprint();
  }
  else
  {
    print1("A mystic flow of theurgic energy courses through your body!");
    SymbolUseHour = hour();
    cleanse(1);
    heal(10);
    player.mana = max(player.mana, calcmana());
  }
}

void i_crystal(Object* o)
{
  if (!o->known)
    print1("You can't figure out how to activate this orb.");
  else
  {
    print1("You gaze into your crystal ball.");
    if (ViewHour == hour())
      print2("All you get is Gilligan's Island reruns.");
    else if ((o->blessing < 0) || (player.iq + player.level < random_range(30)))
    {
      ViewHour = hour();
      print2("Weird interference patterns from the crystal fog your mind....");
      amnesia();
    }
    else
    {
      ViewHour = hour();
      print2("You sense the presence of life...");
      mondet(1);
      morewait();
      print2("You sense the presence of objects...");
      objdet(1);
      morewait();
      print2("You begin to see visions of things beyond your ken....");
      hint();
    }
  }
}

void i_antioch(Object* o)
{
  int x = player.x, y = player.y;
  int count;
  if (!o->known)
  {
    print1("Ka-Boom!");
    print2("You seem to have annihilated yourself.");
    p_death("the Holy Hand-Grenade of Antioch");
  }
  else
  {
    print1("Bring out the Holy Hand-Grenade of Antioch!");
    setspot(&x, &y);
    print2("Ok, you pull the pin.....");
    morewait();
    print1("What do you count up to? ");
    count = (int)parsenum();
    if ((count < 3) && (level->site[x][y].creature != NULL))
    {
      print1("`Three shall be the number of thy counting....");
      print2("And the number of thy counting shall be three.'");
      print3("Your target picks up the grenade and throws it back!");
      morewait();
      clearmsg();
      print1("Ka-Boom!");
      p_death("the Holy Hand-Grenade of Antioch");
    }
    else if (count > 3)
    {
      print1("`Three shall be the number of thy counting.");
      print2("And the number of thy counting shall be three.'");
      morewait();
      clearmsg();
      print1("Ka-Boom!");
      p_death("the Holy Hand-Grenade of Antioch");
    }
    else
    {
      print1("Ka-Boom!");
      gain_experience(1000);
      level->site[x][y].locchar = TRAP;
      level->site[x][y].p_locf = L_TRAP_DOOR;
      lset(x, y, CHANGED);
      if (level->site[x][y].creature != NULL)
      {
        m_death(level->site[x][y].creature);
        print2("You are covered with gore.");
      }
      level->site[x][y].things = NULL;
    }
  }
  dispose_lost_objects(1, o);
}

void i_kolwynia(Object* o)
{
  int i;
  if (!o->known)
  {
    print1("You destroy youself with a mana storm. How sad.");
    p_death("Kolwynia, The Key That Was Lost");
  }
  else
  {
    gain_experience(5000);
    print1("You seem to have gained complete mastery of magic.");
    player.pow = player.maxpow = 2 * player.maxpow;
    for (i = 0; i < NUMSPELLS; i++)
      Spells[i].known = TRUE;
  }
  dispose_lost_objects(1, o);
}

void i_enchantment(Object* o)
{
  char response;
  if (ZapHour == hour())
    print1("The staff doesn't seem to have recharged yet.");
  else if (!o->known)
  {
    ZapHour = hour();
    print1("You blast the staff backwards....");
    dispel(-1);
  }
  else
  {
    ZapHour = hour();
    print1("Zap with white or black end [wb] ");
    do
      response = (char)mcigetc();
    while ((response != 'w') && (response != 'b'));
    print2("The staff discharges!");
    if (response == 'w')
      enchant(o->blessing * 2 + 1);
    else
      dispel(o->blessing);
  }
}

void i_helm(Object* o)
{
  if (HelmHour == hour())
    print1("The helm doesn't seem to have recharged yet.");
  else if (!o->known)
  {
    HelmHour = hour();
    print1("You put the helm on backwards....");
    p_teleport(-1);
  }
  else
  {
    HelmHour = hour();
    print1("Your environment fades.... and rematerializes.");
    p_teleport(o->blessing);
  }
}

void i_death(Object* o)
{
  clearmsg();
  print1("Bad move...");
  p_death("the Potion of Death");
}

void i_life(Object* o)
{
  clearmsg();
  print1("Good move.");
  player.hp = player.maxhp = 2 * player.maxhp;
  dispose_lost_objects(1, o);
}

/* f = fire, w = water, e = earth, a = air, m = mastery */
int orbcheck(char element)
{
  char response;
  print1("The orb begins to glow with increasing intensity!");
  print2("You have the feeling you need to do something more....");
  morewait();
  print1("Burn it in fire [f] ");
  print2("Douse it with water [w] ");
  morewait();
  print1("Smash it against the earth [e] ");
  print2("Toss is through the air [a] ");
  morewait();
  print1("Mix the above actions, doing them in sequence [m] ");
  do
  {
    print2("Which one [f,w,e,a,m] ");
    response = (char)mcigetc();
  } while ((response != 'f') &&
           (response != 'w') &&
           (response != 'e') &&
           (response != 'a') &&
           (response != 'm'));
  return (response == element);
}

/* orb functions */
void i_orbfire(Object* o)
{
  if (!orbcheck('f'))
  {
    print1("Bad choice!");
    print2("The Orb of Fire blasts you!");
    fball(player.x, player.y, player.x, player.y, 250);
    o->known = 1;
  }
  else
  {
    print1("The Orb of Fire flares a brilliant red!");
    Spells[S_FIREBOLT].known = TRUE;
    gain_experience(10000);
    player.immunity[FLAME] += 100;
    print2("You feel fiery!");
    o->plus = 100;
    o->blessing = 100;
    i_firebolt(o);
  }
  *o = Objects[ARTIFACTID + 5];
}

void i_orbwater(Object* o)
{
  if (!orbcheck('w'))
  {
    print1("A serious mistake!");
    print2("The Orb of Water blasts you!");
    heal(-250);
    o->known = 1;
  }
  else
  {
    print1("The Orb of Water pulses a deep green!");
    Spells[S_DISRUPT].known = TRUE;
    player.immunity[POISON] += 100;
    gain_experience(10000);
    print2("You feel wet!");
    o->plus = 100;
    o->blessing = 100;
    i_disrupt(o);
  }
  *o = Objects[ARTIFACTID + 5];
}

void i_orbearth(Object* o)
{
  int i;
  if (!orbcheck('e'))
  {
    print1("What a maroon!");
    print2("The Orb of Earth blasts you!");
    player.con -= 10;
    if (player.con < 3)
      p_death("congestive heart failure");
    else
    {
      print3("Your possessions disintegrate!");
      for (i = 0; i < MAXITEMS; i++)
        if (player.possessions[i] != NULL)
          dispose_lost_objects(player.possessions[i]->number,
                               player.possessions[i]);
      for (i = 0; i < MAXPACK; i++)
        if (player.pack[i] != NULL)
        {
          free((char *)player.pack[i]);
          player.pack[i] = NULL;
        }
      player.packptr = 0;
      o->known = 1;
    }
  }
  else
  {
    print1("The Orb of Earth emanates a brownish aura!");
    Spells[S_DISINTEGRATE].known = TRUE;
    gain_experience(10000);
    player.immunity[NEGENERGY] += 100;
    print2("You feel earthy!");
    o->plus = 100;
    o->blessing = 100;
    i_disintegrate(o);
  }
  *o = Objects[ARTIFACTID + 5];
}

void i_orbair(Object* o)
{
  if (!orbcheck('a'))
  {
    print1("You lose!");
    print2("The Orb of Air blasts you!");
    lball(player.x, player.y, player.x, player.y, 100);
    o->known = 1;
  }
  else
  {
    print1("The Orb of Air flashes blue!");
    Spells[S_LBALL].known = TRUE; /* lball */
    gain_experience(10000);
    print2("You feel airy!");
    player.immunity[ELECTRICITY] += 100;
    o->plus = 100;
    o->blessing = 100;
    i_invisible(o);
    i_lbolt(o);
  }
  *o = Objects[ARTIFACTID + 5];
}

void i_orbmastery(Object* o)
{

  if (!orbcheck('m'))
  {
    print1("A fatal error!");
    print2("The Orb of Mastery blasts you to cinders!");
    p_death("playing with the Orb of Mastery");
    o->known = 1;
  }
  else if ((find_and_remove_item(ARTIFACTID + 1, -1)) &&
           (find_and_remove_item(ARTIFACTID + 2, -1)) &&
           (find_and_remove_item(ARTIFACTID + 3, -1)) &&
           (find_and_remove_item(ARTIFACTID + 4, -1)))
  {
    print1("The Orb of Mastery radiates rainbow colors!");
    print2("You feel godlike.");
    player.iq = player.maxiq = 2 * player.maxiq;
    player.pow = player.maxpow = 2 * player.maxpow;
    player.str = player.maxstr = 2 * player.maxstr;
    player.dex = player.maxdex = 2 * player.maxdex;
    player.con = player.maxcon = 2 * player.maxcon;
    player.agi = player.maxagi = 2 * player.maxagi;
    dataprint();
    morewait();
    print1("You have been imbued with a cosmic power....");
    morewait();
    wish(1);
    morewait();
    clearmsg();
    print2("You feel much more experienced.");
    gain_experience(20000);
    *o = Objects[ARTIFACTID + 5];
  }
  else
  {
    print1("The Orb of Mastery's power is unbalanced!");
    print2("The Orb of Mastery blasts you to cinders!");
    p_death("playing with the Orb of Mastery");
  }
}

void i_orbdead(Object* o)
{
  int i;
  print1("The burnt-out orb drains all your energy!");
  for (i = 0; i < NUMSPELLS; i++)
    Spells[i].known = FALSE;
  print2("You feel not at all like a mage.");
  for (i = 0; i < MAXITEMS; i++)
  {
    if (player.possessions[i] != NULL)
    {
      player.possessions[i]->plus = 0;
      if (player.possessions[i]->usef > 100)
        player.possessions[i]->usef = I_NOTHING;
    }
  }
  print3("A storm of mundanity surounds you!");
  level_drain(player.level - 1, "a Burnt-out Orb");
  player.mana = 0;
  player.pow -= 10;
}

void i_dispel(Object* o)
{
  dispel((o->blessing > -1) ? o->blessing + random_range(3) : o->blessing);
}

/* stick functions */

/* wand of apportation */
void i_apport(Object* o)
{
  o->known = max(1, o->known);
  Objects[o->id].known = 1;
  apport(o->blessing);
}

/* staff of firebolts */
void i_firebolt(Object* o)
{
  int x = player.x, y = player.y;
  o->known = max(1, o->known);
  Objects[o->id].known = 1;
  setspot(&x, &y);
  if (o->blessing < 0)
  {
    x = player.x;
    y = player.y;
  }
  fbolt(player.x, player.y, x, y, player.dex * 2 + player.level, 75);
}

void i_disintegrate(Object* o)
{
  int x = player.x, y = player.y;
  o->known = max(1, o->known);
  Objects[o->id].known = 1;
  setspot(&x, &y);
  if (o->blessing < 0)
  {
    x = player.x;
    y = player.y;
  }
  disintegrate(x, y);
}

void i_disrupt(Object* o)
{
  int x = player.x, y = player.y;
  o->known = max(1, o->known);
  Objects[o->id].known = 1;
  setspot(&x, &y);
  if (o->blessing < 0)
  {
    x = player.x;
    y = player.y;
  }
  disrupt(x, y, 100);
}

/* staff of lightning bolts */
void i_lbolt(Object* o)
{
  int x = player.x, y = player.y;
  o->known = max(1, o->known);
  Objects[o->id].known = 1;
  setspot(&x, &y);
  if (o->blessing < 0)
  {
    x = player.x;
    y = player.y;
  }
  lbolt(player.x, player.y, x, y, player.dex * 2 + player.level, 75);
}

/* wand of magic missiles */
void i_missile(Object* o)
{
  int x = player.x, y = player.y;
  o->known = max(1, o->known);
  Objects[o->id].known = 1;
  setspot(&x, &y);
  if (o->blessing < 0)
  {
    x = player.x;
    y = player.y;
  }
  nbolt(player.x, player.y, x, y, player.dex * 2 + player.level, 20);
}

/* wand of fire balls */
void i_fireball(Object* o)
{
  int x = player.x, y = player.y;
  Objects[o->id].known = 1;
  o->known = max(1, o->known);
  setspot(&x, &y);
  if (o->blessing < 0)
  {
    x = player.x;
    y = player.y;
  }
  fball(player.x, player.y, x, y, 35);
}

/* wand of snowballs */
void i_snowball(Object* o)
{
  int x = player.x, y = player.y;
  Objects[o->id].known = 1;
  o->known = max(1, o->known);
  setspot(&x, &y);
  if (o->blessing < 0)
  {
    x = player.x;
    y = player.y;
  }
  snowball(player.x, player.y, x, y, 20);
}

/* wand of lightning balls */
void i_lball(Object* o)
{
  int x = player.x, y = player.y;
  Objects[o->id].known = 1;
  o->known = max(1, o->known);
  setspot(&x, &y);
  if (o->blessing < 0)
  {
    x = player.x;
    y = player.y;
  }
  lball(player.x, player.y, x, y, 50);
}

/* staff of sleep */
void i_sleep_other(Object* o)
{
  Objects[o->id].known = 1;
  o->known = max(1, o->known);
  sleep_monster(o->blessing);
}

/* rod of summoning */
/* rod of summoning now always summons as if cursed */
void i_summon(Object* o)
{
  Objects[o->id].known = 1;
  o->known = max(1, o->known);
  summon(-1, -1);
}

void i_hide(Object* o)
{
  int x = player.x, y = player.y;
  Objects[o->id].known = 1;
  o->known = max(1, o->known);
  setspot(&x, &y);
  hide(x, y);
}

void i_polymorph(Object* o)
{
  Objects[o->id].known = 1;
  o->known = max(1, o->known);
  polymorph(o->blessing);
}
