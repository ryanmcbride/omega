/* omega copyright (C) by Laurence Raphael Brothers, 1987,1988,1989 */
/* movef.c */
/* the movefunctions switch functions, for player and monster*/

#include "glob.h"
#include <map>
#include <functional>

void p_movefunction(int movef)
{
  /* loc functs above traps should be activated whether levitating or not */
  drawvision(player.x, player.y);
  sign_print(player.x, player.y, FALSE);
  if (player.status[SHADOWFORM]){
    static std::map<int,std::function<void()>> move_map = { /* player in shadow form is unable to do most things */
    {L_CHAOS,l_chaos},
    {L_ABYSS,l_abyss},
    {L_ARENA_EXIT,l_arena_exit},
    {L_ENTER_COURT,l_enter_court},
    {L_ESCALATOR,l_escalator},
    {L_COLLEGE,l_college},
    {L_SORCERORS,l_sorcerors},
    {L_ALTAR,l_altar},
    {L_TACTICAL_EXIT,l_tactical_exit},
    {L_HOUSE_EXIT,l_house_exit},
    {L_HOUSE,l_house},
    {L_HOVEL,l_hovel},
    {L_MANSION,l_mansion},
    {L_COUNTRYSIDE,l_countryside},
    {L_ORACLE,l_oracle},
    {L_TEMPLE_WARNING,l_temple_warning},
    {L_ENTER_CIRCLE,l_enter_circle},
    {L_CIRCLE_LIBRARY,l_circle_library},
    {L_TOME1,l_tome1},
    {L_TOME2,l_tome2},
    {L_ADEPT,l_adept},
    {L_VOICE1,l_voice1},
    {L_VOICE2,l_voice2},
    {L_VOICE3,l_voice3},
    {L_VOID,l_void},
    {L_FIRE_STATION,l_fire_station},
    {L_EARTH_STATION,l_earth_station},
    {L_WATER_STATION,l_water_station},
    {L_AIR_STATION,l_air_station},
    {L_VOID_STATION,l_void_station}};
    auto move = move_map[movef];
      if(move != nullptr){
        move();      
      }
  } else if ((!player.status[LEVITATING]) ||
           gamestatusp(MOUNTED) ||
           (Cmd == '@') || /* @ command activates all effects under player */
           (movef < LEVITATION_AVOIDANCE))
  {
    static std::map<int,std::function<void()>> move_map = {
    {L_NO_OP,l_no_op},
    {L_HEDGE,l_hedge},
    {L_WATER,l_water},
    {L_LIFT,l_lift},
    {L_LAVA,l_lava},
    {L_FIRE,l_fire},
    {L_WHIRLWIND,l_whirlwind},
    {L_RUBBLE,l_rubble},
    {L_MAGIC_POOL,l_magic_pool},
    {L_CHAOS,l_chaos},
    {L_ABYSS,l_abyss},

    {L_PORTCULLIS_TRAP,l_portcullis_trap},
    {L_RAISE_PORTCULLIS,l_raise_portcullis},
    {L_DROP_EVERY_PORTCULLIS,l_drop_every_portcullis},
    {L_ARENA_EXIT,l_arena_exit},
    {L_TRIFID,l_trifid},
    {L_ENTER_COURT,l_enter_court},
    {L_ESCALATOR,l_escalator},
    {L_THRONE,l_throne},

    {L_TRAP_DART,l_trap_dart},
    {L_TRAP_SIREN,l_trap_siren},
    {L_TRAP_PIT,l_trap_pit},
    {L_TRAP_DOOR,l_trap_door},
    {L_TRAP_SNARE,l_trap_snare},
    {L_TRAP_BLADE,l_trap_blade},
    {L_TRAP_FIRE,l_trap_fire},
    {L_TRAP_TELEPORT,l_trap_teleport},
    {L_TRAP_DISINTEGRATE,l_trap_disintegrate},
    {L_TRAP_SLEEP_GAS,l_trap_sleepgas},
    {L_TRAP_MANADRAIN,l_trap_manadrain},
    {L_TRAP_ACID,l_trap_acid},
    {L_TRAP_ABYSS,l_trap_abyss},

      /*door functions */
    {L_BANK,l_bank},
    {L_ARMORER,l_armorer},
    {L_CLUB,l_club},
    {L_GYM,l_gym},
    {L_BROTHEL,l_brothel},
    {L_THIEVES_GUILD,l_thieves_guild},
    {L_COLLEGE,l_college},
    {L_HEALER,l_healer},
    {L_STATUE_WAKE,l_statue_wake},
    {L_CASINO,l_casino},
    {L_COMMANDANT,l_commandant},
    {L_DINER,l_diner},
    {L_CRAP,l_crap},
    {L_TAVERN,l_tavern},
    {L_MERC_GUILD,l_merc_guild},
    {L_ALCHEMIST,l_alchemist},
    {L_SORCERORS,l_sorcerors},
    {L_CASTLE,l_castle},
    {L_ARENA,l_arena},
    {L_VAULT,l_vault},
    {L_DPW,l_dpw},
    {L_LIBRARY,l_library},
    {L_PAWN_SHOP,l_pawn_shop},
    {L_CONDO,l_condo},
    {L_ALTAR,l_altar},
    {L_TACTICAL_EXIT,l_tactical_exit},
    {L_HOUSE_EXIT,l_house_exit},
    {L_SAFE,l_safe},
    {L_HOUSE,l_house},
    {L_HOVEL,l_hovel},
    {L_MANSION,l_mansion},
    {L_COUNTRYSIDE,l_countryside},
    {L_ORACLE,l_oracle},
    {L_ORDER,l_order},
    {L_CARTOGRAPHER,l_cartographer},

    {L_TEMPLE_WARNING,l_temple_warning},
    {L_ENTER_CIRCLE,l_enter_circle},
    {L_CIRCLE_LIBRARY,l_circle_library},
    {L_TOME1,l_tome1},
    {L_TOME2,l_tome2},

    {L_CHARITY,l_charity},

    {L_CHAOSTONE,l_chaostone},
    {L_VOIDSTONE,l_voidstone},
    {L_BALANCESTONE,l_balancestone},
    {L_LAWSTONE,l_lawstone},
    {L_SACRIFICESTONE,l_sacrificestone},
    {L_MINDSTONE,l_mindstone},

    /* challenge functions */
    {L_ADEPT,l_adept},
    {L_VOICE1,l_voice1},
    {L_VOICE2,l_voice2},
    {L_VOICE3,l_voice3},
    {L_VOID,l_void},
    {L_FIRE_STATION,l_fire_station},
    {L_EARTH_STATION,l_earth_station},
    {L_WATER_STATION,l_water_station},
    {L_AIR_STATION,l_air_station},
    {L_VOID_STATION,l_void_station}};
      auto move = move_map[movef];
      if(move != nullptr){
        move();      
      }
    if (movef != L_NO_OP)
    {
      resetgamestatus(FAST_MOVE);
      dataprint();
    }
  }
}

/* execute some move function for a monster */
void m_movefunction(Monster* m, int movef)
{
  /* loc functs above traps should be activated whether levitating or not */
  if (!m_statusp(m, FLYING) && !m_statusp(m, INTANGIBLE)) {
    static std::map<int,std::function<void(Monster*)>> move_map = {
    /* miscellaneous */
    {L_NO_OP,m_no_op},
    {L_WATER,m_water},
    {L_LAVA,m_lava},
    {L_FIRE,m_fire},
    {L_MAGIC_POOL,m_water},
    {L_ABYSS,m_abyss},

    {L_TRAP_DART,m_trap_dart},
    {L_TRAP_PIT,m_trap_pit},
    {L_TRAP_DOOR,m_trap_door},
    {L_TRAP_SNARE,m_trap_snare},
    {L_TRAP_BLADE,m_trap_blade},
    {L_TRAP_FIRE,m_trap_fire},
    {L_TRAP_TELEPORT,m_trap_teleport},
    {L_TRAP_DISINTEGRATE,m_trap_disintegrate},
    {L_TRAP_MANADRAIN,m_trap_manadrain},
    {L_TRAP_SLEEP_GAS,m_trap_sleepgas},
    {L_TRAP_ACID,m_trap_acid},
    {L_TRAP_ABYSS,m_trap_abyss},

    {L_ALTAR,m_altar},
    };
    auto move = move_map[movef];
      if(move != nullptr){
        move(m);      
      }
  }
}

#ifdef MSDOS_SUPPORTED_ANTIQUE
/* ****Moved here from another file**** */
/* if signp is true, always print message, otherwise do so only sometimes */
void sign_print(x, y, signp) int x, y, signp;
{
  if ((level->site[x][y].p_locf >= CITYSITEBASE) &&
      (level->site[x][y].p_locf < CITYSITEBASE + NUMCITYSITES))
    CitySiteList[level->site[x][y].p_locf - CITYSITEBASE][0] = TRUE;
  switch (level->site[x][y].p_locf)
  {
  case L_CHARITY:
    print1("You notice a sign: The Rampart Orphanage And Hospice For The Needy.");
    break;
  case L_MANSION:
    print1("You notice a sign:");
    print2("This edifice protected by DeathWatch Devices, Ltd.");
    morewait();
    break;
  case L_GRANARY:
    print1("You notice a sign:");
    print2("Public Granary: Entrance Strictly Forbidden.");
    break;
  case L_PORTCULLIS:
    if (level->site[x][y].locchar == FLOOR)
      print1("You see a groove in the floor and slots above you.");
    break;
  case L_STABLES:
    print1("You notice a sign:");
    print2("Village Stables");
    break;
  case L_COMMONS:
    print1("You notice a sign:");
    print2("Village Commons: No wolves allowed.");
    break;
  case L_MAZE:
    print1("You notice a sign:");
    print2("Hedge maze closed for trifid extermination.");
    break;
  case L_BANK:
    if (signp)
    {
      print1("You notice a sign:");
      print2("First Bank of Omega: Autoteller Carrel.");
    }
    break;
  case L_TEMPLE:
    print1("You see the ornate portico of the Rampart Pantheon");
    break;
  case L_ARMORER:
    if (signp)
    {
      print1("You notice a sign:");
      print2("Julie's Armor of Proof and Weapons of Quality");
    }
    break;
  case L_CLUB:
    if (signp)
    {
      print1("You notice a sign:");
      print2("Rampart Explorers' Club.");
    }
    break;
  case L_GYM:
    if (signp)
    {
      print1("You notice a sign:");
      print2("The Rampart Gymnasium, (affil. Rampart Coliseum).");
    }
    break;
  case L_HEALER:
    if (signp)
    {
      print1("You notice a sign:");
      print2("Rampart Healers. Member RMA.");
    }
    break;
  case L_CASINO:
    if (signp)
    {
      print1("You notice a sign:");
      print2("Rampart Mithril Nugget Casino.");
    }
    break;
  case L_SEWER:
    print1("A sewer entrance. You don't want to go down THERE, do you?");
    break;
  case L_COMMANDANT:
    if (signp)
    {
      print1("You notice a sign:");
      print2("Commandant Sonder's Rampart-fried Lyzzard partes. Open 24 hrs.");
    }
    break;
  case L_DINER:
    if (signp)
    {
      print1("You notice a sign:");
      print2("The Rampart Diner. All you can eat, 25Au.");
    }
    break;
  case L_CRAP:
    if (signp)
    {
      print1("You notice a sign:");
      print2("Les Crapeuleaux. (****)");
    }
    break;
  case L_TAVERN:
    if (signp)
    {
      print1("You notice a sign:");
      print2("The Centaur and Nymph -- J. Riley, prop.");
    }
    break;
  case L_ALCHEMIST:
    if (signp)
    {
      print1("You notice a sign:");
      print2("Ambrosias' Potions et cie.");
    }
    break;
  case L_DPW:
    if (signp)
    {
      print1("You notice a sign:");
      print2("Rampart Department of Public Works.");
    }
    break;
  case L_LIBRARY:
    if (signp)
    {
      print1("You notice a sign:");
      print2("Rampart Public Library.");
    }
    break;
  case L_CONDO:
    if (signp)
    {
      print1("You notice a sign:");
      if (gamestatusp(SOLD_CONDO))
        print2("Home Sweet Home");
      else
        print2("Luxury Condominium For Sale; Inquire Within");
    }
    break;
  case L_PAWN_SHOP:
    if (signp)
    {
      print1("You notice a sign:");
      print2("Knight's Pawn Shop.");
    }
    break;
  case L_CEMETARY:
    print1("You notice a sign:");
    print2("Rampart City Cemetary. Closed -- Full.");
    break;
  case L_GARDEN:
    print1("You notice a sign:");
    print2("Rampart Botanical Gardens---Do not deface statues.");
    break;
  case L_JAIL:
    print1("You notice a sign:");
    print2("Rampart City Gaol -- always room for more.");
    break;
  case L_ORACLE:
    print1("You notice a sign:");
    print2("The Oracle of the Cyan Flames");
    morewait();
    break;
  }
}
#endif
