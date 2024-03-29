#ifndef __EXTERN_H__
#define __EXTERN_H__
#include "defs.h"
#include <string>
/* omega copyright (c) 1987,1988,1989 by Laurence Raphael Brothers */
/* extern.h -- function declarations */

/* omega.c functions */

int main(int, char *[]);
int game_restore(int, char *[]);
void init_world(void);
void inititem(int);
void initrand(int, int);
void signalexit(int);
void signalsave(int);

/* abyss.c functions */

void load_abyss(void);

/* aux1.c functions */

char *levelname(int);
char *mstatus_string(Monster *);
char *trapid(int);
int getdir(void);
int goberserk(void);
int p_country_moveable(int, int);
int p_moveable(int, int);
int player_on_sanctuary(void);
void calc_melee(void);
int damage_item(Object *);
void describe_player(void);
void fight_monster(Monster *);
void foodcheck(void);
void gain_experience(int);
void p_damage(int, int, std::string);
void p_death(std::string);
void roomcheck(void);
void searchat(int, int);
void setspot(int *, int *);
void showroom(int);
void surrender(Monster *);
void threaten(Monster *);
void tunnelcheck(void);

/* aux2.c functions */

long expval(int);
long item_value(Object *);
long true_item_value(Object *);
char *actionlocstr(char);
int p_immune(int);
int player_hit(int, char, Monster *);
int statmod(int);
void break_weapon(void);
void change_environment(char);
void drop_weapon(void);
void enter_site(Symbol);
void gain_level(void);
void minute_status_check(void);
void moon_check(void);
void movecursor(int *, int *, int, int);
void p_drown(void);
void p_fumble(int);
void p_hit(Monster *, int, int);
void p_win(void);
void player_miss(Monster *, int);
void tacplayer(Monster *);
void tenminute_status_check(void);
void toggle_item_use(int);
void torch_check(void);
void weapon_use(int, Object *, Monster *);

/* aux3.c functions */

char *citysiteid(int);
std::string countryid(Symbol);
char getlocation(void);
int hostilemonstersnear(void);
int magic_resist(int);
int maneuvers(void);
int parsecitysite(void);
int stonecheck(int);
void alert_guards(void);
void countrysearch(void);
void default_maneuvers(void);
void destroy_order(void);
void hourly_check(void);
void indoors_random_event(void);
void outdoors_random_event(void);
void showknownsites(int, int);
void tenminute_check(void);
void terrain_check(int);

/* char.c functions */

long calcmana(void);
FILE *omegarc_check(void);
int competence_check(int);
int fixnpc(int);
void initplayer(void);
void initstats(void);
void omegan_character_stats(void);
void save_omegarc(void);
void user_character_stats(void);

/* city.c functions */

void assign_city_function(int, int);
void load_city(int);
void make_justiciar(int, int);
void make_major_undead(int, int);
void make_minor_undead(int, int);
void mazesite(int, int, int);
void randommazesite(int, int, int);
void repair_jail(void);
void resurrect_guards(void);

/* command1.c functions */

void p_country_process(void);
void p_process(void);

/* command2.c functions */

void pickup(void);
void activate(void);
void bash_item(void);
void bash_location(void);
void callitem(void);
void closedoor(void);
void disarm(void);
void downstairs(void);
void drop(void);
void eat(void);
void floor_inv(void);
void give(void);
void magic(void);
void movepincountry(int, int);
void moveplayer(int, int);
void opendoor(void);
void peruse(void);
void quaff(void);
void rest(void);
void save(int, int);
void search(int *);
void setoptions(void);
void talk(void);
void upstairs(void);
void zapwand(void);

/* command3.c functions */

void abortshadowform(void);
void charid(void);
void city_move(void);
void dismount_steed(void);
void examine(void);
void fire(void);
void frobgamestatus(void);
void help(void);
void hunt(Symbol);
void nap(void);
void pickpocket(void);
void quit(int);
void rename_player(void);
void tacoptions(void);
void tunnel(void);
void vault(void);
void version(void);
void wizard(void);

/* country.c functions */

void load_country(void);
void load_dlair(int, int);
void load_misle(int, int);
void load_werewolf_den(int, int);
void load_speak(int, int);
void load_temple(int, int);
void make_high_priest(int, int, int);
void random_temple_site(int, int, int, int);

/* effect1.c functions */

int random_item(void);
void acquire(int);
void ball(int, int, int, int, int, int);
void bless(int);
void bolt(int, int, int, int, int, int, int);
void enchant(int);
void fball(int, int, int, int, int);
void fbolt(int, int, int, int, int, int);
void heal(int);
void identify(int);
void lball(int, int, int, int, int);
void lbolt(int, int, int, int, int, int);
void manastorm(int, int, int);
void mondet(int);
void nbolt(int, int, int, int, int, int);
void objdet(int);
void snowball(int, int, int, int, int);
void icebolt(int, int, int, int, int, int);
void wish(int);

/* effect2.c functions */

void accuracy(int);
void alert(int);
void augment(int);
void breathe(int);
void displace(int);
void flux(int);
void haste(int);
void i_chaos(Object *);
void i_law(Object *);
void invisible(int);
void knowledge(int);
void recover_stat(int);
void regenerate(int);
void sanctify(int);
void warp(int);

/* effect3.c functions */

int itemlist(int, int);
int monsterlist(void);
void acid_cloud(void);
void aggravate(void);
void amnesia(void);
void annihilate(int);
void apport(int);
void clairvoyance(int);
void cleanse(int);
void cure(int);
void deflection(int);
void disease(int);
void disintegrate(int, int);
void dispel(int);
void disrupt(int, int, int);
void drain(int);
void drain_life(int);
void hellfire(int, int, int);
void hero(int);
void hide(int, int);
void illuminate(int);
void inflict_fear(int, int);
void learnspell(int);
void level_drain(int, char *);
void level_return(void);
void levitate(int);
void p_poison(int);
void p_teleport(int);
void polymorph(int);
void sanctuary(void);
void shadowform(void);
void sleep_monster(int);
void sleep_player(int);
void strategic_teleport(int);
void summon(int, int);
void truesight(int);

/* env.c functions */

void load_arena(void);
void load_circle(int);
void load_court(int);
void make_archmage(int, int);
void make_prime(int, int);

/* etc.c functions */

char *nameprint(void);
char *slotstr(int);
char *wordnum(int);
void hint(void);
void learnclericalspells(int, int);

/* file.c functions */

#ifndef MSDOS
void lock_score_file(void);
void unlock_score_file(void);
#endif
FILE *checkfopen(char *, char *);
int filecheck(void);
int test_file_access(char *, char);
void abyss_file(void);
void adeptfile(void);
void checkhigh(char *, int);
void cityguidefile(void);
void combat_help(void);
void commandlist(void);
void copyfile(char *);
void displayfile(char *);
void displaycryptfile(char *);
void extendlog(char *, int);
void filescanstring(FILE *, char *); /* in util.c if MSDOS defined */
void inv_help(void);
void save_hiscore_npc(int);
void show_license(void);
void showmotd(void);
void showscores(void);
void theologyfile(void);
void user_intro(void);
void wishfile(void);

/* gen1.c functions */

char *roomname(int);
Level *findlevel(Level *, char);
void build_room(int, int, int, char, int);
void build_square_room(int, int, int, char, int);
void cavern_level(void);
void change_level(char, char, char);
void clear_level(Level *);
void corridor_crawl(int *, int *, int, int, int, Symbol, char);
void find_stairs(char, char);
void free_dungeon(void);
void install_specials(void);
void install_traps(void);
void makedoor(int, int);
void sewer_corridor(int, int, int, int, Symbol);
void sewer_level(void);
void straggle_corridor(int, int, int, int, Symbol, char);

/* gen2.c functions */

void make_country_screen(Symbol);
void make_general_map(char *);
void make_forest(void);
void make_jungle(void);
void make_mountains(void);
void make_plains(void);
void make_river(void);
void make_road(void);
void make_stairs(int);
void make_swamp(void);
void maze_corridor(int, int, int, int, char, char);
void maze_level(void);
void room_corridor(int, int, int, int, int);
void room_level(void);

/* guild1.c functions */

void l_arena(void);
void l_castle(void);
void l_merc_guild(void);

/* guild2.c functions */

void l_college(void);
void l_order(void);
void l_sorcerors(void);
void l_thieves_guild(void);

/* house.c functions */

void load_house(int, int);
void make_house_npc(int, int);
void make_mansion_npc(int, int);

/* inv.c functions */

void do_inventory_control(void);
int key_to_index(signed char);
signed char index_to_key(int);
long get_money(long);
char *cashstr(void);
std::string itemid(Object *);
int baditem(int);
int badobject(char);
int cursed(Object *);
int find_and_remove_item(int, int);
int find_item(Object **, int, int);
int get_inventory_slot(void);
int get_item_number(Object *);
int get_to_pack(Object *);
int getitem(Symbol);
int item_useable(Object *, int);
int objequal(Object *, Object *);
int slottable(Object *, int);
int take_from_pack(int, int);
Object *detach_money(void);
Object *split_item(int, Object *);
void add_to_pack(Object *);
void conform_lost_object(Object *);
void conform_lost_objects(int, Object *);
void conform_unused_object(Object *);
void dispose_lost_objects(int, Object *);
void drop_at(int, int, Object *);
void drop_from_slot(int);
void drop_money(void);
void fixpack(void);
void gain_item(Object *);
void give_money(Monster *);
void givemonster(Monster *, Object *);
void inventory_control(void);
void item_inventory(int);
void lose_all_items(void);
void merge_item(int);
void p_drop_at(int, int, int, Object *);
void pack_extra_items(Object *);
void pickup_at(int, int);
void put_to_pack(int);
void setchargestr(Object *, char *);
void setnumstr(Object *, char *);
void setplustr(Object *, char *);
void show_inventory_slot(int, int);
void switch_to_slot(int);
void top_inventory_control(void);

/* item.c functions */

void shuffle(int[], int);
char *bootname(int);
char *cloakname(int);
char *grotname(void);
char *potionname(int);
char *ringname(int);
char *scrollname(int);
char *stickname(int);
int itemblessing(void);
int itemcharge(void);
int itemplus(void);
int twohandedp(int);

/* itemf1.c functions */

void i_accuracy(Object *);
void i_acquire(Object *);
void i_alert(Object *);
void i_augment(Object *);
void i_azoth(Object *);
void i_bless(Object *);
void i_breathing(Object *);
void i_charge(Object *);
void i_clairvoyance(Object *);
void i_corpse(Object *);
void i_cure(Object *);
void i_deflect(Object *);
void i_displace(Object *);
void i_enchant(Object *);
void i_fear_resist(Object *);
void i_flux(Object *);
void i_food(Object *);
void i_heal(Object *);
void i_hero(Object *);
void i_id(Object *);
void i_illuminate(Object *);
void i_immune(Object *);
void i_invisible(Object *);
void i_jane_t(Object *);
void i_key(Object *);
void i_knowledge(Object *);
void i_lembas(Object *);
void i_levitate(Object *);
void i_mondet(Object *);
void i_neutralize_poison(Object *);
void i_no_op(Object *);
void i_nothing(Object *);
void i_objdet(Object *);
void i_pepper_food(Object *);
void i_perm_accuracy(Object *);
void i_perm_agility(Object *);
void i_perm_displace(Object *);
void i_perm_hero(Object *);
void i_perm_illuminate(Object *);
void i_perm_invisible(Object *);
void i_perm_levitate(Object *);
void i_perm_negimmune(Object *);
void i_perm_protection(Object *);
void i_perm_speed(Object *);
void i_perm_truesight(Object *);
void i_pick(Object *);
void i_poison_food(Object *);
void i_pow(Object *);
void i_raise_portcullis(Object *);
void i_regenerate(Object *);
void i_restore(Object *);
void i_sleep_self(Object *);
void i_speed(Object *);
void i_spells(Object *);
void i_stim(Object *);
void i_teleport(Object *);
void i_trap(Object *);
void i_truesight(Object *);
void i_warp(Object *);
void i_wish(Object *);

/* itemf2.c functions */

void i_defend(Object *);
void i_demonblade(Object *);
void i_desecrate(Object *);
void i_lightsabre(Object *);
void i_mace_disrupt(Object *);
void i_normal_armor(Object *);
void i_normal_shield(Object *);
void i_normal_weapon(Object *);
void i_perm_breathing(Object *);
void i_perm_burden(Object *);
void i_perm_deflect(Object *);
void i_perm_energy_resist(Object *);
void i_perm_fear_resist(Object *);
void i_perm_fire_resist(Object *);
void i_perm_gaze_immune(Object *);
void i_perm_knowledge(Object *);
void i_perm_poison_resist(Object *);
void i_perm_regenerate(Object *);
void i_perm_strength(Object *);
void i_victrix(Object *);
void weapon_acidwhip(int, Object *, Monster *);
void weapon_mjolnir(int, Object *, Monster *);
void weapon_arrow(int, Object *, Monster *);
void weapon_bare_hands(int, Monster *);
void weapon_bolt(int, Object *, Monster *);
void weapon_defend(int, Object *, Monster *);
void weapon_demonblade(int, Object *, Monster *);
void weapon_desecrate(int, Object *, Monster *);
void weapon_firestar(int, Object *, Monster *);
void weapon_lightsabre(int, Object *, Monster *);
void weapon_mace_disrupt(int, Object *, Monster *);
void weapon_normal_hit(int, Object *, Monster *);
void weapon_scythe(int, Object *, Monster *);
void weapon_tangle(int, Object *, Monster *);
void weapon_victrix(int, Object *, Monster *);
void weapon_vorpal(int, Object *, Monster *);

/* itemf3.c functions */

int orbcheck(char);
void i_antioch(Object *);
void i_apport(Object *);
void i_crystal(Object *);
void i_death(Object *);
void i_disintegrate(Object *);
void i_dispel(Object *);
void i_disrupt(Object *);
void i_enchantment(Object *);
void i_fear(Object *);
void i_fireball(Object *);
void i_firebolt(Object *);
void i_helm(Object *);
void i_hide(Object *);
void i_juggernaut(Object *);
void i_kolwynia(Object *);
void i_lball(Object *);
void i_lbolt(Object *);
void i_life(Object *);
void i_missile(Object *);
void i_orbair(Object *);
void i_orbdead(Object *);
void i_orbearth(Object *);
void i_orbfire(Object *);
void i_orbmastery(Object *);
void i_orbwater(Object *);
void i_planes(Object *);
void i_polymorph(Object *);
void i_sceptre(Object *);
void i_sleep_other(Object *);
void i_snowball(Object *);
void i_stargem(Object *);
void i_summon(Object *);
void i_symbol(Object *);

/* lev.c functions */

int difficulty(void); /* this function in util.c if MSDOS defined */
Monster *m_create(int, int, int, int);
Monster *make_creature(int);
void make_country_monsters(Symbol);
void make_site_monster(int, int, int);
void make_site_treasure(int, int, int);
void make_specific_treasure(int, int, int);
void populate_level(int);
void stock_level(void);
void wandercheck(void);

/* mmelee.c functions */

char random_loc(void);
int monster_hit(Monster *, char, int);
void m_hit(Monster *, int);
void monster_melee(Monster *, char, int);
void tacmonster(Monster *);
void transcribe_monster_actions(Monster *);

/* mmove.c functions */

void m_confused_move(Monster *);
void m_flutter_move(Monster *);
void m_follow_move(Monster *);
void m_move_animal(Monster *);
void m_normal_move(Monster *);
void m_random_move(Monster *);
void m_scaredy_move(Monster *);
void m_simple_move(Monster *);
void m_smart_move(Monster *);
void m_spirit_move(Monster *);
void m_teleport(Monster *);
void m_vanish(Monster *);
void m_move_leash(Monster *);

/* mon.c functions */

char *mantype(void);
void determine_npc_behavior(Monster *, int, int);
void m_abyss(Monster *);
void m_altar(Monster *);
void m_damage(Monster *, int, int);
void m_death(Monster *);
void m_dropstuff(Monster *);
void m_fire(Monster *);
void m_lava(Monster *);
void m_no_op(Monster *);
void m_pickup(Monster *, Object *);
void m_pulse(Monster *);
void m_trap_abyss(Monster *);
void m_trap_acid(Monster *);
void m_trap_blade(Monster *);
void m_trap_dart(Monster *);
void m_trap_disintegrate(Monster *);
void m_trap_door(Monster *);
void m_trap_fire(Monster *);
void m_trap_manadrain(Monster *);
void m_trap_pit(Monster *);
void m_trap_sleepgas(Monster *);
void m_trap_snare(Monster *);
void m_trap_teleport(Monster *);
void m_water(Monster *);
void make_hiscore_npc(Monster *, int);
void make_log_npc(Monster *);
void monster_action(Monster *, int);
void monster_move(Monster *);
void monster_special(Monster *);
void monster_strike(Monster *);
void monster_talk(Monster *);
void movemonster(Monster *, int, int);
void strengthen_death(Monster *);
void resurrect_wereking(Monster *);

/* move.c functions */

void l_abyss(void);
void l_air_station(void);
void l_arena_exit(void);
void l_balancestone(void);
void l_chaos(void);
void l_chaostone(void);
void l_circle_library(void);
void l_drop_every_portcullis(void);
void l_earth_station(void);
void l_enter_circle(void);
void l_enter_court(void);
void l_escalator(void);
void l_fire(void);
void l_fire_station(void);
void l_hedge(void);
void l_house_exit(void);
void l_lava(void);
void l_lawstone(void);
void l_lift(void);
void l_magic_pool(void);
void l_mindstone(void);
void l_no_op(void);
void l_portcullis_trap(void);
void l_raise_portcullis(void);
void l_rubble(void);
void l_sacrificestone(void);
void l_tactical_exit(void);
void l_temple_warning(void);
void l_throne(void);
void l_tome1(void);
void l_tome2(void);
void l_voice1(void);
void l_voice2(void);
void l_voice3(void);
void l_void(void);
void l_void_station(void);
void l_voidstone(void);
void l_water(void);
void l_water_station(void);
void l_whirlwind(void);
void stationcheck(void);

/* movef.c functions */

void m_movefunction(Monster *, int);
void p_movefunction(int);
void sign_print(int, int, int); /* this function in site1.c if MSDOS defined */

/* mspec.c functions */

void m_aggravate(Monster *);
void m_huge_sounds(Monster *);
void m_illusion(Monster *);
void m_sp_acid_cloud(Monster *);
void m_sp_angel(Monster *);
void m_sp_av(Monster *);
void m_sp_blackout(Monster *);
void m_sp_bogthing(Monster *);
void m_sp_court(Monster *);
void m_sp_demon(Monster *);
void m_sp_demonlover(Monster *);
void m_sp_dragonlord(Monster *);
void m_sp_wereking(Monster *);
void m_sp_eater(Monster *);
void m_sp_escape(Monster *);
void m_sp_explode(Monster *);
void m_sp_ghost(Monster *);
void m_sp_lair(Monster *);
void m_sp_lw(Monster *);
void m_sp_mb(Monster *);
void m_sp_merchant(Monster *);
void m_sp_mirror(Monster *);
void m_sp_mp(Monster *);
void m_sp_ng(Monster *);
void m_sp_poison_cloud(Monster *);
void m_sp_prime(Monster *);
void m_sp_raise(Monster *);
void m_sp_seductor(Monster *);
void m_sp_servant(Monster *);
void m_sp_spell(Monster *);
void m_sp_surprise(Monster *);
void m_sp_swarm(Monster *);
void m_sp_were(Monster *);
void m_sp_whistleblower(Monster *);
void m_summon(Monster *);
void m_thief_f(Monster *);

/* mstrike.c functions */

void m_blind_strike(Monster *);
void m_fireball(Monster *);
void m_firebolt(Monster *);
void m_lball(Monster *);
void m_nbolt(Monster *);
void m_snowball(Monster *);
void m_strike_sonic(Monster *);

/* mtalk.c functions */

void m_talk_animal(Monster *);
void m_talk_archmage(Monster *);
void m_talk_assassin(Monster *);
void m_talk_beg(Monster *);
void m_talk_burble(Monster *);
void m_talk_demonlover(Monster *);
void m_talk_druid(Monster *);
void m_talk_ef(Monster *);
void m_talk_evil(Monster *);
void m_talk_gf(Monster *);
void m_talk_greedy(Monster *);
void m_talk_guard(Monster *);
void m_talk_hint(Monster *);
void m_talk_horse(Monster *);
void m_talk_hungry(Monster *);
void m_talk_hyena(Monster *);
void m_talk_im(Monster *);
void m_talk_man(Monster *);
void m_talk_merchant(Monster *);
void m_talk_mimsy(Monster *);
void m_talk_mp(Monster *);
void m_talk_ninja(Monster *);
void m_talk_parrot(Monster *);
void m_talk_prime(Monster *);
void m_talk_wereking(Monster *);
void m_talk_robot(Monster *);
void m_talk_scream(Monster *);
void m_talk_seductor(Monster *);
void m_talk_servant(Monster *);
void m_talk_silent(Monster *);
void m_talk_slithy(Monster *);
void m_talk_stupid(Monster *);
void m_talk_thief(Monster *);
void m_talk_titter(Monster *);

/* priest.c functions */

int check_sacrilege(int);
void answer_prayer(void);
void hp_req_print(void);
void hp_req_test(void);
int increase_priest_rank(int);
void l_altar(void);
void make_hp(Object *);

/* save.c functions */

int ok_outdated(int);
int restore_game(char *);
void restore_hiscore_npc(Monster *, int);
Object *restore_item(FILE *, int);
Objectlist *restore_itemlist(FILE *, int);
void restore_country(FILE *, int);
void restore_level(FILE *, int);
void restore_monsters(FILE *, Level *, int);
void restore_player(FILE *, int);
int save_game(int, char *);
int save_country(FILE *);
int save_item(FILE *, Object *);
int save_itemlist(FILE *, Objectlist *);
int save_level(FILE *, Level *);
int save_monsters(FILE *, Monsterlist *);
int save_player(FILE *);
void signalsave(int);

/* scr.c functions */

int mcigetc(void);
long parsenum(void);
char *msgscanstring(void);
Symbol getspot(int, int, int);
char lgetc(void);
char menugetc(void);
char mgetc(void);
int ynq(void);
int ynq1(void);
int ynq2(void);
int getnumber(int);
int litroom(int, int);
int move_slot(int, int, int);
int stillonblock(void);
void blankoutspot(int, int);
void blotspot(int, int);
void buffercycle(std::string);
int bufferappend(std::string);
void bufferprint(void);
void checkclear(void);
void clear_if_necessary(void);
void clear_screen(void);
void clearmsg(void);
void clearmsg1(void);
void clearmsg3(void);
void colour_on(void);
void colour_off(void);
void commanderror(void);
void comwinprint(void);
void dataprint(void);
void deathprint(void);
void display_bigwin(void);
void display_death(std::string);
void display_inventory_slot(int, int);
void display_option_slot(int);
void display_options(void);
void display_pack(void);
void display_possessions(void);
void display_quit(void);
void display_win(void);
void dobackspace(void);
void dodrawspot(int, int);
void draw_explosion(Symbol, int, int);
void drawmonsters(int);
void drawomega(void);
void drawplayer(void);
void drawscreen(void);
void drawspot(int, int);
void drawvision(int, int);
void endgraf(void);
void erase_level(void);
void erase_monster(Monster *);
void hide_line(int);
void initgraf(void);
void levelrefresh(void);
void lightspot(int, int);
void locprint(std::string);
void maddch(char);
void menuaddch(char);
void menuclear(void);
void menulongprint(long);
void menunumprint(int);
void menuprint(std::string);
void menuspellprint(int);
void showmenu(void);
void mlongprint(long);
void mnumprint(int);
void morewait(void);
void mprint(std::string);
void nprint1(std::string);
void nprint2(std::string);
void nprint3(std::string);
void phaseprint(void);
void plotchar(Symbol, int, int);
void plotmon(Monster *);
void plotspot(int, int, int);
void print1(std::string);
void print2(std::string);
void print3(std::string);
void putspot(int, int, Symbol);
void redraw(void);
void screencheck(int);
void setlastxy(int, int);
void show_screen(void);
void omshowcursor(int, int);
void showflags(void);
void spreadroomdark(int, int, int);
void spreadroomlight(int, int, int);
void timeprint(void);
void title(void);
void xredraw(void);
void omega_title();

/* site1.c functions */

void buyfromstock(int, int);
void l_alchemist(void);
void l_armorer(void);
void l_bank(void);
void l_casino(void);
void l_club(void);
void l_commandant(void);
void l_crap(void);
void l_diner(void);
void l_dpw(void);
void l_gym(void);
void l_healer(void);
void l_library(void);
void l_pawn_shop(void);
void l_statue_wake(void);
void l_tavern(void);
void statue_random(int, int);
void wake_statue(int, int, int);

/* site2.c functions */

void cureforpay(void);
void gymtrain(int *, int *);
void healforpay(void);
void l_adept(void);
void l_brothel(void);
void l_cartographer(void);
void l_charity(void);
void l_condo(void);
void l_countryside(void);
void l_house(void);
void l_hovel(void);
void l_mansion(void);
void l_oracle(void);
void l_safe(void);
void l_trifid(void);
void l_vault(void);
void pacify_guards(void);
void send_to_jail(void);

/* spell.c functions */

char *spellid(int);
int getspell(void);
int spellparse(void);
void cast_spell(int);
void initspells(void);
void s_accuracy(void);
void s_alert(void);
void s_apport(void);
void s_bless(void);
void s_breathe(void);
void s_clairvoyance(void);
void s_cure(void);
void s_desecrate(void);
void s_disintegrate(void);
void s_dispel(void);
void s_disrupt(void);
void s_drain(void);
void s_enchant(void);
void s_fear(void);
void s_firebolt(void);
void s_haste(void);
void s_heal(void);
void s_hellfire(void);
void s_hero(void);
void s_identify(void);
void s_invisible(void);
void s_knowledge(void);
void s_lball(void);
void s_levitate(void);
void s_missile(void);
void s_mondet(void);
void s_objdet(void);
void s_polymorph(void);
void s_regenerate(void);
void s_restore(void);
void s_return(void);
void s_ritual(void);
void s_sanctify(void);
void s_sanctuary(void);
void s_shadowform(void);
void s_sleep(void);
void s_summon(void);
void s_teleport(void);
void s_truesight(void);
void s_warp(void);
void s_wish(void);
void showknownspells(int, int);

/* time.c functions */

void fix_phantom(Monster *);
void time_clock(int);

/* trap.c functions */

void l_trap_abyss(void);
void l_trap_acid(void);
void l_trap_blade(void);
void l_trap_dart(void);
void l_trap_disintegrate(void);
void l_trap_door(void);
void l_trap_fire(void);
void l_trap_manadrain(void);
void l_trap_pit(void);
void l_trap_siren(void);
void l_trap_sleepgas(void);
void l_trap_snare(void);
void l_trap_teleport(void);

/* util.c functions */

long calc_points(void);
char *getarticle(char *);
char *month(void);
char *ordinal(int);
char *salloc(char *);
char inversedir(int);
void init_perms(void);
int confirmation(void);
char cryptkey(char *);
int day(void);
int distance(int, int, int, int);
int hitp(int, int);
int hour(void);
int inbounds(int, int);
int los_p(int, int, int, int);
int m_unblocked(Monster *, int, int);
int nighttime(void);
int offscreen(int);
int ok_to_free(Level *);
void free_level(Level *);
void free_mons_and_objs(Monsterlist *);
void free_objlist(Objectlist *);
int random_range(int);
int screenmod(int);
int showhour(void);
int showminute(void);
int strmem(char, char *);
int strprefix(char *, char *);
int unblocked(int, int);
int view_los_p(int, int, int, int);
int view_unblocked(int, int);
void calc_weight(void);
void change_to_game_perms(void);
void change_to_user_perms(void);
void do_los(Symbol, int *, int *, int, int);
void do_object_los(Symbol, int *, int *, int, int);
void findspace(int *, int *, int);
void initdirs(void);
#ifdef NO_USLEEP
void usleep(int);
#endif

/* village.c functions */

void assign_village_function(int, int, int);
void load_village(int, int);
void make_food_bin(int, int);
void make_guard(int, int);
void make_horse(int, int);
void make_merchant(int, int);
void make_sheep(int, int);
void special_village_site(int, int, int);
#endif