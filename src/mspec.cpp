/* omega copyright (c) 1987,1988,1989 by Laurence Raphael Brothers */
/* mspec.c */
/* monster special functions */

#include "glob.h"

void m_sp_mp(monster* m)
{
  if (m->attacked && (random_range(3) == 1))
  {
    mprint("You feel cursed!");
    p_damage(10, UNSTOPPABLE, "a mendicant priest's curse");
    m_vanish(m);
  }
  else if (!m_statusp(m, NEEDY))
  {
    mprint("The mendicant priest makes a mystical gesture....");
    mprint("You feel impressed...");
    player.alignment += 5;
    if (player.alignment > 20)
      player.hp = max(player.hp, player.maxhp);
    m_vanish(m);
  }
}

void m_sp_ng(monster* m)
{
  if (distance(m->x, m->y, player.x, player.y) < 2)
    if ((random_range(5) == 1) || (player.status[VULNERABLE] > 0))
    {
      mprint("The night gaunt grabs you and carries you off!");
      mprint("Its leathery wings flap and flap, and it giggles insanely.");
      mprint("It tickles you cunningly to render you incapable of escape.");
      mprint("Finally, it deposits you in a strange place.");
      p_teleport(0);
    }
}

void m_sp_poison_cloud(monster* m)
{
  if (distance(m->x, m->y, player.x, player.y) < 3)
  {
    mprint("A cloud of poison gas surrounds you!");
    if (player.status[BREATHING] > 0)
      mprint("You can breathe freely, however.");
    else
      p_poison(7);
  }
}

void m_sp_explode(monster* m)
{
  if ((distance(player.x, player.y, m->x, m->y) < 2) &&
      (m->hp > 0) &&
      (m->hp < Monsters[m->id].hp))
    fball(m->x, m->y, m->x, m->y, m->hp);
}

void m_sp_demon(monster* m)
{
  int mid;

  if (random_range(2))
  {
    if ((m->id != INCUBUS) && /*succubi don't give fear */
        los_p(m->x, m->y, player.x, player.y) &&
        (random_range(30) > player.level + 10) &&
        (player.status[AFRAID] == 0))
    {
      mprint("You are stricken with fear!");
      if (!p_immune(FEAR))
        player.status[AFRAID] += m->level;
      else
        mprint("You master your reptile brain and stand fast.");
    }
    else
      m_sp_spell(m);
  }
  if ((m->hp < (m->level * 5)) && (m->hp > 1))
  {
    mprint("The demon uses its waning lifeforce to summon help!");
    m->hp = 1;
    switch (m->level)
    {
    case 3:
      mid = NIGHT_GAUNT;
      break;
    case 4:
    case 5:
      mid = L_FDEMON;
      break; /* lesser frost demon */
    case 6:
      mid = FROST_DEMON;
      break;
    case 7:
      mid = OUTER_DEMON;
      break; /* outer circle demon */
    case 8:
      mid = DEMON_SERP;
      break; /* demon serpent */
    case 9:
      mid = INNER_DEMON;
      break; /* inner circle demon */
    }
    summon(-1, mid);
    summon(-1, mid);
  }
}

void m_sp_acid_cloud(monster* m)
{
  if (m_statusp(m, HOSTILE) &&
      (distance(m->x, m->y, player.x, player.y) < 3))
    acid_cloud();
}

void m_sp_escape(monster* m)
{
  if (m_statusp(m, HOSTILE))
    m_vanish(m);
}

void m_sp_ghost(monster* m)
{
  if (m_statusp(m, HOSTILE))
  {
    mprint("The ghost moans horribly....");
    p_damage(1, FEAR, "a ghost-inspired heart attack");
    mprint("You've been terrorized!");
    if (!p_immune(FEAR))
      player.status[AFRAID] += m->level;
    else
      mprint("You master your reptile brain and stand fast.");
  }
}

/* random spell cast by monster */
void m_sp_spell(monster* m)
{
  char action[80];
  if (m_statusp(m, HOSTILE) && los_p(player.x, player.y, m->x, m->y))
  {
    if (m->uniqueness == COMMON)
      strcpy(action, "The ");
    else
      strcpy(action, "");
    strcat(action, m->monstring);
    strcat(action, " casts a spell...");
    mprint(action);
    if (!magic_resist(m->level))
      switch (random_range(m->level + 7))
      {
      case 0:
        nbolt(m->x, m->y, player.x, player.y, m->hit, 10);
        break;
      case 1:
        mprint("It seems stronger...");
        m->hp += random_range(m->level * m->level);
        break;
      case 2:
        haste(-1);
        break;
      case 3:
        cure(-1);
        break;
      case 4:
        /* WDT: I'd like to make this (and "case 5" below) dependant on
       * the monster's IQ in some way -- dumb but powerful monsters
       * deserve what they get :).  No rush. */
        if (m_immunityp(m, ELECTRICITY) ||
            distance(m->x, m->y, player.x, player.y) > 2)
          lball(m->x, m->y, player.x, player.y, 20);
        else
          lbolt(m->x, m->y, player.x, player.y, m->hit, 20);
        break;
      case 5:
        if (m_immunityp(m, COLD) ||
            distance(m->x, m->y, player.x, player.y) > 2)
          snowball(m->x, m->y, player.x, player.y, 30);
        else
          icebolt(m->x, m->y, player.x, player.y, m->hit, 30);
        break;
      case 6:
        enchant(-1);
        break;
      case 7:
        bless(0 - m->level);
        break;
      case 8:
        p_poison(m->level);
        break;
      case 9:
        sleep_player(m->level / 2);
        break;
      case 10:
        fbolt(m->x, m->y, player.x, player.y, m->hit * 3, 50);
        break;
      case 11:
        acquire(0 - m->level);
        break;
      case 12:
        dispel(-1);
        break;
      case 13:
        disrupt(player.x, player.y, 50);
        break;
      case 14:
        if (m->uniqueness == COMMON)
        {
          strcpy(Str2, "a ");
          strcat(Str2, m->monstring);
        }
        else
          strcpy(Str2, m->monstring);
        level_drain(m->level, Str2);
        break;
      case 15:
      case 16:
        disintegrate(player.x, player.y);
        break;
      }
  }
}

/* monsters with this have some way to hide, camouflage, etc until they 
   attack */
void m_sp_surprise(monster* m)
{
  if (m->attacked)
  {
    if (m_statusp(m, HOSTILE) &&
        (!player.status[TRUESIGHT]) &&
        m_statusp(m, M_INVISIBLE))
    {
      m->monchar = Monsters[m->id].monchar;
      if (!player.status[ALERT])
      {
        switch (random_range(4))
        {
        case 0:
          mprint("You are surprised by a sudden treacherous attack!");
          break;
        case 1:
          mprint("You are shocked out of your reverie by the scream of battle!");
          break;
        case 2:
          mprint("Suddenly, from out of the shadows, a surprise attack!");
          break;
        case 3:
          mprint("A shriek of hatred causes you to momentarily freeze up!");
          break;
        }
        morewait();
        setgamestatus(SKIP_PLAYER);
        m_status_reset(m, M_INVISIBLE);
      }
      else
      {
        mprint("You alertly sense the presence of an attacker!");
        m_status_reset(m, M_INVISIBLE);
      }
    }
  }
}

void m_sp_whistleblower(monster* m)
{
  if (m_statusp(m, HOSTILE))
  {
    alert_guards();
    m->specialf = M_MELEE_NORMAL;
  }
}

void m_sp_seductor(monster* m)
{
  if (m_statusp(m, HOSTILE))
  {
    if (m->uniqueness == COMMON)
    {
      strcpy(Str2, "The ");
      strcat(Str2, m->monstring);
    }
    else
      strcpy(Str2, m->monstring);
    strcat(Str2, " runs away screaming for help....");
    mprint(Str2);
    m_vanish(m);
    summon(-1, -1);
    summon(-1, -1);
    summon(-1, -1);
  }
  else if (distance(player.x, player.y, m->x, m->y) < 2)
    m_talk_seductor(m);
}

void m_sp_demonlover(monster* m)
{
  if (distance(player.x, player.y, m->x, m->y) < 2)
    m_talk_demonlover(m);
}

void m_sp_eater(monster* m)
{
  int i;
  if (player.rank[COLLEGE])
    m_status_set(m, HOSTILE);
  if (m_statusp(m, HOSTILE))
    if (los_p(m->x, m->y, player.x, player.y))
    {
      mprint("A strange numbing sensation comes over you...");
      morewait();
      player.mana = player.mana / 2;
      if (random_range(4))
        enchant(-1);
      else
        dispel(-1);
      player.pow--;
      if (--player.pow < 1)
        p_death("the Eater of Magic");
    }
  if (m->hp < 10)
  {
    mprint("The Eater explodes in a burst of mana!");
    manastorm(m->x, m->y, 1000);
  }
}

void m_sp_dragonlord(monster* m)
{
  if (m_statusp(m, HOSTILE))
  {
    if (distance(m->x, m->y, player.x, player.y) < 2)
    {
      if (!player.status[IMMOBILE])
      {
        mprint("A gust of wind from the Dragonlord's wings knocks you down!");
        p_damage(25, NORMAL_DAMAGE, "a gust of wind");
        setgamestatus(SKIP_PLAYER);
        player.status[IMMOBILE] += 2;
      }
      else if (!Constriction)
      {
        mprint("The Dragonlord grabs you with his tail!");
        Constriction = 25;
        player.status[IMMOBILE] += 1;
      }
      else if (random_range(2))
      {
        mprint("The coils squeeze tighter and tighter...");
        p_damage(Constriction, NORMAL_DAMAGE, "the Dragonlord");
        player.status[IMMOBILE] += 1;
        Constriction *= 2;
      }
      else
      {
        mprint("The Dragonlord hurls you to the ground!");
        p_damage(2 * Constriction, NORMAL_DAMAGE, "the Dragonlord");
        Constriction = 0;
      }
      m_sp_spell(m);
    }
    else
    {
      Constriction = 0;
      if (view_los_p(m->x, m->y, player.x, player.y))
      {
        if ((!player.immunity[FEAR]) && (!player.status[AFRAID]))
        {
          mprint("You are awestruck at the sight of the Dragonlord.");
          player.status[AFRAID] += 5;
        }
        if (random_range(3))
        {
          m_sp_spell(m);
          m_sp_spell(m);
        }
      }
    }
  }
  else if (distance(m->x, m->y, player.x, player.y) < 2)
    mprint("You are extremely impressed at the sight of the Dragonlord.");
}

void m_sp_blackout(monster* m)
{
  if ((distance(m->x, m->y, player.x, player.y) < 4) &&
      (player.status[BLINDED] == 0))
  {
    mprint("The fungus emits a burst of black spores. You've been blinded!");
    if (player.status[TRUESIGHT] > 0)
      mprint("The blindness quickly passes.");
    else
      player.status[BLINDED] += 4;
  }
  if (loc_statusp(m->x, m->y, LIT))
  {
    mprint("The fungus chirps.... ");
    mprint("The area is plunged into darkness.");
    torch_check();
    torch_check();
    torch_check();
    torch_check();
    torch_check();
    torch_check();
    spreadroomdark(m->x, m->y, level->site[m->x][m->y].roomnumber);
    levelrefresh();
  }
}

void m_sp_bogthing(monster* m)
{
  if (player.status[IMMOBILE] &&
      (distance(player.x, player.y, m->x, m->y) < 2))
  {
    if (!player.status[AFRAID])
    {
      mprint("As the bogthing touches you, you feel a frisson of terror....");
      if (player.immunity[FEAR])
        mprint("which you shake off.");
      else
        player.status[AFRAID] += 2;
    }
    else
    {
      mprint("The bogthing's touch causes you scream in agony!");
      p_damage(50, UNSTOPPABLE, "fright");
      mprint("Your struggles grow steadily weaker....");
      player.con--;
      player.str--;
      if ((player.con < 3) || (player.str < 3))
        p_death("congestive heart failure");
    }
  }
}

void m_sp_were(monster* m)
{
  int mid;
  if (m_statusp(m, HOSTILE) || (Phase == 6))
  {
    do
      mid = random_range(ML9 - NML_0) + ML1;
    /* log npc, 0th level npc, high score npc or were-creature */
    while (mid == NPC || mid == ZERO_NPC ||
           mid == HISCORE_NPC || mid == WEREHUMAN ||
           (Monsters[mid].uniqueness != COMMON) ||
           (!m_statusp(&(Monsters[mid]), MOBILE)) ||
           (!m_statusp(&(Monsters[mid]), HOSTILE)));
    m->id = Monsters[mid].id;
    m->hp += Monsters[mid].hp;
    m->status |= Monsters[mid].status;
    m->ac = Monsters[mid].ac;
    m->dmg = Monsters[mid].dmg;
    m->speed = Monsters[mid].speed;
    m->immunity |= Monsters[mid].immunity;
    m->xpv += Monsters[mid].xpv;
    m->corpseweight = Monsters[mid].corpseweight;
    m->monchar = Monsters[mid].monchar;
    m->talkf = Monsters[mid].talkf;
    m->meleef = Monsters[mid].meleef;
    m->strikef = Monsters[mid].strikef;
    m->specialf = Monsters[mid].specialf;
    strcpy(Str1, "were-");
    strcat(Str1, Monsters[mid].monstring);
    strcpy(Str2, "dead were-");
    strcat(Str2, Monsters[mid].monstring);
    m->monstring = salloc(Str1);
    m->corpsestr = salloc(Str2);
    m->immunity += pow2(NORMAL_DAMAGE);
    if (los_p(m->x, m->y, player.x, player.y))
      mprint("You witness a hideous transformation!");
    else
      mprint("You hear a distant howl.");
  }
}

void m_sp_servant(monster* m)
{
  if ((m->id == SERV_LAW) && (player.alignment < 0))
    m_status_set(m, HOSTILE);
  else if ((m->id == SERV_CHAOS) && (player.alignment > 0))
    m_status_set(m, HOSTILE);
}

void m_sp_av(monster* m)
{
  if (player.mana > 0)
  {
    mprint("You feel a sudden loss of mana!");
    player.mana -= (max(0, 10 - distance(m->x, m->y, player.x, player.y)));
    dataprint();
  }
}

void m_sp_lw(monster* m)
{
  if (random_range(2))
  {
    if (level->site[m->x][m->y].locchar == FLOOR)
    {
      level->site[m->x][m->y].locchar = LAVA;
      level->site[m->x][m->y].p_locf = L_LAVA;
      lset(m->x, m->y, CHANGED);
    }
    else if (level->site[m->x][m->y].locchar == WATER)
    {
      level->site[m->x][m->y].locchar = FLOOR;
      level->site[m->x][m->y].p_locf = L_NO_OP;
      lset(m->x, m->y, CHANGED);
    }
  }
}

void m_sp_angel(monster* m)
{
  int mid, hostile = FALSE;
  switch (m->aux1)
  {
  case ATHENA:
  case ODIN:
    hostile = ((player.patron == HECATE) || (player.patron == SET));
    break;
  case SET:
  case HECATE:
    hostile = ((player.patron == ODIN) || (player.patron == ATHENA));
    break;
  case DESTINY:
    hostile = (player.patron != DESTINY);
    break;
  }
  if (hostile)
    m_status_set(m, HOSTILE);
  if (m_statusp(m, HOSTILE))
  {
    mprint("The angel summons a heavenly host!");
    switch (m->level)
    {
    case 9:
      mid = HIGH_ANGEL;
      break;
    case 8:
      mid = ANGEL;
      break;
    default:
    case 6:
      mid = PHANTOM;
      break;
    }
    summon(-1, mid);
    summon(-1, mid);
    summon(-1, mid);
    /* prevent angel from summoning infinitely */
    m->specialf = M_NO_OP;
  }
}

/* Could completely fill up level */
void m_sp_swarm(monster* m)
{
  if (random_range(5) == 1)
  {
    if (view_los_p(m->x, m->y, player.x, player.y))
      mprint("The swarm expands!");
    else
      mprint("You hear an aggravating humming noise.");
    summon(-1, SWARM);
  }
}

/* raise nearby corpses from the dead.... */
void m_sp_raise(monster* m)
{
  int x, y;
  Objectlist* t;
  for (x = m->x - 2; x <= m->x + 2; x++)
    for (y = m->y - 2; y <= m->y + 2; y++)
      if (inbounds(x, y))
        if (level->site[x][y].things != NULL)
          if (level->site[x][y].things->thing->id == CORPSEID)
          {
            mprint("The Zombie Overlord makes a mystical gesture...");
            summon(-1, level->site[x][y].things->thing->charge);
            t = level->site[x][y].things;
            level->site[x][y].things = level->site[x][y].things->next;
            delete t;
          }
}

void m_sp_mb(monster* m)
{
  if (distance(m->x, m->y, player.x, player.y) == 1)
  {
    mprint("The manaburst explodes!");
    if (m_statusp(m, HOSTILE))
    {
      mprint("You get blasted!");
      p_damage(random_range(100), UNSTOPPABLE, "a manaburst");
      mprint("You feel cold all over!");
      player.pow -= 3;
      player.iq--;
      player.con--;
      player.str -= 2;
      player.dex--;
      player.agi--;
      dispel(-1);
    }
    else
    {
      mprint("You feel toasty warm inside!");
      player.pow++;
      player.mana = max(player.mana, calcmana());
      player.hp = max(player.hp, ++player.maxhp);
    }
    m->hp = 0;
  }
}

void m_sp_mirror(monster* m)
{
  int i, x, y;
  if (view_los_p(m->x, m->y, player.x, player.y))
  {
    if (random_range(20) + 6 < m->level)
    {
      summon(-1, m->id);
      mprint("You hear the sound of a mirror shattering!");
    }
    else
      for (i = 0; i < 5; i++)
      {
        x = m->x + random_range(13) - 6;
        y = m->y + random_range(13) - 6;
        if (inbounds(x, y))
        {
          level->site[x][y].showchar = m->monchar;
          putspot(x, y, m->monchar);
        }
      }
  }
}

void m_illusion(monster* m)
{
  int i = random_range(NUMMONSTERS);
  if (i == NPC || i == HISCORE_NPC || i == ZERO_NPC)
    i = m->id; /* can't imitate NPC */
  if (player.status[TRUESIGHT])
  {
    m->monchar = Monsters[m->id].monchar;
    m->monstring = Monsters[m->id].monstring;
  }
  else if (random_range(5) == 1)
  {
    m->monchar = Monsters[i].monchar;
    m->monstring = Monsters[i].monstring;
  }
}

void m_huge_sounds(monster* m)
{
  if (m_statusp(m, AWAKE) &&
      (!los_p(m->x, m->y, player.x, player.y)) &&
      (random_range(10) == 1))
    mprint("The dungeon shakes!");
}

void m_thief_f(monster* m)
{
  int i = random_item();
  if (random_range(3) == 1)
  {
    if (distance(player.x, player.y, m->x, m->y) < 2)
    {
      if (p_immune(THEFT) || (player.level > (m->level * 2) + random_range(20)))
        mprint("You feel secure.");
      else
      {
        if (i == ABORT)
          mprint("You feel fortunate.");
        else if ((player.possessions[i]->used) ||
                 (player.dex < m->level * random_range(10)))
        {
          mprint("You feel a sharp tug.... You hold on!");
        }
        else
        {
          mprint("You feel uneasy for a moment.");
          if (m->uniqueness == COMMON)
          {
            strcpy(Str2, "The ");
            strcat(Str2, m->monstring);
          }
          else
            strcpy(Str2, m->monstring);
          strcat(Str2, " suddenly runs away for some reason.");
          mprint(Str2);
          m_teleport(m);
          m->movef = M_MOVE_SCAREDY;
          m->specialf = M_MOVE_SCAREDY;
          m_pickup(m, player.possessions[i]);
          conform_unused_object(player.possessions[i]);
          player.possessions[i] = NULL;
        }
      }
    }
  }
}

void m_summon(monster* m)
{
  if ((distance(player.x, player.y, m->x, m->y) < 2) &&
      (random_range(3) == 1))
  {
    summon(0, -1);
    summon(0, -1);
  }
}

void m_aggravate(monster* m)
{

  if (m_statusp(m, HOSTILE))
  {
    if (m->uniqueness == COMMON)
    {
      strcpy(Str2, "The ");
      strcat(Str2, m->monstring);
    }
    else
      strcpy(Str2, m->monstring);
    strcat(Str2, " emits an irritating humming sound.");
    mprint(Str2);
    aggravate();
    m_status_reset(m, HOSTILE);
  }
}

void m_sp_merchant(monster* m)
{
  Monsterlist* ml;
  if (m_statusp(m, HOSTILE))
    if (Current_Environment == E_VILLAGE)
    {
      mprint("The merchant screams: 'Help! Murder! Guards! Help!'");
      mprint("You hear the sound of police whistles and running feet.");
      for (ml = level->mlist; ml != NULL; ml = ml->next)
      {
        m_status_set(ml->m, AWAKE);
        m_status_set(ml->m, HOSTILE);
      }
      m->specialf = M_NO_OP;
    }
}

/* The special function of the various people in the court of the archmage */
/* and the sorcerors' circle */
void m_sp_court(monster* m)
{
  Monsterlist* ml;
  if (m_statusp(m, HOSTILE))
  {
    mprint("A storm of spells hits you!");
    for (ml = level->mlist; ml != NULL; ml = ml->next)
    {
      m_status_set(ml->m, HOSTILE);
      m_sp_spell(ml->m);
      if (ml->m->specialf == M_SP_COURT)
        ml->m->specialf = M_SP_SPELL;
    }
  }
}

/* The special function of the dragons in the dragons' lair */
void m_sp_lair(monster* m)
{
  Monsterlist* ml;
  if (m_statusp(m, HOSTILE))
  {
    mprint("You notice a number of dragons waking up....");
    mprint("You are struck by a quantity of firebolts.");
    morewait();
    for (ml = level->mlist; ml != NULL; ml = ml->next)
      if (ml->m->hp > 0 && ml->m->specialf == M_SP_LAIR)
      {
        m_status_set(ml->m, HOSTILE);
        fbolt(ml->m->x, ml->m->y, player.x, player.y, 100, 100);
        if (ml->m->id == DRAGON_LORD)
          ml->m->specialf = M_SP_DRAGONLORD;
        else
          ml->m->specialf = M_STRIKE_FBOLT;
      }
  }
}

void m_sp_prime(monster* m)
{
  if (m_statusp(m, HOSTILE))
  {
    mprint("The prime sorceror gestures and a pentacular gate opens!");
    mprint("You are surrounded by demons!");
    summon(-1, DEMON_PRINCE);
    summon(-1, DEMON_PRINCE);
    summon(-1, DEMON_PRINCE);
    summon(-1, DEMON_PRINCE);
  }
  m->specialf = M_SP_SPELL;
}
