/* omega copyright (C) 1987,1988,1989 by Laurence Raphael Brothers */
/* itemf2.c */

/* mostly ring, armor, and weapon functions */

#include "glob.h"

/* ring functions */
void i_perm_knowledge(Object* o)
{
  if (o->known < 1)
    o->known = 1;
  if (o->blessing > -1)
    Objects[o->id].known = 1;
  if (o->used)
    knowledge(o->blessing);
}

void i_perm_strength(Object* o)
{
  if (o->known < 1)
    o->known = 1;
  Objects[o->id].known = 1;
  if (o->used)
  {
    if (o->blessing > -1)
      player.str += abs(o->plus) + 1;
    else
      player.str -= abs(o->plus) + 1;
  }
  else
  {
    if (o->blessing > -1)
      player.str -= abs(o->plus) + 1;
    else
      player.str += abs(o->plus) + 1;
  }
  calc_melee();
}

void i_perm_burden(Object* o)
{
  int i;

  if (o->used)
  {
    o->weight = 1000;
    mprint("You feel heavier.");
  }
  else
  {
    o->weight = 1;
    mprint("Phew. What a relief.");
  }
  player.itemweight = 0;
  for (i = 0; i < MAXITEMS; i++)
  {
    if (player.possessions[i] != NULL)
      player.itemweight +=
          (player.possessions[i]->weight * player.possessions[i]->number);
  }
}

void i_perm_gaze_immune(Object* o)
{
  if (o->used)
    player.immunity[GAZE]++;
  else
    player.immunity[GAZE]--;
}

void i_perm_fire_resist(Object* o)
{
  if (o->used)
    player.immunity[FLAME]++;
  else
    player.immunity[FLAME]--;
}

void i_perm_poison_resist(Object* o)
{
  if (o->used)
  {
    if (o->blessing < 0)
    {
      player.immunity[POISON] = 0;
      p_poison(100);
    }
    else
    {
      player.immunity[POISON]++;
      if (player.status[POISONED] > 0)
      {
        mprint("You feel much better now.");
        player.status[POISONED] = 0;
      }
    }
  }
  else
  {
    player.status[POISONED] = 0;
    player.immunity[POISON]--;
  }
}

void i_perm_regenerate(Object* o)
{
  if (o->known < 1)
    o->known = 1;
  if (o->blessing > -1)
    Objects[o->id].known = 1;
  if (o->used)
  {
    mprint("You seem abnormally healthy.");
    player.status[REGENERATING] += 1500;
  }
  else
  {
    player.status[REGENERATING] -= 1500;
    if (player.status[REGENERATING] < 1)
    {
      mprint("Your vitality is back to normal");
      player.status[REGENERATING] = 0;
    }
  }
}

/* armor functions */

void i_normal_armor(Object* o)
{
  if (o->used)
    mprint("You put on your suit of armor.");
}

void i_perm_energy_resist(Object* o)
{
  if (o->used)
  {
    player.immunity[FLAME]++;
    player.immunity[COLD]++;
    player.immunity[ELECTRICITY]++;
  }
  else
  {
    player.immunity[FLAME]--;
    player.immunity[COLD]--;
    player.immunity[ELECTRICITY]--;
  }
}

void i_perm_fear_resist(Object* o)
{
  if (o->used)
  {
    player.immunity[FEAR]++;
    if (o->blessing < 0)
    {
      player.status[BERSERK] += 1500;
      mprint("You feel blood-simple!");
    }
  }
  else
  {
    player.immunity[FEAR]--;
    if (o->blessing < 0)
    {
      player.status[BERSERK] -= 1500;
      if (player.status[BERSERK] < 1)
      {
        mprint("You feel less rabid now.");
        player.status[BERSERK] = 0;
      }
    }
  }
}

void i_perm_breathing(Object* o)
{
  if (o->known < 1)
    o->known = 1;
  if (o->blessing > -1)
    Objects[o->id].known = 1;

  if (o->blessing > -1)
  {
    if (o->used)
    {
      mprint("Your breath is energized!");
      player.status[BREATHING] += 1500;
    }
    else
    {
      player.status[BREATHING] -= 1500;
      if (player.status[BREATHING] < 1)
      {
        mprint("Your breathing is back to normal.");
        player.status[BREATHING] = 0;
      }
    }
  }
  else if (o->used)
  {
    player.status[BREATHING] = 0;
    p_drown();
    print1("Water pours from the broken suit.");
  }
}

/* weapons functions */

void weapon_acidwhip(int dmgmod, Object* o, monster* m)
{
  if ((random_range(2) == 1) && (!m_immunityp(m, NORMAL_DAMAGE)))
  {
    mprint("You entangle the monster!");
    m_status_reset(m, MOBILE);
  }
  p_hit(m, player.dmg + dmgmod, ACID);
}

void weapon_scythe(int dmgmod, Object* o, monster* m)
{
  mprint("Slice!");
  m_death(m);
  if (!player.rank[ADEPT])
  {
    mprint("Ooops!");
    mprint("You accidentally touch yourself on the backswing....");
    p_death("the Scythe of Death");
  }
}

void weapon_demonblade(int dmgmod, Object* o, monster* m)
{
  if (o->blessing > -1)
  {
    mprint("Demonblade disintegrates with a soft sigh.");
    mprint("You stop foaming at the mouth.");
    player.status[BERSERK] = 0;
    conform_lost_object(o);
  }
  else if (m->specialf == M_SP_DEMON)
  {
    mprint("The demon flees in terror before your weapon!");
    m_vanish(m);
  }
  else if (m->meleef != M_MELEE_SPIRIT)
  {
    if (m->level > random_range(10))
    {
      if (player.hp < player.maxhp)
        player.hp = min(player.maxhp, player.hp + m->hp);
      player.str++;
      if (player.pow < player.maxpow)
        player.pow = min(player.maxpow, player.pow + m->level);
      m_death(m);
      mprint("You feel a surge of raw power from Demonblade!");
    }
    else
      p_hit(m, player.dmg + dmgmod, NORMAL_DAMAGE);
  }
  else
  {
    mprint("Demonblade howls as it strikes the spirit!");
    if (random_range(10) == 1)
    {
      mprint("... and shatters into a thousand lost fragments!");
      morewait();
      p_damage(50, UNSTOPPABLE, "Demonblade exploding");
      conform_lost_object(o);
    }
    else
    {
      mprint("You feel your lifeforce draining....");
      p_damage(25, UNSTOPPABLE, "a backlash of negative energies");
      player.str -= 3;
      player.con -= 3;
      if (player.str < 1 || player.con < 1)
        p_death("a backlash of negative energies");
    }
  }
}

void weapon_lightsabre(int dmgmod, Object* o, monster* m)
{
  if (!o->known)
  {
    mprint("Fumbling with the cylinder, you press the wrong stud....");
    p_damage(100, UNSTOPPABLE, "fumbling with a lightsabre");
    o->known = 1;
  }
  else
  {
    /* test prevents confusing immunity messages.... */
    if (!m_immunityp(m, NORMAL_DAMAGE))
    {
      mprint("Vzzzzmmm!");
      m_damage(m, 20, NORMAL_DAMAGE);
    }
    if ((m->hp > 0) && (!m_immunityp(m, FLAME)))
    {
      mprint("Zzzzap!");
      m_damage(m, 20, FLAME);
    }
  }
}

void weapon_tangle(int dmgmod, Object* o, monster* m)
{
  if ((random_range(2) == 1) && (!m_immunityp(m, NORMAL_DAMAGE)))
  {
    mprint("You entangle the monster!");
    m_status_reset(m, MOBILE);
  }
  p_hit(m, player.dmg + dmgmod, NORMAL_DAMAGE);
}

/* if wielding a bow, add bow damage to arrow damage */
void weapon_arrow(int dmgmod, Object* o, monster* m)
{
  if ((player.possessions[O_WEAPON_HAND] != NULL) &&
      (player.possessions[O_WEAPON_HAND]->id == WEAPONID + 26)) /* ie, using a bow */
    p_hit(m, player.dmg + o->plus + o->dmg + dmgmod, NORMAL_DAMAGE);
  else
    p_hit(m, o->plus + o->dmg + dmgmod, NORMAL_DAMAGE);
}

/* if wielding a crossbow, add bow damage to arrow damage */
void weapon_bolt(int dmgmod, Object* o, monster* m)
{
  if ((player.possessions[O_WEAPON_HAND] != NULL) &&
      (player.possessions[O_WEAPON_HAND]->id == WEAPONID + 27) && /*ie using a crossbow */
      (player.possessions[O_WEAPON_HAND]->aux == LOADED))
  {
    p_hit(m, player.dmg + o->plus + o->dmg + dmgmod, NORMAL_DAMAGE);
    player.possessions[O_WEAPON_HAND]->aux = UNLOADED;
  }
  else
    p_hit(m, o->plus + o->dmg, NORMAL_DAMAGE);
}

void weapon_mace_disrupt(int dmgmod, Object* o, monster* m)
{
  if (m->meleef == M_MELEE_SPIRIT)
  {
    mprint("The monster crumbles away to dust!");
    m_death(m);
  }
  else
    p_hit(m, player.dmg + dmgmod, UNSTOPPABLE);
}

void weapon_normal_hit(int dmgmod, Object* o, monster* m)
{
  p_hit(m, player.dmg + dmgmod, NORMAL_DAMAGE);
}

/* will be updated eventually */
void weapon_bare_hands(int dmgmod, monster* m)
{
  p_hit(m, player.dmg + dmgmod, NORMAL_DAMAGE);
}

void i_demonblade(Object* o)
{
  if (o->used)
  {
    o->known = 2;
    mprint("Demonblade's fangs open and bury themselves in your wrist!");
    mprint("You hear evil laughter in the distance....");
    mprint("You begin to foam at the mouth!");
    player.status[BERSERK] = 1500;
  }
  else
  {
    mprint("You hear a sound like a demon cursing.");
    mprint("You feel less like biting your shield.");
    player.status[BERSERK] = 0;
  }
}

void i_normal_weapon(Object* o)
{
  if (o->used)
    mprint("You ready your weapon for battle.");
}

void i_lightsabre(Object* o)
{
  if (o->used)
    mprint("You feel one with the Force.");
  else
    mprint("You feel out of touch with the Force.");
}

void i_mace_disrupt(Object* o)
{
  mprint("That's a damned heavy mace!");
}

void weapon_vorpal(int dmgmod, Object* o, monster* m)
{
  if ((random_range(10) < 3) && (!m_immunityp(m, NORMAL_DAMAGE)))
  {
    o->known = 2;
    if (random_range(2) == 1)
      mprint("One Two! One Two! And through and through!");
    else
      mprint("Your vorpal blade goes snicker-snack!");
    m_death(m);
  }
  else
    weapon_normal_hit(dmgmod, o, m);
}

void weapon_desecrate(int dmgmod, Object* o, monster* m)
{
  o->known = 2;
  if (player.alignment < 0)
  {
    mprint("Your opponent screams in agony!");
    p_hit(m, player.dmg + dmgmod, UNSTOPPABLE);
    player.alignment--;
    if (player.hp < player.maxhp)
    {
      mprint("You feel a thrill of power surging up your blade!");
      player.hp = min(player.maxhp, player.hp + player.dmg + dmgmod);
    }
  }
  else
  {
    mprint("Your blade turns in your hands and hits you!");
    mprint("You hear evil laughter....");
    level_drain(player.dmg, "the sword Desecrator");
    player.alignment -= 10;
    mprint("A strange force spreads from the wound throughout your body...");
    mprint("You feel much more chaotic now.");
  }
}

void weapon_firestar(int dmgmod, Object* o, monster* m)
{
  if (random_range(3) == 1)
  {
    o->known = 2;
    fball(player.x, player.y, player.x, player.y, max(player.dmg, 25));
  }
  if (m->hp > 0)
    weapon_normal_hit(dmgmod, o, m);
}

void weapon_mjolnir(int dmgmod, Object* o, monster* m)
{
  if (random_range(3) == 1)
  {
    o->known = 2;
    lball(player.x, player.y, player.x, player.y, max(player.dmg, 25));
  }
  if (m->hp > 0)
    weapon_normal_hit(dmgmod, o, m);
}

void weapon_defend(int dmgmod, Object* o, monster* m)
{
  if ((player.alignment < 0) && (o->blessing > 0))
  {
    mprint("The Holy Defender screams in your hands....");
    mprint("You stagger before the sound of its rage....");
    p_damage(50, UNSTOPPABLE, "a pissed-off Holy Defender");
    mprint("The weapon finally quiets. It seems less holy now.");
    o->truename = o->cursestr;
    player.status[PROTECTION] -= (o->hit);
    o->plus = 0 - abs(o->plus);
    o->blessing = -1;
  }
  if ((o->blessing > 0) &&
      ((m->specialf == M_SP_DEMON) ||
       (m->meleef == M_MELEE_SPIRIT)))
  {
    mprint("Your opponent shies back before your holy weapon!");
    m->hit = 0;
    m->speed *= 2;
  }
  weapon_normal_hit(dmgmod, o, m);
}

void weapon_victrix(int dmgmod, Object* o, monster* m)
{
  if (m->meleef == M_MELEE_SPIRIT)
  {
    mprint("Your opponent dissipates in a harmless cloud of vapors...");
    m_death(m);
  }
  else
    weapon_normal_hit(dmgmod, o, m);
}

void i_defend(Object* o)
{
  o->known = 2;
  if (o->used)
  {
    mprint("You feel under an aegis!");
    player.status[PROTECTION] += o->hit;
  }
  else
    player.status[PROTECTION] -= o->hit;
}

void i_victrix(Object* o)
{
  o->known = 2;
  o->blessing = abs(o->blessing);
  if (o->used)
  {
    player.immunity[POISON]++;
    player.immunity[FEAR]++;
    player.immunity[INFECTION]++;
  }
  else
  {
    player.immunity[POISON]--;
    player.immunity[FEAR]--;
    player.immunity[INFECTION]--;
  }
}

void i_desecrate(Object* o)
{
  if (o->known < 1)
    o->known = 2;
  if (o->blessing > 0)
  {
    mprint("How weird, a blessed desecrator... ");
    mprint("The structure of reality cannot permit such a thing....");
    dispose_lost_objects(1, o);
  }
  else if (level->site[player.x][player.y].locchar == ALTAR)
    sanctify(-1);
}

/* shield functions */
void i_normal_shield(Object* o)
{
  if (o->used)
    mprint("You sling your shield across a forearm.");
}

void i_perm_deflect(Object* o)
{
  if (o->known < 1)
    o->known = 2;
  if (o->blessing > -1)
  {
    if (o->used)
    {
      mprint("You feel buffered.");
      player.status[DEFLECTION] += 1500;
    }
    else
    {
      player.status[DEFLECTION] -= 1500;
      if (player.status[DEFLECTION] < 1)
      {
        mprint("You feel less defended");
        player.status[DEFLECTION] = 0;
      }
    }
  }
  else
  {
    if (o->used)
    {
      mprint("You feel naked.");
      player.status[VULNERABLE] += 1500;
      player.status[DEFLECTION] = 0;
    }
    else
    {
      player.status[VULNERABLE] -= 1500;
      if (player.status[VULNERABLE] < 1)
      {
        mprint("You feel less vulnerable");
        player.status[VULNERABLE] = 0;
      }
    }
  }
}
