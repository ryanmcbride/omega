/* omega copyright (C) by Laurence Raphael Brothers, 1987,1988,1989 */
/* trap.c */
/* trap movement functions */

#include "glob.h"

/* various traps */

/* note special function on different levels */
void l_trap_siren()
{
  Monsterlist* ml;
  level->site[player.x][player.y].locchar = TRAP;
  lset(player.x, player.y, CHANGED);
  print1("A klaxon goes off!");
  print2("'Intruder Alert -- Intruder Alert -- Intruder Alert'");
  print3("You have the feeling you have been discovered....");
  morewait();
  clearmsg();
  if ((Current_Environment == E_HOUSE) ||
      (Current_Environment == E_MANSION))
  {
    if (!gamestatusp(DESTROYED_ORDER))
    {
      print1("The city guard arrives!");
      print2("You are apprehended....");
      morewait();
      send_to_jail();
    }
    else
      print1("Nobody answers the alarm.");
  }
  else if (Current_Environment == E_HOVEL)
    print1("Nobody answers the alarm.");
  else
  {
    if (Current_Environment == E_CIRCLE)
    {
      summon(-1, DEMON_PRINCE); /* prime circle demon */
      summon(-1, DEMON_PRINCE);
      summon(-1, DEMON_PRINCE);
    }
    for (ml = level->mlist; ml != NULL; ml = ml->next)
    {
      m_status_set(ml->m, AWAKE);
      ml->m->sense *= 2;
      if ((Current_Environment == E_CIRCLE) ||
          ((Current_Environment == E_VILLAGE) && (ml->m->id == GUARD)) ||
          ((Current_Environment == E_CITY) && (ml->m->id == GUARD)))
        m_status_set(ml->m, HOSTILE);
    }
  }
}

void l_trap_dart()
{
  level->site[player.x][player.y].locchar = TRAP;
  lset(player.x, player.y, CHANGED);
  if (gamestatusp(MOUNTED))
  {
    mprint("A dart annoys your horse....");
  }
  else if (random_range(100) < player.absorption)
    mprint("A dart plinks off your armor");
  else
  {
    mprint("You were hit by a dart!");
    p_damage(difficulty(), NORMAL_DAMAGE, "a dart trap");
    if (random_range(3) == 1)
    {
      mprint("It was poisoned!");
      morewait();
      p_poison(difficulty());
    }
  }
}

void l_trap_pit()
{
  level->site[player.x][player.y].locchar = TRAP;
  lset(player.x, player.y, CHANGED);
  if (gamestatusp(MOUNTED))
  {
    mprint("Your horse stumbles into a pit and breaks a leg!");
    morewait();
    mprint("You are forced to put it out of its misery.");
    morewait();
    resetgamestatus(MOUNTED);
    showflags();
  }
  else if (player.itemweight < ((int)(player.maxweight / 2)))
    mprint("You nimbly dodge a pit trap.");
  else
  {
    mprint("You fell into a pit!");
    if (random_range(3) == 1)
    {
      mprint("And were impaled by spikes!");
      morewait();
      p_damage(difficulty() * 5, NORMAL_DAMAGE, "a spiked pit");
    }
    else
      p_damage(difficulty() * 2, NORMAL_DAMAGE, "a pit");
    player.status[IMMOBILE]++;
  }
}

void l_trap_door()
{
  if (Current_Environment != Current_Dungeon)
    mprint("You feel oddly lucky.");
  else
  {
    level->site[player.x][player.y].locchar = TRAP;
    lset(player.x, player.y, CHANGED);
    if (gamestatusp(MOUNTED))
    {
      mprint("You and your horse fall through a trap door!");
      morewait();
      mprint("Your horse breaks its back. Snif.");
      morewait();
      if (level->site[player.x][player.y].aux != S_DISINTEGRATE)
      {
        mprint("You're hit by a rockslide!");
        morewait();
        p_damage(level->depth * difficulty(), UNSTOPPABLE, "a rockslide");
      }
      change_level(level->depth, level->depth + 1, FALSE);
      resetgamestatus(MOUNTED);
      showflags();
      roomcheck();
    }
    else if (random_range(100) < player.agi)
      mprint("You leap over a trap door.");
    else
    {
      mprint("You fell through a trap door!");
      morewait();
      p_damage(difficulty(), NORMAL_DAMAGE, "a trap door");
      if (level->site[player.x][player.y].aux != S_DISINTEGRATE)
      {
        mprint("You're hit by a rockslide!");
        morewait();
        p_damage(level->depth * difficulty(), UNSTOPPABLE, "a rockslide");
      }
      change_level(level->depth, level->depth + 1, FALSE);
      roomcheck();
    }
  }
}

void l_trap_snare()
{
  level->site[player.x][player.y].locchar = TRAP;
  lset(player.x, player.y, CHANGED);
  if (gamestatusp(MOUNTED))
    mprint("Your horse steps out of a snare trap.");
  else if (random_range(100) < player.agi)
    mprint("You agilely avoid a snare.");
  else
  {
    mprint("You were caught in a snare!");
    player.status[IMMOBILE] += difficulty();
  }
}

void l_trap_blade()
{
  level->site[player.x][player.y].locchar = TRAP;
  lset(player.x, player.y, CHANGED);
  if (random_range(30) < player.agi + player.level)
    mprint("You duck under a scything blade!");
  else
  {
    if (gamestatusp(MOUNTED))
    {
      mprint("Your horse is struck by a scything blade and killed instantly.");
      morewait();
      resetgamestatus(MOUNTED);
      showflags();
    }
    else
    {
      mprint("A heavy blade scythes across the room and hits you!");
      morewait();
      p_damage(random_range(difficulty() * 3) + difficulty() - player.absorption,
               NORMAL_DAMAGE,
               "a blade trap");
    }
  }
}

void l_trap_fire()
{
  if (gamestatusp(MOUNTED))
  {
    mprint("Your horse is struck by a blast of fire and is charbroiled!");
    morewait();
    resetgamestatus(MOUNTED);
    showflags();
  }
  else if (random_range(50) < player.agi + player.level)
    mprint("You dodge a pillar of fire!");
  else
  {
    mprint("You were blasted by a fire trap!");
    morewait();
    p_damage(random_range((difficulty() + 1) * 5), FLAME, "a fire trap");
  }
  level->site[player.x][player.y].locchar = FIRE;
  level->site[player.x][player.y].p_locf = L_FIRE;
  lset(player.x, player.y, CHANGED);
}

void l_trap_teleport()
{
  level->site[player.x][player.y].locchar = TRAP;
  lset(player.x, player.y, CHANGED);
  mprint("You experience a momentary disorientation....");
  morewait();
  if (random_range(10000) > difficulty() * difficulty())
    p_teleport(0);
  else
    p_teleport(-1);
}

void l_trap_disintegrate()
{
  level->site[player.x][player.y].locchar = TRAP;
  lset(player.x, player.y, CHANGED);
  mprint("Oh, no! A disintegration trap!");
  morewait();
  if (gamestatusp(MOUNTED))
  {
    mprint("Your horse falls apart into its component atoms...");
    morewait();
    resetgamestatus(MOUNTED);
    showflags();
  }
  disintegrate(player.x, player.y);
}

void l_trap_sleepgas()
{
  level->site[player.x][player.y].locchar = TRAP;
  lset(player.x, player.y, CHANGED);
  mprint("Hsssssssss....");
  morewait();
  mprint("You detect a strange odor....");
  morewait();
  sleep_player((difficulty() / 5) + 1);
}

void l_trap_acid()
{
  int i, k, itemdamage;
  level->site[player.x][player.y].locchar = TRAP;
  lset(player.x, player.y, CHANGED);
  if (player.agi + player.level < random_range(100))
  {
    mprint("You are drenched by a spray of acid!");
    morewait();
    if (gamestatusp(MOUNTED))
    {
      mprint("Your horse dies unpleasantly.");
      morewait();
      resetgamestatus(MOUNTED);
      showflags();
    }
    p_damage(random_range(difficulty() * 5), ACID, "an acid trap");
    if (!p_immune(ACID))
    {
      mprint("The acid seeps over your possessions...");
      morewait();
      itemdamage = random_range(5);
      for (i = k = 0; ((i < MAXITEMS) && (k < itemdamage)); i++)
        if (player.possessions[i] != NULL)
        {
          k++;
          (void)damage_item(player.possessions[i]);
        }
    }
  }
  else
    mprint("You somehow dodge a shower of hydroflouric acid!");
}

void l_trap_abyss()
{
  level->site[player.x][player.y].locchar = ABYSS;
  lset(player.x, player.y, CHANGED);
  if (gamestatusp(MOUNTED))
  {
    mprint("You and your horse fall into the infinite abyss!");
    morewait();
    l_abyss();
  }
  if (player.dex + player.level < random_range(100))
  {
    mprint("You stumble over a concealed entrance to the abyss!");
    morewait();
    l_abyss();
  }
  else
    mprint("You gingerly step around a concealed entrance to the abyss!");
}

void l_trap_manadrain()
{
  level->site[player.x][player.y].locchar = TRAP;
  lset(player.x, player.y, CHANGED);
  if (player.mana == 0)
  {
    if (random_range(10) == 3)
    {
      mprint("The manadrain trap overloads -- positive feedback....");
      mprint("That's strange.... You feel repowered!");
      morewait();
      level->site[player.x][player.y].locchar = FLOOR;
      level->site[player.x][player.y].p_locf = L_NO_OP;
      lset(player.x, player.y, CHANGED);
      player.mana = calcmana();
    }
    else
      mprint("You feel strangely unaffected by the manadrain trap.");
  }
  else
  {
    mprint("A weird rainbow light seems to play over you....");
    mprint("You feel drained.");
    morewait();
    while (player.mana > 1)
    {
      player.mana /= 2;
      dataprint();
    }
    player.mana = 0;
    dispel(-1);
  }
}
