/* omega copyright (c) 1987,1988,1989 by Laurence Raphael Brothers */
/* init.c */

extern "C" {
#include "defs.h"
}
#include <vector>


static std::vector<object> _objects;
extern "C" {
 int NUMSCROLLS = 24;
 int NUMPOTIONS = 18;
 int NUMFOODS = 16;
 int NUMTHINGS = 26;
 int NUMWEAPONS = 42;
 int NUMARMOR = 17;
 int NUMSHIELDS = 8;
 int NUMCLOAKS = 7;
 int NUMBOOTS = 7;
 int NUMRINGS = 10;
 int NUMSTICKS = 17;
 int NUMARTIFACTS = 24;

/* running sum of itemtypes, for indexing into Objects array */
 int THINGID = 0; 
 int FOODID;
 int SCROLLID;
 int POTIONID;
 int WEAPONID;
 int ARMORID;
 int SHIELDID;
 int CLOAKID;
 int BOOTID;
 int RINGID;
 int STICKID;
 int ARTIFACTID;
 int CASHID;
/* Corpse's aux field is monster id */
 int CORPSEID;

 int TOTALITEMS; 

struct object* Objects; 
}
extern "C" void init_items(){
_objects = {
{ 0,10,0,0,0,0,0,1,10,50,0,0,0,0,COMMON,I_RAISE_PORTCULLIS,2,THING,"small grey box with red button","disposeable garage door opener","disposeable garage door opener" },
{ 1,20,0,0,0,0,0,1,20,2000,0,0,0,0,COMMON,I_NO_OP,4,THING,"some rocks","uncut diamonds","uncut diamonds" },{ 2,15,0,0,0,0,0,1,10,50,0,0,0,0,COMMON,I_PICK,2,THING,"twisted piece of metal","thieve's pick","thieve's pick" },{ 3,10,0,0,0,0,0,1,15,1500,0,0,0,0,COMMON,I_NO_OP,1,THING,"large green gem","humongous emerald","humongous emerald" },
{ 4,200,0,0,0,0,0,1,18,1750,0,0,0,0,COMMON,I_NO_OP,4,THING,"gold ingot","gold ingot","gold ingot" },
{ 5,5,0,0,0,0,0,1,1,3000,0,0,0,0,COMMON,I_NO_OP,5,THING,"old illegible documents","bearer bonds","bearer bonds" },
{ 6,100,0,0,0,0,0,1,1,1,0,0,0,0,COMMON,I_NO_OP,0,THING,"bucket of salt water","bucket of salt water","bucket of salt water" },
{ 7,3,0,0,0,0,0,1,10,20,0,0,0,0,COMMON,I_KEY,2,THING,"key","magic key","magic key" },
{ 8,30,0,0,0,0,6,1,8,10,0,0,0,0,COMMON,I_PERM_ILLUMINATE,0,THING,"torch","torch","torch" },
{ 9,10,0,0,0,0,0,1,12,0,0,0,0,0,COMMON,I_NO_OP,0,THING,"grot","grot","grot" },
{ 10,10,0,0,0,0,0,1,12,0,0,0,0,0,COMMON,I_NO_OP,0,THING,"grot","grot","grot" },
{ 11,10,0,0,0,0,0,1,12,0,0,0,0,0,COMMON,I_NO_OP,0,THING,"grot","grot","grot" },
{ 12,10,0,0,0,0,0,1,12,0,0,0,0,0,COMMON,I_NO_OP,0,THING,"grot","grot","grot" },
{ 13,10,0,0,0,0,0,1,12,0,0,0,0,0,COMMON,I_NO_OP,0,THING,"grot","grot","grot" },
{ 14,10,0,0,0,0,0,1,12,0,0,0,0,0,COMMON,I_NO_OP,0,THING,"grot","grot","grot" },
{ 15,10,0,0,0,0,0,1,12,0,0,0,0,0,COMMON,I_NO_OP,0,THING,"grot","grot","grot" },
{ 16,10,0,0,0,0,0,1,12,0,0,0,0,0,UNIQUE_MADE,I_NO_OP,0,THING,"Justiciar's Badge","Justiciar's Badge","Justiciar's Badge" },
{ 17,10,0,0,0,0,89,1,3,30,0,0,0,0,COMMON,I_TRAP,0,THING,"spring-loaded tube","dart-trap component","dart-trap component" },
{ 18,10,0,0,0,0,98,1,3,30,0,0,0,0,COMMON,I_TRAP,0,THING,"pressurized cannister","acid-trap component","acid-trap component" },
{ 19,10,0,0,0,0,92,1,3,30,0,0,0,0,COMMON,I_TRAP,0,THING,"coil of fine wire","snare component","snare component" },
{ 20,10,0,0,0,0,94,1,3,30,0,0,0,0,COMMON,I_TRAP,0,THING,"mound of powdered aluminum","fire-trap component","fire-trap component" },
{ 21,10,0,0,0,0,95,1,3,30,0,0,0,0,COMMON,I_TRAP,0,THING,"powerful rune","teleport-trap component","teleport-trap component" },
{ 22,10,0,0,0,0,97,1,3,30,0,0,0,0,COMMON,I_TRAP,0,THING,"pressurized cannister","sleepgas-trap component","sleepgas-trap component" },
{ 23,10,0,0,0,0,96,1,3,30,0,0,0,0,COMMON,I_TRAP,0,THING,"powerful rune","disintegration-trap component","disintegration-trap component" },
{ 24,10,0,0,0,0,100,1,3,30,0,0,0,0,COMMON,I_TRAP,0,THING,"dark fabric patch","abyss-trap component","abyss-trap component" },
{ 25,10,0,0,0,0,99,1,3,30,0,0,0,0,COMMON,I_TRAP,0,THING,"powerful rune","manadrain-trap component","manadrain-trap component" },
{ 26,20,0,0,0,0,8,1,0,2,0,0,0,0,COMMON,I_FOOD,0,FOOD,"red and white striped bucket","food ration","food ration" },
{ 27,10,0,0,0,0,48,1,0,200,0,0,0,0,COMMON,I_LEMBAS,2,FOOD,"wafer of lembas","wafer of lembas","wafer of lembas" },
{ 28,1,0,0,0,0,1,1,0,50,0,0,0,0,COMMON,I_STIM,3,FOOD,"small gray tablet","stimtab","stimtab" },
{ 29,1,0,0,0,0,1,1,0,100,0,0,0,0,COMMON,I_POW,3,FOOD,"small gray tablet","powtab","powtab" },
{ 30,1,0,0,0,0,36,1,0,20,0,0,0,0,COMMON,I_FOOD,3,FOOD,"small gray tablet","nutritab","nutritab" },
{ 31,1,0,0,0,0,1,1,0,500,0,0,0,0,COMMON,I_IMMUNE,3,FOOD,"small gray tablet","immunotab","immunotab" },
{ 32,1,0,0,0,0,2,1,0,1,0,0,0,0,COMMON,I_FOOD,0,FOOD,"jelly baby","jelly baby","jelly baby" },
{ 33,20,0,0,0,0,-1,1,0,25,0,0,0,0,COMMON,I_POISON_FOOD,1,FOOD,"food ration","poisoned ration","poisoned ration" },
{ 34,2,0,0,0,0,1,1,0,100,0,0,0,0,COMMON,I_PEPPER_FOOD,2,FOOD,"withered reddish stringy vegetable","szechuan pepper","szechuan pepper" },
{ 35,2,0,0,0,0,8,1,0,5,0,0,0,0,COMMON,I_FOOD,2,FOOD,"messy red and white disk","pepperoni pizza pie","pepperoni pizza pie" },
{ 36,2,0,0,0,0,6,1,0,7,0,0,0,0,COMMON,I_FOOD,2,FOOD,"brown bag with strange ideograms","hunan take-out","hunan take-out" },
{ 37,2,0,0,0,0,2,1,0,5,0,0,0,0,COMMON,I_FOOD,2,FOOD,"strange foamy cylinders","twinkies","twinkies" },
{ 38,2,0,0,0,0,3,1,0,3,0,0,0,0,COMMON,I_FOOD,2,FOOD,"squiggly orange spirals","cheese-doodles","cheese-doodles" },
{ 39,2,0,0,0,0,4,1,0,3,0,0,0,0,COMMON,I_FOOD,2,FOOD,"sweet nutty-smelling disks","pecan twirls","pecan_twirls" },
{ 40,2,0,0,0,0,10,1,0,75,0,0,0,0,COMMON,I_FOOD,2,FOOD,"pale white strips with green dots","veal piccata with capers","veal piccata with capers" },
{ 41,2,0,0,0,0,3,1,0,5,0,0,0,0,COMMON,I_FOOD,2,FOOD,"a bag of hard brown kernels","a bag of unmilled grain","a bag of unmilled grain" },
{ 42,5,0,0,0,0,0,1,1,5,0,0,0,0,COMMON,I_NOTHING,0,SCROLL,"?","blank scroll","Antinomy!" },
{ 43,5,0,0,0,0,0,1,1,250,0,0,0,0,COMMON,I_SPELLS,1,SCROLL,"?","scroll of spells","scroll of spell loss" },
{ 44,5,0,0,0,0,0,1,1,400,0,0,0,0,COMMON,I_BLESS,2,SCROLL,"?","scroll of blessing","scroll of cursing" },
{ 45,5,0,0,0,0,0,1,1,5000,0,0,0,0,COMMON,I_ACQUIRE,7,SCROLL,"?","scroll of acquirement","scroll of destruction" },
{ 46,5,0,0,0,0,0,1,1,200,0,0,0,0,COMMON,I_ENCHANT,2,SCROLL,"?","scroll of enchantment","scroll of disenchantment" },
{ 47,5,0,0,0,0,0,1,1,75,0,0,0,0,COMMON,I_TELEPORT,1,SCROLL,"?","scroll of teleportation","scroll of teleportation" },
{ 48,5,0,0,0,0,0,1,1,10000,0,0,0,0,COMMON,I_WISH,10,SCROLL,"?","scroll of wishing","scroll of wishing" },
{ 49,5,0,0,0,0,0,1,1,25,0,0,0,0,COMMON,I_CLAIRVOYANCE,1,SCROLL,"?","scroll of clairvoyance","scroll of amnesia" },
{ 50,5,0,0,0,0,0,1,1,50,0,0,0,0,COMMON,I_DISPLACE,2,SCROLL,"?","scroll of displacement","scroll of vulnerability" },
{ 51,5,0,0,0,0,0,1,1,20,0,0,0,0,COMMON,I_ID,0,SCROLL,"?","scroll of identification","scroll of forgetfulness" },
{ 52,5,0,0,0,0,0,1,1,10,0,0,0,0,COMMON,I_HINT,0,SCROLL,"?","hint sheet","hint sheet" },
{ 53,5,0,0,0,0,0,1,1,50,0,0,0,0,COMMON,I_JANE_T,2,SCROLL,"?","Jane's guide to treasure","Jane's guide to treasure" },
{ 54,5,0,0,0,0,0,1,1,50,0,0,0,0,COMMON,I_ALERT,1,SCROLL,"?","scroll of alertness","scroll of drowsiness" },
{ 55,5,0,0,0,0,0,1,1,300,0,0,0,0,COMMON,I_FLUX,5,SCROLL,"?","scroll of cosmic flux","scroll of cosmic flux" },
{ 56,5,0,0,0,0,0,1,1,100,0,0,0,0,COMMON,I_CHARGE,2,SCROLL,"?","scroll of charging","scroll of draining" },
{ 57,5,0,0,0,0,0,1,1,100,0,0,0,0,COMMON,I_WARP,3,SCROLL,"?","scroll of the warp","scroll of the warp" },
{ 58,5,0,0,0,0,0,1,1,10,0,0,0,0,COMMON,I_KNOWLEDGE,1,SCROLL,"?","scroll of self-knowledge","scroll of delusion" },
{ 59,5,0,0,0,0,0,1,1,100,0,0,0,0,COMMON,I_LAW,2,SCROLL,"?","scroll of law","scroll of law" },
{ 60,5,0,0,0,0,0,1,1,200,0,0,0,0,COMMON,I_HERO,5,SCROLL,"?","scroll of heroism","scroll of cowardliness" },
{ 61,5,0,0,0,0,0,1,1,50,0,0,0,0,COMMON,I_TRUESIGHT,2,SCROLL,"?","scroll of true sight","scroll of blindness" },
{ 62,5,0,0,0,0,0,1,1,250,0,0,0,0,COMMON,I_DISPEL,3,SCROLL,"?","scroll of dispelling","scroll of self-dispelling" },
{ 63,5,0,0,0,0,0,1,1,300,0,0,0,0,COMMON,I_SUMMON,2,SCROLL,"?","scroll of summoning","scroll of summoning" },
{ 64,5,0,0,0,0,0,1,1,30,0,0,0,0,COMMON,I_ILLUMINATE,0,SCROLL,"?","scroll of light","scroll of darkness" },
{ 65,5,0,0,0,0,0,1,1,250,0,0,0,0,COMMON,I_DEFLECT,3,SCROLL,"?","scroll of deflection","scroll of vulnerability" },
{ 66,20,0,0,0,0,0,1,5,0,0,0,0,0,COMMON,I_NO_OP,0,POTION,"?","potion of quenching thirst","Antinomy!" },
{ 67,20,0,0,0,0,0,1,5,40,0,0,0,0,COMMON,I_HEAL,2,POTION,"?","potion of healing","potion of disruption" },
{ 68,20,0,0,0,0,0,1,5,10,0,0,0,0,COMMON,I_OBJDET,1,POTION,"?","potion of object detection","potion of object detection" },
{ 69,20,0,0,0,0,0,1,5,10,0,0,0,0,COMMON,I_MONDET,1,POTION,"?","potion of monster detection","potion of monster detection" },
{ 70,20,0,0,0,0,0,1,5,20,0,0,0,0,COMMON,I_NEUTRALIZE_POISON,2,POTION,"?","potion of neutralize poison","potion of poison" },
{ 71,20,0,0,0,0,0,1,5,100,0,0,0,0,COMMON,I_ALERT,0,POTION,"?","potion of alertness","potion of sleep" },
{ 72,20,0,0,0,0,0,1,5,40,0,0,0,0,COMMON,I_SPEED,1,POTION,"?","potion of speed","potion of slowness" },
{ 73,20,0,0,0,0,0,1,5,50,0,0,0,0,COMMON,I_RESTORE,3,POTION,"?","potion of restoration","potion of debilitation" },
{ 74,20,-1,0,0,0,0,1,5,1500,0,0,0,0,COMMON,I_AZOTH,7,POTION,"mercury","Azoth","mercury" },
{ 75,20,0,0,0,0,0,1,5,100,0,0,0,0,COMMON,I_REGENERATE,4,POTION,"?","potion of regeneration","potion of great disruption" },
{ 76,20,0,0,0,0,0,1,5,100,0,0,0,0,COMMON,I_INVISIBLE,2,POTION,"?","potion of invisibility","potion of aggravation" },
{ 77,20,0,0,0,0,0,1,5,30,0,0,0,0,COMMON,I_BREATHING,2,POTION,"?","potion of breathing","potion of choking" },
{ 78,20,0,0,0,0,0,1,5,200,0,0,0,0,COMMON,I_AUGMENT,5,POTION,"?","potion of augmentation","potion of debilitation" },
{ 79,20,0,0,0,0,0,1,5,50,0,0,0,0,COMMON,I_FEAR_RESIST,2,POTION,"?","potion of banishing fear","potion of fear" },
{ 80,20,0,0,0,0,0,1,5,100,0,0,0,0,COMMON,I_CHAOS,3,POTION,"?","potion of chaos","Antinomy!" },
{ 81,20,0,0,0,0,0,1,5,200,0,0,0,0,COMMON,I_ACCURACY,3,POTION,"?","potion of accuracy","potion of fuzziness" },
{ 82,20,0,0,0,0,0,1,5,50,0,0,0,0,COMMON,I_LEVITATION,1,POTION,"?","potion of levitation","potion of levitation" },
{ 83,20,0,0,0,0,0,1,5,50,0,0,0,0,COMMON,I_CURE,1,POTION,"?","potion of curing","potion of disease" },
{ 84,10,0,0,6,12,0,1,15,5,0,0,0,THRUSTING,COMMON,I_NORMAL_WEAPON,0,WEAPON,"dagger","dagger","dagger" },
{ 85,25,0,0,8,11,0,1,15,40,0,0,0,CUTTING,COMMON,I_NORMAL_WEAPON,1,WEAPON,"short sword","short sword","short sword" },
{ 86,40,0,0,12,9,0,1,15,90,0,0,0,CUTTING,COMMON,I_NORMAL_WEAPON,2,WEAPON,"broad sword","broad sword","broad sword" },
{ 87,50,0,0,16,8,0,1,15,250,0,0,0,CUTTING,COMMON,I_NORMAL_WEAPON,3,WEAPON,"bastard sword","bastard sword","bastard sword" },
{ 88,50,0,0,16,10,0,1,15,500,0,0,0,CUTTING,COMMON,I_NORMAL_WEAPON,4,WEAPON,"katana","katana","katana" },
{ 89,75,0,0,20,7,0,1,15,400,0,0,0,CUTTING,COMMON,I_NORMAL_WEAPON,5,WEAPON,"great-sword","great-sword","great-sword" },
{ 90,15,0,0,6,15,0,1,15,50,0,0,0,THRUSTING,COMMON,I_NORMAL_WEAPON,2,WEAPON,"epee","epee","epee" },
{ 91,20,0,0,8,13,0,1,15,250,0,0,0,THRUSTING,COMMON,I_NORMAL_WEAPON,3,WEAPON,"rapier","rapier","rapier" },
{ 92,25,0,0,11,12,0,1,15,500,0,0,0,THRUSTING,COMMON,I_NORMAL_WEAPON,5,WEAPON,"estoc","estoc","estoc" },
{ 93,35,0,0,8,8,0,1,15,40,0,0,0,CUTTING,COMMON,I_NORMAL_WEAPON,1,WEAPON,"cutlass","cutlass","cutlass" },
{ 94,25,0,0,8,10,0,1,15,50,0,0,0,CUTTING,COMMON,I_NORMAL_WEAPON,1,WEAPON,"hand-axe","hand-axe","hand-axe" },
{ 95,50,0,0,12,8,0,1,15,100,0,0,0,CUTTING,COMMON,I_NORMAL_WEAPON,2,WEAPON,"battle-axe","battle-axe","battle-axe" },
{ 96,100,0,0,24,7,0,1,15,200,0,0,0,CUTTING,COMMON,I_NORMAL_WEAPON,5,WEAPON,"great-axe","great-axe","great-axe" },
{ 97,50,0,0,12,8,0,1,15,50,0,0,0,STRIKING,COMMON,I_NORMAL_WEAPON,2,WEAPON,"mace","mace","mace" },
{ 98,50,0,0,14,6,0,1,15,60,0,0,0,STRIKING,COMMON,I_NORMAL_WEAPON,2,WEAPON,"war-hammer","war-hammer","war-hammer" },
{ 99,60,0,0,16,7,0,1,15,150,0,0,0,STRIKING,COMMON,I_NORMAL_WEAPON,5,WEAPON,"morning-star","morning-star","morning-star" },
{ 100,50,0,0,12,7,0,1,15,50,0,0,0,STRIKING,COMMON,I_NORMAL_WEAPON,3,WEAPON,"flail","flail","flail" },
{ 101,30,0,0,6,10,0,1,15,5,0,0,0,STRIKING,COMMON,I_NORMAL_WEAPON,0,WEAPON,"club","club","club" },
{ 102,80,0,0,9,12,0,1,15,30,0,0,0,STRIKING,COMMON,I_NORMAL_WEAPON,1,WEAPON,"quarterstaff","quarterstaff","quarterstaff" },
{ 103,50,0,0,10,10,0,1,15,50,0,0,0,THRUSTING,COMMON,I_NORMAL_WEAPON,2,WEAPON,"spear","spear","spear" },
{ 104,100,0,0,16,6,0,1,15,100,0,0,0,CUTTING,COMMON,I_NORMAL_WEAPON,3,WEAPON,"halberd","halberd","halberd" },
{ 105,80,0,0,12,7,0,1,15,75,0,0,0,THRUSTING,COMMON,I_NORMAL_WEAPON,3,WEAPON,"trident","trident","trident" },
{ 106,20,0,0,4,8,1005,1,15,100,0,0,0,STRIKING,COMMON,I_NORMAL_WEAPON,2,WEAPON,"whip","whip","whip" },
{ 107,20,0,0,30,20,1002,1,15,2000,0,0,0,THRUSTING,COMMON,I_LIGHTSABRE,9,WEAPON,"grey metal cylinder","lightsabre","lightsabre" },
{ 108,500,8,0,16,8,1003,1,15,1000,0,0,-8,CUTTING,COMMON,I_DEMONBLADE,9,WEAPON,"bastard sword","Demonblade","Demonblade" },
{ 109,250,7,0,17,10,1004,1,15,3000,0,0,7,STRIKING,COMMON,I_MACE_DISRUPT,7,WEAPON,"mace","mace of disruption","mace" },
{ 110,100,0,0,12,15,0,1,15,300,0,0,0,MISSILE,COMMON,I_NORMAL_WEAPON,2,MISSILEWEAPON,"longbow","longbow","longbow" },
{ 111,150,0,0,20,15,0,1,15,500,0,0,0,MISSILE,COMMON,I_NORMAL_WEAPON,3,MISSILEWEAPON,"crossbow","crossbow","crossbow" },
{ 112,2,0,0,3,3,1006,1,15,2,0,0,0,MISSILE,COMMON,I_NORMAL_WEAPON,1,MISSILEWEAPON,"arrow","arrow","arrow" },
{ 113,2,0,0,3,0,1007,1,15,5,0,0,0,MISSILE,COMMON,I_NORMAL_WEAPON,1,MISSILEWEAPON,"bolt","bolt","bolt" },
{ 114,50,0,0,3,10,1005,1,15,50,0,0,0,MISSILE,COMMON,I_NORMAL_WEAPON,2,MISSILEWEAPON,"bola","bola","bola" },
{ 115,40,5,0,12,9,1008,1,15,3000,0,0,0,CUTTING,COMMON,I_NORMAL_WEAPON,7,WEAPON,"broad sword","vorpal sword","sword of self-mutilation" },
{ 116,100,7,0,20,7,1009,1,15,5000,0,0,-7,CUTTING,COMMON,I_DESECRATE,9,WEAPON,"great-sword","Desecrator","Desecrator" },
{ 117,60,7,0,16,7,1010,1,15,2000,0,0,0,STRIKING,COMMON,I_PERM_FIRE_RESIST,6,WEAPON,"morning-star","Firestar","Firestar" },
{ 118,50,7,0,10,12,1011,1,15,3000,0,0,7,THRUSTING,COMMON,I_DEFEND,7,WEAPON,"estoc","Defender","Defender" },
{ 119,50,10,0,100,10,1012,1,15,5000,0,0,10,THRUSTING,UNIQUE_MADE,I_VICTRIX,10,WEAPON,"ivory spear","Victrix","Victrix" },
{ 120,500,6,0,32,6,0,1,15,2000,0,0,0,CUTTING,UNIQUE_MADE,I_NORMAL_WEAPON,7,WEAPON,"great-axe","Goblins' Hewer","Goblins' Hewer" },
{ 121,100,20,0,30,10,0,1,15,500,0,0,-10,CUTTING,COMMON,I_NORMAL_WEAPON,6,WEAPON,"scythe","scythe of slicing","scythe of slicing" },
{ 122,250,0,0,50,-10,0,1,15,100,0,0,0,STRIKING,COMMON,I_NORMAL_WEAPON,5,WEAPON,"giant club","giant club","giant club" },
{ 123,500,0,0,10000,1000,1014,1,15,10000,0,0,0,CUTTING,UNIQUE_MADE,I_NORMAL_WEAPON,10,WEAPON,"Scythe of Death","Scythe of Death","Scythe of Death" },
{ 124,30,0,0,16,16,1015,1,15,1000,0,0,0,STRIKING,COMMON,I_NORMAL_WEAPON,4,WEAPON,"whip","Acid whip","Acid whip" },
{ 125,60,7,0,20,10,1016,1,15,2000,0,0,0,STRIKING,COMMON,I_PERM_ENERGY_RESIST,6,WEAPON,"war-hammer","Mjolnir","Mjolnir" },
{ 126,100,0,0,1,0,0,1,20,5,0,0,0,0,COMMON,I_NORMAL_ARMOR,0,ARMOR,"flak jacket","flak jacket","flak jacket" },
{ 127,200,0,0,2,0,1,1,20,10,0,0,0,0,COMMON,I_NORMAL_ARMOR,1,ARMOR,"soft leather armor","soft leather armor","soft leather armor" },
{ 128,200,0,0,2,0,1,1,20,30,0,0,0,0,COMMON,I_NORMAL_ARMOR,1,ARMOR,"cuirbouilli","cuirbouilli","cuirbouilli" },
{ 129,300,0,0,3,0,2,1,20,100,0,0,0,0,COMMON,I_NORMAL_ARMOR,2,ARMOR,"ring mail","ring mail","ring mail" },
{ 130,400,0,0,4,0,3,1,20,200,0,0,0,0,COMMON,I_NORMAL_ARMOR,3,ARMOR,"chain mail","chain mail","chain mail" },
{ 131,400,0,0,4,0,2,1,20,300,0,0,0,0,COMMON,I_NORMAL_ARMOR,4,ARMOR,"scale mail","scale mail","scale mail" },
{ 132,400,0,0,5,0,3,1,20,450,0,0,0,0,COMMON,I_NORMAL_ARMOR,5,ARMOR,"partial plate mail","partial plate mail","partial plate mail" },
{ 133,600,0,0,6,0,4,1,20,750,0,0,0,0,COMMON,I_NORMAL_ARMOR,6,ARMOR,"full plate mail","full plate mail","full plate mail" },
{ 134,500,0,0,7,0,4,1,20,1500,0,0,0,0,COMMON,I_NORMAL_ARMOR,6,ARMOR,"plate armor","plate armor","plate armor" },
{ 135,200,0,0,5,0,2,1,20,1500,0,0,0,0,COMMON,I_NORMAL_ARMOR,6,ARMOR,"lamellar armor","lamellar armor","lamellar armor" },
{ 136,200,0,0,5,0,2,1,20,2000,0,0,0,0,COMMON,I_PERM_FEAR_RESIST,7,ARMOR,"mithril chain mail","mithril chain mail","mithril chain mail" },
{ 137,300,0,0,8,0,3,1,20,3000,0,0,0,0,COMMON,I_PERM_FEAR_RESIST,7,ARMOR,"mithril plate armor","mithril plate armor","mithril plate armor" },
{ 138,500,0,0,6,0,3,1,20,3000,0,0,0,0,COMMON,I_PERM_FIRE_RESIST,7,ARMOR,"dragonscale armor","dragonscale armor","dragonscale armor" },
{ 139,100,9,0,7,0,2,1,20,1000,0,0,0,0,COMMON,I_PERM_ENERGY_RESIST,8,ARMOR,"prismatrix armor","prismatrix armor","prismatrix armor" },
{ 140,0,0,0,20,0,0,1,20,5000,0,0,0,0,COMMON,I_PERM_BREATHING,9,ARMOR,"powered combat armor","powered combat armor","powered combat armor" },
{ 141,0,0,0,10,0,0,1,20,3000,0,0,0,0,COMMON,I_PERM_BREATHING,7,ARMOR,"powered scout armor","powered scout armor","powered scout armor" },
{ 142,100,5,0,5,0,0,1,20,2000,0,0,-9,0,COMMON,I_PERM_ENERGY_RESIST,3,ARMOR,"demonhide armor","demonhide armor","demonhide armor" },
{ 143,20,0,0,0,0,1,1,15,10,0,0,0,0,COMMON,I_NORMAL_SHIELD,0,SHIELD,"buckler","buckler","buckler" },
{ 144,40,0,0,0,0,2,1,15,20,0,0,0,0,COMMON,I_NORMAL_SHIELD,1,SHIELD,"small round shield","small round shield","small round shield" },
{ 145,100,0,0,0,0,3,1,15,50,0,0,0,0,COMMON,I_NORMAL_SHIELD,2,SHIELD,"large round shield","large round shield","large round shield" },
{ 146,200,0,0,0,0,4,1,15,75,0,0,0,0,COMMON,I_NORMAL_SHIELD,2,SHIELD,"heater shield","heater shield","heater shield" },
{ 147,300,0,0,0,0,5,1,15,150,0,0,0,0,COMMON,I_NORMAL_SHIELD,3,SHIELD,"hoplon","hoplon","hoplon" },
{ 148,500,0,0,0,0,6,1,15,200,0,0,0,0,COMMON,I_NORMAL_SHIELD,4,SHIELD,"tower shield","tower shield","tower shield" },
{ 149,20,0,0,0,0,7,1,15,1000,0,0,0,0,COMMON,I_NORMAL_SHIELD,6,SHIELD,"plasteel shield","plasteel shield","plasteel shield" },
{ 150,200,6,0,0,0,6,1,15,2000,0,0,0,0,COMMON,I_PERM_DEFLECT,7,SHIELD,"shield of deflection","shield of deflection","shield of deflection" },
{ 151,30,0,0,0,0,0,1,4,15,0,0,0,0,COMMON,I_NO_OP,0,CLOAK,"?","cloak of wool","cloak of wool" },
{ 152,30,0,0,0,0,0,1,4,500,0,0,0,0,COMMON,I_PERM_NEGIMMUNE,3,CLOAK,"?","cloak of negimmunity","cloak of level drain" },
{ 153,30,0,0,0,0,0,1,4,500,0,0,0,0,COMMON,I_PERM_INVISIBLE,5,CLOAK,"?","cloak of invisibility","cloak of invisibility" },
{ 154,30,0,0,0,0,0,1,4,1000,0,0,0,0,COMMON,I_PERM_ACCURACY,5,CLOAK,"?","cloak of skill","cloak of skill" },
{ 155,30,0,0,0,0,0,1,4,500,0,0,0,0,COMMON,I_PERM_PROTECTION,3,CLOAK,"?","cloak of protection","cloak of damage" },
{ 156,30,0,0,0,0,0,1,4,2000,0,0,0,0,COMMON,I_PERM_DISPLACE,6,CLOAK,"?","cloak of displacement","cloak of vulnerability" },
{ 157,30,0,0,0,0,0,1,4,500,0,0,0,0,COMMON,I_PERM_TRUESIGHT,3,CLOAK,"?","cloak of true sight","cloak of blindness" },
{ 158,30,0,0,0,0,0,1,6,1000,0,0,0,0,COMMON,I_PERM_SPEED,4,BOOTS,"?","boots of speed","boots of slowness" },
{ 159,30,0,0,0,0,0,1,6,1000,0,0,0,0,COMMON,I_PERM_HERO,6,BOOTS,"?","boots of heroism","boots of cowardliness" },
{ 160,30,0,0,0,0,0,1,6,500,0,0,0,0,COMMON,I_PERM_LEVITATE,3,BOOTS,"?","boots of levitation","boots of levitation" },
{ 161,30,0,0,0,0,0,1,6,250,0,0,0,0,COMMON,I_PERM_AGILITY,3,BOOTS,"?","boots of agility","boots of clumsiness" },
{ 162,30,0,0,0,0,0,1,6,200,0,0,0,0,COMMON,I_BOOTS_JUMPING,2,BOOTS,"?","jumping boots","jumping boots" },
{ 163,30,0,0,0,0,0,1,6,7,0,0,0,0,COMMON,I_NO_OP,0,BOOTS,"?","boots of leather","boots of leather" },
{ 164,30,0,0,0,0,0,1,6,2700,0,0,0,0,COMMON,I_BOOTS_7LEAGUE,7,BOOTS,"?","seven league boots","umpteen league boots" },
{ 165,1,0,0,0,0,0,1,10,400,0,0,0,0,COMMON,I_PERM_TRUESIGHT,3,RING,"?","ring of truesight","ring of blindness" },
{ 166,1,0,0,0,0,0,1,10,1,0,0,-1,0,COMMON,I_PERM_BURDEN,0,RING,"?","ring of burden","ring of burden" },
{ 167,1,0,0,0,0,0,1,10,100,0,0,0,0,COMMON,I_PERM_STRENGTH,1,RING,"?","ring of strength","ring of strength" },
{ 168,1,0,0,0,0,0,1,10,100,0,0,0,0,COMMON,I_PERM_GAZE_IMMUNE,2,RING,"?","ring of gaze immunity","ring of gaze immunity" },
{ 169,1,0,0,0,0,0,1,10,100,0,0,0,0,COMMON,I_PERM_FIRE_RESIST,3,RING,"?","ring of fire resistance","ring of fire resistance" },
{ 170,1,0,0,0,0,0,1,10,10,0,0,0,0,COMMON,I_NO_OP,0,RING,"?","ring of brass and glass","ring of brass and glass" },
{ 171,1,0,0,0,0,0,1,10,100,0,0,0,0,COMMON,I_PERM_POISON_RESIST,4,RING,"?","ring of poison resistance","ring of poison" },
{ 172,1,0,0,0,0,0,1,10,1000,0,0,0,0,COMMON,I_PERM_REGENERATE,5,RING,"?","ring of regeneration","ring of regeneration" },
{ 173,1,0,0,0,0,0,1,10,100,0,0,0,0,COMMON,I_PERM_KNOWLEDGE,0,RING,"?","ring of self-knowledge","ring of delusion" },
{ 174,1,0,0,0,0,0,1,10,500,0,0,0,0,COMMON,I_PERM_PROTECTION,4,RING,"?","ring of protection","ring of vulnerability" },
{ 175,80,0,0,0,0,0,1,10,500,0,0,0,0,COMMON,I_FIREBOLT,3,STICK,"?","staff of firebolts","staff of firebolts" },
{ 176,80,0,0,0,0,0,1,10,10,0,0,0,0,COMMON,I_NOTHING,0,STICK,"?","walking stick","walking stick" },
{ 177,80,0,0,0,0,0,1,10,100,0,0,0,0,COMMON,I_SLEEP_OTHER,1,STICK,"?","staff of sleep","staff of sleep" },
{ 178,80,0,0,0,0,0,1,10,500,0,0,0,0,COMMON,I_LBALL,4,STICK,"?","wand of ball lightning","wand of ball lightning" },
{ 179,80,0,0,0,0,0,1,10,500,0,0,0,0,COMMON,I_SUMMON,2,STICK,"?","rod of summoning","rod of summoning" },
{ 180,80,0,0,0,0,0,1,10,100,0,0,0,0,COMMON,I_HIDE,1,STICK,"?","rod of hiding","rod of hiding" },
{ 181,80,0,0,0,0,0,1,10,500,0,0,0,0,COMMON,I_LBOLT,3,STICK,"?","staff of lightning bolts","staff of lightning bolts" },
{ 182,80,0,0,0,0,0,1,10,500,0,0,0,0,COMMON,I_FIREBALL,5,STICK,"?","wand of fireballs","wand of fireballs" },
{ 183,80,0,0,0,0,0,1,10,2000,0,0,0,0,COMMON,I_DISINTEGRATE,7,STICK,"?","rod of disintegration","rod of disintegration" },
{ 184,80,0,0,0,0,0,1,10,1000,0,0,0,0,COMMON,I_DISRUPT,6,STICK,"?","staff of disruption","staff of disruption" },
{ 185,80,0,0,0,0,0,1,10,100,0,0,0,0,COMMON,I_SNOWBALL,2,STICK,"?","snowball stick","snowball stick" },
{ 186,80,0,0,0,0,0,1,10,50,0,0,0,0,COMMON,I_MISSILE,1,STICK,"?","staff of missiles","staff of missiles" },
{ 187,80,0,0,0,0,0,1,10,200,0,0,0,0,COMMON,I_APPORT,2,STICK,"?","rod of apportation","rod of lossage" },
{ 188,80,0,0,0,0,0,1,10,750,0,0,0,0,COMMON,I_DISPEL,6,STICK,"?","staff of dispelling","staff of self-dispelling" },
{ 189,80,0,0,0,0,0,1,10,500,0,0,0,0,COMMON,I_HEAL,3,STICK,"?","staff of healing","staff of harming" },
{ 190,80,0,0,0,0,0,1,10,1000,0,0,0,0,COMMON,I_POLYMORPH,3,STICK,"wand of stupidity","wand of polymorph","wand of stupidity" },
{ 191,80,0,0,0,0,0,1,10,500,0,0,0,0,COMMON,I_FEAR,2,STICK,"?","wand of fear","wand of fear" },
{ 192,500,0,0,0,0,0,1,15,10000,0,0,0,0,UNIQUE_MADE,I_ORBMASTERY,10,ARTIFACT,"Mysterious Orb","Orb of Mastery","Orb of Mastery" },
{ 193,50,0,0,0,0,0,1,15,2000,0,0,0,0,COMMON,I_ORBFIRE,9,ARTIFACT,"Mysterious Orb","Orb of Fire","Orb of Fire" },
{ 194,50,0,0,0,0,0,1,15,2000,0,0,0,0,COMMON,I_ORBWATER,8,ARTIFACT,"Mysterious Orb","Orb of Water","Orb of Water" },
{ 195,50,0,0,0,0,0,1,15,2000,0,0,0,0,COMMON,I_ORBEARTH,7,ARTIFACT,"Mysterious Orb","Orb of Earth","Orb of Earth" },
{ 196,50,0,0,0,0,0,1,15,2000,0,0,0,0,COMMON,I_ORBAIR,6,ARTIFACT,"Mysterious Orb","Orb of Air","Orb of Air" },
{ 197,25,0,0,0,0,0,1,15,100,0,0,0,0,COMMON,I_ORBDEAD,1,ARTIFACT,"Black Orb","Burnt-out Orb","Burnt-out Orb" },
{ 198,75,0,0,0,0,0,1,15,500,0,0,0,0,COMMON,I_CRYSTAL,3,ARTIFACT,"Glass Orb","Crystal Ball","Ball of Mindlessness" },
{ 199,25,0,0,0,0,0,1,15,1000,0,0,0,0,COMMON,I_ANTIOCH,5,ARTIFACT,"Metal Pineapple","Holy Hand-Grenade of Antioch","Holy Hand-Grenade of Antioch" },
{ 200,500,0,0,0,0,0,1,15,1,0,0,0,0,UNIQUE_UNMADE,I_NOTHING,1,ARTIFACT,"Mystic Amulet","Amulet of Yendor","Amulet of Yendor" },
{ 201,1,0,0,0,0,0,1,15,20000,0,0,0,0,UNIQUE_MADE,I_KOLWYNIA,7,ARTIFACT,"Key","Kolwynia, the Key That Was Lost","Kolwynia, the Key That was Lost" },
{ 202,10,0,0,0,0,0,1,15,500,0,0,0,0,UNIQUE_UNMADE,I_DEATH,3,ARTIFACT,"?","Potion of Death","Potion of Death" },
{ 203,100,0,0,0,0,0,1,15,2000,0,0,0,0,UNIQUE_UNMADE,I_ENCHANTMENT,5,ARTIFACT,"Scintillating Staff","Staff of Enchantment","Staff of Enchantment" },
{ 204,0,0,0,0,0,0,1,15,1500,0,0,0,0,UNIQUE_UNMADE,I_HELM,2,ARTIFACT,"Strange Weightless Helm","Helm of Teleportation","Helm of Teleportation" },
{ 205,10,0,0,0,0,0,1,15,500,0,0,0,0,UNIQUE_UNMADE,I_LIFE,6,ARTIFACT,"?","Potion of Life","Potion of Life" },
{ 206,5,0,0,0,0,1,1,15,5000,0,0,0,0,UNIQUE_MADE,I_SYMBOL,10,ARTIFACT,"Silver Gallows","Holy Symbol of Odin","Holy Symbol of Odin" },
{ 207,5,0,0,0,0,2,1,15,5000,0,0,0,0,UNIQUE_MADE,I_SYMBOL,10,ARTIFACT,"Jet Scarab","Holy Symbol of Set","Holy Symbol of Set" },
{ 208,5,0,0,0,0,3,1,15,5000,0,0,0,0,UNIQUE_MADE,I_SYMBOL,10,ARTIFACT,"Gold Owl Pendant","Holy Symbol of Athena","Holy Symbol of Athena" },
{ 209,5,0,0,0,0,4,1,15,5000,0,0,0,0,UNIQUE_MADE,I_SYMBOL,10,ARTIFACT,"Obsidian Crescent","Holy Symbol of Hecate","Holy Symbol of Hecate" },
{ 210,5,0,0,0,0,5,1,15,5000,0,0,0,0,UNIQUE_MADE,I_SYMBOL,10,ARTIFACT,"Sprig of Mistletoe","Holy Symbol of Druidism","Holy Symbol of Druidism" },
{ 211,5,0,0,0,0,6,1,15,5000,0,0,0,0,UNIQUE_MADE,I_SYMBOL,10,ARTIFACT,"Blue Crystal Pendant","Holy Symbol of Destiny","Holy Symbol of Destiny" },
{ 212,1000,0,0,0,0,0,1,15,1000,0,0,0,0,UNIQUE_UNMADE,I_JUGGERNAUT,6,ARTIFACT,"Crudely Carved Monolith","Juggernaut of Karnak","Juggernaut of Karnak" },
{ 213,10,0,0,0,0,0,1,0,10000,0,0,0,0,UNIQUE_MADE,I_STARGEM,7,ARTIFACT,"Strangely Glowing Crystal","Star Gem","Star Gem" },
{ 214,1000,0,0,0,0,0,1,10,1000,0,0,0,0,UNIQUE_MADE,I_SCEPTRE,10,ARTIFACT,"Extremely Heavy Stick ","Sceptre of High Magic","Sceptre of High Magic" },
{ 215,10,0,0,0,0,0,1,10,1000,0,0,0,0,UNIQUE_MADE,I_PLANES,10,ARTIFACT,"Octagonal Copper Amulet ","Amulet of the Planes","Amulet of the Planes" },
{ 216,0,0,0,0,0,0,1,10,0,0,0,0,0,COMMON,I_NO_OP,0,CASH,"money","money","money (the root of all evil)" },
{ 217,100,0,0,0,0,0,1,10,0,0,0,0,0,COMMON,I_CORPSE,0,CORPSE,"a mysterious corpse","a mysterious corpse","a mysterious corpse" },
};

Objects = _objects.data();
  
 THINGID = 0; 
 FOODID = NUMTHINGS;
 SCROLLID = (FOODID + NUMFOODS);
 POTIONID = (SCROLLID + NUMSCROLLS);
 WEAPONID = (POTIONID + NUMPOTIONS);
 ARMORID = (WEAPONID + NUMWEAPONS);
 SHIELDID = (ARMORID + NUMARMOR);
 CLOAKID = (SHIELDID + NUMSHIELDS);
 BOOTID = (CLOAKID + NUMCLOAKS);
 RINGID = (BOOTID + NUMBOOTS);
 STICKID = (RINGID + NUMRINGS);
 ARTIFACTID = (STICKID + NUMSTICKS);
 CASHID = (ARTIFACTID+NUMARTIFACTS);
/* Corpse's aux field is monster id */
  CORPSEID = (CASHID+1);

  TOTALITEMS = (CORPSEID+1); 
     for(int i = THINGID; i < TOTALITEMS; i++){
        assert(Objects[i].id == i);
        if(i >= THINGID && i < FOODID) assert(Objects[i].objchar == THING);
        if(i >= FOODID && i < SCROLLID) assert(Objects[i].objchar == FOOD);
        if(i >= SCROLLID && i < POTIONID) assert(Objects[i].objchar == SCROLL);
        if(i >= POTIONID && i < WEAPONID) assert(Objects[i].objchar == POTION);
        if(i >= WEAPONID && i < ARMORID) assert(Objects[i].objchar == WEAPON || Objects[i].objchar == MISSILEWEAPON);
        if(i >= ARMORID && i < SHIELDID) assert(Objects[i].objchar == ARMOR);
        if(i >= SHIELDID && i < CLOAKID) assert(Objects[i].objchar == SHIELD);
        if(i >= CLOAKID && i < BOOTID) assert(Objects[i].objchar == CLOAK);
        if(i >= BOOTID && i < RINGID) assert(Objects[i].objchar == BOOTS);
        if(i >= RINGID && i < STICKID) assert(Objects[i].objchar == RING);
        if(i >= STICKID && i < ARTIFACTID) assert(Objects[i].objchar == STICK);
        if(i >= ARTIFACTID && i < CASHID) assert(Objects[i].objchar == ARTIFACT);
        if(i >= CASHID && i < CORPSEID) assert(Objects[i].objchar == CASH);
        if(i >= CORPSEID) assert(Objects[i].objchar == CORPSE);
     }
  }

/* omega, (C) 1987,1988,1989 by Laurence Raphael Brothers */
/* minit.h */
/* This file defines and initializes the Monsters Array */

static std::vector<monster> _monsters;
extern "C" {
  struct monster* Monsters;
}

extern "C" void init_monsters(){
_monsters = {
{ NULL,0,0,0,0,0,0,0,1,1,10,2,4,1,0,1,50,0,1,1,1,-1,-1,COMMON,M_TALK_STUPID,M_MOVE_FLUTTER,M_MELEE_NORMAL,M_NO_OP,M_NO_OP,MOBILE|HOSTILE|FLYING|POISONOUS,0,'h'|CLR(YELLOW),"hornet","dead hornet","AXAX" },
{ NULL,0,0,0,0,0,0,1,30,0,0,0,10,10,0,5,100,2,15,1000,0,-1,-1,COMMON,M_TALK_MP,M_MOVE_FOLLOW,M_MELEE_MP,M_NO_OP,M_SP_MP,MOBILE|NEEDY,0,'@'|CLR(RED),"mendicant priest","dead mendicant priest","BX" },
{ NULL,0,0,0,0,0,0,2,15,0,0,0,10,10,0,7,0,3,5,1000,0,-1,-1,COMMON,M_TALK_IM,M_MOVE_FOLLOW,M_NO_OP,M_NO_OP,M_SP_ESCAPE,MOBILE,0,'@'|CLR(RED),"itinerant merchant","dead itinerant merchant","BX" },
{ NULL,0,0,0,0,0,0,3,150,20,20,25,10,1,0,3,50,0,150,1000,0,-1,WEAPONID+5,COMMON,M_TALK_GUARD,M_MOVE_SMART,M_MELEE_NORMAL,M_NO_OP,M_SP_WHISTLEBLOWER,MOBILE,0,'G'|CLR(RED),"guardsman","dead guardsman","A?A?A?B?B?B?" },
{ NULL,0,0,0,0,0,0,4,5,5,5,5,5,5,0,5,5,0,5,1000,0,-1,-1,COMMON,M_TALK_MAN,M_MOVE_SMART,M_MELEE_NORMAL,M_NO_OP,M_NO_OP,AWAKE|HOSTILE,0,'@'|CLR(RED),"Log NPC","dead NPC","A?B?" },
{ NULL,0,0,0,0,0,0,5,5,5,5,1,2,1,0,5,25,0,2,200,10,-1,-1,COMMON,M_TALK_ANIMAL,M_MOVE_RANDOM,M_MELEE_NORMAL,M_NO_OP,M_NO_OP,MOBILE|SWIMMING|EDIBLE,0,'s'|CLR(WHITE),"sheep","side of mutton","ALBX" },
{ NULL,0,0,0,0,0,0,6,16,6,6,1,2,1,0,6,0,0,6,200,0,-1,-1,COMMON,M_TALK_MERCHANT,M_NO_OP,M_MELEE_NORMAL,M_NO_OP,M_SP_MERCHANT,MOBILE,0,'@'|CLR(RED),"merchant","dead merchant","A?B?" },
{ NULL,0,0,0,0,0,0,7,10,5,5,5,5,5,0,5,25,1,5,1800,0,-1,-1,COMMON,M_TALK_MAN,M_MOVE_SMART,M_MELEE_NORMAL,M_NO_OP,M_NO_OP,MOBILE|WANDERING,0,'@'|CLR(RED),"0th level NPC","dead 0th level NPC","AXBX" },
{ NULL,0,0,0,0,0,0,8,5,5,5,5,5,5,0,5,5,0,5,1000,0,-1,-1,UNIQUE_MADE,M_TALK_MAN,M_MOVE_SMART,M_MELEE_NORMAL,M_NO_OP,M_NO_OP,AWAKE|HOSTILE,0,'@'|CLR(RED),"Hiscore NPC","dead NPC","A?B?" },
{ NULL,0,0,0,0,0,0,9,25,12,5,15,3,3,1,8,100,0,10,100,0,-1,WEAPONID+17,COMMON,M_TALK_STUPID,M_MOVE_NORMAL,M_MELEE_NORMAL,M_NO_OP,M_NO_OP,MOBILE|HOSTILE|HUNGRY|POISONOUS,pow2(FLAME)|pow2(COLD)|pow2(ELECTRICITY),'g'|CLR(BROWN),"grunt","dead grunt","ACAC" },
{ NULL,0,0,0,0,0,0,10,1,10,5,2,10,10,1,4,0,0,3,1,5,POTIONID+5,-1,COMMON,M_TALK_STUPID,M_MOVE_FLUTTER,M_MELEE_SLEEP,M_NO_OP,M_NO_OP,MOBILE|HOSTILE|FLYING,0,'t'|CLR(PURPLE),"tse-tse fly","dead tse-tse fly","AX" },
{ NULL,0,0,0,0,0,0,11,1,0,0,0,10,10,1,10,0,1,5,2,50,SCROLLID+21,-1,COMMON,M_TALK_STUPID,M_MOVE_FLUTTER,M_NO_OP,M_NO_OP,M_SP_SUMMON,0,0,'f'|CLR(PURPLE),"fnord","fnord's antennae","" },  
{ NULL,0,0,0,0,0,0,12,5,5,3,5,5,2,1,3,30,0,5,10,0,-1,-1,COMMON,M_TALK_STUPID,M_MOVE_FLUTTER,M_MELEE_DISEASE,M_NO_OP,M_NO_OP,MOBILE|HOSTILE|HUNGRY|SWIMMING,0,'r'|CLR(BROWN),"sewer rat","dead sewer rat","ALAL" },  
{ NULL,0,0,0,0,0,0,13,12,0,0,0,10,10,1,10,0,0,1,1,0,-1,-1,COMMON,M_TALK_STUPID,M_NO_OP,M_NO_OP,M_NO_OP,M_SP_AGGRAVATE,0,pow2(FLAME),'f'|CLR(CYAN),"aggravator fungus","aggravator fungus spores","" },  
  /* WDT: this one used to blink.  I HATE BLINKING. */
{ NULL,0,0,0,0,0,0,14,50,0,5,0,3,3,1,24,100,2,20,20,25,SCROLLID+5,-1,COMMON,M_TALK_STUPID,M_NO_OP,M_NO_OP,M_NO_OP,M_MOVE_TELEPORT,MOBILE,0,'b'|CLR(BRIGHT_WHITE)/*|CLR(FG_BLINK)*/,"blipper","blipper organ","BX" },
{ NULL,0,0,0,0,0,0,15,8,10,8,8,10,2,1,5,0,1,10,500,0,-1,WEAPONID+0,COMMON,M_TALK_GREEDY,M_MOVE_SMART,M_MELEE_NORMAL,M_NO_OP,M_NO_OP,MOBILE|HOSTILE|GREEDY,0,'g'|CLR(GREEN),"goblin","dead goblin","AXBX" },
{ NULL,0,0,0,0,0,0,16,10,10,10,10,4,4,1,9,50,1,25,5,10,SCROLLID+19,-1,COMMON,M_TALK_SILENT,M_MOVE_SMART,M_MELEE_NORMAL,M_NO_OP,M_SP_ILLUSION,MOBILE|HOSTILE|POISONOUS,pow2(SLEEP),'p'|CLR(RED),"phantasticon","phantasticon's eyes","AXAXBX" },
{ NULL,0,0,0,0,0,0,17,5,10,10,15,10,3,1,12,100,0,15,25,0,-1,-1,COMMON,M_TALK_ROBOT,M_MOVE_NORMAL,M_MELEE_NORMAL,M_NO_OP,M_NO_OP,MOBILE,pow2(ELECTRICITY)|pow2(POISON)|pow2(FEAR)|pow2(SLEEP),'R'|CLR(GREY),"household robot","household robot battery","ACBC" },
{ NULL,0,0,0,0,0,0,18,1,5,5,5,10,10,1,8,50,0,1,250,0,-1,-1,COMMON,M_TALK_STUPID,M_MOVE_SCAREDY,M_MELEE_NORMAL,M_NO_OP,M_NO_OP,MOBILE|HOSTILE,0,'g'|CLR(WHITE),"pencil-necked geek","dead pencil-necked geek","AX" },
{ NULL,0,0,0,0,0,0,19,6,8,5,6,4,3,1,4,50,0,6,30,0,-1,-1,COMMON,M_TALK_MIMSY,M_MOVE_FLUTTER,M_MELEE_NORMAL,M_NO_OP,M_NO_OP,MOBILE|FLYING|EDIBLE,0,'b'|CLR(GREEN),"borogrove","borogrove wings","AXBX" },
{ NULL,0,0,0,0,0,0,20,3,0,15,1,4,4,1,2,50,0,1,20,0,-1,-1,COMMON,M_TALK_ANIMAL,M_MOVE_FLUTTER,M_MELEE_NORMAL,M_NO_OP,M_NO_OP,MOBILE|FLYING|EDIBLE,0,'q'|CLR(BROWN),"quail","quail en brochet","" },
{ NULL,0,0,0,0,0,0,21,13,10,5,5,2,1,1,4,50,0,3,20,0,-1,-1,COMMON,M_TALK_ANIMAL,M_MOVE_ANIMAL,M_MELEE_NORMAL,M_NO_OP,M_NO_OP,MOBILE|SWIMMING|EDIBLE,0,'b'|CLR(BROWN),"badger","badger ribs","ALAL" },
{ NULL,0,0,0,0,0,0,22,7,15,10,10,10,5,1,2,50,0,10,20,0,-1,-1,COMMON,M_TALK_ANIMAL,M_MOVE_ANIMAL,M_MELEE_NORMAL,M_NO_OP,M_NO_OP,MOBILE|FLYING|EDIBLE,0,'h'|CLR(BROWN),"hawk","buffalo style hawk wings","AH" },
{ NULL,0,0,0,0,0,0,23,23,5,10,5,10,10,1,2,50,0,5,500,0,-1,-1,COMMON,M_TALK_ANIMAL,M_MOVE_ANIMAL,M_MELEE_NORMAL,M_NO_OP,M_NO_OP,MOBILE|SWIMMING|EDIBLE,0,'d'|CLR(BROWN),"deer","venison","AXBXBX" },
{ NULL,0,0,0,0,0,0,24,30,10,5,10,4,2,1,5,50,0,5,500,0,-1,-1,COMMON,M_TALK_ANIMAL,M_MOVE_ANIMAL,M_MELEE_NORMAL,M_NO_OP,M_NO_OP,MOBILE|HOSTILE|HUNGRY|EDIBLE,0,'c'|CLR(BROWN),"camel","hump au jus","AXBX" },
{ NULL,0,0,0,0,0,0,25,20,0,5,5,4,2,1,4,50,0,3,400,0,-1,-1,COMMON,M_TALK_ANIMAL,M_MOVE_ANIMAL,M_MELEE_NORMAL,M_NO_OP,M_NO_OP,MOBILE|SWIMMING|EDIBLE,0,'a'|CLR(BROWN),"anteater","roast loin of anteater","AL" },
{ NULL,0,0,0,0,0,0,26,3,0,7,1,4,4,1,3,50,0,1,20,0,-1,-1,COMMON,M_TALK_ANIMAL,M_MOVE_ANIMAL,M_MELEE_NORMAL,M_NO_OP,M_NO_OP,MOBILE|SWIMMING|EDIBLE,0,'r'|CLR(BROWN),"rabbit","bunnyburgers","AL" },
{ NULL,0,0,0,0,0,0,27,3,0,18,1,4,4,1,2,50,0,1,20,0,-1,-1,COMMON,M_TALK_ANIMAL,M_MOVE_ANIMAL,M_NO_OP,M_NO_OP,M_NO_OP,MOBILE|ONLYSWIM|EDIBLE,0,'t'|CLR(CYAN),"trout","filet of trout","" },
{ NULL,0,0,0,0,0,0,28,1,0,0,0,4,4,1,4,50,0,1,20,0,-1,-1,COMMON,M_TALK_ANIMAL,M_MOVE_ANIMAL,M_NO_OP,M_NO_OP,M_NO_OP,MOBILE|ONLYSWIM|EDIBLE,0,'b'|CLR(CYAN),"striped bass","bass filets","" },
{ NULL,0,0,0,0,0,0,29,5,10,10,12,10,2,1,3,50,0,5,20,0,-1,-1,COMMON,M_TALK_PARROT,M_MOVE_FLUTTER,M_MELEE_NORMAL,M_NO_OP,M_NO_OP,MOBILE|HUNGRY|FLYING|EDIBLE,0,'p'|CLR(PURPLE),"parrot","grilled breast of parrot","AH" },
{ NULL,0,0,0,0,0,0,30,10,10,5,5,10,2,1,4,20,0,8,20,0,-1,-1,COMMON,M_TALK_HYENA,M_MOVE_ANIMAL,M_MELEE_NORMAL,M_NO_OP,M_NO_OP,MOBILE|HOSTILE|HUNGRY|SWIMMING|EDIBLE,0,'h'|CLR(BROWN),"hyena","hyena ribs","AX" },
{ NULL,0,0,0,0,0,0,31,20,16,10,15,10,3,2,3,50,1,40,1000,0,-1,WEAPONID+1,COMMON,M_TALK_NINJA,M_MOVE_SMART,M_MELEE_NORMAL,M_NO_OP,M_SP_SURPRISE,MOBILE|HOSTILE|M_INVISIBLE,0,'n'|CLR(GREY),"apprentice ninja","dead ninja","A?A?B?B?" },
{ NULL,0,0,0,0,0,0,32,30,15,10,5,10,10,2,6,0,0,35,250,100,-1,-1,COMMON,M_TALK_TITTER,M_MOVE_FLUTTER,M_MELEE_NG,M_NO_OP,M_NO_OP,MOBILE|HOSTILE|FLYING|POISONOUS,0,'n'|CLR(GREY),"night gaunt","dead night gaunt","ACAC" },
{ NULL,0,0,0,0,0,0,33,32,0,10,0,10,10,2,2,0,3,20,1000,0,-1,-1,COMMON,M_TALK_THIEF,M_MOVE_SMART,M_NO_OP,M_NO_OP,M_SP_THIEF,MOBILE|HOSTILE|GREEDY,0,'@'|CLR(RED),"sneak-thief","dead sneak-thief","AXB?B?B?" },
{ NULL,0,0,0,0,0,0,34,25,0,0,0,10,10,2,5,0,0,10,1,20,POTIONID+16,-1,COMMON,M_NO_OP,M_MOVE_RANDOM,M_NO_OP,M_NO_OP,M_SP_EXPLODE,MOBILE|FLYING,pow2(SLEEP),'e'|CLR(GREEN),"floating eye","dead floating eye","" },
{ NULL,0,0,0,0,0,0,35,30,10,10,10,6,3,2,4,0,0,25,10,0,-1,-1,COMMON,M_TALK_SLITHY,M_MOVE_FLUTTER,M_MELEE_NORMAL,M_NO_OP,M_NO_OP,MOBILE,0,'t'|CLR(GREEN),"tove","dead tove","ALBX" },
{ NULL,0,0,0,0,0,0,36,32,15,10,5,5,3,2,8,0,1,30,50,30,POTIONID+10,-1,COMMON,M_NO_OP,M_MOVE_FLUTTER,M_MELEE_NORMAL,M_STRIKE_MISSILE,M_NO_OP,MOBILE|HOSTILE|M_INVISIBLE,0,'n'|CLR(GREY),"transparent nasty","dead transparent nasty","ACAC" },
{ NULL,0,0,0,0,0,0,37,32,0,10,0,5,10,2,20,0,0,30,1,0,-1,-1,COMMON,M_TALK_HINT,M_MOVE_SPIRIT,M_NO_OP,M_NO_OP,M_SP_GHOST,MOBILE|WANDERING|INTANGIBLE,pow2(NORMAL_DAMAGE)|pow2(FEAR)|pow2(SLEEP),'g'|CLR(GREY),"ghost","ghost ectoplasm","" },
{ NULL,0,0,0,0,0,0,38,20,5,10,5,5,3,2,8,0,2,40,1,100,-1,-1,COMMON,M_TALK_EVIL,M_MOVE_SCAREDY,M_MELEE_NORMAL,M_NO_OP,M_SP_SPELL,MOBILE|HOSTILE,pow2(COLD),'e'|CLR(RED),"enchanter","dead enchanter","AXBXBX" },
{ NULL,0,0,0,0,0,0,39,7,0,0,0,10,3,2,12,0,0,40,1,10,SCROLLID+22,-1,COMMON,M_NO_OP,M_NO_OP,M_NO_OP,M_NO_OP,M_SP_BLACKOUT,AWAKE|HOSTILE|POISONOUS,0,'f'|CLR(GREY),"murk fungus","murk cloud particles","" },
{ NULL,0,0,0,0,0,0,40,25,20,12,10,10,3,2,4,0,1,30,1,-1,-1,WEAPONID+12,COMMON,M_TALK_EVIL,M_MOVE_SMART,M_MELEE_NORMAL,M_STRIKE_MISSILE,M_NO_OP,MOBILE|HOSTILE|GREEDY,pow2(FEAR),'G'|CLR(GREEN),"goblin chieftain","dead goblin chieftain","A?A?B?" },
{ NULL,0,0,0,0,0,0,41,40,15,5,15,8,3,2,4,10,0,35,50,0,-1,-1,COMMON,M_TALK_ANIMAL,M_MOVE_NORMAL,M_MELEE_NORMAL,M_NO_OP,M_NO_OP,MOBILE|HOSTILE|HUNGRY|SWIMMING|EDIBLE,pow2(FEAR)|pow2(SLEEP),'w'|CLR(BROWN),"wolf","wolf cutlets","AXAXAX" },
{ NULL,0,0,0,0,0,0,42,20,15,15,10,3,3,2,3,10,0,30,50,0,-1,-1,COMMON,M_TALK_ANIMAL,M_MOVE_NORMAL,M_MELEE_POISON,M_NO_OP,M_NO_OP,MOBILE|HOSTILE|POISONOUS,pow2(FEAR)|pow2(SLEEP),'a'|CLR(RED),"giant soldier ant","ant mandibles","AXAXAX" },
{ NULL,0,0,0,0,0,0,43,100,25,25,50,3,3,2,12,10,0,50,500,0,-1,-1,COMMON,M_TALK_ANIMAL,M_MOVE_ANIMAL,M_MELEE_NORMAL,M_NO_OP,M_NO_OP,MOBILE|HUNGRY|SWIMMING|EDIBLE,0,'e'|CLR(GREY),"elephant","trunk steak","AX" },
{ NULL,0,0,0,0,0,0,44,50,20,5,20,6,3,2,4,10,0,40,500,0,-1,-1,COMMON,M_TALK_HORSE,M_MOVE_NORMAL,M_MELEE_NORMAL,M_NO_OP,M_NO_OP,MOBILE|HUNGRY|SWIMMING|EDIBLE,0,'h'|CLR(BROWN),"horse","steaming horsemeat","AX" },
{ NULL,0,0,0,0,0,0,45,35,15,5,30,4,1,3,4,50,0,75,50,50,RINGID+4,-1,COMMON,M_TALK_STUPID,M_MOVE_FLUTTER,M_MELEE_FIRE,M_NO_OP,M_NO_OP,MOBILE|HOSTILE|GREEDY,pow2(FLAME),'s'|CLR(LIGHT_RED),"salamander","salamander scales","AXAX" },
{ NULL,0,0,0,0,0,0,46,100,10,10,20,5,2,3,8,50,0,50,10,50,RINGID+3,-1,COMMON,M_TALK_STUPID,M_MOVE_NORMAL,M_MELEE_NORMAL,M_STRIKE_BLIND,M_NO_OP,MOBILE|HOSTILE|HUNGRY|GREEDY,0,'C'|CLR(GREEN),"catoblepas","catoblepas' eyes","AXBX" },
{ NULL,0,0,0,0,0,0,47,15,18,15,15,3,3,3,4,0,2,80,25,50,STICKID+10,-1,COMMON,M_TALK_EVIL,M_MOVE_SMART,M_MELEE_COLD,M_NO_OP,M_SP_DEMON,MOBILE|HOSTILE,pow2(COLD)|pow2(POISON)|pow2(FEAR)|pow2(SLEEP),'f'|CLR(LIGHT_BLUE),"lesser frost demon","lesser frost demon's heart","A?A?B?" },
{ NULL,0,0,0,0,0,0,48,10,20,0,50,5,1,3,20,0,0,60,10,0,-1,-1,COMMON,M_NO_OP,M_MOVE_FOLLOW,M_MELEE_NORMAL,M_NO_OP,M_SP_ACID_CLOUD,MOBILE|FLYING,pow2(POISON)|pow2(SLEEP),'a'|CLR(YELLOW),"acid cloud","acid pool","AX" },
{ NULL,0,0,0,0,0,0,49,1,20,0,0,5,5,2,10,100,0,90,10,0,-1,-1,COMMON,M_TALK_SILENT,M_MOVE_SPIRIT,M_MELEE_SPIRIT,M_NO_OP,M_SP_SURPRISE,MOBILE|HOSTILE|FLYING|INTANGIBLE|M_INVISIBLE,pow2(NORMAL_DAMAGE)|pow2(POISON)|pow2(FEAR)|pow2(SLEEP),'p'|CLR(GREY),"phantom","hardly anything at all","AX" },
{ NULL,0,0,0,0,0,0,50,32,18,10,32,5,20,3,5,100,3,500,100,0,-1,WEAPONID+36,UNIQUE_MADE,M_TALK_GREEDY,M_MOVE_SMART,M_MELEE_NORMAL,M_STRIKE_MISSILE,M_NO_OP,MOBILE|HOSTILE|GREEDY,0,'K'|CLR(LIGHT_GREEN),"The Goblin King","The Head of the Goblin King","A?A?B?B?" },
{ NULL,0,0,0,0,0,0,51,42,16,10,10,8,4,3,3,0,0,75,500,1,-1,-1,COMMON,M_TALK_ANIMAL,M_MOVE_FLUTTER,M_MELEE_NORMAL,M_NO_OP,M_NO_OP,MOBILE|HOSTILE|FLYING|EDIBLE,pow2(FEAR)|pow2(SLEEP),'P'|CLR(PURPLE),"pterodactyl","pterodactyl patee","AH" },
{ NULL,0,0,0,0,0,0,52,25,10,10,10,5,5,3,6,0,2,40,500,-1,-1,-1,COMMON,M_TALK_EVIL,M_MOVE_SMART,M_MELEE_NORMAL,M_NO_OP,M_SP_SPELL,MOBILE|HOSTILE|GREEDY,0,'G'|CLR(GREEN),"goblin shaman","dead goblin shaman","AXBX" },
{ NULL,0,0,0,0,0,0,53,60,20,10,25,5,1,3,3,0,0,50,50,-1,-1,-1,COMMON,M_TALK_ANIMAL,M_MOVE_NORMAL,M_MELEE_NORMAL,M_NO_OP,M_NO_OP,MOBILE|HOSTILE|HUNGRY|SWIMMING|EDIBLE,0,'l'|CLR(YELLOW),"lion","lion souflee","AXAX" },
{ NULL,0,0,0,0,0,0,54,30,15,10,15,5,1,3,5,0,2,75,50,-1,-1,WEAPONID+27,COMMON,M_TALK_GREEDY,M_MOVE_SMART,M_MELEE_NORMAL,M_STRIKE_MISSILE,M_NO_OP,MOBILE|HOSTILE|GREEDY,0,'b'|CLR(RED),"brigand","dead brigand","AXAXBX" },
{ NULL,0,0,0,0,0,0,55,70,25,20,40,3,1,3,10,80,0,55,500,-1,-1,-1,COMMON,M_TALK_ANIMAL,M_MOVE_ANIMAL,M_MELEE_NORMAL,M_NO_OP,M_NO_OP,MOBILE|HUNGRY|SWIMMING|EDIBLE,pow2(FEAR),'b'|CLR(BROWN),"bear","bear's sirloin tips","AXAXBX" },
{ NULL,0,0,0,0,0,0,56,10,25,10,20,3,1,3,3,40,0,45,30,0,-1,-1,COMMON,M_TALK_ANIMAL,M_MOVE_NORMAL,M_MELEE_POISON,M_NO_OP,M_NO_OP,MOBILE|HOSTILE|POISONOUS,0,'m'|CLR(RED),"mamba","mamba filet","AXAX" },
{ NULL,0,0,0,0,0,0,57,40,15,10,30,3,1,3,7,0,1,40,20,0,-1,-1,COMMON,M_NO_OP,M_MOVE_NORMAL,M_MELEE_POISON,M_NO_OP,M_NO_OP,MOBILE|HOSTILE|HUNGRY|ONLYSWIM|POISONOUS,pow2(POISON),'M'|CLR(BLUE),"man o' war","deliquescing tentacles","AXAX" },
{ NULL,0,0,0,0,0,0,58,40,5,10,10,5,2,3,5,0,1,100,20,0,-1,-1,COMMON,M_TALK_MAN,M_MOVE_NORMAL,M_MELEE_NORMAL,M_NO_OP,M_SP_WERE,MOBILE,0,'@'|CLR(RED),"were-human","dead were-human","AXBX" },
{ NULL,0,0,0,0,0,0,59,4,0,0,1,5,2,3,5,0,1,50,20,0,-1,-1,COMMON,M_TALK_SILENT,M_MOVE_SPIRIT,M_MELEE_SPIRIT,M_NO_OP,M_NO_OP,MOBILE|HOSTILE,pow2(COLD)|pow2(ELECTRICITY)|pow2(POISON)|pow2(ACID)|pow2(FEAR)|pow2(SLEEP)|pow2(NEGENERGY)|pow2(OTHER_MAGIC)|pow2(THEFT)|pow2(GAZE)|pow2(INFECTION),'T'|CLR(GREY),"thought-form","a velleity","ACACACACAC" },
{ NULL,0,0,0,0,0,0,60,100,15,12,25,6,2,4,6,25,2,150,300,20,STICKID+11,-1,COMMON,M_TALK_HUNGRY,M_MOVE_NORMAL,M_MELEE_NORMAL,M_STRIKE_MISSILE,M_NO_OP,MOBILE|HOSTILE|HUNGRY|FLYING,0,'M'|CLR(YELLOW),"manticore","manticore spikes","AXAX" },
{ NULL,0,0,0,0,0,0,61,50,12,10,10,10,10,4,2,50,0,100,300,10,POTIONID+6,-1,COMMON,M_TALK_HUNGRY,M_MOVE_FLUTTER,M_MELEE_NORMAL,M_NO_OP,M_NO_OP,MOBILE|HOSTILE|HUNGRY,0,'T'|CLR(BROWN),"tasmanian devil","dead tasmanian devil","AXAXAXAX" },
{ NULL,0,0,0,0,0,0,62,100,15,15,50,5,2,4,7,100,0,100,100,0,-1,-1,COMMON,M_TALK_ROBOT,M_MOVE_SMART,M_MELEE_NORMAL,M_NO_OP,M_SP_POISON_CLOUD,MOBILE|HOSTILE,pow2(ELECTRICITY)|pow2(POISON)|pow2(FEAR)|pow2(SLEEP),'a'|CLR(GREY),"automatum minor","automatum minor battery","ACBC" },
{ NULL,0,0,0,0,0,0,63,75,30,10,15,5,1,4,12,75,0,125,50,20,POTIONID+17,-1,COMMON,M_TALK_SILENT,M_MOVE_NORMAL,M_MELEE_DISEASE,M_NO_OP,M_SP_SURPRISE,MOBILE|HOSTILE|HUNGRY|M_INVISIBLE|SWIMMING,pow2(FLAME)|pow2(ELECTRICITY)|pow2(POISON),'s'|CLR(GREEN),"denebian slime devil","denebian slime","AL" },  
{ NULL,0,0,0,0,0,0,64,50,18,12,25,5,1,4,3,75,0,125,500,0,-1,-1,COMMON,M_TALK_BURBLE,M_MOVE_FLUTTER,M_MELEE_NORMAL,M_NO_OP,M_NO_OP,MOBILE|HOSTILE|HUNGRY|FLYING|EDIBLE,pow2(POISON),'j'|CLR(PURPLE),"jub-jub bird","jube-jubes","AHAH" },
{ NULL,0,0,0,0,0,0,65,50,15,5,20,4,1,4,7,0,0,150,500,0,-1,-1,COMMON,M_TALK_EVIL,M_MOVE_NORMAL,M_MELEE_POISON,M_NO_OP,M_SP_SURPRISE,MOBILE|HOSTILE|HUNGRY|M_INVISIBLE|POISONOUS,pow2(POISON)|pow2(FEAR)|pow2(SLEEP),'h'|CLR(GREY),"haunt","dessicated corpse","ACAC" },
{ NULL,0,0,0,0,0,0,66,50,20,10,10,4,4,4,5,0,1,150,1,200,-1,-1,COMMON,M_TALK_DEMONLOVER,M_MOVE_SMART,M_NO_OP,M_NO_OP,M_SP_DEMONLOVER,MOBILE|HOSTILE|POISONOUS,pow2(POISON)|pow2(FEAR)|pow2(SLEEP),'!'|CLR(RED),"incubus/succubus","(null)","(null)" },
{ NULL,0,0,0,0,0,0,67,50,0,10,0,4,4,4,6,0,0,50,1,0,-1,-1,COMMON,M_TALK_SEDUCTOR,M_MOVE_SMART,M_NO_OP,M_NO_OP,M_SP_SEDUCTOR,MOBILE|NEEDY,0,'!'|CLR(RED),"satyr or nymph","(null)","(null)" },
{ NULL,0,0,0,0,0,0,68,80,25,20,30,4,1,4,8,50,0,100,300,100,-1,-1,COMMON,M_NO_OP,M_MOVE_NORMAL,M_MELEE_NORMAL,M_NO_OP,M_NO_OP,MOBILE|HOSTILE|HUNGRY|ONLYSWIM,0,'c'|CLR(GREEN),"giant crocodile","crocodile hide","ALALBX" },
{ NULL,0,0,0,0,0,0,69,40,30,0,10,4,4,4,12,0,0,120,30,50,POTIONID+5,-1,COMMON,M_TALK_STUPID,M_MOVE_NORMAL,M_MELEE_SLEEP,M_NO_OP,M_NO_OP,MOBILE|HOSTILE|HUNGRY,pow2(FEAR)|pow2(SLEEP),'t'|CLR(BROWN),"torpor beast","a valium gland","AXBX" },
{ NULL,0,0,0,0,0,0,70,40,20,10,15,8,8,4,2,0,0,120,300,0,-1,-1,COMMON,M_TALK_ANIMAL,M_MOVE_LEASH,M_MELEE_NORMAL,M_NO_OP,M_NO_OP,MOBILE|HOSTILE,pow2(FEAR)|pow2(SLEEP),'d'|CLR(BROWN),"doberman death-hound","dead doberman death-hound","LXLXLX" },
{ NULL,0,0,0,0,0,0,71,40,10,10,10,8,8,4,1,0,0,100,0,0,-1,-1,COMMON,M_NO_OP,M_MOVE_SPIRIT,M_MELEE_COLD,M_NO_OP,M_NO_OP,MOBILE|HOSTILE|INTANGIBLE,pow2(FLAME)|pow2(FEAR)|pow2(SLEEP),'F'|CLR(GREY),"astral fuzzy","nothing much","AX" },
{ NULL,0,0,0,0,0,0,72,30,40,40,20,8,8,4,5,0,2,120,0,0,-1,-1,COMMON,M_TALK_SERVANT,M_MOVE_SMART,M_MELEE_NORMAL,M_STRIKE_MISSILE,M_SP_SERVANT,MOBILE,pow2(FEAR)|pow2(SLEEP),'l'|CLR(BLUE),"servant of law","dead servant","L?R?" },
{ NULL,0,0,0,0,0,0,73,40,25,20,10,8,8,4,5,0,2,120,500,0,-1,-1,COMMON,M_TALK_SILENT,M_MOVE_SMART,M_MELEE_NORMAL,M_STRIKE_MISSILE,M_SP_SERVANT,MOBILE,pow2(FEAR)|pow2(SLEEP),'c'|CLR(RED),"servant of chaos","dead servant","AXAXAXAX?" },
{ NULL,0,0,0,0,0,0,74,40,15,0,10,3,0,4,10,0,0,50,1,0,-1,-1,COMMON,M_NO_OP,M_MOVE_NORMAL,M_MELEE_NORMAL,M_NO_OP,M_SP_SWARM,MOBILE|HOSTILE|FLYING,pow2(NORMAL_DAMAGE)|pow2(FEAR)|pow2(SLEEP),'s'|CLR(YELLOW),"swarm","dead swarm members","AX" },
{ NULL,0,0,0,0,0,0,75,40,10,20,10,8,8,4,4,0,2,100,50,0,-1,-1,COMMON,M_TALK_SCREAM,M_MOVE_NORMAL,M_MELEE_SPIRIT,M_STRIKE_SONIC,M_NO_OP,MOBILE|HOSTILE|FLYING,pow2(FEAR)|pow2(SLEEP),'b'|CLR(GREY),"ban sidhe","dead ban sidhe","LX" },
{ NULL,0,0,0,0,0,0,76,50,20,20,20,3,1,4,6,60,3,100,1,0,-1,-1,COMMON,M_TALK_SILENT,M_MOVE_SPIRIT,M_MELEE_NORMAL,M_NO_OP,M_NO_OP,MOBILE|HOSTILE|INTANGIBLE,pow2(NORMAL_DAMAGE),'e'|CLR(GREEN),"etheric grue","dead etheric grue","LHAHLH" },
{ NULL,0,0,0,0,0,0,77,40,20,13,30,8,4,4,5,0,1,100,500,100,-1,-1,COMMON,M_TALK_NINJA,M_MOVE_NORMAL,M_MELEE_POISON,M_STRIKE_MISSILE,M_SP_SURPRISE,MOBILE|HOSTILE|M_INVISIBLE,pow2(POISON)|pow2(SLEEP),'n'|CLR(GREY),"ninja (genin)","dead ninja","A?A?R?R" },
{ NULL,0,0,0,0,0,0,78,50,20,15,40,10,2,5,3,90,4,180,500,50,RINGID+4,-1,COMMON,M_TALK_GREEDY,M_MOVE_NORMAL,M_MELEE_DRAGON,M_STRIKE_FBOLT,M_NO_OP,MOBILE|HOSTILE|HUNGRY|GREEDY|FLYING|EDIBLE,pow2(FLAME),'d'|CLR(LIGHT_RED),"dragonette","dragon steak","AXAXBXBX" },
{ NULL,0,0,0,0,0,0,79,50,15,10,40,10,2,5,12,40,0,150,100,200,STICKID+3,-1,COMMON,M_TALK_STUPID,M_MOVE_FLUTTER,M_MELEE_ELEC,M_STRIKE_LBALL,M_NO_OP,MOBILE|HOSTILE,pow2(ELECTRICITY),'t'|CLR(LIGHT_BLUE),"tesla monster","tesla monster whip","AXAX" },
{ NULL,0,0,0,0,0,0,80,100,20,12,20,4,2,5,4,80,2,150,100,150,RINGID+6,-1,COMMON,M_TALK_GREEDY,M_MOVE_NORMAL,M_MELEE_POISON,M_NO_OP,M_NO_OP,MOBILE|HOSTILE|GREEDY|FLYING|POISONOUS,pow2(FLAME),'W'|CLR(LIGHT_RED),"wyvern","wyvern's sting","AXAXBXBX" },
{ NULL,0,0,0,0,0,0,81,50,15,10,20,10,2,5,2,50,0,250,400,0,-1,-1,COMMON,M_TALK_HUNGRY,M_MOVE_FLUTTER,M_MELEE_NORMAL,M_NO_OP,M_SP_FLUTTER,MOBILE|HOSTILE|HUNGRY|FLYING,pow2(FEAR),'c'|CLR(BROWN),"radeligian cateagle","dead radeligian cateagle","AXAXAXAXAX" },
{ NULL,0,0,0,0,0,0,82,75,20,20,20,5,5,5,3,50,3,200,50,200,STICKID+4,-1,COMMON,M_TALK_EVIL,M_MOVE_SMART,M_MELEE_COLD,M_STRIKE_SNOWBALL,M_SP_DEMON,MOBILE|HOSTILE|POISONOUS,pow2(COLD)|pow2(POISON)|pow2(FEAR)|pow2(SLEEP),'f'|CLR(WHITE),"frost demon","frost demon's heart","A?A?B?B?" },
{ NULL,0,0,0,0,0,0,83,75,20,20,20,5,2,5,6,50,0,200,10,200,CLOAKID+1,-1,COMMON,M_TALK_EVIL,M_MOVE_SPIRIT,M_MELEE_SPIRIT,M_NO_OP,M_NO_OP,MOBILE|HOSTILE|FLYING,pow2(POISON)|pow2(FEAR)|pow2(SLEEP),'S'|CLR(GREY),"spectre","spectre's veil","A?A?A?" },
{ NULL,0,0,0,0,0,0,84,50,12,13,10,5,5,5,5,0,4,205,10,500,-1,SCROLLID+1,COMMON,M_TALK_EVIL,M_MOVE_SCAREDY,M_MELEE_NORMAL,M_NO_OP,M_SP_SPELL,MOBILE|HOSTILE,pow2(FLAME)|pow2(COLD)|pow2(ELECTRICITY),'n'|CLR(RED),"necromancer","dead necromancer","A?B?B?B?" },
{ NULL,0,0,0,0,0,0,85,40,18,18,20,5,5,5,7,50,2,175,2,10,SCROLLID+22,-1,COMMON,M_TALK_EVIL,M_MOVE_SPIRIT,M_MELEE_SPIRIT,M_NO_OP,M_SP_BLACKOUT,MOBILE|HOSTILE|INTANGIBLE,pow2(NORMAL_DAMAGE),'S'|CLR(GREY),"shadow spirit","shadowstuff","ACACAC" },
{ NULL,0,0,0,0,0,0,86,80,22,8,30,3,3,5,12,50,2,275,20,0,-1,-1,COMMON,M_TALK_EVIL,M_MOVE_SMART,M_MELEE_GRAPPLE,M_NO_OP,M_SP_BOG,MOBILE|HOSTILE|ONLYSWIM|POISONOUS,pow2(NORMAL_DAMAGE),'B'|CLR(GREEN),"bog thing","swamp slime","AXAXB?B?" },
{ NULL,0,0,0,0,0,0,87,40,25,0,0,20,3,5,6,0,2,175,20,0,-1,-1,COMMON,M_TALK_SILENT,M_MOVE_SPIRIT,M_MELEE_SPIRIT,M_NO_OP,M_SP_AV,MOBILE|HOSTILE|INTANGIBLE,pow2(NORMAL_DAMAGE)|pow2(FEAR)|pow2(SLEEP),'V'|CLR(GREY),"astral vampire","dead astral vampire","R?R?R?" },
{ NULL,0,0,0,0,0,0,88,100,40,0,60,3,1,5,10,75,0,175,2000,0,-1,-1,COMMON,M_NO_OP,M_MOVE_NORMAL,M_MELEE_FIRE,M_NO_OP,M_SP_LW,MOBILE|HOSTILE|SWIMMING|POISONOUS,pow2(FLAME),'W'|CLR(LIGHT_RED),"lava worm","dead lava worm","AX" },
{ NULL,0,0,0,0,0,0,89,1,0,0,0,30,30,5,20,0,0,100,0,0,-1,-1,COMMON,M_TALK_SILENT,M_MOVE_RANDOM,M_NO_OP,M_NO_OP,M_SP_MB,MOBILE|HOSTILE|INTANGIBLE,0,'m'|CLR(PURPLE),"manaburst","feeling of warmth","BX" },
{ NULL,0,0,0,0,0,0,90,120,25,20,20,6,6,5,4,0,1,150,2000,0,-1,WEAPONID+8,COMMON,M_TALK_EVIL,M_MOVE_SMART,M_MELEE_FIRE,M_MELEE_POISON,M_SP_DEMON,MOBILE|HOSTILE|POISONOUS,pow2(FLAME)|pow2(POISON)|pow2(FEAR)|pow2(SLEEP),'d'|CLR(LIGHT_RED),"outer circle demon","dead outer circle demon","L?R?R?R?" },
{ NULL,0,0,0,0,0,0,91,40,15,10,30,8,8,5,6,0,1,100,20,0,-1,-1,COMMON,M_NO_OP,M_MOVE_SMART,M_MELEE_SPIRIT,M_NO_OP,M_SP_MIRROR,MOBILE|HOSTILE,pow2(FLAME)|pow2(COLD)|pow2(ELECTRICITY),'m'|CLR(GREY),"mirrorshade","some broken glass","AXAXAX" },
{ NULL,0,0,0,0,0,0,92,125,30,0,50,10,2,6,4,100,0,250,1,200,STICKID+7,-1,COMMON,M_TALK_SILENT,M_MOVE_NORMAL,M_MELEE_FIRE,M_STRIKE_FBALL,M_NO_OP,MOBILE|HOSTILE|FLYING,pow2(FLAME)|pow2(POISON)|pow2(ACID)|pow2(SLEEP),'F'|CLRS(WHITE,RED),"fire elemental","essence of fire elemental","AXAXAXRXRX" },
{ NULL,0,0,0,0,0,0,93,125,25,0,20,10,2,6,2,100,0,250,1,200,CLOAKID+2,-1,COMMON,M_TALK_SILENT,M_MOVE_FLUTTER,M_MELEE_NORMAL,M_NO_OP,M_SP_WHIRL,MOBILE|HOSTILE|FLYING|INTANGIBLE,pow2(ELECTRICITY)|pow2(POISON)|pow2(ACID)|pow2(SLEEP),'A'|CLRS(WHITE,BLUE),"air elemental","essence of air elemental","AXAXAXAXBXBX" },
{ NULL,0,0,0,0,0,0,94,100,15,10,30,5,1,6,6,100,0,250,1,200,STICKID+14,-1,COMMON,M_TALK_SILENT,M_MOVE_NORMAL,M_MELEE_NORMAL,M_NO_OP,M_NO_OP,MOBILE|HOSTILE|ONLYSWIM,pow2(COLD)|pow2(SLEEP),'W'|CLRS(WHITE,BLUE),"water elemental","essence of water elemental","AXAXBXBX" },
{ NULL,0,0,0,0,0,0,95,200,20,25,100,5,1,6,15,100,0,250,1,200,CLOAKID+4,-1,COMMON,M_TALK_SILENT,M_MOVE_SPIRIT,M_MELEE_NORMAL,M_NO_OP,M_NO_OP,MOBILE|HOSTILE,pow2(POISON)|pow2(SLEEP),'E'|CLRS(WHITE,BROWN),"earth elemental","essence of earth elemental","AXBX" },
{ NULL,0,0,0,0,0,0,96,100,20,20,50,3,1,6,2,50,1,250,1000,100,-1,-1,COMMON,M_TALK_SILENT,M_MOVE_FLUTTER,M_MELEE_NORMAL,M_NO_OP,M_NO_OP,MOBILE|HOSTILE,pow2(SLEEP),'b'|CLRS(YELLOW,BROWN),"bandersnatch","bandersnatch hide","AXAXAXBX" },
{ NULL,0,0,0,0,0,0,97,100,15,20,50,5,1,6,3,50,5,300,100,1000,-1,-1,COMMON,M_TALK_EVIL,M_MOVE_SMART,M_MELEE_SPIRIT,M_NO_OP,M_SP_SPELL,MOBILE|HOSTILE,pow2(FLAME)|pow2(POISON)|pow2(FEAR)|pow2(SLEEP),'L'|CLRS(BLACK,WHITE),"lich","lich's skeleton","A?A?A?B?B?" },
{ NULL,0,0,0,0,0,0,98,100,20,20,30,5,3,6,5,30,3,300,10,500,-1,WEAPONID+21,COMMON,M_TALK_EVIL,M_MOVE_SMART,M_MELEE_NORMAL,M_NO_OP,M_SP_SPELL,MOBILE|HOSTILE|SWIMMING,pow2(SLEEP),'T'|CLRS(LIGHT_GREEN,BLUE),"triton","dead triton","A?A?A?B?B?" },
{ NULL,0,0,0,0,0,0,99,100,0,20,0,10,3,6,3,0,5,200,10,0,-1,THINGID+2,COMMON,M_TALK_THIEF,M_MOVE_SMART,M_NO_OP,M_NO_OP,M_SP_THIEF,MOBILE|HOSTILE|GREEDY|SWIMMING,0,'@'|CLR(RED),"human","dead master thief","A?B?B?B?" },
{ NULL,0,0,0,0,0,0,100,200,50,50,80,3,1,6,8,0,0,300,100000,0,-1,-1,COMMON,M_TALK_ANIMAL,M_MOVE_NORMAL,M_MELEE_NORMAL,M_NO_OP,M_NO_OP,MOBILE|HOSTILE|SWIMMING,pow2(FEAR)|pow2(SLEEP),'T'|CLRS(GREEN,BROWN),"triceratops","dead triceratops","LX" },
{ NULL,0,0,0,0,0,0,101,100,20,20,20,10,2,6,3,50,4,250,10,0,-1,WEAPONID+5,COMMON,M_TALK_EVIL,M_MOVE_SMART,M_MELEE_NORMAL,M_STRIKE_FBOLT,M_SP_ILLUSION,MOBILE|HOSTILE,pow2(FLAME)|pow2(FEAR)|pow2(SLEEP),'R'|CLRS(YELLOW,WHITE),"rakshasa","dead rakshasa","L?L?R?R?" },
{ NULL,0,0,0,0,0,0,102,100,40,20,30,5,1,6,7,90,4,250,10,500,-1,-1,COMMON,M_TALK_EVIL,M_MOVE_NORMAL,M_MELEE_POISON,M_STRIKE_FBALL,M_SP_DEMON,MOBILE|HOSTILE|SWIMMING,pow2(FLAME)|pow2(POISON)|pow2(FEAR)|pow2(SLEEP),'S'|CLRS(GREEN,RED),"demon serpent","demon serpent's jewel","L?L?" },
{ NULL,0,0,0,0,0,0,103,120,30,20,20,10,10,6,4,0,1,250,10,0,-1,-1,COMMON,M_TALK_SILENT,M_MOVE_SMART,M_MELEE_NORMAL,M_NO_OP,M_SP_ANGEL,MOBILE|FLYING,pow2(FEAR)|pow2(SLEEP),'a'|CLRS(YELLOW,WHITE),"angel","angel's gown","L?R?RX" },
{ NULL,0,0,0,0,0,0,104,100,25,15,40,9,4,6,4,0,1,200,100,100,-1,-1,COMMON,M_TALK_NINJA,M_MOVE_NORMAL,M_MELEE_POISON,M_STRIKE_MISSILE,M_SP_SURPRISE,MOBILE|HOSTILE|M_INVISIBLE,pow2(POISON)|pow2(SLEEP),'n'|CLRS(BLACK,WHITE),"ninja (chunin)","dead ninja","A?A?R?R?R" },
{ NULL,0,0,0,0,0,0,105,300,30,5,120,3,3,7,15,100,0,400,500,50,RINGID+2,-1,COMMON,M_TALK_STUPID,M_MOVE_NORMAL,M_MELEE_NORMAL,M_NO_OP,M_SP_HUGE,MOBILE|HOSTILE|SWIMMING,pow2(ELECTRICITY),'B'|CLRS(BLACK,BROWN),"behemoth","behemoth's gonads","AHBXBX" },
{ NULL,0,0,0,0,0,0,106,250,40,20,20,10,5,7,5,0,0,500,100,2000,-1,WEAPONID+24,COMMON,M_TALK_EVIL,M_MOVE_SPIRIT,M_MELEE_SPIRIT,M_NO_OP,M_SP_SPELL,MOBILE|HOSTILE|FLYING,pow2(COLD)|pow2(POISON)|pow2(FEAR)|pow2(SLEEP),'N'|CLRS(BLACK,WHITE),"nazgul","nazgul's husk","A?A?A?B?B?" },
{ NULL,0,0,0,0,0,0,107,100,100,30,50,10,3,7,2,50,0,400,100,500,RINGID+6,-1,COMMON,M_TALK_SILENT,M_MOVE_NORMAL,M_MELEE_NORMAL,M_NO_OP,M_MOVE_SCAREDY,MOBILE|SWIMMING,pow2(POISON)|pow2(FEAR),'U'|CLRS(BLACK,WHITE),"unicorn","unicorn's horn","ACACB?B?B?B?B?B?B?" },
{ NULL,0,0,0,0,0,0,108,150,30,20,50,10,3,7,3,50,0,400,100,0,-1,-1,COMMON,M_NO_OP,M_MOVE_NORMAL,M_MELEE_DISEASE,M_NO_OP,M_SP_SURPRISE,MOBILE|HOSTILE|HUNGRY|M_INVISIBLE|SWIMMING,pow2(FEAR),'r'|CLRS(BLACK,BROWN),"rodent of unusual size","dead R.O.U.S.","AXAXAX" },
{ NULL,0,0,0,0,0,0,109,100,20,25,30,10,2,7,5,50,3,400,0,0,-1,-1,COMMON,M_NO_OP,M_MOVE_NORMAL,M_MELEE_NORMAL,M_NO_OP,M_SP_ILLUSION,MOBILE|HOSTILE|GREEDY,pow2(OTHER_MAGIC),'F'|CLRS(BLACK,WHITE),"illusory fiend","not much of anything","AXAXAX" },
{ NULL,0,0,0,0,0,0,110,250,40,30,20,10,1,7,5,100,8,500,1500,2000,-1,WEAPONID+34,UNIQUE_MADE,M_TALK_EVIL,M_MOVE_NORMAL,M_MELEE_NORMAL,M_MELEE_COLD,M_SP_WYRM,MOBILE|HOSTILE|SWIMMING,pow2(COLD)|pow2(POISON)|pow2(FEAR)|pow2(SLEEP),'W'|CLRS(GREY,RED),"Great Wyrm","The head of the Great Wyrm","AXAXAX" },
{ NULL,0,0,0,0,0,0,111,150,30,30,20,10,1,7,1,100,8,350,1500,0,-1,WEAPONID+33,COMMON,M_NO_OP,M_MOVE_SMART,M_MELEE_FIRE,M_NO_OP,M_NO_OP,MOBILE|HOSTILE|FLYING,pow2(FLAME)|pow2(POISON)|pow2(FEAR)|pow2(SLEEP),'F'|CLRS(GREY,RED),"flame devil","dead flame devil","A?A?R?R?R?" },
{ NULL,0,0,0,0,0,0,112,150,50,10,20,1,0,7,1,100,4,400,1500,0,-1,-1,COMMON,M_NO_OP,M_NO_OP,M_MELEE_NORMAL,M_NO_OP,M_NO_OP,HOSTILE|HUNGRY,0,OPEN_DOOR,"lurker at the threshold","dead lurker","L?L?L?" },
{ NULL,0,0,0,0,0,0,113,50,30,30,20,10,1,7,4,0,2,450,500,0,-1,-1,COMMON,M_TALK_SILENT,M_MOVE_NORMAL,M_MELEE_SLEEP,M_NO_OP,M_NO_OP,MOBILE|HOSTILE|FLYING,pow2(NORMAL_DAMAGE)|pow2(SLEEP),'S'|CLRS(YELLOW,BROWN),"sandman","mound of sand","AX" },
{ NULL,0,0,0,0,0,0,114,50,40,10,10,10,10,7,2,0,5,350,50,0,-1,-1,COMMON,M_NO_OP,M_MOVE_SMART,M_MELEE_SLEEP,M_NO_OP,M_SP_MIRROR,MOBILE|HOSTILE|FLYING,pow2(OTHER_MAGIC),'m'|CLRS(RED,WHITE),"mirror master","shards of glass","AXAX" },
{ NULL,0,0,0,0,0,0,115,150,30,30,20,10,1,7,4,90,2,450,500,0,-1,-1,COMMON,M_TALK_HUNGRY,M_MOVE_NORMAL,M_MELEE_POISON,M_NO_OP,M_NO_OP,MOBILE|HOSTILE|HUNGRY|FLYING,pow2(POISON)|pow2(FEAR),'G'|CLRS(GREY,GREEN),"elder etheric grue","dead elder etheric grue","AXAXAXL?B?B?" },
{ NULL,0,0,0,0,0,0,116,150,50,40,60,3,3,7,8,90,6,380,500,0,-1,-1,COMMON,M_TALK_HUNGRY,M_MOVE_NORMAL,M_MELEE_POISON,M_NO_OP,M_SP_ACID_CLOUD,MOBILE|HOSTILE|HUNGRY|SWIMMING,pow2(POISON)|pow2(FEAR)|pow2(SLEEP),'S'|CLRS(GREY,GREEN),"loathly serpent","dead loathly serpent","AXAXAXL?B?B?" }, 
{ NULL,0,0,0,0,0,0,117,100,10,30,20,8,3,7,3,20,2,460,500,0,-1,-1,COMMON,M_TALK_EVIL,M_MOVE_SCAREDY,M_MELEE_SPIRIT,M_NO_OP,M_SP_RAISE,MOBILE|HOSTILE,pow2(FEAR),'Z'|CLRS(BLACK,WHITE),"zombie overlord","extremely dead zombie overlord","L?R?R?R?" },
{ NULL,0,0,0,0,0,0,118,50,30,30,2,13,1,7,1,30,0,250,50,0,-1,-1,COMMON,M_TALK_STUPID,M_MOVE_FLUTTER,M_MELEE_NORMAL,M_NO_OP,M_MOVE_FLUTTER,MOBILE|HOSTILE|FLYING,0,'r'|CLRS(GREY,BROWN),"ricochet","dead ricochet","L?" },
{ NULL,0,0,0,0,0,0,119,240,35,30,40,8,8,7,3,0,3,300,3000,0,-1,-1,COMMON,M_TALK_EVIL,M_MOVE_SMART,M_MELEE_FIRE,M_MELEE_SLEEP,M_SP_DEMON,MOBILE|HOSTILE|POISONOUS,pow2(FLAME)|pow2(POISON)|pow2(FEAR)|pow2(SLEEP),'D'|CLRS(GREY,RED),"inner circle demon","dead inner circle demon","L?L?R?R?R?RXRXRX" },
{ NULL,0,0,0,0,0,0,120,1,0,100,0,6,2,8,3,0,0,50,100,0,-1,-1,COMMON,M_TALK_GF,M_MOVE_RANDOM,M_NO_OP,M_NO_OP,M_NO_OP,MOBILE|FLYING,pow2(FLAME)|pow2(COLD)|pow2(SLEEP),'f'|CLRS(YELLOW,WHITE),"fairy","good fairy dust","B?" },
{ NULL,0,0,0,0,0,0,121,100,50,50,20,10,10,8,3,0,0,500,3,0,-1,-1,COMMON,M_TALK_EF,M_MOVE_RANDOM,M_NO_OP,M_NO_OP,M_NO_OP,MOBILE|HOSTILE|FLYING|POISONOUS,pow2(FLAME)|pow2(COLD)|pow2(SLEEP),'f'|CLRS(YELLOW,WHITE),"fairy","evil fairy dust","B?" },
{ NULL,0,0,0,0,0,0,122,500,30,50,100,5,2,8,3,100,0,500,1000,0,-1,WEAPONID+23,COMMON,M_TALK_ROBOT,M_MOVE_SMART,M_MELEE_NORMAL,M_STRIKE_LBALL,M_SP_POISON_CLOUD,MOBILE|HOSTILE,pow2(ELECTRICITY)|pow2(POISON)|pow2(FEAR)|pow2(SLEEP),'A'|CLRS(GREY,WHITE),"automatum major","automatum major components","A?A?R?R?" },
{ NULL,0,0,0,0,0,0,123,500,50,30,75,20,1,8,5,100,7,750,500,1000,ARMORID+12,-1,COMMON,M_TALK_GREEDY,M_MOVE_NORMAL,M_MELEE_DRAGON,M_STRIKE_FBOLT,M_NO_OP,MOBILE|HOSTILE|HUNGRY|GREEDY|FLYING,pow2(FLAME)|pow2(POISON)|pow2(SLEEP),'D'|CLRS(GREY,RED),"dragon","dragon scales","A?A?A?A?B?B?" },
{ NULL,0,0,0,0,0,0,124,500,40,25,100,5,1,8,2,75,2,600,500,1000,WEAPONID+31,-1,COMMON,M_TALK_BURBLE,M_MOVE_FLUTTER,M_MELEE_NORMAL,M_NO_OP,M_NO_OP,MOBILE|HOSTILE|HUNGRY,pow2(POISON)|pow2(SLEEP),'J'|CLRS(BROWN,RED),"jabberwock","jabberwock's head","A?A?A?A?A?" },
{ NULL,0,0,0,0,0,0,125,350,40,40,40,10,10,8,2,25,5,700,100,500,WEAPONID+24,-1,COMMON,M_TALK_EVIL,M_MOVE_SMART,M_MELEE_COLD,M_STRIKE_SNOWBALL,M_SP_DEMON,MOBILE|HOSTILE|HUNGRY,pow2(COLD)|pow2(POISON)|pow2(FEAR)|pow2(SLEEP),'F'|CLRS(LIGHT_BLUE,WHITE),"frost demon lord","frost demon lord's sigil","A?A?A?R?R?R?" },
{ NULL,0,0,0,0,0,0,126,350,35,30,40,10,4,8,2,25,0,700,100,100,-1,-1,COMMON,M_NO_OP,M_MOVE_NORMAL,M_MELEE_NORMAL,M_NO_OP,M_NO_OP,MOBILE|HOSTILE|HUNGRY|ONLYSWIM,pow2(COLD)|pow2(POISON)|pow2(FEAR)|pow2(SLEEP),'T'|CLRS(YELLOW,BLUE),"tigershark","tigershark pelt","AXAXAXAX" },
{ NULL,0,0,0,0,0,0,127,250,40,25,50,10,4,8,3,0,2,800,100,100,-1,-1,COMMON,M_TALK_NINJA,M_MOVE_NORMAL,M_MELEE_POISON,M_STRIKE_MISSILE,M_SP_SURPRISE,MOBILE|HOSTILE|M_INVISIBLE,pow2(POISON)|pow2(SLEEP),'n'|CLRS(BLACK,WHITE),"ninja (jonin)","dead ninja","A?A?R?R?R?R?R?" },
{ NULL,0,0,0,0,0,0,128,250,30,40,30,10,4,8,3,0,3,500,10,75,RINGID+0,-1,COMMON,M_TALK_EVIL,M_MOVE_SPIRIT,M_MELEE_POISON,M_SP_SPELL,M_SP_BLACKOUT,MOBILE|HOSTILE|INTANGIBLE|M_INVISIBLE,pow2(NORMAL_DAMAGE)|pow2(POISON)|pow2(SLEEP),'S'|CLRS(BLACK,WHITE),"shadow slayer","shadow matrix","A?A?B?B?" },
{ NULL,0,0,0,0,0,0,129,250,30,30,30,10,4,8,6,0,3,700,10,75,-1,WEAPONID+13,COMMON,M_TALK_SILENT,M_MOVE_SMART,M_MELEE_NORMAL,M_STRIKE_MISSILE,M_SP_SPELL,MOBILE|HOSTILE,pow2(SLEEP),'@'|CLR(RED),"militant priest","dead militant priest","A?A?A?B?B?" },
{ NULL,0,0,0,0,0,0,130,150,25,40,30,10,4,8,5,0,3,500,10,75,-1,-1,COMMON,M_TALK_SILENT,M_MOVE_SMART,M_MELEE_SLEEP,M_NO_OP,M_NO_OP,MOBILE|HOSTILE|M_INVISIBLE,pow2(SLEEP),'C'|CLRS(GREY,BROWN),"coma beast","dead coma beast","AXAXAXBX" },
{ NULL,0,0,0,0,0,0,131,250,50,40,30,10,10,8,3,0,3,500,10,0,-1,-1,COMMON,M_TALK_SILENT,M_MOVE_SMART,M_MELEE_NORMAL,M_STRIKE_FBOLT,M_SP_ANGEL,MOBILE|FLYING,pow2(FLAME)|pow2(FEAR)|pow2(SLEEP),'A'|CLRS(YELLOW,WHITE),"high angel","high angel's robes","L?R?RXRX" },
{ NULL,0,0,0,0,0,0,132,750,80,50,200,10,2,9,8,90,5,1000,500,2000,-1,WEAPONID+38,COMMON,M_TALK_GREEDY,M_MOVE_NORMAL,M_MELEE_NORMAL,M_STRIKE_MISSILE,M_SP_HUGE,MOBILE|HOSTILE|HUNGRY|GREEDY,pow2(COLD)|pow2(FEAR),'J'|CLRS(GREY,BROWN),"jotun","jotun's head","AHAHB?" },
{ NULL,0,0,0,0,0,0,133,1000,50,30,40,20,2,9,4,40,0,750,100,200,CLOAKID+2,-1,COMMON,M_TALK_SILENT,M_MOVE_FLUTTER,M_MELEE_NORMAL,M_NO_OP,M_NO_OP,MOBILE|HOSTILE|FLYING|M_INVISIBLE,pow2(ELECTRICITY),'i'|CLRS(BLACK,WHITE),"invisible slayer","dead slayer","AXAXAX" },
{ NULL,0,0,0,0,0,0,134,700,50,32,50,5,2,9,3,80,4,1000,100,50,RINGID+6,-1,COMMON,M_TALK_GREEDY,M_MOVE_NORMAL,M_MELEE_POISON,M_NO_OP,M_NO_OP,MOBILE|HOSTILE|GREEDY|FLYING,pow2(FLAME)|pow2(POISON),'W'|CLRS(GREEN,RED),"king wyvern","king wyvern's sting","AXAXAXBXBX" },
{ NULL,0,0,0,0,0,0,135,500,30,50,30,10,2,9,4,50,0,500,40,500,WEAPONID+33,-1,COMMON,M_NO_OP,M_MOVE_RANDOM,M_MELEE_NORMAL,M_NO_OP,M_SP_EXPLODE,MOBILE|HOSTILE|HUNGRY|FLYING|POISONOUS,pow2(FLAME),'d'|CLRS(BLACK,WHITE),"deathstar","deathstar's eye","BX" },
{ NULL,0,0,0,0,0,0,136,250,20,25,25,5,5,9,4,50,4,1500,50,3000,-1,-1,COMMON,M_TALK_EVIL,M_MOVE_SMART,M_MELEE_NORMAL,M_SP_SPELL,M_SP_SPELL,MOBILE,pow2(FLAME)|pow2(COLD)|pow2(ELECTRICITY),'T'|CLRS(YELLOW,WHITE),"high thaumaturgist","dead thaumaturgist","A?B?B?B?B?" },
{ NULL,0,0,0,0,0,0,137,750,70,50,50,10,1,9,2,50,0,1000,1,200,CLOAKID+1,-1,COMMON,M_TALK_EVIL,M_MOVE_SPIRIT,M_MELEE_SPIRIT,M_MELEE_SPIRIT,M_SP_SURPRISE,MOBILE|HOSTILE|FLYING|M_INVISIBLE,pow2(POISON)|pow2(FEAR)|pow2(SLEEP),'V'|CLRS(BLACK,RED),"vampire lord","vampire dust","A?A?A?B?B?B?" },
{ NULL,0,0,0,0,0,0,138,1000,100,50,50,20,20,9,2,100,5,1500,15,3000,-1,WEAPONID+34,COMMON,M_TALK_SILENT,M_MOVE_SMART,M_MELEE_NORMAL,M_MELEE_SLEEP,M_SP_ANGEL,MOBILE|FLYING,pow2(FLAME)|pow2(COLD)|pow2(POISON)|pow2(FEAR)|pow2(SLEEP)|pow2(OTHER_MAGIC),'A'|CLRS(YELLOW,WHITE),"archangel","archangel's diadem","L?R?R?R?R?R?R?R?R?" },
{ NULL,0,0,0,0,0,0,139,800,80,40,80,12,12,9,2,0,5,1200,4500,3000,-1,WEAPONID+24,COMMON,M_TALK_EVIL,M_MOVE_SMART,M_MELEE_NORMAL,M_MELEE_NORMAL,M_SP_DEMON,MOBILE|HOSTILE|FLYING|POISONOUS,pow2(FLAME)|pow2(POISON)|pow2(FEAR)|pow2(SLEEP)|pow2(OTHER_MAGIC),'D'|CLRS(BLACK,RED),"demon prince","dead demon prince","LLLCLHRLRCRHRLRCRH" },
{ NULL,0,0,0,0,0,0,140,100,10,10,1,100,100,100,10,0,0,0,0,1,-1,WEAPONID+39,UNIQUE_MADE,M_TALK_EVIL,M_MOVE_SMART,M_MELEE_DEATH,M_NO_OP,M_SP_DEATH,MOBILE|HOSTILE,pow2(FEAR)|pow2(SLEEP)|pow2(NEGENERGY)|pow2(OTHER_MAGIC),'D'|CLRS(BLACK,WHITE),"Death","No way can you be seeing this!","AX" },
{ NULL,0,0,0,0,0,0,141,1000,0,20,0,3,3,10,5,50,0,10000,1000,250,STICKID+13,-1,UNIQUE_MADE,M_TALK_SILENT,M_MOVE_RANDOM,M_NO_OP,M_NO_OP,M_SP_EATER,MOBILE,pow2(FLAME)|pow2(COLD)|pow2(ELECTRICITY)|pow2(POISON)|pow2(ACID)|pow2(FEAR)|pow2(SLEEP)|pow2(NEGENERGY)|pow2(OTHER_MAGIC)|pow2(THEFT)|pow2(GAZE)|pow2(INFECTION),'E'|CLRS(BLACK,WHITE),"The Eater of Magic","The Heart of the Eater of Magic","B?B?B?B?B?" },
{ NULL,0,0,0,0,0,0,142,500,50,50,50,5,3,10,5,50,0,10000,1000,2000,-1,WEAPONID+34,UNIQUE_MADE,M_TALK_LB,M_MOVE_SMART,M_MELEE_NORMAL,M_NO_OP,M_SP_LAWBRINGER,MOBILE,pow2(NORMAL_DAMAGE),'L'|CLRS(BRIGHT_WHITE,BLUE),"The LawBringer","The LawBringer's Crown","A?A?B?B?B?B?" },
{ NULL,0,0,0,0,0,0,143,2000,100,100,100,10,1,10,1,100,10,10000,1000,2000,ARMORID+12,-1,UNIQUE_MADE,M_TALK_EVIL,M_MOVE_NORMAL,M_MELEE_DRAGON,M_STRIKE_FBOLT,M_SP_DRAGONLORD,MOBILE|HOSTILE|FLYING,pow2(FLAME)|pow2(COLD)|pow2(ELECTRICITY)|pow2(ACID),'D'|CLRS(BRIGHT_WHITE,RED),"The Dragon Lord","The Dragon Lord's Hide","A?A?A?A?A?B?B?B?" },
{ NULL,0,0,0,0,0,0,144,3000,200,100,200,20,20,10,2,0,7,20000,1000,3000,-1,ARTIFACTID+23,UNIQUE_MADE,M_TALK_EVIL,M_MOVE_SPIRIT,M_MELEE_SPIRIT,M_MELEE_NORMAL,M_SP_DEMON,MOBILE|HOSTILE|INTANGIBLE|M_INVISIBLE,pow2(FLAME)|pow2(COLD)|pow2(ELECTRICITY)|pow2(POISON)|pow2(ACID)|pow2(FEAR)|pow2(SLEEP)|pow2(NEGENERGY)|pow2(OTHER_MAGIC)|pow2(THEFT)|pow2(GAZE)|pow2(INFECTION),'D'|CLRS(GREY,RED),"The Demon Emperor","The Demon Emperor's Regalia","L?L?L?L?L?R?R?R?R?R?" },
{ NULL,0,0,0,0,0,0,145,2000,200,100,200,5,1,10,12,0,0,5000,10000,1,-1,ARTIFACTID+4,UNIQUE_MADE,M_TALK_SILENT,M_MOVE_SPIRIT,M_MELEE_NORMAL,M_MELEE_NORMAL,M_SP_DE,MOBILE|INTANGIBLE,pow2(FLAME)|pow2(COLD)|pow2(POISON)|pow2(ACID)|pow2(FEAR)|pow2(SLEEP)|pow2(NEGENERGY)|pow2(OTHER_MAGIC)|pow2(THEFT)|pow2(GAZE)|pow2(INFECTION),'E'|CLRS(BROWN,WHITE),"The Elemental Lord of Earth","some dirt","A?B?B?B?" },
{ NULL,0,0,0,0,0,0,146,1000,100,50,50,20,1,10,1,100,0,5000,0,1,-1,ARTIFACTID+3,UNIQUE_MADE,M_TALK_SILENT,M_MOVE_SPIRIT,M_MELEE_NORMAL,M_STRIKE_LBALL,M_SP_WHIRL,MOBILE|FLYING|INTANGIBLE|M_INVISIBLE,pow2(FLAME)|pow2(COLD)|pow2(ELECTRICITY)|pow2(POISON)|pow2(ACID)|pow2(FEAR)|pow2(SLEEP)|pow2(NEGENERGY)|pow2(THEFT)|pow2(GAZE)|pow2(INFECTION),'A'|CLRS(LIGHT_BLUE,WHITE),"The Elemental Lord of Air","some air","A?A?A?A?A?A?A?A?A?B?" },
{ NULL,0,0,0,0,0,0,147,1500,100,100,100,5,1,10,5,100,0,5000,10,1,-1,ARTIFACTID+1,UNIQUE_MADE,M_TALK_SILENT,M_MOVE_NORMAL,M_MELEE_NORMAL,M_STRIKE_SNOWBALL,M_NO_OP,MOBILE|ONLYSWIM,pow2(COLD)|pow2(ELECTRICITY)|pow2(POISON)|pow2(ACID)|pow2(FEAR)|pow2(SLEEP)|pow2(NEGENERGY)|pow2(OTHER_MAGIC)|pow2(THEFT)|pow2(GAZE)|pow2(INFECTION),'W'|CLRS(BLUE,WHITE),"The Elemental Lord of Water","some water","A?A?A?B?B?B?" },
{ NULL,0,0,0,0,0,0,148,1500,200,100,300,10,1,10,3,100,0,5000,1000,1,-1,ARTIFACTID+2,UNIQUE_MADE,M_TALK_SILENT,M_MOVE_NORMAL,M_MELEE_FIRE,M_STRIKE_FBALL,M_NO_OP,MOBILE,pow2(FLAME)|pow2(ELECTRICITY)|pow2(POISON)|pow2(ACID)|pow2(FEAR)|pow2(SLEEP)|pow2(NEGENERGY)|pow2(OTHER_MAGIC)|pow2(THEFT)|pow2(GAZE)|pow2(INFECTION),'F'|CLRS(LIGHT_RED,WHITE),"The Elemental Lord of Fire","a spark","A?A?A?R?R?R?R?" },
{ NULL,0,0,0,0,0,0,149,1000,200,200,200,20,20,10,2,0,10,10000,10000,1,-1,ARTIFACTID+0,UNIQUE_MADE,M_TALK_EVIL,M_MOVE_SMART,M_MELEE_MASTER,M_STRIKE_MASTER,M_SP_MASTER,MOBILE|FLYING|SWIMMING,pow2(NORMAL_DAMAGE)|pow2(COLD)|pow2(ELECTRICITY)|pow2(POISON)|pow2(ACID)|pow2(FEAR)|pow2(SLEEP)|pow2(NEGENERGY)|pow2(OTHER_MAGIC)|pow2(THEFT)|pow2(GAZE)|pow2(INFECTION),'M'|CLRS(PURPLE,WHITE),"The Elemental Master","A burning mound of bubbling mud","A?A?A?A?R?R?R?R?" }
};
  Monsters = _monsters.data();
}
