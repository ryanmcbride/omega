#ifndef __EXTERN_H__
#define __EXTERN_H__
#include "defs.h"
/* omega copyright (c) 1987,1988,1989 by Laurence Raphael Brothers */
/* extern.h -- function declarations */

#ifdef __STDC__
#define ARGS(x) x
#else
#define ARGS(x) ()
#endif

/* omega.c functions */

int main ARGS((int,char *[]));
int game_restore ARGS((int,char *[]));
void init_world ARGS((void));
void inititem ARGS((int));
void initrand ARGS((int, int));
void signalexit ARGS((int));
void signalsave ARGS((int));

/* abyss.c functions */

#ifdef MSDOS_SUPPORTED_ANTIQUE
void check_memory ARGS((void));
void kill_all_levels ARGS((void));
void kill_levels ARGS((char *));
void msdos_init ARGS((void));
Level* msdos_changelevel ARGS((Level*,int,int));
#endif
void load_abyss ARGS((void));

/* aux1.c functions */

char *levelname ARGS((int));
char *mstatus_string ARGS((Monster *));
char *trapid ARGS((int));
int getdir ARGS((void));
int goberserk ARGS((void));
int p_country_moveable ARGS((int,int));
int p_moveable ARGS((int,int));
int player_on_sanctuary ARGS((void));
void calc_melee ARGS((void));
int damage_item ARGS((Object*));
void describe_player ARGS((void));
void fight_monster ARGS((Monster *));
void foodcheck ARGS((void));
void gain_experience ARGS((int));
void p_damage ARGS((int,int,char *));
void p_death ARGS((char *));
void roomcheck ARGS((void));
void searchat ARGS((int,int));
void setspot ARGS((int *,int *));
void showroom ARGS((int));
void surrender ARGS((Monster *));
void threaten ARGS((Monster *));
void tunnelcheck ARGS((void));

/* aux2.c functions */

long expval ARGS((int));
long item_value ARGS((Object*));
long true_item_value ARGS((Object*));
char *actionlocstr ARGS((char));
int p_immune ARGS((int));
int player_hit ARGS((int,char,Monster *));
int statmod ARGS((int));
void break_weapon ARGS((void));
void change_environment ARGS((char));
void drop_weapon ARGS((void));
void enter_site ARGS((Symbol));
void gain_level ARGS((void));
void minute_status_check ARGS((void));
void moon_check ARGS((void));
void movecursor ARGS((int *,int *,int,int));
void p_drown ARGS((void));
void p_fumble ARGS((int));
void p_hit  ARGS((Monster *,int,int));
void p_win ARGS((void));
void player_miss ARGS((Monster *,int));
void tacplayer ARGS((Monster *));
void tenminute_status_check ARGS((void));
void toggle_item_use ARGS((int));
void torch_check ARGS((void));
void weapon_use ARGS((int,Object*,Monster *));

/* aux3.c functions */

char *citysiteid ARGS((int));
std::string countryid ARGS((Symbol));
char getlocation ARGS((void));
int hostilemonstersnear ARGS((void));
int magic_resist ARGS((int));
int maneuvers ARGS((void));
int parsecitysite ARGS((void));
int stonecheck ARGS((int));
void alert_guards ARGS((void));
void countrysearch ARGS((void));
void default_maneuvers ARGS((void));
void destroy_order ARGS((void));
void hourly_check ARGS((void));
void indoors_random_event ARGS((void));
void outdoors_random_event ARGS((void));
void showknownsites ARGS((int, int));
void tenminute_check ARGS((void));
void terrain_check ARGS((int));

/* char.c functions */

long calcmana ARGS((void));
FILE *omegarc_check ARGS((void));
int competence_check ARGS((int));
int fixnpc ARGS((int));
void initplayer ARGS((void));
void initstats ARGS((void));
void omegan_character_stats ARGS((void));
void save_omegarc ARGS((void));
void user_character_stats ARGS((void));

/* city.c functions */

void assign_city_function ARGS((int,int));
void load_city ARGS((int));
void make_justiciar ARGS((int,int));
void make_major_undead ARGS((int,int));
void make_minor_undead ARGS((int,int));
void mazesite ARGS((int,int,int));
void randommazesite ARGS((int,int,int));
void repair_jail ARGS((void));
void resurrect_guards ARGS((void));

/* command1.c functions */

void p_country_process ARGS((void));
void p_process ARGS((void));

/* command2.c functions */

 void pickup ARGS((void));
void activate ARGS((void));
void bash_item ARGS((void));
void bash_location ARGS((void));
void callitem ARGS((void));
void closedoor ARGS((void));
void disarm ARGS((void));
void downstairs ARGS((void));
void drop ARGS((void));
void eat ARGS((void));
void floor_inv ARGS((void));
void give ARGS((void));
void magic ARGS((void));
void movepincountry ARGS((int,int));
void moveplayer ARGS((int,int));
void opendoor ARGS((void));
void peruse ARGS((void));
void quaff ARGS((void));
void rest ARGS((void));
void save ARGS((int, int));
void search ARGS((int *));
void setoptions ARGS((void));
void talk ARGS((void));
void upstairs ARGS((void));
void zapwand ARGS((void));

/* command3.c functions */

void abortshadowform ARGS((void));
void charid ARGS((void));
void city_move ARGS((void));
void dismount_steed ARGS((void));
void examine ARGS((void));
void fire ARGS((void));
void frobgamestatus ARGS((void));
void help ARGS((void));
void hunt ARGS((Symbol));
void nap ARGS((void));
void pickpocket ARGS((void));
void quit ARGS((int));
void rename_player ARGS((void));
void tacoptions ARGS((void));
void tunnel ARGS((void));
void vault ARGS((void));
void version ARGS((void));
void wizard ARGS((void));

/* country.c functions */

void load_country ARGS((void));
void load_dlair ARGS((int,int));
void load_misle ARGS((int,int));
void load_werewolf_den ARGS((int,int));
void load_speak ARGS((int,int));
void load_temple ARGS((int,int));
void make_high_priest ARGS((int,int,int));
void random_temple_site ARGS((int,int,int,int));

/* effect1.c functions */

int random_item ARGS((void));
void acquire ARGS((int));
void ball ARGS((int,int,int,int,int,int));
void bless ARGS((int));
void bolt ARGS((int,int,int,int,int,int,int));
void enchant ARGS((int));
void fball ARGS((int,int,int,int,int));
void fbolt ARGS((int,int,int,int,int,int));
void heal ARGS((int));
void identify ARGS((int));
void lball ARGS((int,int,int,int,int));
void lbolt ARGS((int,int,int,int,int,int));
void manastorm ARGS((int,int,int));
void mondet ARGS((int));
void nbolt ARGS((int,int,int,int,int,int));
void objdet ARGS((int));
void snowball ARGS((int,int,int,int,int));
void icebolt ARGS((int,int,int,int,int,int));
void wish ARGS((int));

/* effect2.c functions */

void accuracy ARGS((int));
void alert ARGS((int));
void augment ARGS((int));
void breathe ARGS((int));
void displace ARGS((int));
void flux ARGS((int));
void haste ARGS((int));
void i_chaos ARGS((Object*));
void i_law ARGS((Object*));
void invisible ARGS((int));
void knowledge ARGS((int));
void recover_stat ARGS((int));
void regenerate ARGS((int));
void sanctify ARGS((int));
void warp ARGS((int));

/* effect3.c functions */

int itemlist ARGS((int,int));
int monsterlist ARGS((void));
void acid_cloud ARGS((void));
void aggravate ARGS((void));
void amnesia ARGS((void));
void annihilate ARGS((int));
void apport ARGS((int));
void clairvoyance ARGS((int));
void cleanse ARGS((int));
void cure ARGS((int));
void deflection ARGS((int));
void disease ARGS((int));
void disintegrate ARGS((int,int));
void dispel ARGS((int));
void disrupt ARGS((int,int,int));
void drain ARGS((int));
void drain_life ARGS((int));
void hellfire ARGS((int,int,int));
void hero ARGS((int));
void hide ARGS((int,int));
void illuminate ARGS((int));
void inflict_fear ARGS((int,int));
void learnspell ARGS((int));
void level_drain ARGS((int,char *));
void level_return ARGS((void));
void levitate ARGS((int));
void p_poison ARGS((int));
void p_teleport ARGS((int));
void polymorph ARGS((int));
void sanctuary ARGS((void));
void shadowform ARGS((void));
void sleep_monster ARGS((int));
void sleep_player ARGS((int));
void strategic_teleport ARGS((int));
void summon ARGS((int,int));
void truesight ARGS((int));

/* env.c functions */

void load_arena ARGS((void));
void load_circle ARGS((int));
void load_court ARGS((int));
void make_archmage ARGS((int,int));
void make_prime ARGS((int,int));

/* etc.c functions */

char *nameprint ARGS((void));
char *slotstr ARGS((int));
char *wordnum ARGS((int));
void hint ARGS((void));
void learnclericalspells ARGS((int,int));

/* file.c functions */

#ifndef MSDOS
void lock_score_file ARGS((void));
void unlock_score_file ARGS((void));
#endif
FILE *checkfopen ARGS((char *,char *));
int filecheck ARGS((void));
int test_file_access ARGS((char *, char));
void abyss_file ARGS((void));
void adeptfile ARGS((void));
void checkhigh ARGS((char *,int));
void cityguidefile ARGS((void));
void combat_help ARGS((void));
void commandlist ARGS((void));
void copyfile ARGS((char *));
void displayfile ARGS((char *));
void displaycryptfile ARGS((char *));
void extendlog ARGS((char *,int));
void filescanstring ARGS((FILE *,char *));	/* in util.c if MSDOS defined */
void inv_help ARGS((void));
void save_hiscore_npc ARGS((int));
void show_license ARGS((void));
void showmotd ARGS((void));
void showscores ARGS((void));
void theologyfile ARGS((void));
void user_intro ARGS((void));
void wishfile ARGS((void));

/* gen1.c functions */

char *roomname ARGS((int));
Level* findlevel ARGS((Level *,char));
void build_room ARGS((int,int,int,char,int));
void build_square_room ARGS((int,int,int,char,int));
void cavern_level ARGS((void));
void change_level ARGS((char,char,char));
void clear_level ARGS((Level *));
void corridor_crawl ARGS((int *,int *,int,int,int,Symbol,char));
void find_stairs ARGS((char,char));
void free_dungeon ARGS((void));
void install_specials ARGS((void));
void install_traps ARGS((void));
void makedoor ARGS((int,int));
void sewer_corridor ARGS((int,int,int,int,Symbol));
void sewer_level ARGS((void));
void straggle_corridor ARGS((int,int,int,int,Symbol,char));

/* gen2.c functions */

void make_country_screen ARGS((Symbol));
void make_general_map ARGS((char *));
void make_forest ARGS((void));
void make_jungle ARGS((void));
void make_mountains ARGS((void));
void make_plains ARGS((void));
void make_river ARGS((void));
void make_road ARGS((void));
void make_stairs ARGS((int));
void make_swamp ARGS((void));
void maze_corridor ARGS((int,int,int,int,char,char));
void maze_level ARGS((void));
void room_corridor ARGS((int,int,int,int,int));
void room_level ARGS((void));

/* guild1.c functions */

void l_arena ARGS((void));
void l_castle ARGS((void));
void l_merc_guild ARGS((void));

/* guild2.c functions */

void l_college ARGS((void));
void l_order ARGS((void));
void l_sorcerors ARGS((void));
void l_thieves_guild ARGS((void));

/* house.c functions */

void load_house ARGS((int,int));
void make_house_npc ARGS((int,int));
void make_mansion_npc ARGS((int,int));

/* inv.c functions */

void do_inventory_control ARGS((void));
int  key_to_index ARGS((signed char));
signed char index_to_key ARGS((int));
long get_money ARGS((long));
char *cashstr ARGS((void));
std::string itemid(Object*);
int baditem ARGS((int));
int badobject ARGS((char));
int cursed ARGS((Object*));
int find_and_remove_item ARGS((int,int));
int find_item ARGS((Object* *,int,int));
int get_inventory_slot ARGS((void));
int get_item_number ARGS((Object*));
int get_to_pack ARGS((Object*));
int getitem ARGS((Symbol));
int item_useable ARGS((Object*,int));
int objequal ARGS((Object *,Object *));
int slottable ARGS((Object*,int));
int take_from_pack ARGS((int,int));
Object* detach_money ARGS((void));
Object* split_item ARGS((int,Object*));
void add_to_pack ARGS((Object*));
void conform_lost_object ARGS((Object*));
void conform_lost_objects ARGS((int,Object*));
void conform_unused_object ARGS((Object*));
void dispose_lost_objects ARGS((int,Object*));
void drop_at ARGS((int,int,Object*));
void drop_from_slot ARGS((int));
void drop_money ARGS((void));
void fixpack ARGS((void));
void gain_item ARGS((Object*));
void give_money ARGS((Monster *));
void givemonster ARGS((Monster *, Object *));
void inventory_control ARGS((void));
void item_inventory ARGS((int));
void lose_all_items ARGS((void));
void merge_item ARGS((int));
void p_drop_at ARGS((int,int,int,Object*));
void pack_extra_items ARGS((Object*));
void pickup_at ARGS((int,int));
void put_to_pack ARGS((int));
void setchargestr ARGS((Object*,char *));
void setnumstr ARGS((Object*,char *));
void setplustr ARGS((Object*,char *));
void show_inventory_slot ARGS((int,int));
void switch_to_slot ARGS((int));
void top_inventory_control ARGS((void));

/* item.c functions */

void shuffle ARGS((int [], int));
char *bootname ARGS((int));
char *cloakname ARGS((int));
char *grotname ARGS((void));
char *potionname ARGS((int));
char *ringname ARGS((int));
char *scrollname ARGS((int));
char *stickname ARGS((int));
int itemblessing ARGS((void));
int itemcharge ARGS((void));
int itemplus ARGS((void));
int twohandedp ARGS((int));
Object* create_object ARGS((int));
void item_use ARGS((Object *));
void make_armor ARGS((Object*, int));
void make_artifact ARGS((Object*, int));
void make_boots ARGS((Object*, int));
void make_cloak ARGS((Object*, int));
void make_corpse ARGS((Object*, Monster *));
void make_food ARGS((Object*, int));
void make_potion ARGS((Object*, int));
void make_ring ARGS((Object*, int));
void make_scroll ARGS((Object*, int));
void make_shield ARGS((Object*, int));
void make_stick ARGS((Object*, int));
void make_thing ARGS((Object*, int));

/* itemf1.c functions */

void i_accuracy ARGS((Object*));
void i_acquire ARGS((Object*));
void i_alert ARGS((Object*));
void i_augment ARGS((Object*));
void i_azoth ARGS((Object*));
void i_bless ARGS((Object*));
void i_breathing ARGS((Object*));
void i_charge ARGS((Object*));
void i_clairvoyance ARGS((Object*));
void i_corpse ARGS((Object*));
void i_cure ARGS((Object*));
void i_deflect ARGS((Object*));
void i_displace ARGS((Object*));
void i_enchant ARGS((Object*));
void i_fear_resist ARGS((Object*));
void i_flux ARGS((Object*));
void i_food ARGS((Object*));
void i_heal ARGS((Object*));
void i_hero ARGS((Object*));
void i_id ARGS((Object*));
void i_illuminate ARGS((Object*));
void i_immune ARGS((Object*));
void i_invisible ARGS((Object*));
void i_jane_t ARGS((Object*));
void i_key ARGS((Object*));
void i_knowledge ARGS((Object*));
void i_lembas ARGS((Object*));
void i_levitate ARGS((Object*));
void i_mondet ARGS((Object*));
void i_neutralize_poison ARGS((Object*));
void i_no_op ARGS((Object*));
void i_nothing ARGS((Object*));
void i_objdet ARGS((Object*));
void i_pepper_food ARGS((Object*));
void i_perm_accuracy ARGS((Object*));
void i_perm_agility ARGS((Object*));
void i_perm_displace ARGS((Object*));
void i_perm_hero ARGS((Object*));
void i_perm_illuminate ARGS((Object*));
void i_perm_invisible ARGS((Object*));
void i_perm_levitate ARGS((Object*));
void i_perm_negimmune ARGS((Object*));
void i_perm_protection ARGS((Object*));
void i_perm_speed ARGS((Object*));
void i_perm_truesight ARGS((Object*));
void i_pick ARGS((Object*));
void i_poison_food ARGS((Object*));
void i_pow ARGS((Object*));
void i_raise_portcullis ARGS((Object*));
void i_regenerate ARGS((Object*));
void i_restore ARGS((Object*));
void i_sleep_self ARGS((Object*));
void i_speed ARGS((Object*));
void i_spells ARGS((Object*));
void i_stim ARGS((Object*));
void i_teleport ARGS((Object*));
void i_trap ARGS((Object*));
void i_truesight ARGS((Object*));
void i_warp ARGS((Object*));
void i_wish ARGS((Object*));

/* itemf2.c functions */

void i_defend ARGS((Object*));
void i_demonblade ARGS((Object*));
void i_desecrate ARGS((Object*));
void i_lightsabre ARGS((Object*));
void i_mace_disrupt ARGS((Object*));
void i_normal_armor ARGS((Object*));
void i_normal_shield ARGS((Object*));
void i_normal_weapon ARGS((Object*));
void i_perm_breathing ARGS((Object*));
void i_perm_burden ARGS((Object*));
void i_perm_deflect ARGS((Object*));
void i_perm_energy_resist ARGS((Object*));
void i_perm_fear_resist ARGS((Object*));
void i_perm_fire_resist ARGS((Object*));
void i_perm_gaze_immune ARGS((Object*));
void i_perm_knowledge ARGS((Object*));
void i_perm_poison_resist ARGS((Object*));
void i_perm_regenerate ARGS((Object*));
void i_perm_strength ARGS((Object*));
void i_victrix ARGS((Object*));
void weapon_acidwhip ARGS((int, Object*, Monster *));
void weapon_mjolnir ARGS((int, Object*, Monster *));
void weapon_arrow ARGS((int, Object*, Monster *));
void weapon_bare_hands ARGS((int, Monster *));
void weapon_bolt ARGS((int, Object*, Monster *));
void weapon_defend ARGS((int, Object*, Monster *));
void weapon_demonblade ARGS((int, Object*, Monster *));
void weapon_desecrate ARGS((int, Object*, Monster *));
void weapon_firestar ARGS((int, Object*, Monster *));
void weapon_lightsabre ARGS((int, Object*, Monster *));
void weapon_mace_disrupt ARGS((int, Object*, Monster *));
void weapon_normal_hit ARGS((int, Object*, Monster *));
void weapon_scythe ARGS((int, Object*, Monster *));
void weapon_tangle ARGS((int, Object*, Monster *));
void weapon_victrix ARGS((int, Object*, Monster *));
void weapon_vorpal ARGS((int, Object*, Monster *));

/* itemf3.c functions */

int orbcheck ARGS((char));
void i_antioch ARGS((Object*));
void i_apport ARGS((Object*));
void i_crystal ARGS((Object*));
void i_death ARGS((Object*));
void i_disintegrate ARGS((Object*));
void i_dispel ARGS((Object*));
void i_disrupt ARGS((Object*));
void i_enchantment ARGS((Object*));
void i_fear ARGS((Object*));
void i_fireball ARGS((Object*));
void i_firebolt ARGS((Object*));
void i_helm ARGS((Object*));
void i_hide ARGS((Object*));
void i_juggernaut ARGS((Object*));
void i_kolwynia ARGS((Object*));
void i_lball ARGS((Object*));
void i_lbolt ARGS((Object*));
void i_life ARGS((Object*));
void i_missile ARGS((Object*));
void i_orbair ARGS((Object*));
void i_orbdead ARGS((Object*));
void i_orbearth ARGS((Object*));
void i_orbfire ARGS((Object*));
void i_orbmastery ARGS((Object*));
void i_orbwater ARGS((Object*));
void i_planes ARGS((Object*));
void i_polymorph ARGS((Object*));
void i_sceptre ARGS((Object*));
void i_sleep_other ARGS((Object*));
void i_snowball ARGS((Object*));
void i_stargem ARGS((Object*));
void i_summon ARGS((Object*));
void i_symbol ARGS((Object*));

/* lev.c functions */

int difficulty ARGS((void));	/* this function in util.c if MSDOS defined */
Monster* m_create ARGS((int,int,int,int));
Monster* make_creature ARGS((int));
void make_country_monsters ARGS((Symbol));
void make_site_monster ARGS((int,int,int));
void make_site_treasure ARGS((int,int,int));
void make_specific_treasure ARGS((int,int,int));
void populate_level ARGS((int));
void stock_level ARGS((void));
void wandercheck ARGS((void));

/* mmelee.c functions */

char random_loc ARGS((void));
int monster_hit ARGS((Monster *,char,int));
void m_hit ARGS((Monster *,int));
void monster_melee ARGS((Monster *,char,int));
void tacmonster ARGS((Monster *));
void transcribe_monster_actions ARGS((Monster *));

/* mmove.c functions */

void m_confused_move ARGS((Monster *));
void m_flutter_move ARGS((Monster *));
void m_follow_move ARGS((Monster *));
void m_move_animal ARGS((Monster *));
void m_normal_move ARGS((Monster *));
void m_random_move ARGS((Monster *));
void m_scaredy_move ARGS((Monster *));
void m_simple_move ARGS((Monster *));
void m_smart_move ARGS((Monster *));
void m_spirit_move ARGS((Monster *));
void m_teleport ARGS((Monster *));
void m_vanish ARGS((Monster *));
void m_move_leash ARGS((Monster *));

/* mon.c functions */

char *mantype ARGS((void));
void determine_npc_behavior ARGS((Monster*,int,int));
void m_abyss ARGS((Monster *));
void m_altar ARGS((Monster *));
void m_damage ARGS((Monster *,int,int));
void m_death ARGS((Monster *));
void m_dropstuff ARGS((Monster *));
void m_fire ARGS((Monster *));
void m_lava ARGS((Monster *));
void m_no_op ARGS((Monster *));
void m_pickup ARGS((Monster *,Object *));
void m_pulse ARGS((Monster *));
void m_trap_abyss ARGS((Monster *));
void m_trap_acid ARGS((Monster *));
void m_trap_blade ARGS((Monster *));
void m_trap_dart ARGS((Monster *));
void m_trap_disintegrate ARGS((Monster *));
void m_trap_door ARGS((Monster *));
void m_trap_fire ARGS((Monster *));
void m_trap_manadrain ARGS((Monster *));
void m_trap_pit ARGS((Monster *));
void m_trap_sleepgas ARGS((Monster *));
void m_trap_snare ARGS((Monster *));
void m_trap_teleport ARGS((Monster *));
void m_water ARGS((Monster *));
void make_hiscore_npc ARGS((Monster*,int));
void make_log_npc ARGS((Monster *));
void monster_action ARGS((Monster *,int));
void monster_move ARGS((Monster *));
void monster_special ARGS((Monster *));
void monster_strike ARGS((Monster *));
void monster_talk ARGS((Monster *));
void movemonster ARGS((Monster *,int,int));
void strengthen_death ARGS((Monster *));
void resurrect_wereking(Monster*);

/* move.c functions */

void l_abyss ARGS((void));
void l_air_station ARGS((void));
void l_arena_exit ARGS((void));
void l_balancestone ARGS((void));
void l_chaos ARGS((void));
void l_chaostone ARGS((void));
void l_circle_library ARGS((void));
void l_drop_every_portcullis ARGS((void));
void l_earth_station ARGS((void));
void l_enter_circle ARGS((void));
void l_enter_court ARGS((void));
void l_escalator ARGS((void));
void l_fire ARGS((void));
void l_fire_station ARGS((void));
void l_hedge ARGS((void));
void l_house_exit ARGS((void));
void l_lava ARGS((void));
void l_lawstone ARGS((void));
void l_lift ARGS((void));
void l_magic_pool ARGS((void));
void l_mindstone ARGS((void));
void l_no_op ARGS((void));
void l_portcullis_trap ARGS((void));
void l_raise_portcullis ARGS((void));
void l_rubble ARGS((void));
void l_sacrificestone ARGS((void));
void l_tactical_exit ARGS((void));
void l_temple_warning ARGS((void));
void l_throne ARGS((void));
void l_tome1 ARGS((void));
void l_tome2 ARGS((void));
void l_voice1 ARGS((void));
void l_voice2 ARGS((void));
void l_voice3 ARGS((void));
void l_void ARGS((void));
void l_void_station ARGS((void));
void l_voidstone ARGS((void));
void l_water ARGS((void));
void l_water_station ARGS((void));
void l_whirlwind ARGS((void));
void stationcheck ARGS((void));

/* movef.c functions */

void m_movefunction ARGS((Monster *,int));
void p_movefunction ARGS((int));
void sign_print ARGS((int,int,int));	/* this function in site1.c if MSDOS defined */

/* mspec.c functions */

void m_aggravate ARGS((Monster *));
void m_huge_sounds ARGS((Monster *));
void m_illusion ARGS((Monster *));
void m_sp_acid_cloud ARGS((Monster *));
void m_sp_angel ARGS((Monster *));
void m_sp_av ARGS((Monster *));
void m_sp_blackout ARGS((Monster *));
void m_sp_bogthing ARGS((Monster *));
void m_sp_court ARGS((Monster *));
void m_sp_demon ARGS((Monster *));
void m_sp_demonlover ARGS((Monster *));
void m_sp_dragonlord ARGS((Monster *));
void m_sp_wereking ARGS((Monster *));
void m_sp_eater ARGS((Monster *));
void m_sp_escape ARGS((Monster *));
void m_sp_explode ARGS((Monster *));
void m_sp_ghost ARGS((Monster *));
void m_sp_lair ARGS((Monster *));
void m_sp_lw ARGS((Monster *));
void m_sp_mb ARGS((Monster *));
void m_sp_merchant ARGS((Monster *));
void m_sp_mirror ARGS((Monster *));
void m_sp_mp ARGS((Monster *));
void m_sp_ng ARGS((Monster *));
void m_sp_poison_cloud ARGS((Monster *));
void m_sp_prime ARGS((Monster *));
void m_sp_raise ARGS((Monster *));
void m_sp_seductor ARGS((Monster *));
void m_sp_servant ARGS((Monster *));
void m_sp_spell ARGS((Monster *));
void m_sp_surprise ARGS((Monster *));
void m_sp_swarm ARGS((Monster *));
void m_sp_were ARGS((Monster *));
void m_sp_whistleblower ARGS((Monster *));
void m_summon ARGS((Monster *));
void m_thief_f ARGS((Monster *));

/* mstrike.c functions */

void m_blind_strike ARGS((Monster *));
void m_fireball ARGS((Monster *));
void m_firebolt ARGS((Monster *));
void m_lball ARGS((Monster *));
void m_nbolt ARGS((Monster *));
void m_snowball ARGS((Monster *));
void m_strike_sonic ARGS((Monster *));

/* mtalk.c functions */

void m_talk_animal ARGS((Monster *));
void m_talk_archmage ARGS((Monster *));
void m_talk_assassin ARGS((Monster *));
void m_talk_beg ARGS((Monster *));
void m_talk_burble ARGS((Monster *));
void m_talk_demonlover ARGS((Monster *));
void m_talk_druid ARGS((Monster *));
void m_talk_ef ARGS((Monster *));
void m_talk_evil ARGS((Monster *));
void m_talk_gf ARGS((Monster *));
void m_talk_greedy ARGS((Monster *));
void m_talk_guard ARGS((Monster *));
void m_talk_hint ARGS((Monster *));
void m_talk_horse ARGS((Monster *));
void m_talk_hungry ARGS((Monster *));
void m_talk_hyena ARGS((Monster *));
void m_talk_im ARGS((Monster *));
void m_talk_man ARGS((Monster *));
void m_talk_merchant ARGS((Monster *));
void m_talk_mimsy ARGS((Monster *));
void m_talk_mp ARGS((Monster *));
void m_talk_ninja ARGS((Monster *));
void m_talk_parrot ARGS((Monster *));
void m_talk_prime ARGS((Monster *));
void m_talk_wereking ARGS((Monster *));
void m_talk_robot ARGS((Monster *));
void m_talk_scream ARGS((Monster *));
void m_talk_seductor ARGS((Monster *));
void m_talk_servant ARGS((Monster *));
void m_talk_silent ARGS((Monster *));
void m_talk_slithy ARGS((Monster *));
void m_talk_stupid ARGS((Monster *));
void m_talk_thief ARGS((Monster *));
void m_talk_titter ARGS((Monster *));

/* priest.c functions */

int check_sacrilege ARGS((int));
void answer_prayer ARGS((void));
void hp_req_print ARGS((void));
void hp_req_test ARGS((void));
int increase_priest_rank ARGS((int));
void l_altar ARGS((void));
void make_hp ARGS((Object*));

/* save.c functions */

int ok_outdated ARGS((int));
int restore_game ARGS((char *));
void restore_hiscore_npc ARGS((Monster*, int));
Object* restore_item ARGS((FILE *, int));
Objectlist* restore_itemlist ARGS((FILE *, int));
void restore_country ARGS((FILE *, int));
void restore_level ARGS((FILE *, int));
void restore_monsters ARGS((FILE *,Level*, int));
void restore_player ARGS((FILE *, int));
int save_game ARGS((int,char *));
int save_country ARGS((FILE *));
int save_item ARGS((FILE *,Object*));
int save_itemlist ARGS((FILE *,Objectlist*));
int save_level ARGS((FILE *,Level*));
int save_monsters ARGS((FILE *,Monsterlist*));
int save_player ARGS((FILE *));
void signalsave ARGS((int));

/* scr.c functions */

int mcigetc ARGS((void));
long parsenum ARGS((void));
char *msgscanstring ARGS((void));
Symbol getspot ARGS((int,int,int));
char lgetc ARGS((void));
char menugetc ARGS((void));
char mgetc ARGS((void));
int ynq ARGS((void));
int ynq1 ARGS((void));
int ynq2 ARGS((void));
int getnumber ARGS((int));
int litroom ARGS((int,int));
int move_slot ARGS((int,int,int));
int stillonblock ARGS((void));
void blankoutspot ARGS((int,int));
void blotspot ARGS((int,int));
void buffercycle(std::string);
int bufferappend(std::string);
void bufferprint ARGS((void));
void checkclear ARGS((void));
void clear_if_necessary ARGS((void));
void clear_screen ARGS((void));
void clearmsg ARGS((void));
void clearmsg1 ARGS((void));
void clearmsg3 ARGS((void));
void colour_on ARGS((void));
void colour_off ARGS((void));
void commanderror ARGS((void));
void comwinprint ARGS((void));
void dataprint ARGS((void));
void deathprint ARGS((void));
void display_bigwin ARGS((void));
void display_death(std::string);
void display_inventory_slot ARGS((int,int));
void display_option_slot ARGS((int));
void display_options ARGS((void));
void display_pack ARGS((void));
void display_possessions ARGS((void));
void display_quit ARGS((void));
void display_win ARGS((void));
void dobackspace ARGS((void));
void dodrawspot ARGS((int,int));
void draw_explosion ARGS((Symbol,int,int));
void drawmonsters ARGS((int));
void drawomega ARGS((void));
void drawplayer ARGS((void));
void drawscreen ARGS((void));
void drawspot ARGS((int,int));
void drawvision ARGS((int,int));
void endgraf ARGS((void));
void erase_level ARGS((void));
void erase_monster ARGS((Monster *));
void hide_line ARGS((int));
void initgraf ARGS((void));
void levelrefresh ARGS((void));
void lightspot ARGS((int,int));
void locprint(std::string);
void maddch ARGS((char));
void menuaddch ARGS((char));
void menuclear ARGS((void));
void menulongprint ARGS((long));
void menunumprint ARGS((int));
void menuprint(std::string);
void menuspellprint ARGS((int));
void showmenu ARGS((void));
void mlongprint ARGS((long));
void mnumprint ARGS((int));
void morewait ARGS((void));
void mprint(std::string);
void nprint1(std::string);
void nprint2(std::string);
void nprint3(std::string);
void phaseprint ARGS((void));
void plotchar ARGS((Symbol,int,int));
void plotmon ARGS((Monster *));
void plotspot ARGS((int,int,int));
void print1(std::string);
void print2(std::string);
void print3(std::string);
void putspot ARGS((int,int,Symbol));
void redraw ARGS((void));
void screencheck ARGS((int));
void setlastxy ARGS((int, int));
void show_screen ARGS((void));
void omshowcursor ARGS((int,int));
void showflags ARGS((void));
void spreadroomdark ARGS((int,int,int));
void spreadroomlight ARGS((int,int,int));
void timeprint ARGS((void));
void title ARGS((void));
void xredraw ARGS((void));
void omega_title();

/* site1.c functions */

void buyfromstock ARGS((int,int));
void l_alchemist ARGS((void));
void l_armorer ARGS((void));
void l_bank ARGS((void));
void l_casino ARGS((void));
void l_club ARGS((void));
void l_commandant ARGS((void));
void l_crap ARGS((void));
void l_diner ARGS((void));
void l_dpw ARGS((void));
void l_gym ARGS((void));
void l_healer ARGS((void));
void l_library ARGS((void));
void l_pawn_shop ARGS((void));
void l_statue_wake ARGS((void));
void l_tavern ARGS((void));
void statue_random ARGS((int,int));
void wake_statue ARGS((int,int,int));

/* site2.c functions */

void cureforpay ARGS((void));
void gymtrain ARGS((int *,int *));
void healforpay ARGS((void));
void l_adept ARGS((void));
void l_brothel ARGS((void));
void l_cartographer ARGS((void));
void l_charity ARGS((void));
void l_condo ARGS((void));
void l_countryside ARGS((void));
void l_house ARGS((void));
void l_hovel ARGS((void));
void l_mansion ARGS((void));
void l_oracle ARGS((void));
void l_safe ARGS((void));
void l_trifid ARGS((void));
void l_vault ARGS((void));
void pacify_guards ARGS((void));
void send_to_jail ARGS((void));

/* spell.c functions */

char *spellid ARGS((int));
int getspell ARGS((void));
int spellparse ARGS((void));
void cast_spell ARGS((int));
void initspells ARGS((void));
void s_accuracy ARGS((void));
void s_alert ARGS((void));
void s_apport ARGS((void));
void s_bless ARGS((void));
void s_breathe ARGS((void));
void s_clairvoyance ARGS((void));
void s_cure ARGS((void));
void s_desecrate ARGS((void));
void s_disintegrate ARGS((void));
void s_dispel ARGS((void));
void s_disrupt ARGS((void));
void s_drain ARGS((void));
void s_enchant ARGS((void));
void s_fear ARGS((void));
void s_firebolt ARGS((void));
void s_haste ARGS((void));
void s_heal ARGS((void));
void s_hellfire ARGS((void));
void s_hero ARGS((void));
void s_identify ARGS((void));
void s_invisible ARGS((void));
void s_knowledge ARGS((void));
void s_lball ARGS((void));
void s_levitate ARGS((void));
void s_missile ARGS((void));
void s_mondet ARGS((void));
void s_objdet ARGS((void));
void s_polymorph ARGS((void));
void s_regenerate ARGS((void));
void s_restore ARGS((void));
void s_return ARGS((void));
void s_ritual ARGS((void));
void s_sanctify ARGS((void));
void s_sanctuary ARGS((void));
void s_shadowform ARGS((void));
void s_sleep ARGS((void));
void s_summon ARGS((void));
void s_teleport ARGS((void));
void s_truesight ARGS((void));
void s_warp ARGS((void));
void s_wish ARGS((void));
void showknownspells ARGS((int, int));

/* time.c functions */

void fix_phantom ARGS((Monster *));
void time_clock ARGS((int));

/* trap.c functions */

void l_trap_abyss ARGS((void));
void l_trap_acid ARGS((void));
void l_trap_blade ARGS((void));
void l_trap_dart ARGS((void));
void l_trap_disintegrate ARGS((void));
void l_trap_door ARGS((void));
void l_trap_fire ARGS((void));
void l_trap_manadrain ARGS((void));
void l_trap_pit ARGS((void));
void l_trap_siren ARGS((void));
void l_trap_sleepgas ARGS((void));
void l_trap_snare ARGS((void));
void l_trap_teleport ARGS((void));

/* util.c functions */

long calc_points ARGS((void));
char *getarticle ARGS((char *));
char *month ARGS((void));
char *ordinal ARGS((int));
char *salloc ARGS((char *));
char inversedir ARGS((int));
void init_perms ARGS((void));
int confirmation ARGS((void));
char cryptkey ARGS((char*));
int day ARGS((void));
int distance ARGS((int,int,int,int));
int hitp ARGS((int,int));
int hour ARGS((void));
int inbounds ARGS((int,int));
int los_p ARGS((int,int,int,int));
int m_unblocked ARGS((Monster *,int,int));
int nighttime ARGS((void));
int offscreen ARGS((int));
int ok_to_free ARGS((Level*));
void free_level ARGS((Level*));
void free_mons_and_objs ARGS((Monsterlist*));
void free_objlist ARGS((Objectlist*));
int random_range ARGS((int));
int screenmod ARGS((int));
int showhour ARGS((void));
int showminute ARGS((void));
int strmem ARGS((char,char *));
int strprefix ARGS((char *,char *));
int unblocked ARGS((int,int));
int view_los_p ARGS((int,int,int,int));
int view_unblocked ARGS((int,int));
void calc_weight ARGS((void));
void change_to_game_perms ARGS((void));
void change_to_user_perms ARGS((void));
void do_los ARGS((Symbol,int *,int *,int,int));
void do_object_los(Symbol,int *,int *,int,int);
void findspace ARGS((int *,int *,int));
void initdirs ARGS((void));
#ifdef NO_USLEEP
void usleep ARGS((int));
#endif

/* village.c functions */

void assign_village_function ARGS((int,int,int));
void load_village ARGS((int, int));
void make_food_bin ARGS((int,int));
void make_guard ARGS((int,int));
void make_horse ARGS((int,int));
void make_merchant ARGS((int,int));
void make_sheep ARGS((int,int));
void special_village_site ARGS((int,int,int));
#endif