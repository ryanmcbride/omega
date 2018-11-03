/* omega copyright (C) by Laurence Raphael Brothers, 1987,1988,1989 */
/* effect2.c */

#include "glob.h"

void knowledge(int blessing)
{
  if (blessing < 0)
    mprint("You feel ignorant.");
  else
  {
    mprint("You feel knowledgeable!");
    menuclear();
    menuprint("Current Point Total: ");
    menulongprint(calc_points());
    menuprint("\nAlignment:");
    if (player.alignment == 0)
      menuprint("Neutral, embodying the Cosmic Balance");
    else if (abs(player.alignment) < 10)
      menuprint("Neutral, tending toward ");
    else if (abs(player.alignment) < 50)
      menuprint("Neutral-");
    else if (abs(player.alignment) < 100)
      ;
    else if (abs(player.alignment) < 200)
      menuprint("Servant of ");
    else if (abs(player.alignment) < 400)
      menuprint("Master of ");
    else if (abs(player.alignment) < 800)
      menuprint("The Essence of ");
    else
      menuprint("The Ultimate Avatar of ");
    if (player.alignment < 0)
      menuprint("Chaos\n");
    else if (player.alignment > 0)
      menuprint("Law\n");
    showmenu();
    morewait();
    menuclear();
    menuprint("Current stati:\n");
    if (player.status[BLINDED])
      menuprint("Blinded\n");
    if (player.status[SLOWED])
      menuprint("Slowed\n");
    if (player.status[HASTED])
      menuprint("Hasted\n");
    if (player.status[DISPLACED])
      menuprint("Displaced\n");
    if (player.status[SLEPT])
      menuprint("Slept\n");
    if (player.status[DISEASED])
      menuprint("Diseased\n");
    if (player.status[POISONED])
      menuprint("Poisoned\n");
    if (player.status[BREATHING])
      menuprint("Breathing\n");
    if (player.status[INVISIBLE])
      menuprint("Invisible\n");
    if (player.status[REGENERATING])
      menuprint("Regenerating\n");
    if (player.status[VULNERABLE])
      menuprint("Vulnerable\n");
    if (player.status[BERSERK])
      menuprint("Berserk\n");
    if (player.status[IMMOBILE])
      menuprint("Immobile\n");
    if (player.status[ALERT])
      menuprint("Alert\n");
    if (player.status[AFRAID])
      menuprint("Afraid\n");
    if (player.status[ACCURATE])
      menuprint("Accurate\n");
    if (player.status[HERO])
      menuprint("Heroic\n");
    if (player.status[LEVITATING])
      menuprint("Levitating\n");
    if (player.status[TRUESIGHT]) /* FIXED! 12/30/98 DG */
      menuprint("Sharp\n");
    if (player.status[SHADOWFORM])
      menuprint("Shadowy\n");
    if (player.status[ILLUMINATION])
      menuprint("Glowing\n");
    if (player.status[DEFLECTION])
      menuprint("Buffered\n");
    if (player.status[RETURNING])
      menuprint("Returning\n");
    showmenu();
    morewait();
    menuclear();
    menuprint("Immunities:\n");
    if (p_immune(NORMAL_DAMAGE))
      menuprint("Normal Damage\n");
    if (p_immune(FLAME))
      menuprint("Flame\n");
    if (p_immune(ELECTRICITY))
      menuprint("Electricity\n");
    if (p_immune(COLD))
      menuprint("Cold\n");
    if (p_immune(POISON))
      menuprint("Poison\n");
    if (p_immune(ACID))
      menuprint("Acid\n");
    if (p_immune(FEAR))
      menuprint("Fear\n");
    if (p_immune(SLEEP))
      menuprint("Sleep\n");
    if (p_immune(NEGENERGY))
      menuprint("Negative Energies\n");
    if (p_immune(THEFT))
      menuprint("Theft\n");
    if (p_immune(GAZE))
      menuprint("Gaze\n");
    if (p_immune(INFECTION))
      menuprint("Infection\n");
    showmenu();
    morewait();
    menuclear();
    menuprint("Ranks:\n");
    switch (player.rank[LEGION])
    {
    case COMMANDANT:
      menuprint("Commandant of the Legion");
      break;
    case COLONEL:
      menuprint("Colonel of the Legion");
      break;
    case FORCE_LEADER:
      menuprint("Force Leader of the Legion");
      break;
    case CENTURION:
      menuprint("Centurion of the Legion");
      break;
    case LEGIONAIRE:
      menuprint("Legionaire");
      break;
    }
    if (player.rank[LEGION] > 0)
    {
      menuprint(" (");
      menunumprint(player.guildxp[LEGION]);
      menuprint(" XP).\n");
    }
    switch (player.rank[ARENA])
    {
    case -1:
      menuprint("Ex-gladiator\n");
      break;
    case CHAMPION:
      menuprint("Gladiator Champion");
      break;
    case GLADIATOR:
      menuprint("Gladiator of the Arena");
      break;
    case RETIARIUS:
      menuprint("Retiarius of the Arena");
      break;
    case BESTIARIUS:
      menuprint("Bestiarius of the Arena");
      break;
    case TRAINEE:
      menuprint("Gladiator Trainee of the Arena");
      break;
    }
    if (player.rank[ARENA] > 0)
    {
      menuprint(" (Opponent ");
      menunumprint(Arena_Opponent);
      menuprint(")\n");
    }
    switch (player.rank[COLLEGE])
    {
    case ARCHMAGE:
      menuprint("Archmage of the Collegium Magii");
      break;
    case MAGE:
      menuprint("Collegium Magii: Mage");
      break;
    case PRECEPTOR:
      menuprint("Collegium Magii: Preceptor");
      break;
    case STUDENT:
      menuprint("Collegium Magii: Student");
      break;
    case NOVICE:
      menuprint("Collegium Magii: Novice");
      break;
    }
    if (player.rank[COLLEGE] > 0)
    {
      menuprint(" (");
      menunumprint(player.guildxp[COLLEGE]);
      menuprint(" XP).\n");
    }
    switch (player.rank[NOBILITY])
    {
    case DUKE:
      menuprint("Duke of Rampart");
      break;
    case LORD:
      menuprint("Peer of the Realm");
      break;
    case KNIGHT:
      menuprint("Order of the Knights of Rampart");
      break;
    case ESQUIRE:
      menuprint("Squire of Rampart");
      break;
    case COMMONER:
      menuprint("Commoner");
      break;
    default:
      menuprint("Lowly Commoner\n");
      break;
    }
    if (player.rank[NOBILITY] > 1)
    {
      menuprint(" (");
      menunumprint(player.rank[NOBILITY] - 1);
      menuprint(ordinal(player.rank[NOBILITY] - 1));
      menuprint(" Quest Completed)\n");
    }
    else if (player.rank[NOBILITY] == 1)
    {
      menuprint(" (1st Quest Undertaken)\n");
    }
    switch (player.rank[CIRCLE])
    {
    case -1:
      menuprint("Former member of the Circle.\n");
      break;
    case PRIME:
      menuprint("Prime Sorceror of the Inner Circle");
      break;
    case HIGHSORCEROR:
      menuprint("High Sorceror of the Inner Circle");
      break;
    case SORCEROR:
      menuprint("Member of the Circle of Sorcerors");
      break;
    case ENCHANTER:
      menuprint("Member of the Circle of Enchanters");
      break;
    case INITIATE:
      menuprint("Member of the Circle of Initiates");
      break;
    }
    if (player.rank[CIRCLE] > 0)
    {
      menuprint(" (");
      menunumprint(player.guildxp[CIRCLE]);
      menuprint(" XP).\n");
    }
    switch (player.rank[ORDER])
    {
    case -1:
      menuprint("Washout from the Order of Paladins\n");
      break;
    case JUSTICIAR:
      menuprint("Justiciar of the Order of Paladins");
      break;
    case PALADIN:
      menuprint("Paladin of the Order");
      break;
    case CHEVALIER:
      menuprint("Chevalier of the Order");
      break;
    case GUARDIAN:
      menuprint("Guardian of the Order");
      break;
    case GALLANT:
      menuprint("Gallant of the Order");
      break;
    }
    if (player.rank[ORDER] > 0)
    {
      menuprint(" (");
      menunumprint(player.guildxp[ORDER]);
      menuprint(" XP).\n");
    }
    switch (player.rank[THIEVES])
    {
    case SHADOWLORD:
      menuprint("Guild of Thieves: Shadowlord");
      break;
    case TMASTER:
      menuprint("Guild of Thieves: Master Thief");
      break;
    case THIEF:
      menuprint("Guild of Thieves: Thief");
      break;
    case ATHIEF:
      menuprint("Guild of Thieves: Apprentice Thief");
      break;
    case TMEMBER:
      menuprint("Guild of Thieves: Candidate Member");
      break;
    }
    if (player.rank[THIEVES] > 0)
    {
      menuprint(" (");
      menunumprint(player.guildxp[THIEVES]);
      menuprint(" XP).\n");
    }
    switch (player.rank[PRIESTHOOD])
    {
    case LAY:
      menuprint("A lay devotee of ");
      break;
    case ACOLYTE:
      menuprint("An Acolyte of ");
      break;
    case PRIEST:
      menuprint("A Priest of ");
      break;
    case SPRIEST:
      menuprint("A Senior Priest of ");
      break;
    case HIGHPRIEST:
      menuprint("The High Priest of ");
      break;
    }
    switch (player.patron)
    {
    case ODIN:
      menuprint("Odin");
      break;
    case SET:
      menuprint("Set");
      break;
    case ATHENA:
      menuprint("Athena");
      break;
    case HECATE:
      menuprint("Hecate");
      break;
    case DRUID:
      menuprint("Druidism");
      break;
    case DESTINY:
      menuprint("the Lords of Destiny");
      break;
    }
    if (player.rank[PRIESTHOOD] > 0)
    {
      menuprint(" (");
      menunumprint(player.guildxp[PRIESTHOOD]);
      menuprint(" XP).\n");
    }
    switch (player.rank[WEREWOLF])
    {
    case PUP:
      menuprint("Werewolf Pack: Pup");
      break;
    case DELTA:
      menuprint("Werewolf Pack: Delta");
      break;
    case BETA:
      menuprint("Werewolf Pack: Beta");
      break;
    case ALPHA:
      menuprint("Werewolf Pack: Alpha");
      break;
    case KING:
      menuprint("Werewolf Pack: King");
      break;
    }
    if (player.rank[WEREWOLF] > 0)
    {
      menuprint(" (");
      menunumprint(player.guildxp[WEREWOLF]);
      menuprint(" XP).\n");
    }
    if (player.rank[ADEPT] > 0)
      menuprint("**************\n*Omegan Adept*\n**************\n");
    showmenu();
    morewait();
    xredraw();
  }
}

/* Recreates the current level */
void flux(int blessing)
{
  mprint("The universe warps around you!");
  if (Current_Environment == E_CITY)
  {
    mprint("Sensing dangerous high order magic, the Collegium Magii");
    mprint("and the Circle of Sorcerors join forces to negate the spell.");
    mprint("You are zapped by an antimagic ray!!!");
    dispel(-1);
    mprint("The universe unwarps itself....");
  }
  else if (Current_Environment != Current_Dungeon)
    mprint("Odd.... No effect!");
  else
  {
    mprint("You stagger as the very nature of reality warps!");
    erase_level();
    level->generated = FALSE;
    mprint("The fabric of spacetime reknits....");
    change_level(level->depth - 1, level->depth, TRUE);
  }
}

/*Turns on displacement status for the player */
void displace(int blessing)
{
  if (blessing > -1)
  {
    mprint("You feel a sense of dislocation.");
    player.status[DISPLACED] = blessing + random_range(6);
  }
  else
  {
    mprint("You feel vulnerable");
    player.status[VULNERABLE] += random_range(6) - blessing;
  }
}

void invisible(int blessing)
{
  if (blessing > -1)
  {
    mprint("You feel transparent!");
    player.status[INVISIBLE] += 2 + 5 * blessing;
  }
  else
  {
    mprint("You feel dangerous!");
    player.status[VULNERABLE] +=
        random_range(10) + 1;
  }
}

void warp(int blessing)
{
  int newlevel;
  if (Current_Environment != Current_Dungeon)
    mprint("How strange! No effect....");
  else
  {
    mprint("Warp to which level? ");
    newlevel = (int)parsenum();
    if (newlevel >= MaxDungeonLevels || blessing < 0 || newlevel < 1)
    {
      mprint("You have been deflected!");
      newlevel = random_range(MaxDungeonLevels - 1) + 1;
    }
    mprint("You dematerialize...");
    change_level(level->depth, newlevel, FALSE);
  }
  roomcheck();
}

void alert(int blessing)
{
  if (blessing > -1)
  {
    mprint("You feel on-the-ball.");
    player.status[ALERT] += 4 + (5 * blessing);
  }
  else
    sleep_player(abs(blessing) + 3);
}

void regenerate(int blessing)
{
  if (blessing < 0)
    heal(blessing * 10);
  else
  {
    mprint("You feel abnormally healthy.");
    player.status[REGENERATING] += (blessing + 1) * 50;
  }
}

void haste(int blessing)
{
  if (blessing > -1)
  {
    if (!player.status[HASTED])
      mprint("The world slows down!");
    else
      mprint("Nothing much happens.");
    if (player.status[SLOWED])
      player.status[SLOWED] = 0;
    player.status[HASTED] += (blessing * 100) + random_range(250);
  }
  else
  {
    mprint("You feel slower.");
    if (player.status[HASTED] > 0)
      mprint("...but the feeling quickly fades.");
    else
      player.status[SLOWED] += random_range(250) + 250;
  }
}

void recover_stat(int blessing)
{
  if (blessing < 0)
  {
    mprint("You feel a cold surge!");
    switch (random_range(6))
    {
    case 0:
      player.str = min(player.str - 1, player.maxstr - 1);
      break;
    case 1:
      player.con = min(player.con - 1, player.maxcon - 1);
      break;
    case 2:
      player.dex = min(player.dex - 1, player.maxdex - 1);
      break;
    case 3:
      player.agi = min(player.agi - 1, player.maxagi - 1);
      break;
    case 4:
      player.iq = min(player.iq - 1, player.maxiq - 1);
      break;
    case 5:
      player.pow = min(player.pow - 1, player.maxpow - 1);
      break;
    }
  }
  else
  {
    mprint("You feel a warm tingle!");
    player.str = max(player.str, player.maxstr);
    player.con = max(player.con, player.maxcon);
    player.dex = max(player.dex, player.maxdex);
    player.agi = max(player.agi, player.maxagi);
    player.iq = max(player.iq, player.maxiq);
    player.pow = max(player.pow, player.maxpow);
  }
  calc_melee();
}

void augment(int blessing)
{
  if (blessing < 0)
  {
    mprint("You feel a cold surge!");
    switch (random_range(6))
    {
    case 0:
      player.str = min(player.str - 1, player.maxstr - 1);
      break;
    case 1:
      player.con = min(player.con - 1, player.maxcon - 1);
      break;
    case 2:
      player.dex = min(player.dex - 1, player.maxdex - 1);
      break;
    case 3:
      player.agi = min(player.agi - 1, player.maxagi - 1);
      break;
    case 4:
      player.iq = min(player.iq - 1, player.maxiq - 1);
      break;
    case 5:
      player.pow = min(player.pow - 1, player.maxpow - 1);
      break;
    }
  }
  else if (blessing == 0)
  {
    mprint("You feel a warm tingle!");
    switch (random_range(6))
    {
    case 0:
      player.str = max(player.str + 1, player.maxstr + 1);
      break;
    case 1:
      player.con = max(player.con + 1, player.maxcon + 1);
      break;
    case 2:
      player.dex = max(player.dex + 1, player.maxdex + 1);
      break;
    case 3:
      player.agi = max(player.agi + 1, player.maxagi + 1);
      break;
    case 4:
      player.iq = max(player.iq + 1, player.maxiq + 1);
      break;
    case 5:
      player.pow = max(player.pow + 1, player.maxpow + 1);
      break;
    }
  }
  else
  {
    mprint("You feel a hot flash!");
    player.str = max(player.str + 1, player.maxstr + 1);
    player.con = max(player.con + 1, player.maxcon + 1);
    player.dex = max(player.dex + 1, player.maxdex + 1);
    player.agi = max(player.agi + 1, player.maxagi + 1);
    player.iq = max(player.iq + 1, player.maxiq + 1);
    player.pow = max(player.pow + 1, player.maxpow + 1);
  }
  calc_melee();
}

void breathe(int blessing)
{
  if (blessing > -1)
  {
    mprint("Your breath is energized!");
    player.status[BREATHING] += 6 + blessing;
  }
  else
  {
    mprint("You choke as your lungs fill with water!");
    p_damage(50, UNSTOPPABLE, "drowning");
  }
}

void i_chaos(Object* o)
{
  if (player.alignment < 0)
  {
    player.alignment -= random_range(20);
    mprint("You feel deliciously chaotic!");
    gain_experience(abs(player.alignment) * 10);
  }
  else
  {
    mprint("You feel a sense of inner turmoil!");
    player.alignment -= random_range(20);
  }
}

void i_law(Object* o)
{
  if (player.alignment > 0)
  {
    player.alignment += random_range(20);
    mprint("You feel wonderfully lawful!");
    gain_experience(player.alignment * 10);
  }
  else
  {
    mprint("You feel a sense of inner constraint!");
    player.alignment += random_range(20);
  }
}

void sanctify(int blessing)
{
  if (blessing > -1)
  {
    if (level->environment == E_TEMPLE)
      mprint("Odd, the spell has no effect. I wonder why.");
    else if (level->site[player.x][player.y].locchar == ALTAR)
      mprint("This site can't get any holier!");
    else if (player.patron == 0)
    {
      mprint("The gods are angered!");
      level->site[player.x][player.y].locchar = LAVA;
      level->site[player.x][player.y].p_locf = L_LAVA;
      lset(player.x, player.y, CHANGED);
      p_movefunction(L_LAVA);
    }
    else
    {
      level->site[player.x][player.y].locchar = ALTAR;
      level->site[player.x][player.y].aux = player.patron;
      level->site[player.x][player.y].p_locf = L_ALTAR;
      lset(player.x, player.y, CHANGED);
      mprint("You are standing on sacred ground!");
    }
  }
  else
  {
    if (level->site[player.x][player.y].locchar == ALTAR)
    {
      mprint("The altar crumbles before your unholy blast....");
      level->site[player.x][player.y].locchar = FLOOR;
      level->site[player.x][player.y].p_locf = L_NO_OP;
      lset(player.x, player.y, CHANGED);
      if (level->site[player.x][player.y].aux == player.patron)
      {
        mprint("Your deity is not amused....");
        p_damage(player.hp - 1, UNSTOPPABLE, "Divine Wrath");
      }
      else if ((player.patron == ATHENA) || (player.patron == ODIN))
      {
        if ((level->site[player.x][player.y].aux == SET) ||
            (level->site[player.x][player.y].aux == HECATE))
        {
          mprint("Your deity applauds the eradication of Chaos' taint");
          gain_experience(1000);
        }
        else
        {
          mprint("Your deity approves of your action.");
          gain_experience(100);
        }
      }
      else if ((player.patron == SET) || (player.patron == HECATE))
      {
        if ((level->site[player.x][player.y].aux == ODIN) ||
            (level->site[player.x][player.y].aux == ATHENA))
        {
          mprint("Your deity applauds the obliteration of Law");
          gain_experience(1000);
        }
        else
        {
          mprint("Your deity approves of your action.");
          gain_experience(100);
        }
      }
      else if (player.patron == DRUID)
      {
        mprint("Your attempt to maintain the Balance is applauded....");
        gain_experience(250);
      }
      else
        mprint("Nothing much happens");
    }
    else
      mprint("You feel an aura of unholiness arising from this spot....");
  }
}

void accuracy(int blessing)
{
  if (blessing > -1)
  {
    mprint("Everything seems covered in bullseyes!");
    player.status[ACCURACY] += random_range(5) + 1 + blessing * 5;
    calc_melee();
  }
  else
  {
    player.status[ACCURACY] = 0;
    calc_melee();
    mprint("Your vision blurs...");
  }
}
