#include "glob.h"
#include "defs.h"
#include <vector>

void Weapon::init(std::vector<Object>& objects)
{
  std::vector<Weapon> things = {
      {84, 10, 0, 0, 6, 12, 0, 1, 15, 5, 0, 0, 0, THRUSTING, COMMON, I_NORMAL_WEAPON, 0, WEAPON, "dagger", "dagger", "dagger"},
      {85, 25, 0, 0, 8, 11, 0, 1, 15, 40, 0, 0, 0, CUTTING, COMMON, I_NORMAL_WEAPON, 1, WEAPON, "short sword", "short sword", "short sword"},
      {86, 40, 0, 0, 12, 9, 0, 1, 15, 90, 0, 0, 0, CUTTING, COMMON, I_NORMAL_WEAPON, 2, WEAPON, "broad sword", "broad sword", "broad sword"},
      {87, 50, 0, 0, 16, 8, 0, 1, 15, 250, 0, 0, 0, CUTTING, COMMON, I_NORMAL_WEAPON, 3, WEAPON, "bastard sword", "bastard sword", "bastard sword"},
      {88, 50, 0, 0, 16, 10, 0, 1, 15, 500, 0, 0, 0, CUTTING, COMMON, I_NORMAL_WEAPON, 4, WEAPON, "katana", "katana", "katana"},
      {89, 75, 0, 0, 20, 7, 0, 1, 15, 400, 0, 0, 0, CUTTING, COMMON, I_NORMAL_WEAPON, 5, WEAPON, "great-sword", "great-sword", "great-sword"},
      {90, 15, 0, 0, 6, 15, 0, 1, 15, 50, 0, 0, 0, THRUSTING, COMMON, I_NORMAL_WEAPON, 2, WEAPON, "epee", "epee", "epee"},
      {91, 20, 0, 0, 8, 13, 0, 1, 15, 250, 0, 0, 0, THRUSTING, COMMON, I_NORMAL_WEAPON, 3, WEAPON, "rapier", "rapier", "rapier"},
      {92, 25, 0, 0, 11, 12, 0, 1, 15, 500, 0, 0, 0, THRUSTING, COMMON, I_NORMAL_WEAPON, 5, WEAPON, "estoc", "estoc", "estoc"},
      {93, 35, 0, 0, 8, 8, 0, 1, 15, 40, 0, 0, 0, CUTTING, COMMON, I_NORMAL_WEAPON, 1, WEAPON, "cutlass", "cutlass", "cutlass"},
      {94, 25, 0, 0, 8, 10, 0, 1, 15, 50, 0, 0, 0, CUTTING, COMMON, I_NORMAL_WEAPON, 1, WEAPON, "hand-axe", "hand-axe", "hand-axe"},
      {95, 50, 0, 0, 12, 8, 0, 1, 15, 100, 0, 0, 0, CUTTING, COMMON, I_NORMAL_WEAPON, 2, WEAPON, "battle-axe", "battle-axe", "battle-axe"},
      {96, 100, 0, 0, 24, 7, 0, 1, 15, 200, 0, 0, 0, CUTTING, COMMON, I_NORMAL_WEAPON, 5, WEAPON, "great-axe", "great-axe", "great-axe"},
      {97, 50, 0, 0, 12, 8, 0, 1, 15, 50, 0, 0, 0, STRIKING, COMMON, I_NORMAL_WEAPON, 2, WEAPON, "mace", "mace", "mace"},
      {98, 50, 0, 0, 14, 6, 0, 1, 15, 60, 0, 0, 0, STRIKING, COMMON, I_NORMAL_WEAPON, 2, WEAPON, "war-hammer", "war-hammer", "war-hammer"},
      {99, 60, 0, 0, 16, 7, 0, 1, 15, 150, 0, 0, 0, STRIKING, COMMON, I_NORMAL_WEAPON, 5, WEAPON, "morning-star", "morning-star", "morning-star"},
      {100, 50, 0, 0, 12, 7, 0, 1, 15, 50, 0, 0, 0, STRIKING, COMMON, I_NORMAL_WEAPON, 3, WEAPON, "flail", "flail", "flail"},
      {101, 30, 0, 0, 6, 10, 0, 1, 15, 5, 0, 0, 0, STRIKING, COMMON, I_NORMAL_WEAPON, 0, WEAPON, "club", "club", "club"},
      {102, 80, 0, 0, 9, 12, 0, 1, 15, 30, 0, 0, 0, STRIKING, COMMON, I_NORMAL_WEAPON, 1, WEAPON, "quarterstaff", "quarterstaff", "quarterstaff"},
      {103, 50, 0, 0, 10, 10, 0, 1, 15, 50, 0, 0, 0, THRUSTING, COMMON, I_NORMAL_WEAPON, 2, WEAPON, "spear", "spear", "spear"},
      {104, 100, 0, 0, 16, 6, 0, 1, 15, 100, 0, 0, 0, CUTTING, COMMON, I_NORMAL_WEAPON, 3, WEAPON, "halberd", "halberd", "halberd"},
      {105, 80, 0, 0, 12, 7, 0, 1, 15, 75, 0, 0, 0, THRUSTING, COMMON, I_NORMAL_WEAPON, 3, WEAPON, "trident", "trident", "trident"},
      {106, 20, 0, 0, 4, 8, 1005, 1, 15, 100, 0, 0, 0, STRIKING, COMMON, I_NORMAL_WEAPON, 2, WEAPON, "whip", "whip", "whip"},
      {107, 20, 0, 0, 30, 20, 1002, 1, 15, 2000, 0, 0, 0, THRUSTING, COMMON, I_LIGHTSABRE, 9, WEAPON, "grey metal cylinder", "lightsabre", "lightsabre"},
      {108, 500, 8, 0, 16, 8, 1003, 1, 15, 1000, 0, 0, -8, CUTTING, COMMON, I_DEMONBLADE, 9, WEAPON, "bastard sword", "Demonblade", "Demonblade"},
      {109, 250, 7, 0, 17, 10, 1004, 1, 15, 3000, 0, 0, 7, STRIKING, COMMON, I_MACE_DISRUPT, 7, WEAPON, "mace", "mace of disruption", "mace"},
      {110, 100, 0, 0, 12, 15, 0, 1, 15, 300, 0, 0, 0, MISSILE, COMMON, I_NORMAL_WEAPON, 2, MISSILEWEAPON, "longbow", "longbow", "longbow"},
      {111, 150, 0, 0, 20, 15, 0, 1, 15, 500, 0, 0, 0, MISSILE, COMMON, I_NORMAL_WEAPON, 3, MISSILEWEAPON, "crossbow", "crossbow", "crossbow"},
      {112, 2, 0, 0, 3, 3, 1006, 1, 15, 2, 0, 0, 0, MISSILE, COMMON, I_NORMAL_WEAPON, 1, MISSILEWEAPON, "arrow", "arrow", "arrow"},
      {113, 2, 0, 0, 3, 0, 1007, 1, 15, 5, 0, 0, 0, MISSILE, COMMON, I_NORMAL_WEAPON, 1, MISSILEWEAPON, "bolt", "bolt", "bolt"},
      {114, 50, 0, 0, 3, 10, 1005, 1, 15, 50, 0, 0, 0, MISSILE, COMMON, I_NORMAL_WEAPON, 2, MISSILEWEAPON, "bola", "bola", "bola"},
      {115, 40, 5, 0, 12, 9, 1008, 1, 15, 3000, 0, 0, 0, CUTTING, COMMON, I_NORMAL_WEAPON, 7, WEAPON, "broad sword", "vorpal sword", "sword of self-mutilation"},
      {116, 100, 7, 0, 20, 7, 1009, 1, 15, 5000, 0, 0, -7, CUTTING, COMMON, I_DESECRATE, 9, WEAPON, "great-sword", "Desecrator", "Desecrator"},
      {117, 60, 7, 0, 16, 7, 1010, 1, 15, 2000, 0, 0, 0, STRIKING, COMMON, I_PERM_FIRE_RESIST, 6, WEAPON, "morning-star", "Firestar", "Firestar"},
      {118, 50, 7, 0, 10, 12, 1011, 1, 15, 3000, 0, 0, 7, THRUSTING, COMMON, I_DEFEND, 7, WEAPON, "estoc", "Defender", "Defender"},
      {119, 50, 10, 0, 100, 10, 1012, 1, 15, 5000, 0, 0, 10, THRUSTING, UNIQUE_MADE, I_VICTRIX, 10, WEAPON, "ivory spear", "Victrix", "Victrix"},
      {120, 500, 6, 0, 32, 6, 0, 1, 15, 2000, 0, 0, 0, CUTTING, UNIQUE_MADE, I_NORMAL_WEAPON, 7, WEAPON, "great-axe", "Goblins' Hewer", "Goblins' Hewer"},
      {121, 100, 20, 0, 30, 10, 0, 1, 15, 500, 0, 0, -10, CUTTING, COMMON, I_NORMAL_WEAPON, 6, WEAPON, "scythe", "scythe of slicing", "scythe of slicing"},
      {122, 250, 0, 0, 50, -10, 0, 1, 15, 100, 0, 0, 0, STRIKING, COMMON, I_NORMAL_WEAPON, 5, WEAPON, "giant club", "giant club", "giant club"},
      {123, 500, 0, 0, 10000, 1000, 1014, 1, 15, 10000, 0, 0, 0, CUTTING, UNIQUE_MADE, I_NORMAL_WEAPON, 10, WEAPON, "Scythe of Death", "Scythe of Death", "Scythe of Death"},
      {124, 30, 0, 0, 16, 16, 1015, 1, 15, 1000, 0, 0, 0, STRIKING, COMMON, I_NORMAL_WEAPON, 4, WEAPON, "whip", "Acid whip", "Acid whip"},
      {125, 60, 7, 0, 75, 50, 1016, 1, 15, 2000, 0, 0, 0, STRIKING, COMMON, I_PERM_ENERGY_RESIST, 6, WEAPON, "war-hammer", "Mjolnir", "Mjolnir"},
  };
  objects.insert(objects.end(), things.begin(), things.end());
}