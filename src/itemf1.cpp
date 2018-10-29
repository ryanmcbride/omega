/* omega copyright (C) 1987,1988,1989 by Laurence Raphael Brothers */
/* itemf1.c */

/* various item functions: potions,scrolls,boots,cloaks,things,food */

#include "glob.h"

/* general item functions */

void i_no_op(Object* o)
{
}

void i_nothing(Object* o)
{
}

/*  scroll functions */

void i_knowledge(Object* o)
{
  if (o->blessing > -1)
    Objects[o->id].known = 1;
  knowledge(o->blessing);
}

void i_jane_t(Object* o)
{
  int volume = random_range(6);
  int i, j, k;
  char v;

  Objects[o->id].known = 1;
  print1("Jane's Guide to the World's Treasures: ");
  switch (volume)
  {
  case 0:
    nprint1("SCROLLS");
    j = SCROLLID;
    k = POTIONID;
    break;
  case 1:
    nprint1("POTIONS");
    j = POTIONID;
    k = WEAPONID;
    break;
  case 2:
    nprint1("CLOAKS");
    j = CLOAKID;
    k = BOOTID;
    break;
  case 3:
    nprint1("BOOTS");
    j = BOOTID;
    k = RINGID;
    break;
  case 4:
    nprint1("RINGS");
    j = RINGID;
    k = STICKID;
    break;
  case 5:
    nprint1("STICKS");
    j = STICKID;
    k = ARTIFACTID;
    break;
  }
  menuclear();
  menuprint("You could probably now recognise:\n");
  for (i = j; i < k; i++)
  {
    Objects[i].known = 1;
    v = Objects[i].truename[0];
    if ((v >= 'A' && v <= 'Z') || volume == 3)
      sprintf(Str1, "   %s\n", Objects[i].truename);
    else if (v == 'a' || v == 'e' || v == 'i' || v == 'o' || v == 'u')
      sprintf(Str1, "   an %s\n", Objects[i].truename);
    else
      sprintf(Str1, "   a %s\n", Objects[i].truename);
    menuprint(Str1);
  }
  showmenu();
  morewait();
  xredraw();
}

void i_flux(Object* o)
{
  if (o->blessing > -1)
    Objects[o->id].known = 1;
  flux(o->blessing);
}

/* enchantment */
void i_enchant(Object* o)
{
  if (o->blessing > -1)
    Objects[o->id].known = 1;
  enchant(o->blessing < 0 ? -1 - o->plus : o->plus + 1);
}

/* scroll of clairvoyance */
void i_clairvoyance(Object *o)
{
  if (o->blessing > -1)
    Objects[o->id].known = 1;
  if (o->blessing < 0)
    amnesia();
  else
    clairvoyance(5 + o->blessing * 5);
}

void i_acquire(Object* o)
{
  int blessing;

  if (o->blessing > -1)
    Objects[o->id].known = 1;
  blessing = o->blessing;
  *o = Objects[SCROLLID + 0]; /* blank out the scroll */
  acquire(blessing);
}

void i_teleport(Object* o)
{
  if (o->blessing > -1)
    Objects[o->id].known = 1;
  p_teleport(o->blessing);
}

void i_spells(Object* o)
{
  if (o->blessing > -1)
    Objects[o->id].known = 1;
  mprint("A scroll of spells.");
  morewait();
  learnspell(o->blessing);
}

/* scroll of blessing */
void i_bless(Object* o)
{
  Objects[o->id].known = 1;
  bless(o->blessing);
}

/* scroll of wishing */
void i_wish(Object* o)
{
  if (o->blessing > -1)
    Objects[o->id].known = 1;
  wish(o->blessing);
  *o = Objects[SCROLLID + 0]; /* blank out the scroll */
}

/* scroll of displacement */
void i_displace(Object* o)
{
  if (o->blessing > -1)
    Objects[o->id].known = 1;
  displace(o->blessing);
}

/* scroll of deflection */
void i_deflect(Object* o)
{
  if (o->blessing > -1)
    Objects[o->id].known = 1;
  deflection(o->blessing);
}

/* scroll of identification */
void i_id(Object* o)
{
  if (o->blessing > -1)
    Objects[o->id].known = 1;
  identify(o->blessing);
}

/* potion functions */

/* potion of healing */
void i_heal(Object* o)
{
  if (o->blessing > -1)
  {
    Objects[o->id].known = 1;
    heal(1 + o->plus);
  }
  else
    heal(-1 - abs(o->plus));
}

/* potion of monster detection */
void i_mondet(Object* o)
{
  if (o->blessing > -1)
    Objects[o->id].known = 1;
  mondet(o->blessing);
}

/* potion of object detection */
void i_objdet(Object* o)
{

  if (o->blessing > -1)
    Objects[o->id].known = 1;
  objdet(o->blessing);
}

/* potion of neutralize poison */
void i_neutralize_poison(Object* o)
{
  if (o->blessing > -1)
  {
    Objects[o->id].known = 1;
    mprint("You feel vital!");
    player.status[POISONED] = 0;
  }
  else
    p_poison(random_range(20) + 5);
}

/* potion of sleep */
void i_sleep_self(Object* o)
{
  sleep_player(6);
  Objects[o->id].known = 1;
}

/* potion of speed */
void i_speed(Object* o)
{
  if (o->blessing > -1)
    Objects[o->id].known = 1;
  haste(o->blessing);
}

/* potion of restoration */
void i_restore(Object* o)
{
  if (o->blessing > -1)
    Objects[o->id].known = 1;
  recover_stat(o->blessing);
}

void i_augment(Object* o)
{
  if (o->blessing > -1)
    Objects[o->id].known = 1;
  augment(o->blessing);
}

void i_azoth(Object* o)
{
  if (o->plus < 0)
  {
    mprint("The mercury was poisonous!");
    p_poison(25);
  }
  else if (o->plus == 0)
  {
    mprint("The partially enchanted azoth makes you sick!");
    player.con = ((int)(player.con / 2));
    calc_melee();
  }
  else if (o->blessing < 1)
  {
    mprint("The unblessed azoth warps your soul!");
    player.pow = player.maxpow = ((int)(player.maxpow / 2));
    level_drain(random_range(10), "cursed azoth");
  }
  else
  {
    mprint("The azoth fills you with cosmic power!");
    if (player.str > player.maxstr * 2)
    {
      mprint("The power rages out of control!");
      p_death("overdose of azoth");
    }
    else
    {
      heal(10);
      cleanse(1);
      player.mana = calcmana() * 3;
      toggle_item_use(TRUE);
      player.str = (player.maxstr++) * 3;
      toggle_item_use(FALSE);
    }
  }
}

void i_regenerate(Object* o)
{
  regenerate(o->blessing);
}

/* boots functions */
void i_perm_speed(Object* o)
{
  if (o->blessing > -1)
  {
    if (o->used)
    {
      o->known = 2;
      Objects[o->id].known = 1;
      if (player.status[SLOWED] > 0)
      {
        player.status[SLOWED] = 0;
      }
      mprint("The world slows down!");
      player.status[HASTED] += 1500;
    }
    else
    {
      player.status[HASTED] -= 1500;
      if (player.status[HASTED] < 1)
        mprint("The world speeds up again.");
    }
  }
  else
  {
    if (o->used)
    {
      if (player.status[HASTED] > 0)
      {
        player.status[HASTED] = 0;
      }
      mprint("You feel slower.");
      player.status[SLOWED] += 1500;
    }
    else
    {
      player.status[SLOWED] -= 1500;
      if (player.status[SLOWED] < 1)
        mprint("You feel quicker again.");
    }
  }
}

/* cloak functions */
void i_perm_displace(Object* o)
{
  if (o->blessing > -1)
  {
    if (o->used)
    {
      mprint("You feel dislocated.");
      player.status[DISPLACED] += 1500;
    }
    else
    {
      player.status[DISPLACED] -= 1500;
      if (player.status[DISPLACED] < 1)
      {
        mprint("You feel a sense of position.");
        player.status[DISPLACED] = 0;
      }
    }
  }
  else
  {
    if (o->used)
    {
      mprint("You have a forboding of bodily harm!");
      player.status[VULNERABLE] += 1500;
    }
    else
    {
      player.status[VULNERABLE] -= 1500;
      if (player.status[VULNERABLE] < 1)
      {
        mprint("You feel less endangered.");
        player.status[VULNERABLE] = 0;
      }
    }
  }
}

void i_perm_negimmune(Object* o)
{
  if (o->blessing > -1)
  {
    if (o->used)
    {
      player.immunity[NEGENERGY]++;
    }
    else
      player.immunity[NEGENERGY]--;
  }
  else if (o->used)
    level_drain(abs(o->blessing), "cursed cloak of level drain");
}

/* food functions */

void i_food(Object* o)
{
  switch (random_range(5))
  {
  case 0:
    mprint("That tasted horrible!");
    break;
  case 1:
    mprint("Yum!");
    break;
  case 2:
    mprint("How nauseous!");
    break;
  case 3:
    mprint("Can I have some more? Please?");
    break;
  case 4:
    mprint("Your mouth feels like it is growing hair!");
    break;
  }
}

void i_stim(Object* o)
{
  mprint("You feel Hyper!");
  i_speed(o);
  player.str += 3;
  player.con -= 1;
  calc_melee();
}

void i_pow(Object* o)
{
  mprint("You feel a surge of mystic power!");
  player.mana = 2 * calcmana();
}

void i_poison_food(Object* o)
{
  mprint("This food was contaminated with cyanide!");
  p_poison(random_range(20) + 5);
}

void i_pepper_food(Object* o)
{
  mprint("You innocently start to chew the szechuan pepper.....");
  morewait();
  mprint("hot.");
  morewait();
  mprint("Hot.");
  morewait();
  mprint("Hot!");
  morewait();
  mprint("HOT!!!!!!");
  morewait();
  p_damage(1, UNSTOPPABLE, "a szechuan pepper");
  mprint("Your sinuses melt and run out your ears.");
  mprint("Your mouth and throat seem to be permanently on fire.");
  mprint("You feel much more awake now....");
  player.immunity[SLEEP]++;
}

void i_lembas(Object* o)
{
  heal(10);
  cleanse(0);
  player.food = 40;
}

void i_cure(Object* o)
{
  cure(o->blessing);
}

void i_immune(Object* o)
{
  if (o->blessing > 0)
  {
    mprint("You feel a sense of innoculation");
    player.immunity[INFECTION]++;
    cure(o->blessing);
  }
}

void i_breathing(Object* o)
{

  if (o->blessing > -1)
    Objects[o->id].known = 1;
  breathe(o->blessing);
}

void i_invisible(Object* o)
{
  if (o->blessing > -1)
    Objects[o->id].known = 1;
  invisible(o->blessing);
}

void i_perm_invisible(Object* o)
{
  if (o->blessing > -1)
    Objects[o->id].known = 1;
  if (o->used)
  {
    if (o->blessing > -1)
    {
      mprint("You feel transparent!");
      player.status[INVISIBLE] += 1500;
    }
    else
    {
      mprint("You feel a forboding of bodily harm!");
      player.status[VULNERABLE] += 1500;
    }
  }
  else
  {
    if (o->blessing > -1)
    {
      player.status[INVISIBLE] -= 1500;
      if (player.status[INVISIBLE] < 1)
      {
        mprint("You feel opaque again.");
        player.status[INVISIBLE] = 0;
      }
    }
    else
    {
      player.status[VULNERABLE] -= 1500;
      if (player.status[VULNERABLE] < 1)
      {
        mprint("You feel less endangered now.");
        player.status[VULNERABLE] = 0;
      }
    }
  }
}

void i_warp(Object* o)
{
  if (o->blessing > -1)
    Objects[o->id].known = 1;
  warp(o->blessing);
}

void i_alert(Object* o)
{
  if (o->blessing > -1)
  {
    Objects[o->id].known = 1;
    alert(o->blessing);
  }
}

void i_charge(Object* o)
{
  int i;
  if (o->blessing > -1)
    Objects[o->id].known = 1;
  mprint("A scroll of charging.");
  mprint("Charge: ");
  i = getitem(STICK);
  if (i != ABORT)
  {
    if (o->blessing < 0)
    {
      mprint("The stick glows black!");
      player.possessions[i]->charge = 0;
    }
    else
    {
      mprint("The stick glows blue!");
      player.possessions[i]->charge += (random_range(10) + 1) * (o->blessing + 1);
      if (player.possessions[i]->charge > 99)
        player.possessions[i]->charge = 99;
    }
  }
}

void i_fear_resist(Object* o)
{
  if (o->blessing > -1)
  {
    Objects[o->id].known = 1;
    if (player.status[AFRAID] > 0)
    {
      mprint("You feel stauncher now.");
      player.status[AFRAID] = 0;
    }
  }
  else if (!p_immune(FEAR))
  {
    mprint("You panic!");
    player.status[AFRAID] += random_range(100);
  }
}

/* use a thieves pick */
void i_pick(Object* o)
{
  int dir;
  int ox, oy;
  o->used = FALSE;
  if ((!o->known) && (!player.rank[THIEVES]))
    mprint("You have no idea what do with a piece of twisted metal.");
  else
  {
    o->known = 1;
    Objects[o->id].known = 1;
    mprint("Pick lock:");
    dir = getdir();
    if (dir == ABORT)
      resetgamestatus(SKIP_MONSTERS);
    else
    {
      ox = player.x + Dirs[0][dir];
      oy = player.y + Dirs[1][dir];
      if ((level->site[ox][oy].locchar != CLOSED_DOOR) ||
          loc_statusp(ox, oy, SECRET))
      {
        mprint("You can't unlock that!");
        resetgamestatus(SKIP_MONSTERS);
      }
      else if (level->site[ox][oy].aux == LOCKED)
      {
        if (level->depth == MaxDungeonLevels - 1)
          mprint("The lock is too complicated for you!!!");
        else if (level->depth * 2 + random_range(50) <
                 player.dex + player.level + player.rank[THIEVES] * 10)
        {
          mprint("You picked the lock!");
          level->site[ox][oy].aux = UNLOCKED;
          lset(ox, oy, CHANGED);
          gain_experience(max(3, level->depth));
        }
        else
          mprint("You failed to pick the lock.");
      }
      else
        mprint("That door is already unlocked!");
    }
  }
}

/* use a magic key*/
void i_key(Object* o)
{
  int dir;
  int ox, oy;
  o->used = FALSE;
  mprint("Unlock door: ");
  dir = getdir();
  if (dir == ABORT)
    resetgamestatus(SKIP_MONSTERS);
  else
  {
    ox = player.x + Dirs[0][dir];
    oy = player.y + Dirs[1][dir];
    if ((level->site[ox][oy].locchar != CLOSED_DOOR) ||
        loc_statusp(ox, oy, SECRET))
    {
      mprint("You can't unlock that!");
      resetgamestatus(SKIP_MONSTERS);
    }
    else if (level->site[ox][oy].aux == LOCKED)
    {
      mprint("The lock clicks open!");
      level->site[ox][oy].aux = UNLOCKED;
      lset(ox, oy, CHANGED);
      o->blessing--;
      if ((o->blessing < 0) || (level->depth == MaxDungeonLevels - 1))
      {
        mprint("The key disintegrates!");
        conform_lost_objects(1, o);
      }
      else
        mprint("Your key glows faintly.");
    }
    else
      mprint("That door is already unlocked!");
  }
}

void i_corpse(Object* o)
{
  /* WDT HACK: there are some comments in this function which need
   * to be backed up with assert(). */
  /* object's charge holds the former monster id */
  if (o->charge == MEND_PRIEST ||
      o->charge == ITIN_MERCH ||
      o->charge == GUARD ||
      o->charge == NPC ||
      o->charge == MERCHANT ||
      o->charge == ZERO_NPC ||
      o->charge == HISCORE_NPC ||
      o->charge == APPR_NINJA ||
      o->charge == SNEAK_THIEF ||
      o->charge == BRIGAND ||
      o->charge == GENIN ||
      o->charge == MAST_THIEF ||
      o->charge == CHUNIN ||
      o->charge == JONIN)
  { /* cannibalism */
    mprint("Yechh! How could you! You didn't even cook him, first!");
    if (player.alignment > 0)
      player.food = 25;
    player.food += 8;
    player.alignment -= 10;
    foodcheck();
  }
  else if (o->charge == FNORD)
  { /* fnord */
    mprint("You feel illuminated!");
    player.iq++;
  }
  else if (o->charge == DENEBIAN)
  { /* denebian slime devil */
    mprint("I don't believe this. You ate Denebian Slime?");
    mprint("You deserve a horrible wasting death, uncurable by any means!");
  }
  else if (o->charge == DRAGONETTE)
  { /* can't get here... i_usef changed to I_FOOD */
    mprint("Those dragon-steaks were fantastic!");
    player.food = 24;
    foodcheck();
  }
  else if (o->charge == BEHEMOTH)
  {
    mprint("You feel infinitely more virile now.");
    player.str = max(player.str, player.maxstr + 10);
    player.food = 24;
    foodcheck();
  }
  else if (o->charge == INVIS_SLAY)
  {
    mprint("Guess what? You're invisible.");
    if (player.status[INVISIBLE] < 1000)
      player.status[INVISIBLE] = 666;
    player.food += 6;
    foodcheck();
  }
  else if (o->charge == UNICORN)
  {
    mprint("You ATE a unicorn's horn?!?!?");
    player.immunity[POISON] = 1000;
  }
  else if (o->charge == HORNET || /* can't get here... i_usef changed to I_POISON_FOOD */
           o->charge == GRUNT ||
           o->charge == TSETSE || /* can't get here... i_usef changed to I_SLEEP_SELF */
           o->charge == AGGRAVATOR ||
           o->charge == BLIPPER || /* can't get here... i_usef changed to I_TELEPORT */
           o->charge == GOBLIN ||
           o->charge == GEEK ||
           o->charge == NIGHT_GAUNT || /* can't get here... i_usef changed to I_POISON_FOOD */
           o->charge == TOVE ||
           o->charge == TASMANIAN ||
           o->charge == JUBJUB || /* can't get here... i_usef changed to I_FOOD */
           o->charge == CATEAGLE)
  {
    mprint("Well, you forced it down. Not much nutrition, though.");
    player.food++;
    foodcheck();
  }
  else if (o->charge == SEWER_RAT ||
           o->charge == PHANTASTICON || /* can't get here... i_usef changed to I_POISON_FOOD */
           o->charge == EYE ||          /* can't get here... i_usef changed to I_CLAIRVOYANCE */
           o->charge == NASTY ||        /* can't get here... i_usef changed to I_INVISIBLE */
           o->charge == CATOBLEPAS ||
           o->charge == HAUNT || /* can't get here... i_usef changed to I_POISON_FOOD */
           o->charge == ROUS ||
           o->charge == DEATHSTAR || /* can't get here... i_usef changed to I_POISON_FOOD */
           o->charge == EATER)
  {
    mprint("Oh, yuck. The 'food' seems to be tainted.");
    mprint("You feel very sick. You throw up.");
    player.food = min(player.food, 4);
  }
  else
  {
    mprint("It proved completely inedible, but you tried anyhow.");
  }
}

void i_accuracy(Object* o)
{
  o->known = 1;
  Objects[o->id].known = 1;
  accuracy(o->blessing);
}

void i_perm_accuracy(Object* o)
{
  o->known = 1;
  Objects[o->id].known = 1;
  if ((o->used) && (o->blessing > -1))
  {
    player.status[ACCURATE] += 1500;
    mprint("You feel skillful and see bulls' eyes everywhere.");
  }
  else
  {
    player.status[ACCURATE] -= 1500;
    if (player.status[ACCURATE] < 1)
    {
      player.status[ACCURATE] = 0;
      calc_melee();
      mprint("Your vision blurs....");
    }
  }
}

void i_hero(Object* o)
{
  o->known = 1;
  Objects[o->id].known = 1;
  hero(o->blessing);
}

void i_perm_hero(Object* o)
{
  o->known = 1;
  Objects[o->id].known = 1;
  if (o->used)
  {
    if (o->blessing > -1)
    {
      player.status[HERO] += 1500;
      calc_melee();
      mprint("You feel super!");
    }
    else
    {
      player.status[HERO] = 0;
      calc_melee();
      if (!player.immunity[FEAR])
      {
        player.status[AFRAID] += 1500;
        mprint("You feel cowardly....");
      }
    }
  }
  else
  {
    if (o->blessing > -1)
    {
      player.status[HERO] -= 1500;
      if (player.status[HERO] < 1)
      {
        calc_melee();
        mprint("You feel less super now.");
        player.status[HERO] = 0;
      }
    }
    else
    {
      player.status[AFRAID] -= 1500;
      if (player.status[AFRAID] < 1)
      {
        mprint("You finally conquer your fear.");
        player.status[AFRAID] = 0;
      }
    }
  }
}

void i_levitate(Object* o)
{
  o->known = 1;
  Objects[o->id].known = 1;
  levitate(o->blessing);
}

void i_perm_levitate(Object* o)
{
  o->known = 1;
  Objects[o->id].known = 1;
  if (o->blessing > -1)
  {
    if (o->used)
    {
      player.status[LEVITATING] += 1400;
      mprint("You start to float a few inches above the floor");
      mprint("You find you can easily control your altitude");
    }
    else
    {
      player.status[LEVITATING] -= 1500;
      if (player.status[LEVITATING] < 1)
      {
        player.status[LEVITATING] = 0;
        mprint("You sink to the floor.");
      }
    }
  }
  else
    i_perm_burden(o);
}

void i_perm_protection(Object* o)
{
  if (o->used)
  {
    if (o->blessing > -1)
      player.status[PROTECTION] += abs(o->plus) + 1;
    else
      player.status[PROTECTION] -= abs(o->plus) + 1;
  }
  else
  {
    if (o->blessing > -1)
      player.status[PROTECTION] -= abs(o->plus) + 1;
    else
      player.status[PROTECTION] += abs(o->plus) + 1;
  }
  calc_melee();
}

void i_perm_agility(Object* o)
{
  o->known = 2;
  Objects[o->id].known = 1;
  if (o->used)
  {
    if (o->blessing > -1)
      player.agi += abs(o->plus) + 1;
    else
      player.agi -= abs(o->plus) + 1;
  }
  else
  {
    if (o->blessing > -1)
      player.agi -= abs(o->plus) + 1;
    else
      player.agi += abs(o->plus) + 1;
  }
  calc_melee();
}

void i_truesight(Object* o)
{
  o->known = 1;
  Objects[o->id].known = 1;
  truesight(o->blessing);
}

void i_perm_truesight(Object* o)
{
  o->known = 1;
  Objects[o->id].known = 1;
  if (o->used)
  {
    if (o->blessing > -1)
    {
      player.status[TRUESIGHT] += 1500;
      mprint("You feel sharp!");
    }
    else
    {
      player.status[BLINDED] += 1500;
      mprint("You've been blinded!");
    }
  }
  else
  {
    if (o->blessing > -1)
    {
      player.status[TRUESIGHT] -= 1500;
      if (player.status[TRUESIGHT] < 1)
      {
        mprint("You feel less keen now.");
        player.status[TRUESIGHT] = 0;
      }
    }
    else
    {
      player.status[BLINDED] -= 1500;
      if (player.status[BLINDED] < 1)
      {
        mprint("You can see again!");
        player.status[BLINDED] = 0;
      }
    }
  }
}

void i_illuminate(Object* o)
{
  o->known = 1;
  Objects[o->id].known = 1;
  illuminate(o->blessing);
}

void i_perm_illuminate(Object* o)
{
  o->known = 1;
  Objects[o->id].known = 1;
  if (o->used)
    player.status[ILLUMINATION] += 1500;
  else
    player.status[ILLUMINATION] = max(0, player.status[ILLUMINATION] - 1500);
}

void i_trap(Object* o)
{
  Objects[o->id].known = 1;

  if ((level->site[player.x][player.y].locchar != FLOOR) ||
      (level->site[player.x][player.y].p_locf != L_NO_OP))
    mprint("Your attempt fails.");
  else if (!o->known)
  {
    mprint("Fiddling with the thing, you have a small accident....");
    p_movefunction(o->aux);
  }
  else
  {
    mprint("You successfully set a trap at your location.");
    level->site[player.x][player.y].p_locf = o->aux;
    lset(player.x, player.y, CHANGED);
  }
  dispose_lost_objects(1, o);
}

void i_raise_portcullis(Object* o)
{
  l_raise_portcullis();
  mprint("The box beeps once and explodes in your hands!");
  conform_lost_objects(1, o);
}
