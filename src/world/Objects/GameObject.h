/*
 * AscEmu Framework based on ArcEmu MMORPG Server
 * Copyright (c) 2014-2022 AscEmu Team <http://www.ascemu.org>
 * Copyright (C) 2008-2012 ArcEmu Team <http://www.ArcEmu.org/>
 * Copyright (C) 2005-2007 Ascent Team
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Management/QuestMgr.h"
#include "Management/TransporterHandler.h"
#include "Data/WoWGameObject.hpp"
#include "Map/Maps/BaseMap.hpp"
#include "WorldConf.h"

enum LootState : uint8_t
{
    GO_NOT_READY                = 0,
    GO_READY                    = 1,
    GO_ACTIVATED                = 2,
    GO_JUST_DEACTIVATED         = 3
};

enum GameObject_Flags
{
    GO_FLAG_NONE                = 0x000,
    GO_FLAG_NONSELECTABLE       = 0x001,
    GO_FLAG_LOCKED              = 0x002,
    GO_FLAG_UNTARGETABLE        = 0x004,
    GO_FLAG_TRANSPORT           = 0x008,
    GO_FLAG_NOT_SELECTABLE      = 0x010,
    GO_FLAG_NEVER_DESPAWN       = 0x020,
    GO_FLAG_TRIGGERED           = 0x040,
    GO_FLAG_UNK1                = 0x080,
    GO_FLAG_UNK2                = 0x100,
    GO_FLAG_DAMAGED             = 0x200,
    GO_FLAG_DESTROYED           = 0x400
};

// TODO: move these under proper Gameobject subclasses
struct GameObjectValue
{
    //11 GAMEOBJECT_TYPE_TRANSPORT
    uint32_t PathProgress = 0;
    TransportAnimation const* AnimationInfo = nullptr;
    uint32_t CurrentSeg = 0;
};

enum GameObjectTypes
{
    GAMEOBJECT_TYPE_DOOR                    = 0,
    GAMEOBJECT_TYPE_BUTTON                  = 1,
    GAMEOBJECT_TYPE_QUESTGIVER              = 2,
    GAMEOBJECT_TYPE_CHEST                   = 3,
    GAMEOBJECT_TYPE_BINDER                  = 4,
    GAMEOBJECT_TYPE_GENERIC                 = 5,
    GAMEOBJECT_TYPE_TRAP                    = 6,
    GAMEOBJECT_TYPE_CHAIR                   = 7,
    GAMEOBJECT_TYPE_SPELL_FOCUS             = 8,
    GAMEOBJECT_TYPE_TEXT                    = 9,
    GAMEOBJECT_TYPE_GOOBER                  = 10,
    GAMEOBJECT_TYPE_TRANSPORT               = 11,
    GAMEOBJECT_TYPE_AREADAMAGE              = 12,
    GAMEOBJECT_TYPE_CAMERA                  = 13,
    GAMEOBJECT_TYPE_MAP_OBJECT              = 14,
    GAMEOBJECT_TYPE_MO_TRANSPORT            = 15,
    GAMEOBJECT_TYPE_DUEL_ARBITER            = 16,
    GAMEOBJECT_TYPE_FISHINGNODE             = 17,
    GAMEOBJECT_TYPE_RITUAL                  = 18,
    GAMEOBJECT_TYPE_MAILBOX                 = 19,
    GAMEOBJECT_TYPE_AUCTIONHOUSE            = 20,
    GAMEOBJECT_TYPE_GUARDPOST               = 21,
    GAMEOBJECT_TYPE_SPELLCASTER             = 22,
    GAMEOBJECT_TYPE_MEETINGSTONE            = 23,
    GAMEOBJECT_TYPE_FLAGSTAND               = 24,
    GAMEOBJECT_TYPE_FISHINGHOLE             = 25,
    GAMEOBJECT_TYPE_FLAGDROP                = 26,
    GAMEOBJECT_TYPE_MINI_GAME               = 27,
    GAMEOBJECT_TYPE_LOTTERY_KIOSK           = 28,
    GAMEOBJECT_TYPE_CAPTURE_POINT           = 29,
    GAMEOBJECT_TYPE_AURA_GENERATOR          = 30,
    GAMEOBJECT_TYPE_DUNGEON_DIFFICULTY      = 31,
    GAMEOBJECT_TYPE_BARBER_CHAIR            = 32,
    GAMEOBJECT_TYPE_DESTRUCTIBLE_BUILDING   = 33,
    GAMEOBJECT_TYPE_GUILD_BANK              = 34,
    GAMEOBJECT_TYPE_TRAPDOOR                = 35
};

class Player;
class GameObjectAIScript;
class GameObjectModel;

//\todo check this enum - do we (ae) really handle this stuff this way?
enum GameObjectOverrides
{
    GAMEOBJECT_NORMAL_DISTANCE = 0x00,
    GAMEOBJECT_INFVIS = 0x01,                   // Makes the gameobject forever visible on the map after you saw it at least once - for various transports; actually it just doesn't erase it while you're on the same map.
    GAMEOBJECT_MAPWIDE = 0x02,                  // When you enter its map, the gameobject gets pushed to you no matter how far it is (but only for players), especially for Deeprun and Ulduar Trams.
    GAMEOBJECT_AREAWIDE = 0x04,                 //\todo UNIMPLEMENTED, but will work like this: the Map will get marked that it contains an object like this, and on player movement these objects will get distance-checked to spawn them from a greater distance than normal if needed - for few objects on smaller maps, like on battlegrounds; maybe they'll get area-triggered, haven't decided yet.
    GAMEOBJECT_ONMOVEWIDE = 0x08,               // When this gameobject moves and sends updates about it's position, do so in the second range - MapMgr::ChangeObjectLocation, +/- 6 units wide instead of +/- 1.
    GAMEOBJECT_OVERRIDE_FLAGS = 0x10,           //\todo UNIMPLEMENTED, Let the core decide about the flags sent in the A9 - example: 252 instead of 352 for Deeprun Tram.
    GAMEOBJECT_OVERRIDE_BYTES1 = 0x20,          //\todo UNIMPLEMENTED, Let the core use the full field instead an uint8 in GAMEOBJECT_BYTES_1, if the database creator knows what to do with it.
    GAMEOBJECT_OVERRIDE_PARENTROT = 0x40,       // Makes it possible for the core to skip calculating these fields and use whatever was specified in the spawn.
    // Later other types might folow, or the upper bytes might get used for the AREAWIDE option in the overrides variable...
};

typedef std::unordered_map<QuestProperties const*, uint32 > GameObjectGOMap;
typedef std::unordered_map<QuestProperties const*, std::map<uint32, uint32> > GameObjectItemMap;

struct GameObjectProperties
{
    uint32 entry;
    uint32 type;    //uint8_t
    uint32 display_id;
    std::string name;
    std::string category_name;
    std::string cast_bar_text;
    std::string Unkstr;

    // different data fields for GO-types
    // \todo add different structure for go types.
    union
    {
        // 0 GAMEOBJECT_TYPE_DOOR
        struct
        {
            uint32 start_open;                  // parameter_0 client side opened/closed
            uint32 lock_id;                     // parameter_1 from Lock.dbc
            uint32 auto_close_time;             // parameter_2 in secs
            uint32 no_damage_immune;            // parameter_3
            uint32 open_text_id;                // parameter_4
            uint32 close_text_id;               // parameter_5
            uint32 ignored_by_pathing;          // parameter_6
        }door;
        // 1 GAMEOBJECT_TYPE_BUTTON
        struct
        {
            uint32 start_open;                  // parameter_0
            uint32 lock_id;                     // parameter_1 from Lock.dbc
            uint32 auto_close_time;             // parameter_2 in secs
            uint32 linked_trap_id;              // parameter_3
            uint32 no_damage_immune;            // parameter_4 BgObject
            uint32 large;                       // parameter_5
            uint32 open_text_id;                // parameter_6
            uint32 close_text_id;               // parameter_7
            uint32 los_ok;                      // parameter_8
        }button;
        // 2 GAMEOBJECT_TYPE_QUESTGIVER
        struct
        {
            uint32_t lockId;                    // parameter_0 -> Lock.dbc
            uint32_t questList;                 // parameter_1
            uint32_t pageMaterial;              // parameter_2
            uint32_t gossipID;                  // parameter_3
            uint32_t customAnim;                // parameter_4
            uint32_t noDamageImmune;            // parameter_5
            uint32_t openTextID;                // parameter_6 can be used to replace castBarCaption?
            uint32_t losOK;                     // parameter_7
            uint32_t allowMounted;              // parameter_8 Is usable while on mount/vehicle. (0/1)
            uint32_t large;                     // parameter_9
            uint32_t conditionID1;              // parameter_10
        } questgiver;
        // 3 GAMEOBJECT_TYPE_CHEST
        struct
        {
            uint32 lock_id;                     // parameter_0 from Lock.dbc
            uint32 loot_id;                     // parameter_1
            uint32 restock_time;                // parameter_2
            uint32 consumable;                  // parameter_3 bool
            uint32 min_success_opens;           // parameter_4
            uint32 max_success_opens;           // parameter_5
            uint32 event_id;                    // parameter_6 lootedEvent
            uint32 linked_trap_id;              // parameter_7
            uint32 quest_id;                    // parameter_8 quest required for GO activation
            uint32 level;                       // parameter_9
            uint32 los_OK;                      // parameter_10
            uint32 leave_loot;                  // parameter_11
            uint32 not_in_combat;               // parameter_12
            uint32 log_loot;                    // parameter_13
            uint32 open_text_id;                // parameter_14
            uint32 group_loot_rules;            // parameter_15
            uint32 floating_tooltip;            // parameter_16
        } chest;
        // 4 GAMEOBJECT_TYPE_BINDER
        // 5 GAMEOBJECT_TYPE_GENERIC
        struct
        {
            uint32_t floatingTooltip;           // parameter_0
            uint32_t highlight;                 // parameter_1
            uint32_t serverOnly;                // parameter_2
            uint32_t large;                     // parameter_3
            uint32_t floatOnWater;              // parameter_4
            int32_t questID;                    // parameter_5
            uint32_t conditionID1;              // parameter_6
        } _generic;
        // 6 GAMEOBJECT_TYPE_TRAP
        struct
        {
            uint32 lock_id;                     // parameter_0 from Lock.dbc
            uint32 level;                       // parameter_1
            uint32 radius;                      // parameter_2 radius for trap activation
            uint32 spell_id;                    // parameter_3
            uint32 charges;                     // parameter_4
            uint32 cooldown;                    // parameter_5 in secs
            uint32 auto_close_time;             // parameter_6 in secs
            uint32 start_delay;                 // parameter_7
            uint32 server_only;                 // parameter_8
            uint32 stealthed;                   // parameter_9
            uint32 large;                       // parameter_10
            uint32 invisible;                   // parameter_11 not same as parameter_9
            uint32 open_text_id;                // parameter_12
            uint32 close_text_id;               // parameter_13
            uint32 ignore_totems;               // parameter_14
        } trap;
        // 7 GAMEOBJECT_TYPE_CHAIR
        // 8 GAMEOBJECT_TYPE_SPELL_FOCUS
        struct
        {
            uint32 focus_id;                    // parameter_0
            uint32 distance;                    // parameter_1
            uint32 linked_trap_id;              // parameter_2
            uint32 server_only;                 // parameter_3
            uint32 quest_id;                    // parameter_4
            uint32 large;                       // parameter_5
            uint32 floating_tooltip;            // parameter_6
        } spell_focus;
        // 9 GAMEOBJECT_TYPE_TEXT
        struct
        {
            uint32_t pageID;                    // parameter_0
            uint32_t language;                  // parameter_1
            uint32_t pageMaterial;              // parameter_2
            uint32_t allowMounted;              // parameter_3 Is usable while on mount/vehicle. (0/1)
            uint32_t conditionID1;              // parameter_4
        } text;
        // 10 GAMEOBJECT_TYPE_GOOBER
        struct
        {
            uint32 lock_id;                     // parameter_0 from Lock.dbc
            uint32 quest_id;                    // parameter_1
            uint32 event_id;                    // parameter_2
            uint32 auto_close_time;             // parameter_3 in secs
            uint32 custom_anim;                 // parameter_4
            uint32 consumable;                  // parameter_5
            uint32 cooldown;                    // parameter_6
            uint32 page_id;                     // parameter_7
            uint32 language;                    // parameter_8
            uint32 page_material;               // parameter_9
            uint32 spell_id;                    // parameter_10
            uint32 no_damage_immune;            // parameter_11
            uint32 linked_trap_id;              // parameter_12
            uint32 large;                       // parameter_13
            uint32 open_text_iD;                // parameter_14
            uint32 close_text_iD;               // parameter_15
            uint32 los_ok;                      // parameter_16 BgObject
            uint32 allow_mounted;               // parameter_17
            uint32 floating_tooltip;            // parameter_18
            uint32 gossip_id;                   // parameter_19
            uint32 world_state_sets_state;      // parameter_20
        }goober;
        // 11 GAMEOBJECT_TYPE_TRANSPORT
        struct
        {
            uint32_t pause;                     //parameter_0
            uint32_t startOpen;                 //parameter_1
            uint32_t autoCloseTime;             //parameter_2 secs till autoclose = autoCloseTime / 0x10000
            uint32_t pause1EventID;             //parameter_3
            uint32_t pause2EventID;             //parameter_4
            uint32_t mapID;                     //parameter_5
        } transport;
        // 12 GAMEOBJECT_TYPE_AREADAMAGE
        struct
        {
            uint32_t lockId;                    // parameter_0
            uint32_t radius;                    // parameter_1
            uint32_t damageMin;                 // parameter_2
            uint32_t damageMax;                 // parameter_3
            uint32_t damageSchool;              // parameter_4
            uint32_t autoCloseTime;             // parameter_5 secs till autoclose = autoCloseTime / 0x10000
            uint32_t openTextID;                // parameter_6
            uint32_t closeTextID;               // parameter_7
        } areadamage;
        // 13 GAMEOBJECT_TYPE_CAMERA
        struct
        {
            uint32 lock_id;                     // parameter_0 from Lock.dbc
            uint32 cinematic_id;                // parameter_1
            uint32 event_id;                    // parameter_2
            uint32 open_text_id;                // parameter_3
        }camera;
        // 14 GAMEOBJECT_TYPE_MAP_OBJECT
        // 15 GAMEOBJECT_TYPE_MO_TRANSPORT
        struct
        {
            uint32 taxi_path_id;                // parameter_0
            uint32 move_speed;                  // parameter_1
            uint32 accel_rate;                  // parameter_2
            uint32 start_event_id;              // parameter_3
            uint32 stop_event_id;               // parameter_4
            uint32 transport_physics;           // parameter_5
            uint32 map_id;                      // parameter_6
            uint32 world_state;                 // parameter_7
            uint32 can_be_stopped;              // parameter_8
        } mo_transport;
        // 16 GAMEOBJECT_TYPE_DUEL_ARBITER
        // 17 GAMEOBJECT_TYPE_FISHINGNODE
        // 18 GAMEOBJECT_TYPE_RITUAL
        struct
        {
            uint32 req_participants;            // parameter_0
            uint32 spell_id;                    // parameter_1
            uint32 anim_spell;                  // parameter_2
            uint32 ritual_persistent;           // parameter_3
            uint32 caster_target_spell;         // parameter_4
            uint32 caster_target_spell_targets; // parameter_5
            uint32 casters_grouped;             // parameter_6
            uint32 ritual_no_target_check;      // parameter_7
        }summoning_ritual;
        // 19 GAMEOBJECT_TYPE_MAILBOX
        // 20 GAMEOBJECT_TYPE_AUCTIONHOUSE
        // 21 GAMEOBJECT_TYPE_GUARDPOST
        struct
        {
            uint32_t creatureID;                // parameter_0
            uint32_t charges;                   // parameter_1
        } guardpost;
        // 22 GAMEOBJECT_TYPE_SPELLCASTER
        struct
        {
            uint32 spell_id;                    // parameter_0
            uint32 charges;                     // parameter_1
            uint32 party_only;                  // parameter_2
            uint32 allow_mounted;               // parameter_3
            uint32 large;                       // parameter_4
        }spell_caster;
        // 23 GAMEOBJECT_TYPE_MEETINGSTONE
        // 24 GAMEOBJECT_TYPE_FLAGSTAND
        struct
        {
            uint32_t lockId;                    // parameter_0
            uint32_t pickupSpell;               // parameter_1
            uint32_t radius;                    // parameter_2
            uint32_t returnAura;                // parameter_3
            uint32_t returnSpell;               // parameter_4
            uint32_t noDamageImmune;            // parameter_5
            uint32_t openTextID;                // parameter_6
            uint32_t losOK;                     // parameter_7
            uint32_t conditionID1;              // parameter_8
        } flagstand;
        // 25 GAMEOBJECT_TYPE_FISHINGHOLE
        struct
        {
            uint32 radius;                      // parameter_0
            uint32 loot_id;                     // parameter_1
            uint32 min_success_opens;           // parameter_2
            uint32 max_success_opens;           // parameter_3
            uint32 lock_id;                     // parameter_4 from Lock.dbc
        }fishinghole;
        // 26 GAMEOBJECT_TYPE_FLAGDROP
        struct
        {
            uint32_t lockId;                    // parameter_0
            uint32_t eventID;                   // parameter_1
            uint32_t pickupSpell;               // parameter_2
            uint32_t noDamageImmune;            // parameter_3
            uint32_t openTextID;                // parameter_4
        } flagdrop;
        // 27 GAMEOBJECT_TYPE_MINI_GAME
        // 28 GAMEOBJECT_TYPE_LOTTERY_KIOSK
        // 29 GAMEOBJECT_TYPE_CAPTURE_POINT
        struct
        {
            uint32_t radius;                    // parameter_0
            uint32_t spell;                     // parameter_1
            uint32_t worldState1;               // parameter_2
            uint32_t worldstate2;               // parameter_3
            uint32_t winEventID1;               // parameter_4
            uint32_t winEventID2;               // parameter_5
            uint32_t contestedEventID1;         // parameter_6
            uint32_t contestedEventID2;         // parameter_7
            uint32_t progressEventID1;          // parameter_8
            uint32_t progressEventID2;          // parameter_9
            uint32_t neutralEventID1;           // parameter_10
            uint32_t neutralEventID2;           // parameter_11
            uint32_t neutralPercent;            // parameter_12
            uint32_t worldstate3;               // parameter_13
            uint32_t minSuperiority;            // parameter_14
            uint32_t maxSuperiority;            // parameter_15
            uint32_t minTime;                   // parameter_16
            uint32_t maxTime;                   // parameter_17
            uint32_t large;                     // parameter_18
            uint32_t highlight;                 // parameter_19
            uint32_t startingValue;             // parameter_20
            uint32_t unidirectional;            // parameter_21
        } capturePoint;
        // 30 GAMEOBJECT_TYPE_AURA_GENERATOR
        // 31 GAMEOBJECT_TYPE_DUNGEON_DIFFICULTY
        // 32 GAMEOBJECT_TYPE_BARBER_CHAIR
        // 33 GAMEOBJECT_TYPE_DESTRUCTIBLE_BUILDING
        struct
        {
            uint32 intact_num_hits;             // parameter_0
            uint32 credit_proxy_creature;       // parameter_1
            uint32 state1_name;                 // parameter_2
            uint32 intact_event;                // parameter_3
            uint32 damaged_display_id;          // parameter_4
            uint32 damaged_num_hits;            // parameter_5
            uint32 unused1;                     // parameter_6
            uint32 unused2;                     // parameter_7
            uint32 unused3;                     // parameter_8
            uint32 damaged_event;               // parameter_9
            uint32 destroyed_display_id;        // parameter_10
            uint32 unused4;                     // parameter_11
            uint32 unused5;                     // parameter_12
            uint32 unused6;                     // parameter_13
            uint32 destroyed_event;             // parameter_14
            uint32 unused7;                     // parameter_15
            uint32 debuilding_time_secs;        // parameter_16
            uint32 unused8;                     // parameter_17
            uint32 destructible_data;           // parameter_18
            uint32 rebuilding_event;            // parameter_19
            uint32 unused9;                     // parameter_20
            uint32 unused10;                    // parameter_21
            uint32 damage_event;                // parameter_22
            uint32 unused11;                    // parameter_23
        } destructible_building;
        // 34 GAMEOBJECT_TYPE_GUILD_BANK
        // 35 GAMEOBJECT_TYPE_TRAPDOOR

        // raw parameters
        struct
        {
            uint32 parameter_0;
            uint32 parameter_1;
            uint32 parameter_2;
            uint32 parameter_3;
            uint32 parameter_4;
            uint32 parameter_5;
            uint32 parameter_6;
            uint32 parameter_7;
            uint32 parameter_8;
            uint32 parameter_9;
            uint32 parameter_10;
            uint32 parameter_11;
            uint32 parameter_12;
            uint32 parameter_13;
            uint32 parameter_14;
            uint32 parameter_15;
            uint32 parameter_16;
            uint32 parameter_17;
            uint32 parameter_18;
            uint32 parameter_19;
            uint32 parameter_20;
            uint32 parameter_21;
            uint32 parameter_22;
            uint32 parameter_23;
        }raw;
    };
    float size;
    uint32 QuestItems[6];

    // Quests
    // <quest, requirement_count>
    GameObjectGOMap goMap;
    // <quest, [<item, item_count>]>
    GameObjectItemMap itemMap;

    uint32_t getLootId() const
    {
        switch (type)
        {
            case GAMEOBJECT_TYPE_CHEST:       return chest.loot_id;
            case GAMEOBJECT_TYPE_FISHINGHOLE: return fishinghole.loot_id;
            default: return 0;
        }
    }

    uint32_t getCooldown() const                              // Cooldown preventing goober and traps to cast spell
    {
        switch (type)
        {
            case GAMEOBJECT_TYPE_TRAP:        return trap.cooldown;
            case GAMEOBJECT_TYPE_GOOBER:      return goober.cooldown;
            default: return 0;
        }
    }

    uint32_t getLockId() const
    {
        switch (type)
        {
            case GAMEOBJECT_TYPE_DOOR:       return door.lock_id;
            case GAMEOBJECT_TYPE_BUTTON:     return button.lock_id;
            case GAMEOBJECT_TYPE_QUESTGIVER: return questgiver.lockId;
            case GAMEOBJECT_TYPE_CHEST:      return chest.lock_id;
            case GAMEOBJECT_TYPE_TRAP:       return trap.lock_id;
            case GAMEOBJECT_TYPE_GOOBER:     return goober.lock_id;
            case GAMEOBJECT_TYPE_AREADAMAGE: return areadamage.lockId;
            case GAMEOBJECT_TYPE_CAMERA:     return camera.lock_id;
            case GAMEOBJECT_TYPE_FLAGSTAND:  return flagstand.lockId;
            case GAMEOBJECT_TYPE_FISHINGHOLE:return fishinghole.lock_id;
            case GAMEOBJECT_TYPE_FLAGDROP:   return flagdrop.lockId;
            default: return 0;
        }
    }

    uint32_t getCharges() const                               // despawn at uses amount
    {
        switch (type)
        {
            //case GAMEOBJECT_TYPE_TRAP:        return trap.charges;
            case GAMEOBJECT_TYPE_GUARDPOST:   return guardpost.charges;
            case GAMEOBJECT_TYPE_SPELLCASTER: return spell_caster.charges;
            default: return 0;
        }
    }

    bool isDespawnAtAction() const
    {
        switch (type)
        {
            case GAMEOBJECT_TYPE_CHEST:  return chest.consumable != 0;
            case GAMEOBJECT_TYPE_GOOBER: return goober.consumable != 0;
            default: return false;
        }
    }

    bool getDespawnPossibility() const
    {
        switch (type)
        {
            case GAMEOBJECT_TYPE_DOOR:       return door.no_damage_immune != 0;
            case GAMEOBJECT_TYPE_BUTTON:     return button.no_damage_immune != 0;
            case GAMEOBJECT_TYPE_QUESTGIVER: return questgiver.noDamageImmune != 0;
            case GAMEOBJECT_TYPE_GOOBER:     return goober.no_damage_immune != 0;
            case GAMEOBJECT_TYPE_FLAGSTAND:  return flagstand.noDamageImmune != 0;
            case GAMEOBJECT_TYPE_FLAGDROP:   return flagdrop.noDamageImmune != 0;
            default: return true;
        }
    }

    uint32_t getLinkedGameObjectEntry() const
    {
        switch (type)
        {
            case GAMEOBJECT_TYPE_BUTTON:      return button.linked_trap_id;
            case GAMEOBJECT_TYPE_CHEST:       return chest.linked_trap_id;
            case GAMEOBJECT_TYPE_SPELL_FOCUS: return spell_focus.linked_trap_id;
            case GAMEOBJECT_TYPE_GOOBER:      return goober.linked_trap_id;
            default: return 0;
        }
    }

    uint32_t getAutoCloseTime() const
    {
        uint32_t autoCloseTime = 0;
        switch (type)
        {
            case GAMEOBJECT_TYPE_DOOR:          autoCloseTime = door.auto_close_time; break;
            case GAMEOBJECT_TYPE_BUTTON:        autoCloseTime = button.auto_close_time; break;
            case GAMEOBJECT_TYPE_TRAP:          autoCloseTime = trap.auto_close_time; break;
            case GAMEOBJECT_TYPE_GOOBER:        autoCloseTime = goober.auto_close_time; break;
            case GAMEOBJECT_TYPE_TRANSPORT:     autoCloseTime = transport.autoCloseTime; break;
            case GAMEOBJECT_TYPE_AREADAMAGE:    autoCloseTime = areadamage.autoCloseTime; break;
            default: break;
        }
        return autoCloseTime;              // prior to 3.0.3, conversion was / 0x10000;
    }

    bool isLargeGameObject() const
    {
        //todo disable for now Gameobjects wont Update in WorldMap
        return false;
        /*switch (type)
        {
            case GAMEOBJECT_TYPE_BUTTON:            return button.large != 0;
            case GAMEOBJECT_TYPE_QUESTGIVER:        return questgiver.large != 0;
            case GAMEOBJECT_TYPE_GENERIC:           return _generic.large != 0;
            case GAMEOBJECT_TYPE_TRAP:              return trap.large != 0;
            case GAMEOBJECT_TYPE_SPELL_FOCUS:       return spell_focus.large != 0;
            case GAMEOBJECT_TYPE_GOOBER:            return goober.large != 0;
            case GAMEOBJECT_TYPE_SPELLCASTER:       return spell_caster.large != 0;
            case GAMEOBJECT_TYPE_CAPTURE_POINT:     return capturePoint.large != 0;
            default: return false;
        }*/
    }

    bool isInfiniteGameObject() const
    {
        //todo disable for now Gameobjects wont Update in WorldMap
        return false;
        /*switch (type)
        {
            case GAMEOBJECT_TYPE_DOOR:                  return true;
            case GAMEOBJECT_TYPE_FLAGSTAND:             return true;
            case GAMEOBJECT_TYPE_FLAGDROP:              return true;
            case GAMEOBJECT_TYPE_TRAPDOOR:              return true;
            case GAMEOBJECT_TYPE_TRANSPORT:             return true;
            default: return false;
        }*/
    }

    bool cannotBeUsedUnderImmunity() const // Cannot be used/activated/looted by players under immunity effects (example: Divine Shield)
    {
        switch (type)
        {
            case GAMEOBJECT_TYPE_DOOR:       return door.no_damage_immune != 0;
            case GAMEOBJECT_TYPE_BUTTON:     return button.no_damage_immune != 0;
            case GAMEOBJECT_TYPE_QUESTGIVER: return questgiver.noDamageImmune != 0;
            case GAMEOBJECT_TYPE_CHEST:      return true;                           // All chests cannot be opened while immune on 3.3.5a
            case GAMEOBJECT_TYPE_GOOBER:     return goober.no_damage_immune != 0;
            case GAMEOBJECT_TYPE_FLAGSTAND:  return flagstand.noDamageImmune != 0;
            case GAMEOBJECT_TYPE_FLAGDROP:   return flagdrop.noDamageImmune != 0;
            default: return false;
        }
    }

    bool isUsableMounted() const
    {
        switch (type)
        {
            case GAMEOBJECT_TYPE_MAILBOX: return true;
            case GAMEOBJECT_TYPE_BARBER_CHAIR: return false;
            case GAMEOBJECT_TYPE_QUESTGIVER: return questgiver.allowMounted != 0;
            case GAMEOBJECT_TYPE_TEXT: return text.allowMounted != 0;
            case GAMEOBJECT_TYPE_GOOBER: return goober.allow_mounted != 0;
            case GAMEOBJECT_TYPE_SPELLCASTER: return spell_caster.allow_mounted != 0;
            default: return false;
        }
    }
};

enum GameObjectBytes
{
    GAMEOBJECT_BYTES_STATE          = 0,
    GAMEOBJECT_BYTES_TYPE_ID        = 1,
    GAMEOBJECT_BYTES_UNK            = 2,        //\todo unknown atm
    GAMEOBJECT_BYTES_ANIMPROGRESS   = 3,
};

struct WoWGameObject;
class GameEvent;
class SERVER_DECL GameObject : public Object
{
    // MIT Start
public:
    GameObject(uint64_t guid);
    ~GameObject();

    bool loadFromDB(MySQLStructure::GameobjectSpawn* spawn, WorldMap* map, bool addToWorld);
    void saveToDB(bool newSpawn = false);
    void deleteFromDB();
    bool create(uint32_t entry, WorldMap* map, uint32_t phase, LocationVector const& position, QuaternionData const&  rotation, GameObject_State state, uint32_t spawnId = 0);

    uint32_t getSpawnId() const { return m_spawnId; }
    void setSpawnId(uint32_t spawnId) { m_spawnId = spawnId; }

    void despawn(uint32_t delay /*milliseconds*/, uint32_t forceRespawntime /*seconds*/);
    void expireAndDelete();
    void RemoveFromWorld(bool free_guid);

    void setRespawnTime(int32_t respawn);
    time_t getRespawnTime() const { return m_respawnTime; }
    void saveRespawnTime(uint32_t forceDelay = 0);
    void respawn();
    uint32_t getRespawnDelay() const { return m_respawnDelayTime; }
    bool isSpawned() const
    {
        return m_respawnDelayTime == 0 ||
            (m_respawnTime > 0 && !m_spawnedByDefault) ||
            (m_respawnTime == 0 && m_spawnedByDefault);
    }

    bool isSpawnedByDefault() const { return m_spawnedByDefault; }
    void setSpawnedByDefault(bool b) { m_spawnedByDefault = b; }

    void setSpellId(uint32_t id)
    {
        m_spawnedByDefault = false;                     // all summoned object is despawned after delay
        m_spellId = id;
    }
    uint32_t getSpellId() const { return m_spellId; }

    GameObject* getLinkedTrap();
    void setLinkedTrap(GameObject* linkedTrap) { m_linkedTrap = linkedTrap->getGuid(); }

    void addUniqueUse(Player* player);
    void addUse() { ++m_usetimes; }
    uint32_t getUseCount() const { return m_usetimes; }
    uint32_t getUniqueUseCount() const { return static_cast<uint32_t>(m_unique_users.size()); }
    bool isUseable();
    void switchDoorOrButton(bool activate, bool alternative = false);
    void useDoorOrButton(uint32_t time_to_restore = 0, bool alternative = false, Unit* user = nullptr);
    void resetDoorOrButton();
    void triggerLinkedGameObject(uint32_t trapEntry, Unit* target);

    void setOwnerGuid(uint64_t owner)
    {
        // Owner already found and different than expected owner - remove object from old owner
        if (owner && getCreatedByGuid() && getCreatedByGuid() != owner)
            return;

        m_spawnedByDefault = false; // all object with owner is despawned after delay
        setCreatedByGuid(owner);
    }

    LootState getLootState() const { return m_lootState; }
    void setLootState(LootState state, Unit* unit = nullptr);

    void setLocalRotationAngles(float z_rot, float y_rot, float x_rot);
    void setLocalRotation(float qx, float qy, float qz, float qw);
    void setParentRotation(QuaternionData const& rotation);
    QuaternionData const& getLocalRotation() const { return m_localRotation; }
    int64_t getPackedLocalRotation() const { return m_packedRotation; }
    QuaternionData getWorldRotation() const;

    void enableCollision(bool enable);
    GameObjectModel* m_model = nullptr;

    Transporter* ToTransport() { if (GetGameObjectProperties()->type == GAMEOBJECT_TYPE_MO_TRANSPORT) return reinterpret_cast<Transporter*>(this); else return nullptr; }
    Transporter const* ToTransport() const { if (GetGameObjectProperties()->type == GAMEOBJECT_TYPE_MO_TRANSPORT) return reinterpret_cast<Transporter const*>(this); else return nullptr; }
    void updateModelPosition();

    MySQLStructure::GameobjectSpawn* m_spawn = nullptr;

    GameObjectValue const* getGOValue() const { return &m_goValue; }

private:

    void updatePackedRotation();

    //////////////////////////////////////////////////////////////////////////////////////////
    // WoWData
    WoWGameObject* gameObjectData() const { return reinterpret_cast<WoWGameObject*>(wow_data); }

public:

    uint64_t getCreatedByGuid() const;
    void setCreatedByGuid(uint64_t guid);

    uint32_t getDisplayId() const;
    void setDisplayId(uint32_t id);

    uint32_t getFlags() const;
    void setFlags(uint32_t flags);
    void addFlags(uint32_t flags);
    void removeFlags(uint32_t flags);
    bool hasFlags(uint32_t flags) const;

    float getParentRotation(uint8_t type) const;

#if VERSION_STRING < WotLK
    uint32_t getDynamicFlags() const;
    void setDynamicFlags(uint32_t dynamicFlags);
#elif VERSION_STRING < Mop
    uint32_t getDynamicField() const;
    uint16_t getDynamicFlags() const;
    int16_t getDynamicPathProgress() const;
    void setDynamicField(uint32_t dynamic);
    void setDynamicField(uint16_t dynamicFlags, int16_t pathProgress);
    void setDynamicFlags(uint16_t dynamicFlags);
    void setDynamicPathProgress(int16_t pathProgress);
#endif

    uint32_t getFactionTemplate() const;
    void setFactionTemplate(uint32_t id);

    uint32_t getLevel() const;
    void setLevel(uint32_t level);

    //bytes1
    uint8_t getState() const;
    void setState(uint8_t state);

    uint8_t getGoType() const;
    void setGoType(uint8_t type);

    uint8_t getArtKit() const;
    void setArtKit(uint8_t artkit);

    uint8_t getAnimationProgress() const;
    void setAnimationProgress(uint8_t progress);

    virtual uint32_t getTransportPeriod() const;

    //////////////////////////////////////////////////////////////////////////////////////////
    // Type helper
    bool isQuestGiver() const;
    bool isFishingNode() const;

    // Trap objects
    bool invisible = false;
    bool inStealth = false;
    uint8_t invisibilityFlag = INVIS_FLAG_NORMAL;
    uint8_t stealthFlag = STEALTH_FLAG_NORMAL;

    // Owner
    Unit* getUnitOwner() override;
    Player* getPlayerOwner() override;

    // MIT End

    GameEvent* mEvent = nullptr;

    GameObjectProperties const* GetGameObjectProperties() const;
        void SetGameObjectProperties(GameObjectProperties const* go_prop) { gameobject_properties = go_prop; }

        virtual bool IsLootable() { return false; }

        virtual void Use(uint64 /*GUID*/) {}
        void CastSpell(uint64_t TargetGUID, SpellInfo const* sp);
        void CastSpell(uint64_t TargetGUID, uint32_t SpellID);

        void Update(unsigned long time_passed);

        //void _EnvironmentalDamageUpdate();
        // Serialization
        void SaveToFile(std::stringstream & name);

        virtual void InitAI();

        void CallScriptUpdate();

        GameObjectAIScript* GetScript() { return myScript; }

        void OnPushToWorld();
        void onRemoveInRangeObject(Object* pObj);

        uint32_t GetGOReqSkill();
        MapCell* m_respawnCell = nullptr;

        void SetOverrides(uint32 go_overrides) { m_overrides = go_overrides; }
        uint32 GetOverrides() { return m_overrides; }

        //\todo serverdie faction can be handled in update.
        void SetFaction(uint32 id)
        {
            setFactionTemplate(id);
            setServersideFaction();
        }

    protected:

        bool m_summonedGo = false;
        bool m_deleted = false;
        GameObjectProperties const* gameobject_properties = nullptr;

        GameObjectAIScript* myScript = nullptr;
        uint32 _fields[getSizeOfStructure(WoWGameObject)];

        uint32 m_overrides = 0;             //See enum GAMEOBJECT_OVERRIDES!

    //MIT
    public:

        void sendGameobjectCustomAnim(uint32_t anim = 0);
        virtual void onUse(Player* /*player*/);

    protected:
        GameObjectModel* createModel();
        void updateModel();

        virtual void _internalUpdateOnState(unsigned long timeDiff);

        uint32_t m_spellId = 0;

        uint32_t m_spawnId = 0;                 // temporary GameObjects have 0
        time_t m_respawnTime = 0;               // seconds
        uint32_t m_respawnDelayTime = 300;      // seconds
        uint32_t m_despawnDelay = 0;            // milliseconds
        uint32_t m_despawnRespawnTime = 0;      // seconds
        LootState m_lootState = GO_NOT_READY;
        uint64_t m_lootStateUnitGUID = 0;
        bool m_spawnedByDefault = true;
        time_t m_cooldownTime = 0;              // milliseconds
        GameObject_State m_prevGoState = GO_STATE_OPEN; // What state to set whenever resetting

        int64_t m_packedRotation = 0;
        QuaternionData m_localRotation;
        GameObjectValue m_goValue;

        uint64_t m_linkedTrap = 0;

        std::set<uint64_t> m_unique_users;
        uint32_t m_usetimes = 0;
};

//////////////////////////////////////////////////////////////////////////////////////////
// Abstract Base Class for lootables (fishing node, fishing hole, and chests)
class GameObject_Lootable : public GameObject
{
    public:

        GameObject_Lootable(uint64 GUID) : GameObject(GUID) {}
        ~GameObject_Lootable() {}

        virtual bool HasLoot() = 0;

        uint16_t getLootMode() const { return m_LootMode; }
        bool hasLootMode(uint16_t lootMode) const { return (m_LootMode & lootMode) != 0; }
        void setLootMode(uint16_t lootMode) { m_LootMode = lootMode; }
        void addLootMode(uint16_t lootMode) { m_LootMode |= lootMode; }
        void removeLootMode(uint16_t lootMode) { m_LootMode &= ~lootMode; }
        void resetLootMode() { m_LootMode = LOOT_MODE_DEFAULT; }
        void setLootGenerationTime() { m_lootGenerationTime = static_cast<uint32_t>(Util::getTimeNow()); }
        uint32_t getLootGenerationTime() const { return m_lootGenerationTime; }

        time_t getRestockTime() const { return m_restockTime; }
        void setRestockTime(time_t time) { m_restockTime = time; }

        void getFishLoot(Player* loot_owner, bool getJunk = false);

        Loot loot;

    protected:
        time_t m_restockTime = 0;                // seconds

        uint16_t m_LootMode = LOOT_MODE_DEFAULT; // bitmask, determines what loot will be lootable used for Hardmodes example Ulduar Bosses
        uint32_t m_lootGenerationTime = 0;
};

//////////////////////////////////////////////////////////////////////////////////////////
// Implements Type 0 (DOOR) GameObjects
class GameObject_Door : public GameObject
{
    public:

        GameObject_Door(uint64 GUID);
        ~GameObject_Door();

        void InitAI();

        void onUse(Player* player) override;

    protected:
        void _internalUpdateOnState(unsigned long timeDiff) override;
};

//////////////////////////////////////////////////////////////////////////////////////////
// Implements Type 1 (BUTTON) GameObjects
class GameObject_Button : public GameObject
{
    public:

        GameObject_Button(uint64 GUID);
        ~GameObject_Button();

        void InitAI();

        void onUse(Player* player) override;

    protected:
        void _internalUpdateOnState(unsigned long timeDiff) override;

    private:

        SpellInfo const* spell;
};

//////////////////////////////////////////////////////////////////////////////////////////
// implementing Type 2 (QUESTGIVER) GameObjects
class GameObject_QuestGiver : public GameObject
{
    public:

        GameObject_QuestGiver(uint64 GUID);
        ~GameObject_QuestGiver();

        void InitAI();

        bool HasQuests()
        {
            if (m_quests == NULL)
                return false;

            if (m_quests->size() == 0)
                return false;

            return true;
        }

        void onUse(Player* player) override;

        uint32 NumOfQuests()
        {
            return static_cast<uint32>(m_quests->size());
        }

        void AddQuest(QuestRelation* Q)
        {
            m_quests->push_back(Q);
        }

        void DeleteQuest(QuestRelation* Q);

        //////////////////////////////////////////////////////////////////////////////////////////
        // Searches for a QuestRelation in the GO and if found, returns the Quest
        // \param uint32 quest_id  -  Identifier of the Quest
        // \param uint8 quest_relation  -  QuestRelation type
        // \return the Quest on success NULL on failure
        QuestProperties const* FindQuest(uint32_t quest_id, uint8_t quest_relation);

        //////////////////////////////////////////////////////////////////////////////////////////
        // Finds the Quest with quest_id in the GO, and returns it's QuestRelation type
        // \param uint32 quest_id  -  Identifier of the Quest
        // \return Returns the QuestRelation type on success, 0 on failure
        uint16 GetQuestRelation(uint32_t quest_id);

        //////////////////////////////////////////////////////////////////////////////////////////
        // Returns an iterator to the GO's QuestRelation list beginning
        // \return an iterator to the QuestRelation list's beginning
        std::list<QuestRelation*>::iterator QuestsBegin()
        {
            return m_quests->begin();
        };

        //////////////////////////////////////////////////////////////////////////////////////////
        // Returns an iterator to the GO's QuestRelation list end
        // \return an iterator to the QuestRelation list's end
        std::list<QuestRelation*>::iterator QuestsEnd()
        {
            return m_quests->end();
        };

        //////////////////////////////////////////////////////////////////////////////////////////
        // Initializes the QuestRelation list with another
        // \param std::list< QuestRelation* >* qst_lst  -  pointer to the other list
        void SetQuestList(std::list<QuestRelation*>* qst_lst)
        {
            m_quests = qst_lst;
        };

        std::list<QuestRelation*>& getQuestList() const
        {
            return *m_quests;
        }

    private:

        //////////////////////////////////////////////////////////////////////////////////////////
        // Loads the QuestRelations from QuestMgr for this GO
        void LoadQuests() { sQuestMgr.LoadGOQuests(this); }

        std::list<QuestRelation*>* m_quests;

};

//////////////////////////////////////////////////////////////////////////////////////////
// implementing type 3 (CHEST) GameObjects
class GameObject_Chest : public GameObject_Lootable
{
    public:

        GameObject_Chest(uint64 GUID);
        ~GameObject_Chest();

        void InitAI();

        bool IsLootable() { return true; }
        bool HasLoot();

        void onUse(Player* player) override;

        void Open();
        void Close();

    protected:
        void _internalUpdateOnState(unsigned long timeDiff) override;

    private:

        SpellInfo const* spell;
};

//////////////////////////////////////////////////////////////////////////////////////////
// implementing Type 6 (TRAP) GameObjects
class GameObject_Trap : public GameObject
{
    public:

        GameObject_Trap(uint64 GUID);
        ~GameObject_Trap();

        void InitAI();

        void onUse(Player* player) override;

    protected:
        void _internalUpdateOnState(unsigned long timeDiff) override;

    private:

        SpellInfo const* spell;
};

//////////////////////////////////////////////////////////////////////////////////////////
// implementing Type 7 (GAMEOBJECT_TYPE_CHAIR) GameObjects
class GameObject_Chair : public GameObject
{
public:

    GameObject_Chair(uint64 GUID) : GameObject(GUID){}
    ~GameObject_Chair(){};

    void onUse(Player* player) override;

};

//////////////////////////////////////////////////////////////////////////////////////////
// implementing Type 8 (SPELL_FOCUS) GameObjects
class GameObject_SpellFocus : public GameObject
{
    public:

        GameObject_SpellFocus(uint64 GUID);
        ~GameObject_SpellFocus();

        void OnPushToWorld();
};

//////////////////////////////////////////////////////////////////////////////////////////
// implementing Type 10 (GOOBER) GameObjects
class GameObject_Goober : public GameObject
{
    public:

        GameObject_Goober(uint64 GUID);
        ~GameObject_Goober();

        void InitAI();

        void onUse(Player* player) override;

    protected:
        void _internalUpdateOnState(unsigned long timeDiff) override;

    private:
        SpellInfo const* spell;
};

//////////////////////////////////////////////////////////////////////////////////////////
// implementing Type 11 (TRANSPORT) GameObjects
class GameObject_Transport : public GameObject
{
    public:
        GameObject_Transport(uint64_t guid) : GameObject(guid) {}
        ~GameObject_Transport() {}

    protected:
        void _internalUpdateOnState(unsigned long timeDiff) override;
};

//////////////////////////////////////////////////////////////////////////////////////////
// implementing Type 13 (CAMERA) GameObjects
class GameObject_Camera : public GameObject
{
public:

    GameObject_Camera(uint64 GUID) : GameObject(GUID) {}
    ~GameObject_Camera() {}

    void onUse(Player* player) override;

};

//////////////////////////////////////////////////////////////////////////////////////////
// implements Type 17 (FISHINGNODE) GameObjects
class GameObject_FishingNode : public GameObject_Lootable
{
    public:

        GameObject_FishingNode(uint64 GUID);
        ~GameObject_FishingNode();

        void onUse(Player* player) override;

        bool HasLoot();

        bool IsLootable() override { return true; }

    protected:
        void _internalUpdateOnState(unsigned long timeDiff) override;
};

//////////////////////////////////////////////////////////////////////////////////////////
// Class implementing Type 18 (SUMMONING_RITUAL) GameObjects
class GameObject_Ritual : public GameObject
{
    public:

        GameObject_Ritual(uint64 GUID);
        ~GameObject_Ritual();

        void InitAI();

        void onUse(Player* player) override;

        struct RitualStruct
        {
            uint64_t CasterGUID = 0;
            uint64_t TargetGUID = 0;
            uint32_t SpellID = 0;
            uint32_t CurrentMembers = 0;
            uint32_t MaxMembers = 0;
            std::vector<uint64_t> Members;

            RitualStruct(uint32_t members) : MaxMembers(members), Members(members) {}

            void Setup(uint64_t caster_guid, uint64_t target_guid, uint32_t spell_id)
            {
                CasterGUID = caster_guid;
                TargetGUID = target_guid;
                SpellID = spell_id;

                AddMember(caster_guid);
            }

            uint64_t GetCasterGUID() { return CasterGUID; }
            uint64_t GetTargetGUID() { return TargetGUID; }
            uint32_t GetSpellID() { return SpellID; }

            bool AddMember(uint64_t GUID)
            {
                uint32_t i = 0;
                for (; i < MaxMembers; i++)
                    if (Members[i] == 0)
                        break;

                if (i == MaxMembers)
                    return false;

                Members[i] = GUID;
                CurrentMembers++;

                return true;
            }

            bool RemoveMember(uint64_t GUID)
            {
                uint32_t i = 0;
                for (; i < MaxMembers; i++)
                {
                    if (Members[i] == GUID)
                    {
                        Members[i] = 0;
                        CurrentMembers--;
                        return true;
                    }
                }

                return false;
            }

            bool HasMember(uint64_t GUID)
            {
                for (uint32_t i = 0; i < MaxMembers; i++)
                    if (Members[i] == GUID)
                        return true;

                return false;
            }

            uint64_t GetMemberGUIDBySlot(uint32_t Slot) { return Members[Slot]; }

            bool HasFreeSlots()
            {
                if (CurrentMembers < MaxMembers)
                    return true;

                return false;
            }

            uint32_t GetMaxMembers() { return MaxMembers; }

            void Finish() { SpellID = 0; }

            bool IsFinished()
            {
                if (SpellID == 0)
                    return true;

                return false;
            }
        };

        RitualStruct* GetRitual() const { return Ritual; }

    private:
        RitualStruct* Ritual = nullptr;
};

//////////////////////////////////////////////////////////////////////////////////////////
// Implements Type 22 (SPELLCASTER) GameObjects
class GameObject_SpellCaster : public GameObject
{
    public:

        GameObject_SpellCaster(uint64 GUID);
        ~GameObject_SpellCaster();

        void InitAI();

        void onUse(Player* player) override;

    private:

        SpellInfo const* spell;
};

//////////////////////////////////////////////////////////////////////////////////////////
// implementing Type 23 (MEETINGSTONE) GameObjects
class GameObject_Meetingstone : public GameObject
{
public:

    GameObject_Meetingstone(uint64 GUID) : GameObject(GUID) {}
    ~GameObject_Meetingstone() {}

    void onUse(Player* player) override;
};

//////////////////////////////////////////////////////////////////////////////////////////
// implementing Type 24 (FLAGSTAND) GameObjects
class GameObject_FlagStand : public GameObject
{
public:

    GameObject_FlagStand(uint64 GUID) : GameObject(GUID) {}
    ~GameObject_FlagStand() {}

    void onUse(Player* player) override;
};

//////////////////////////////////////////////////////////////////////////////////////////
// implementing Type 25 (FISHINGHOLE) GameObjects
class GameObject_FishingHole : public GameObject_Lootable
{
    public:

        GameObject_FishingHole(uint64 GUID);
        ~GameObject_FishingHole();

        void InitAI();

        void onUse(Player* player) override;

        bool IsLootable() { return true; }
        bool HasLoot();

        uint32_t getMaxOpen() const { return maxOpens; }
        void setMaxOpen(uint32_t max) { maxOpens = max; }

    protected:
        void _internalUpdateOnState(unsigned long timeDiff) override;

    private:
        uint32_t maxOpens = 0;
};

//////////////////////////////////////////////////////////////////////////////////////////
// implementing Type 26 (FLAGDROP) GameObjects
class GameObject_FlagDrop : public GameObject
{
public:

    GameObject_FlagDrop(uint64 GUID) : GameObject(GUID) {}
    ~GameObject_FlagDrop() {}

    void onUse(Player* player) override;
};

//////////////////////////////////////////////////////////////////////////////////////////
// implementing Type 32 (BARBER_CHAIR) GameObjects
class GameObject_BarberChair : public GameObject
{
public:

    GameObject_BarberChair(uint64 GUID) : GameObject(GUID) {}
    ~GameObject_BarberChair() {}

    void onUse(Player* player) override;
};

//////////////////////////////////////////////////////////////////////////////////////////
// Implements Type 33 (DESTRUCTIBLE) GameObjects
class SERVER_DECL GameObject_Destructible : public GameObject
{
    public:

        GameObject_Destructible(uint64 GUID);
        ~GameObject_Destructible();

        void InitAI();

        void Damage(uint32_t damage, uint64_t AttackerGUID, uint64_t ControllerGUID, uint32_t SpellID);

        void Rebuild();

        uint32_t GetHP() { return hitpoints; }
        void setHP(uint32_t hp) { hitpoints = hp; }

        uint32_t GetMaxHP() { return maxhitpoints; }
        void setMaxHP(uint32_t maxHp) { maxhitpoints = maxHp; }

    private:

        void SendDamagePacket(uint32_t damage, uint64_t AttackerGUID, uint64_t ControllerGUID, uint32_t SpellID);

        uint32_t hitpoints;
        uint32_t maxhitpoints;
};

#endif // GAMEOBJECT_H
