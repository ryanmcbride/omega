/* omega copyright (C) 1987,1988,1989 by Laurence Raphael Brothers */
/* item.c */

#include "glob.h"

/* make a random new_obj object, returning pointer */
Object *Object::create_object(int itemlevel)
{
  Object *new_obj;
  int r;
  int ok = FALSE;

  while (!ok)
  {
    new_obj = Object::create();
    r = random_range(135);
    if (r < 20)
      new_obj->make_thing(-1);
    else if (r < 40)
      new_obj->make_food(-1);
    else if (r < 50)
      new_obj->make_scroll(-1);
    else if (r < 60)
      new_obj->make_potion(-1);
    else if (r < 70)
      Object::makeWeapon(-1, new_obj);
    else if (r < 80)
      new_obj->make_armor(-1);
    else if (r < 90)
      new_obj->make_shield(-1);
    else if (r < 100)
      new_obj->make_stick(-1);
    else if (r < 110)
      new_obj->make_boots(-1);
    else if (r < 120)
      new_obj->make_cloak(-1);
    else if (r < 130)
      new_obj->make_ring(-1);
    else
      new_obj->make_artifact(-1);
    /* not ok if object is too good for level, or if unique and already made */
    /* 1/100 chance of finding object if too good for level */
    ok = ((new_obj->uniqueness < UNIQUE_MADE) &&
          ((new_obj->level < itemlevel + random_range(3)) || (random_range(100) == 23)));
    if (!ok)
    {
      delete new_obj;
    }
  }
  if (new_obj->uniqueness == UNIQUE_UNMADE)
    Objects[new_obj->id].uniqueness = UNIQUE_MADE;
  return (new_obj);
}

void Object::make_food(int id)
{
  Object *new_obj = this;
  if (id == -1)
    id = random_range(NUMFOODS);
  *new_obj = Objects[FOODID + id];
}

void Object::make_corpse(Monster *m)
{
  Object *new_obj = this;
  *new_obj = Objects[CORPSEID];
  new_obj->charge = m->id;
  new_obj->weight = m->corpseweight;
  new_obj->basevalue = m->corpsevalue;
  new_obj->known = 2;
  new_obj->objstr = m->corpsestr;
  new_obj->cursestr = new_obj->truename = new_obj->objstr;
/* DG I_CANNIBAL not implemented... fall through to code in I_CORPSE */
#if 0 /* WDT HACK, of course -- we need to implement I_CANNIBAL. */
  if ((m->monchar&0xff) == '@')
    new_obj->usef = I_CANNIBAL;
  else
#endif
  if (m_statusp(m, EDIBLE))
  {
    new_obj->usef = I_FOOD;
    new_obj->aux = 6;
  }
  else if (m_statusp(m, POISONOUS))
    new_obj->usef = I_POISON_FOOD;
  /* Special corpse-eating effects */
  else if (m->id == TSETSE || /*tse tse fly */
           m->id == TORPOR)   /*torpor beast */
  {
    new_obj->usef = I_SLEEP_SELF;
  }
  else if (m->id == NASTY)
  {
    new_obj->usef = I_INVISIBLE;
  }
  else if (m->id == BLIPPER)
  {
    new_obj->usef = I_TELEPORT;
  }
  else if (m->id == EYE) /* floating eye -- it's traditional.... */
  {
    new_obj->usef = I_CLAIRVOYANCE;
  }
  else if (m->id == FUZZY) /*astral fuzzy */
  {
    new_obj->usef = I_DISPLACE;
  }
  else if (m->id == SERV_LAW)
  {
    new_obj->usef = I_CHAOS;
  }
  else if (m->id == SERV_CHAOS)
  {
    new_obj->usef = I_LAW;
  }
  else if (m->id == ASTRAL_VAMP) /* astral vampire */
  {
    new_obj->usef = I_ENCHANT;
  }
  else if (m->id == MANABURST)
  {
    new_obj->usef = I_SPELLS;
  }
  else if (m->id == RAKSHASA)
  {
    new_obj->usef = I_TRUESIGHT;

/* DG fall through to code in I_CORPSE and special case there */
#if 0 /* WDT HACK? */
  case BEHEMOTH:
    new_obj->usef = I_HEAL;
    break;
  case UNICORN:
    new_obj->usef = I_NEUTRALIZE_POISON;
    break;
#endif
  }
  else if (m->id == COMA) /*coma beast */
  {
    new_obj->usef = I_ALERT;
  }
/* DG I_INEDIBLE not implemented... fall through to code in I_CORPSE */
#if 0 /* WDT HACK: yawn. */
  default:
    new_obj->usef = I_INEDIBLE; 
    break;
#endif
}

void Object::make_ring(int id)
{
  Object *new_obj = this;
  if (id == -1)
    id = random_range(NUMRINGS);
  *new_obj = Objects[RINGID + id];
  if (new_obj->blessing == 0)
    new_obj->blessing = itemblessing();
  if (new_obj->plus == 0)
    new_obj->plus = itemplus() + 1;
  if (new_obj->blessing < 0)
    new_obj->plus = -1 - abs(new_obj->plus);
}

void Object::make_thing(int id)
{
  Object *new_obj = this;
  if (id == -1)
    id = random_range(NUMTHINGS);
  *new_obj = Objects[THINGID + id];
  if (new_obj->objstr == "grot")
  {
    new_obj->objstr = grotname();
    new_obj->cursestr = new_obj->truename = new_obj->objstr;
  }
}

void Object::make_scroll(int id)
{
  Object *new_obj = this;
  if (id == -1)
    id = random_range(NUMSCROLLS);
  *new_obj = Objects[SCROLLID + id];
  /* if a scroll of spells, aux is the spell id in Spells */
  if (new_obj->id == SCROLLID + 1)
  {
    new_obj->aux = random_range(NUMSPELLS);
  }
}

void Object::make_potion(int id)
{
  Object *new_obj = this;
  if (id == -1)
    id = random_range(NUMPOTIONS);
  *new_obj = Objects[POTIONID + id];
  if (new_obj->plus == 0)
    new_obj->plus = itemplus();
}

void Object::make_shield(int id)
{
  Object *new_obj = this;
  if (id == -1)
    id = random_range(NUMSHIELDS);
  *new_obj = Objects[SHIELDID + id];
  if (new_obj->plus == 0)
    new_obj->plus = itemplus();
  if (new_obj->blessing == 0)
    new_obj->blessing = itemblessing();
  if (new_obj->blessing < 0)
    new_obj->plus = -1 - abs(new_obj->plus);
  else if (new_obj->blessing > 0)
    new_obj->plus = 1 + abs(new_obj->plus);
}

void Object::make_armor(int id)
{
  Object *new_obj = this;
  if (id == -1)
    id = random_range(NUMARMOR);
  *new_obj = Objects[ARMORID + id];
  if (new_obj->plus == 0)
    new_obj->plus = itemplus();
  if (new_obj->blessing == 0)
    new_obj->blessing = itemblessing();
  if (new_obj->blessing < 0)
    new_obj->plus = -1 - abs(new_obj->plus);
  else if (new_obj->blessing > 0)
    new_obj->plus = 1 + abs(new_obj->plus);
}

void Object::make_cloak(int id)
{
  Object *new_obj = this;
  if (id == -1)
    id = random_range(NUMCLOAKS);
  Objects[CLOAKID + 4].plus = 2;
  *new_obj = Objects[CLOAKID + id];
  if (new_obj->blessing == 0)
    new_obj->blessing = itemblessing();
}

void Object::make_boots(int id)
{
  Object *new_obj = this;
  if (id == -1)
    id = random_range(NUMBOOTS);
  *new_obj = Objects[BOOTID + id];
  if (new_obj->blessing == 0)
    new_obj->blessing = itemblessing();
}

void Object::make_stick(int id)
{
  Object *new_obj = this;
  if (id == -1)
    id = random_range(NUMSTICKS);
  *new_obj = Objects[STICKID + id];
  new_obj->charge = itemcharge();
  if (new_obj->blessing == 0)
    new_obj->blessing = itemblessing();
}

void Object::make_artifact(int id)
{
  Object *new_obj = this;
  if (id == -1)
    do
      id = random_range(NUMARTIFACTS);
    while (Objects[id].uniqueness >= UNIQUE_MADE);
  *new_obj = Objects[ARTIFACTID + id];
}

/* this function is used to shuffle the id numbers of scrolls, potions, etc */
/* taken from Knuth 2 */
void shuffle(int ids[], int number)
{
  int top, swap, with;

  for (top = 0; top < number; top++)
    ids[top] = top;
  for (top = number - 1; top >= 0; top--)
  {
    swap = ids[top];
    with = random_range(top + 1); /* from  0 to top, inclusive */
    ids[top] = ids[with];
    ids[with] = swap;
  }
}

/* item name functions */

char *scrollname(int id)
{
  switch (scroll_ids[id])
  {
  case 0:
    return "scroll-GRISTOGRUE";
  case 1:
    return "scroll-Kho Reck Tighp";
  case 2:
    return "scroll-E Z";
  case 3:
    return "scroll-Kevitz";
  case 4:
    return "scroll-Arcanum Prime";
  case 5:
    return "scroll-NYARLATHOTEP";
  case 6:
    return "scroll-Gilthoniel";
  case 7:
    return "scroll-Zarathustra";
  case 8:
    return "scroll-Ancient Lore";
  case 9:
    return "scroll-Eyes Only";
  case 10:
    return "scroll-Ambogar Empheltz";
  case 11:
    return "scroll-Isengard";
  case 12:
    return "scroll-Deosil Widdershins";
  case 13:
    return "scroll-Magister Paracelsus";
  case 14:
    return "scroll-Qlipphotic Summons";
  case 15:
    return "scroll-Aratron Samael";
  case 16:
    return "scroll-De Wormiis Mysterius";
  case 17:
    return "scroll-Necronomicon";
  case 18:
    return "scroll-Pnakotic Manuscript";
  case 19:
    return "scroll-Codex of Xalimar";
  case 20:
    return "scroll-The Mabinogion";
  case 21:
    return "scroll-Ginseng Shiatsu";
  case 22:
    return "scroll-Tome of Tromax";
  case 23:
    return "scroll-Book of the Dead ";
  case 24:
    return "scroll-The Flame Tongue";
  case 25:
    return "scroll-Karst Khogar";
  case 26:
    return "scroll-The Yellow Sign";
  case 27:
    return "scroll-The Kevillist Manifesto";
  case 28:
    return "scroll-Goshtar Script";
  default:
  case 29:
    return "scroll-Pendragon Encryption";
  }
}

char *grotname()
{
  switch (random_range(20))
  {
  case 0:
    return "pot lid";
  case 1:
    return "mound of offal";
  case 2:
    return "sword that was broken";
  case 3:
    return "salted snail";
  case 4:
    return "key";
  case 5:
    return "toadstool";
  case 6:
    return "greenish spindle";
  case 7:
    return "tin soldier";
  case 8:
    return "broken yo-yo";
  case 9:
    return "NYC subway map";
  case 10:
    return "Nixon's the One! button";
  case 11:
    return "beer can (empty)";
  case 12:
    return "golden bejewelled falcon";
  case 13:
    return "hamster cage";
  case 14:
    return "wooden nickel";
  case 15:
    return "three-dollar bill";
  case 16:
    return "rosebud";
  case 17:
    return "water pistol";
  case 18:
    return "shattered skull";
  default:
  case 19:
    return "jawbone of an ass";
  }
}

char *potionname(int id)
{
  switch (potion_ids[id])
  {
  case 0:
    return "vial of dewy liquid";
  case 1:
    return "jug of tarry black substance";
  case 2:
    return "flask of cold smoking froth";
  case 3:
    return "phial of glowing fluid";
  case 4:
    return "bottle of sickening slime";
  case 5:
    return "sac of greenish gel";
  case 6:
    return "wineskin of odorous goo";
  case 7:
    return "canteen of sweet sap";
  case 8:
    return "urn of clear fluid";
  case 9:
    return "clotted grey ooze";
  case 10:
    return "keg of bubbly golden fluid";
  case 11:
    return "tube of minty paste";
  case 12:
    return "pitcher of aromatic liquid";
  case 13:
    return "pot of rancid grease";
  case 14:
    return "thermos of hot black liquid";
  case 15:
    return "magnum of deep red liquid";
  case 16:
    return "vase full of ichor";
  case 17:
    return "container of white cream";
  case 18:
    return "syringe of clear fluid";
  default:
  case 19:
    return "can of volatile essence";
  }
}

char *stickname(int id)
{
  switch (stick_ids[id])
  {
  case 0:
    return "oaken staff";
  case 1:
    return "heavy metal rod";
  case 2:
    return "shaft of congealed light";
  case 3:
    return "slender ceramic wand";
  case 4:
    return "rune-inscribed bone wand";
  case 5:
    return "knurly staff";
  case 6:
    return "steel knobbed rod";
  case 7:
    return "lucite wand";
  case 8:
    return "sturdy alpenstock";
  case 9:
    return "gem-studded ebony staff";
  case 10:
    return "chromed sequinned staff";
  case 11:
    return "old peeling stick";
  case 12:
    return "jointed metal rod";
  case 13:
    return "wand with lead ferrules";
  case 14:
    return "forked wooden stick";
  case 15:
    return "cane with gold eagle handle";
  case 16:
    return "crystalline wand";
  case 17:
    return "metal stick with trigger";
  case 18:
    return "leather-handled stone rod";
  default:
  case 19:
    return "tiny mithril wand";
  }
}

char *ringname(int id)
{
  switch (ring_ids[id])
  {
  case 0:
    return "gold ring with a blue gem";
  case 1:
    return "brass ring";
  case 2:
    return "mithril ring with a red gem";
  case 3:
    return "platinum ring";
    break;
  case 4:
    return "gold dragon's head ring";
  case 5:
    return "bronze ring";
  case 6:
    return "aardvark seal ring";
  case 7:
    return "grey metal ring";
  case 8:
    return "silver skull ring";
  case 9:
    return "onyx ring";
  case 10:
    return "Collegium Magii class ring";
  case 11:
    return "worn stone ring";
  case 12:
    return "diorite ring";
  case 13:
    return "ancient scarab ring";
    break;
  case 14:
    return "plastic charm ring";
  case 15:
    return "soapy gypsum ring";
  case 16:
    return "glass ring";
  case 17:
    return "glowing bluestone ring";
  case 18:
    return "ring with eye sigil";
  default:
  case 19:
    return "zirconium ring";
  }
}

char *cloakname(int id)
{
  switch (cloak_ids[id])
  {
  case 0:
    return "tattered piece of cloth";
  case 1:
    return "fuligin cloak";
  case 2:
    return "chintz cloak";
  case 3:
    return "diaphanous cape";
    break;
  case 4:
    return "red half-cloak";
  case 5:
    return "mouse-hide cloak";
  case 6:
    return "kelly green cloak";
  case 7:
    return "cloth-of-gold cloak";
  case 8:
    return "dirty old cloak";
  case 9:
    return "weightless cloak";
  case 10:
    return "boat cloak";
  case 11:
    return "greasy tarpaulin";
  case 12:
    return "sable cloak";
  case 13:
    return "soft velvet cloak";
    break;
  case 14:
    return "opera cape";
  case 15:
    return "elegant brocade cloak";
  case 16:
    return "cloak of many colors";
  case 17:
    return "grey-green rag";
  case 18:
    return "puce and chartreuse cloak";
  default:
  case 19:
    return "smoky cloak";
  }
}

char *bootname(int id)
{
  switch (boot_ids[id])
  {
  case 0:
    return "sturdy leather boots";
  case 1:
    return "calf-length moccasins";
  case 2:
    return "dark-colored tabi";
  case 3:
    return "patent-leather shoes";
    break;
  case 4:
    return "beaten-up gumshoes";
  case 5:
    return "alligator-hide boots";
  case 6:
    return "comfortable sandals";
  case 7:
    return "roller skates";
  case 8:
    return "purple suede gaiters";
  case 9:
    return "mirror-plated wingtips";
  case 10:
    return "heavy workboots";
  case 11:
    return "polyurethane-soled sneakers";
  case 12:
    return "clodhoppers";
  case 13:
    return "wooden shoes";
    break;
  case 14:
    return "ski boots";
  case 15:
    return "hob-nailed boots";
  case 16:
    return "elven boots";
  case 17:
    return "cowboy boots";
  case 18:
    return "flipflop slippers";
  default:
  case 19:
    return "riding boots";
  }
}

int itemplus()
{
  int p = 0;

  while (random_range(2) == 0)
    p++;
  return (p);
}

int itemcharge()
{
  return (random_range(20) + 1);
}

int itemblessing()
{
  switch (random_range(10))
  {
  case 0:
  case 1:
    return (-1 - random_range(10));
  case 8:
  case 9:
    return (1 + random_range(10));
  default:
    return (0);
  }
}

int twohandedp(int id)
{
  if (id == Object::getIdByName("great-sword") ||
      id == Object::getIdByName("great-axe") ||
      id == Object::getIdByName("quarterstaff") ||
      id == Object::getIdByName("halberd") ||
      id == Object::getIdByName("longbow") ||
      id == Object::getIdByName("crossbow") ||
      id == Object::getIdByName("Desecrator") ||
      id == Object::getIdByName("Goblins' Hewer") ||
      id == Object::getIdByName("giant club") ||
      id == Object::getIdByName("Scythe of Death"))
    return (TRUE);
  else
    return (FALSE);
}

void Object::item_use()
{
  Object *o = this;
  clearmsg();
  switch (o->usef)
  {
  case -1:
    i_no_op(o);
    break;
  case 0:
    i_nothing(o);
    break;

  /* scrolls */
  case I_SPELLS:
    i_spells(o);
    break;
  case I_BLESS:
    i_bless(o);
    break;
  case I_ACQUIRE:
    i_acquire(o);
    break;
  case I_ENCHANT:
    i_enchant(o);
    break;
  case I_TELEPORT:
    i_teleport(o);
    break;
  case I_WISH:
    i_wish(o);
    break;
  case I_CLAIRVOYANCE:
    i_clairvoyance(o);
    break;
  case I_DISPLACE:
    i_displace(o);
    break;
  case I_ID:
    i_id(o);
    break;
  case I_JANE_T:
    i_jane_t(o);
    break;
  case I_FLUX:
    i_flux(o);
    break;
  case I_WARP:
    i_warp(o);
    break;
  case I_ALERT:
    i_alert(o);
    break;
  case I_CHARGE:
    i_charge(o);
    break;
  case I_KNOWLEDGE:
    i_knowledge(o);
    break;
  case I_LAW:
    i_law(o);
    break;
  case I_HINT:
    hint();
    break;
  case I_HERO:
    i_hero(o);
    break;
  case I_TRUESIGHT:
    i_truesight(o);
    break;
  case I_ILLUMINATE:
    i_illuminate(o);
    break;
  case I_DEFLECT:
    i_deflect(o);
    break;

  /* potion functions */
  case I_HEAL:
    i_heal(o);
    break;
  case I_OBJDET:
    i_objdet(o);
    break;
  case I_MONDET:
    i_mondet(o);
    break;
  case I_SLEEP_SELF:
    i_sleep_self(o);
    break;
  case I_NEUTRALIZE_POISON:
    i_neutralize_poison(o);
    break;
  case I_RESTORE:
    i_restore(o);
    break;
  case I_SPEED:
    i_speed(o);
    break;
  case I_AZOTH:
    i_azoth(o);
    break;
  case I_AUGMENT:
    i_augment(o);
    break;
  case I_REGENERATE:
    i_regenerate(o);
    break;
  case I_INVISIBLE:
    i_invisible(o);
    break;
  case I_BREATHING:
    i_breathing(o);
    break;
  case I_FEAR_RESIST:
    i_fear_resist(o);
    break;
  case I_CHAOS:
    i_chaos(o);
    break;
  case I_ACCURACY:
    i_accuracy(o);
    break;
  case I_LEVITATION:
    i_levitate(o);
    break;
  case I_CURE:
    i_cure(o);
    break;

  /* stick functions */
  case I_FIREBOLT:
    i_firebolt(o);
    break;
  case I_LBOLT:
    i_lbolt(o);
    break;
  case I_MISSILE:
    i_missile(o);
    break;
  case I_SLEEP_OTHER:
    i_sleep_other(o);
    break;
  case I_FIREBALL:
    i_fireball(o);
    break;
  case I_LBALL:
    i_lball(o);
    break;
  case I_SNOWBALL:
    i_snowball(o);
    break;
  case I_SUMMON:
    i_summon(o);
    break;
  case I_HIDE:
    i_hide(o);
    break;
  case I_DISRUPT:
    i_disrupt(o);
    break;
  case I_DISINTEGRATE:
    i_disintegrate(o);
    break;
  case I_APPORT:
    i_apport(o);
    break;
  case I_DISPEL:
    i_dispel(o);
    break;
  case I_POLYMORPH:
    i_polymorph(o);
    break;
  case I_FEAR:
    i_fear(o);
    break;

  /* food functions */
  case I_FOOD:
    i_food(o);
    break;
  case I_LEMBAS:
    i_lembas(o);
    break;
  case I_STIM:
    i_stim(o);
    break;
  case I_POW:
    i_pow(o);
    break;
  case I_IMMUNE:
    i_immune(o);
    break;
  case I_POISON_FOOD:
    i_poison_food(o);
    break;
  case I_CORPSE:
    i_corpse(o);
    break;
  case I_PEPPER_FOOD:
    i_pepper_food(o);
    break;

  /* boots functions */
  case I_PERM_SPEED:
    i_perm_speed(o);
    break;
  case I_PERM_HERO:
    i_perm_hero(o);
    break;
  case I_PERM_LEVITATE:
    i_perm_levitate(o);
    break;
  case I_PERM_AGILITY:
    i_perm_agility(o);
    break;

  /* artifact functions */
  case I_SCEPTRE:
    i_sceptre(o);
    break;
  case I_PLANES:
    i_planes(o);
    break;
  case I_STARGEM:
    i_stargem(o);
    break;
  case I_SYMBOL:
    i_symbol(o);
    break;
  case I_ORBMASTERY:
    i_orbmastery(o);
    break;
  case I_ORBFIRE:
    i_orbfire(o);
    break;
  case I_ORBWATER:
    i_orbwater(o);
    break;
  case I_ORBEARTH:
    i_orbearth(o);
    break;
  case I_ORBAIR:
    i_orbair(o);
    break;
  case I_ORBDEAD:
    i_orbdead(o);
    break;
  case I_CRYSTAL:
    i_crystal(o);
    break;
  case I_LIFE:
    i_life(o);
    break;
  case I_DEATH:
    i_death(o);
    break;
  case I_ANTIOCH:
    i_antioch(o);
    break;
  case I_HELM:
    i_helm(o);
    break;
  case I_KOLWYNIA:
    i_kolwynia(o);
    break;
  case I_ENCHANTMENT:
    i_enchantment(o);
    break;
  case I_JUGGERNAUT:
    i_juggernaut(o);
    break;

  /* cloak functions */
  case I_PERM_DISPLACE:
    i_perm_displace(o);
    break;
  case I_PERM_NEGIMMUNE:
    i_perm_negimmune(o);
    break;
  case I_PERM_INVISIBLE:
    i_perm_invisible(o);
    break;
  case I_PERM_PROTECTION:
    i_perm_protection(o);
    break;
  case I_PERM_ACCURACY:
    i_perm_accuracy(o);
    break;
  case I_PERM_TRUESIGHT:
    i_perm_truesight(o);
    break;

  /* ring functions */
  case I_PERM_BURDEN:
    i_perm_burden(o);
    break;
  case I_PERM_STRENGTH:
    i_perm_strength(o);
    break;
  case I_PERM_GAZE_IMMUNE:
    i_perm_gaze_immune(o);
    break;
  case I_PERM_FIRE_RESIST:
    i_perm_fire_resist(o);
    break;
  case I_PERM_POISON_RESIST:
    i_perm_poison_resist(o);
    break;
  case I_PERM_REGENERATE:
    i_perm_regenerate(o);
    break;
  case I_PERM_KNOWLEDGE:
    i_perm_knowledge(o);
    break;

  /* armor functions */
  case I_NORMAL_ARMOR:
    i_normal_armor(o);
    break;
  case I_PERM_FEAR_RESIST:
    i_perm_fear_resist(o);
    break;
  case I_PERM_ENERGY_RESIST:
    i_perm_energy_resist(o);
    break;
  case I_PERM_BREATHING:
    i_perm_breathing(o);
    break;

  /* weapons functions */
  case I_NORMAL_WEAPON:
    i_normal_weapon(o);
    break;
  case I_LIGHTSABRE:
    i_lightsabre(o);
    break;
  case I_DEMONBLADE:
    i_demonblade(o);
    break;
  case I_DESECRATE:
    i_desecrate(o);
    break;
  case I_MACE_DISRUPT:
    i_mace_disrupt(o);
    break;
  case I_DEFEND:
    i_defend(o);
    break;
  case I_VICTRIX:
    i_victrix(o);
    break;

  /* thing functions */
  case I_PICK:
    i_pick(o);
    break;
  case I_KEY:
    i_key(o);
    break;
  case I_PERM_ILLUMINATE:
    i_perm_illuminate(o);
    break;
  case I_TRAP:
    i_trap(o);
    break;
  case I_RAISE_PORTCULLIS:
    i_raise_portcullis(o);
    break;

  /* shield functions */
  case I_NORMAL_SHIELD:
    i_normal_shield(o);
    break;
  case I_PERM_DEFLECT:
    i_perm_deflect(o);
    break;
#ifdef DEBUG /* WDT: good idea, DG.  I'll be using this often, I predict! */
  /* looking for objects without, or with unimplemented, functions */
  default:
    fprintf(DG_debug_log, "tried to use a %s with o->usef %d\n",
            itemid(o), o->usef);
    break;
#endif
  }
}
