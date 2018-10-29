/* omega copyright (C) by Laurence Raphael Brothers, 1987,1988,1989 */
/* priest.c */
/* functions for clerics. */

#include "glob.h"

/* prayer occurs at altars, hence name of function */
void l_altar()
{
  int i, deity;
  char response;

  if (Current_Environment == E_COUNTRYSIDE)
    deity = DRUID;
  else
    deity = level->site[player.x][player.y].aux;

  switch (deity)
  {
  default:
    print1("This rude altar has no markings.");
    break;
  case ODIN:
    print1("This granite altar is graven with a gallows.");
    break;
  case SET:
    print1("This sandstone altar has a black hand drawn on it.");
    break;
  case HECATE:
    print1("This silver altar is inlaid with a black crescent moon.");
    break;
  case ATHENA:
    print1("This golden altar is inscribed with an owl.");
    break;
  case DESTINY:
    print1("This crystal altar is in the form of an omega.");
    break;
  case DRUID:
    print1("This oaken altar is ornately engraved with leaves.");
    break;
  }
  print2("Worship at this altar? [yn] ");
  if (ynq2() == 'y')
  {
    if (player.rank[PRIESTHOOD] == 0)
      increase_priest_rank(deity);
    else if (!check_sacrilege(deity))
    {
      if (Blessing)
        print1("You have a sense of immanence.");
      print2("Request a Blessing, Sacrifice an item, or just Pray [b,s,p] ");
      do
        response = (char)mcigetc();
      while ((response != 'b') &&
             (response != 's') &&
             (response != 'p') &&
             (response != ESCAPE));
      if (response == 'b')
      {
        print1("You beg a heavenly benefice.");
        print2("You hear a gong resonating throughout eternity....");
        morewait();
        if (Blessing)
        {
          print1("A shaft of lucent radiance lances down from the heavens!");
          print2("You feel uplifted....");
          morewait();
          gain_experience(player.rank[PRIESTHOOD] * player.rank[PRIESTHOOD] * 50);
          cleanse(1);
          heal(10);
          bless(1);
          Blessing = FALSE;
          increase_priest_rank(deity);
        }
        else
        {
          print1("Your ardent plea is ignored.");
          print2("You feel ashamed.");
          player.xp -= (player.xp / 4);
        }
        calc_melee();
      }
      else if (response == 's')
      {
        print1("Which item to Sacrifice?");
        i = getitem(NULL_ITEM);
        if (i == ABORT)
          i = 0;
        if (player.possessions[i] == NULL)
        {
          print1("You have insulted your deity!");
          print2("Not a good idea, as it turns out...");
          dispel(-1);
          p_damage(player.hp - 1, UNSTOPPABLE, "a god's pique");
        }
        else if (true_item_value(player.possessions[i]) >
                 (long)(player.rank[PRIESTHOOD] *
                        player.rank[PRIESTHOOD] *
                        player.rank[PRIESTHOOD] * 50))
        {
          print1("With a burst of blue flame, your offering vanishes!");
          dispose_lost_objects(1, player.possessions[i]);
          print2("A violet nimbus settles around your head and slowly fades.");
          morewait();
          Blessing = TRUE;
        }
        else
        {
          print1("A darkling glow envelopes your offering!");
          print2("The glow slowly fades....");
          morewait();
          setgamestatus(SUPPRESS_PRINTING);
          if (player.possessions[i]->used)
          {
            player.possessions[i]->used = FALSE;
            item_use(player.possessions[i]);
            player.possessions[i]->blessing =
                -1 - abs(player.possessions[i]->blessing);
            player.possessions[i]->used = TRUE;
            item_use(player.possessions[i]);
          }
          else
            player.possessions[i]->blessing =
                -1 - abs(player.possessions[i]->blessing);
          resetgamestatus(SUPPRESS_PRINTING);
        }
      }
      else if (response == 'p')
      {
        if (deity != player.patron)
          print1("Nothing seems to happen.");
        else if (!increase_priest_rank(deity))
          answer_prayer();
      }
    }
  }
}

int check_sacrilege(int deity)
{
  int i, sacrilege = FALSE;
  if ((player.patron != deity) && (player.patron > 0))
  {
    sacrilege = TRUE;
    player.pow--;
    player.maxpow--;
    switch (player.patron)
    {
    case ODIN:
      print1("Odin notices your lack of faith! ");
      morewait();
      if (deity == ATHENA)
      {
        print2("However, Athena intercedes on your behalf.");
        sacrilege = FALSE;
      }
      else
      {
        print2("You are struck by a thunderbolt!");
        p_damage(player.level * 5, UNSTOPPABLE, "Odin's wrath");
        if (player.hp > 0)
        {
          morewait();
          print2("The bolt warps your feeble frame....");
          player.maxcon = player.maxcon / 2;
          player.con = min(player.con, player.maxcon);
          player.maxstr = player.maxstr / 2;
          player.con = min(player.str, player.maxstr);
        }
      }
      morewait();
      break;
    case SET:
      print1("Set notices your lack of faith! ");
      morewait();
      if (deity == HECATE)
      {
        print1("But since you pray to a friendly deity,");
        print2("Set decides not to punish you.");
        sacrilege = FALSE;
      }
      else
      {
        print2("You are blasted by a shaft of black fire!");
        p_damage(player.level * 5, UNSTOPPABLE, "Set's anger");
        if (player.hp > 0)
        {
          morewait();
          print1("You are wreathed in clouds of smoke.");
          for (i = 0; i < MAXITEMS; i++)
            if ((player.possessions[i] != NULL) &&
                (player.possessions[i]->blessing > -1))
              conform_lost_object(player.possessions[i]);
          morewait();
          print2("You feel Set's Black Hand on your heart....");
          player.con = player.maxcon = player.maxcon / 4;
        }
      }
      morewait();
      break;
    case HECATE:
      print1("Hecate notices your lack of faith! ");
      morewait();
      if (deity == SET)
      {
        print1("But ignores the affront since she likes Set.");
        sacrilege = FALSE;
      }
      else
      {
        print1("You are zapped by dark moonbeams!");
        p_damage(player.level * 5, UNSTOPPABLE, "Hecate's malice");
        if (player.hp > 0)
        {
          print2("The beams leach you of magical power!");
          player.maxpow = player.maxpow / 5;
          player.pow = min(player.pow, player.maxpow);
          for (i = 0; i < NUMSPELLS; i++)
            Spells[i].known = FALSE;
        }
      }
      morewait();
      break;
    case ATHENA:
      print1("Athena notices your lack of faith! ");
      morewait();
      if (deity == ODIN)
      {
        print2("But lets you off this time since Odin is also Lawful.");
        sacrilege = FALSE;
      }
      else
      {
        print2("You are zorched by godsfire!");
        if (player.hp > 0)
        {
          morewait();
          print1("The fire burns away your worldly experience!");
          player.level = 0;
          player.xp = 0;
          player.maxhp = player.hp = player.con;
          print2("Your power is reduced by the blast!!!");
          player.pow = player.maxpow = player.maxpow / 3;
          player.mana = min(player.mana, calcmana());
        }
      }
      morewait();
      break;
    case DESTINY:
      print2("The Lords of Destiny ignore your lack of faith.");
      sacrilege = FALSE;
      morewait();
      break;
    case DRUID:
      print2("Your treachery to the ArchDruid has been noted.");
      if (random_range(2) == 1)
        player.alignment += 40;
      else
        player.alignment -= 40;
      morewait();
      break;
    }
    if (sacrilege)
    {
      player.patron = 0;
      player.rank[PRIESTHOOD] = 0;
    }
  }
  return (sacrilege);
}

int increase_priest_rank(int deity)
{
  if (player.rank[PRIESTHOOD] == 0)
    switch (deity)
    {
    default:
      print2("Some nameless god blesses you....");
      player.hp = max(player.hp, player.maxhp);
      morewait();
      print2("The altar crumbles to dust and blows away.");
      level->site[player.x][player.y].locchar = FLOOR;
      level->site[player.x][player.y].p_locf = L_NO_OP;
      lset(player.x, player.y, CHANGED);
      break;
    case ODIN:
      if (player.alignment > 0)
      {
        print1("Odin hears your prayer!");
        print2(Priest[ODIN]);
        nprint2(" personally blesses you.");
        nprint2(" You are now a lay devotee of Odin.");
        player.patron = ODIN;
        player.rank[PRIESTHOOD] = LAY;
        player.guildxp[PRIESTHOOD] = 1;
        morewait();
        learnclericalspells(ODIN, LAY);
      }
      else
        print1("Odin ignores you.");
      break;
    case SET:
      if (player.alignment < 0)
      {
        print1("Set hears your prayer!");
        print2(Priest[SET]);
        nprint2(" personally blesses you. ");
        nprint2(" You are now a lay devotee of Set.");
        player.patron = SET;
        player.rank[PRIESTHOOD] = LAY;
        player.guildxp[PRIESTHOOD] = 1;
        morewait();
        learnclericalspells(SET, LAY);
      }
      else
        print1("Set ignores you.");
      break;
    case ATHENA:
      if (player.alignment > 0)
      {
        print1("Athena hears your prayer!");
        print2(Priest[ATHENA]);
        nprint2(" personally blesses you.");
        nprint2(" You are now a lay devotee of Athena.");
        player.patron = ATHENA;
        player.rank[PRIESTHOOD] = LAY;
        player.guildxp[PRIESTHOOD] = 1;
        morewait();
        learnclericalspells(ATHENA, LAY);
      }
      else
        print1("Athena ignores you.");
      break;
    case HECATE:
      if (player.alignment < 0)
      {
        print1("Hecate hears your prayer!");
        print2(Priest[HECATE]);
        nprint2(" personally blesses you.");
        nprint2(" You are now a lay devotee of Hecate.");
        player.patron = HECATE;
        player.rank[PRIESTHOOD] = LAY;
        player.guildxp[PRIESTHOOD] = 1;
        morewait();
        learnclericalspells(HECATE, LAY);
      }
      else
        print1("Hecate ignores you.");
      break;
    case DRUID:
      if (abs(player.alignment) < 10)
      {
        print1(Priest[DRUID]);
        nprint1(" personally blesses you.");
        print2("You are now a lay devotee of the Druids.");
        player.patron = DRUID;
        player.rank[PRIESTHOOD] = LAY;
        player.guildxp[PRIESTHOOD] = 1;
        morewait();
        learnclericalspells(DRUID, LAY);
      }
      else
      {
        print1("You hear a voice....");
        morewait();
        print2("'Only those who embody the Balance may become Druids.'");
      }
      break;
    case DESTINY:
      print1("The Lords of Destiny could hardly care less.");
      print2("But you can consider yourself now to be a lay devotee.");
      player.patron = DESTINY;
      player.rank[PRIESTHOOD] = LAY;
      player.guildxp[PRIESTHOOD] = 1;
      break;
    }
  else if (deity == player.patron)
  {
    if ((((deity == ODIN) || (deity == ATHENA)) &&
         (player.alignment < 1)) ||
        (((deity == SET) || (deity == HECATE)) &&
         (player.alignment > 1)) ||
        ((deity == DRUID) && (abs(player.alignment) > 10)))
    {
      print1("You have swerved from the One True Path!");
      print2("Your deity is greatly displeased...");
      player.xp -= player.level * player.level;
      player.xp = max(0, player.xp);
    }
    else if (player.rank[PRIESTHOOD] == HIGHPRIEST)
      return 0;
    else if (player.rank[PRIESTHOOD] == SPRIEST)
    {
      if (player.level > Priestlevel[deity])
        hp_req_test();
      else
        return 0;
    }
    else if (player.rank[PRIESTHOOD] == PRIEST)
    {
      if (player.guildxp[PRIESTHOOD] >= 4000)
      {
        print1("An heavenly fanfare surrounds you!");
        print2("Your deity raises you to the post of Senior Priest.");
        hp_req_print();
        player.rank[PRIESTHOOD] = SPRIEST;
        morewait();
        learnclericalspells(deity, SPRIEST);
      }
      else
        return 0;
    }
    else if (player.rank[PRIESTHOOD] == ACOLYTE)
    {
      if (player.guildxp[PRIESTHOOD] >= 1500)
      {
        print1("A trumpet sounds in the distance.");
        print2("Your deity raises you to the post of Priest.");
        player.rank[PRIESTHOOD] = PRIEST;
        morewait();
        learnclericalspells(deity, PRIEST);
      }
      else
        return 0;
    }
    else if (player.rank[PRIESTHOOD] == LAY)
    {
      if (player.guildxp[PRIESTHOOD] >= 400)
      {
        print1("A mellifluous chime sounds from above the altar.");
        print2("Your deity raises you to the post of Acolyte.");
        player.rank[PRIESTHOOD] = ACOLYTE;
        morewait();
        learnclericalspells(deity, ACOLYTE);
      }
      else
        return 0;
    }
  }
  return 1;
}

void answer_prayer()
{
  clearmsg();
  switch (random_range(12))
  {
  case 0:
    print1("You have a revelation!");
    break;
  case 1:
    print1("You feel pious.");
    break;
  case 2:
    print1("A feeling of sanctity comes over you.");
    break;
  default:
    print1("Nothing unusual seems to happen.");
    break;
  }
}

void hp_req_test()
{
  pob o;
  switch (player.patron)
  {
  case ODIN:
    if (find_item(&o, ARTIFACTID + 15, -1))
      make_hp(o);
    else
      hp_req_print();
    break;
  case SET:
    if (find_item(&o, ARTIFACTID + 14, -1))
      make_hp(o);
    else
      hp_req_print();
    break;
  case ATHENA:
    if (find_item(&o, ARTIFACTID + 17, -1))
      make_hp(o);
    else
      hp_req_print();
    break;
  case HECATE:
    if (find_item(&o, ARTIFACTID + 16, -1))
      make_hp(o);
    else
      hp_req_print();
    break;
  case DRUID:
    if (find_item(&o, ARTIFACTID + 14, -1))
      make_hp(o);
    else if (find_item(&o, ARTIFACTID + 15, -1))
      make_hp(o);
    else if (find_item(&o, ARTIFACTID + 16, -1))
      make_hp(o);
    else if (find_item(&o, ARTIFACTID + 17, -1))
      make_hp(o);
    else
      hp_req_print();
    break;
  case DESTINY:
    if (find_item(&o, ARTIFACTID + 19, -1))
      make_hp(o);
    else
      hp_req_print();
    break;
  }
}

void hp_req_print()
{
  morewait();
  print1("To advance further, you must obtain the Holy Symbol of ");
  switch (player.patron)
  {
  case ODIN:
    nprint1(Priest[SET]);
    print2("who may be found in the main Temple of Set.");
    break;
  case SET:
    nprint1(Priest[ODIN]);
    print2("who may be found in the main Temple of Odin.");
    break;
  case ATHENA:
    nprint1(Priest[HECATE]);
    print2("who may be found in the main Temple of Hecate.");
    break;
  case HECATE:
    nprint1(Priest[ATHENA]);
    print2("who may be found in the main Temple of Athena.");
    break;
  case DRUID:
    print2("any of the aligned priests who may be found in their main Temples.");
    break;
  case DESTINY:
    nprint1(Priest[DESTINY]);
    print2("who may be found in the main Temple of Destiny.");
    break;
  }
}

void make_hp(pob o)
{
  print1("A full-scale heavenly choir chants 'Hallelujah' all around you!");
  print2("You notice a change in the symbol you carry....");
  switch (player.patron)
  {
  case ODIN:
    *o = Objects[ARTIFACTID + 14];
    break;
  case SET:
    *o = Objects[ARTIFACTID + 15];
    break;
  case ATHENA:
    *o = Objects[ARTIFACTID + 16];
    break;
  case HECATE:
    *o = Objects[ARTIFACTID + 17];
    break;
  case DRUID:
    *o = Objects[ARTIFACTID + 18];
    break;
  case DESTINY:
    *o = Objects[ARTIFACTID + 19];
    break;
  }
  o->known = 2;
  o->charge = 17; /* random hack to convey bit that symbol is functional */
  morewait();
  if (player.patron == DRUID)
    print1("Your deity raises you to the post of ArchDruid!");
  else
    print1("Your deity raises you to the post of High Priest!");
  print2("You feel holy.");
  strcpy(Priest[player.patron], player.name);
  Priestlevel[player.patron] = player.level;
  player.rank[PRIESTHOOD] = HIGHPRIEST;
  morewait();
  Priestbehavior[player.patron] = fixnpc(4);
  save_hiscore_npc(player.patron);
  learnclericalspells(player.patron, HIGHPRIEST);
}
