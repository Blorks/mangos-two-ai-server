/**
 * MaNGOS is a full featured server for World of Warcraft, supporting
 * the following clients: 1.12.x, 2.4.3, 3.3.5a, 4.3.4a and 5.4.8
 *
 * Copyright (C) 2005-2025 MaNGOS <https://www.getmangos.eu>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * World of Warcraft, and all World of Warcraft or Warcraft art, images,
 * and lore are copyrighted by Blizzard Entertainment, Inc.
 */

/**
 * \addtogroup game
 * @{
 * \file
 */

#ifndef MANGOS_SPELLAURADEFINES_H
#define MANGOS_SPELLAURADEFINES_H

#define MAX_AURAS 64                                        // client support up to 255, but it will cause problems with group auras updating

enum AuraFlags
{
    AFLAG_NONE              = 0x00,
    AFLAG_EFF_INDEX_0       = 0x01,
    AFLAG_EFF_INDEX_1       = 0x02,
    AFLAG_EFF_INDEX_2       = 0x04,
    AFLAG_NOT_CASTER        = 0x08,
    AFLAG_POSITIVE          = 0x10,
    AFLAG_DURATION          = 0x20,
    AFLAG_UNK2              = 0x40,
    AFLAG_NEGATIVE          = 0x80
};

/**
 * This is what's used in a \ref Modifier by the \ref Aura class
 * to tell what the \ref Aura should modify.
 */
enum AuraType
{
    SPELL_AURA_NONE = 0,
    SPELL_AURA_BIND_SIGHT = 1,
    SPELL_AURA_MOD_POSSESS = 2,
    /**
     * The aura should do periodic damage, the function that handles
     * this is \ref Aura::HandlePeriodicDamage, the amount is usually decided
     * by the \ref Unit::SpellDamageBonusDone or \ref Unit::MeleeDamageBonusDone
     * which increases/decreases the \ref Modifier::m_amount
     */
    SPELL_AURA_PERIODIC_DAMAGE = 3,
    /**
     * Used by \ref Aura::HandleAuraDummy
     */
    SPELL_AURA_DUMMY = 4,
    /**
     * Used by \ref Aura::HandleModConfuse, will either confuse or unconfuse
     * the target depending on whether the apply flag is set
     */
    SPELL_AURA_MOD_CONFUSE = 5,
    SPELL_AURA_MOD_CHARM = 6,
    SPELL_AURA_MOD_FEAR = 7,
    /**
     * The aura will do periodic heals of a target, handled by
     * \ref Aura::HandlePeriodicHeal, uses \ref Unit::SpellHealingBonusDone
     * to calculate whether to increase or decrease \ref Modifier::m_amount
     */
    SPELL_AURA_PERIODIC_HEAL = 8,
    /**
     * Changes the attackspeed, the \ref Modifier::m_amount decides
     * how much we change in percent, ie, if the m_amount is
     * 50 the attackspeed will increase by 50%
     */
    SPELL_AURA_MOD_ATTACKSPEED = 9,
    //This doesn't make sense if you look at SpellAuras.cpp:2696
    //Where a bitwise check is made, but the SpellSchools enum is just
    //a normal enumeration, not in the style: 1 2 4 8 ...
    /**
     * Modifies the threat that the \ref Aura does in percent,
     * the \ref Modifier::m_miscvalue decides which of the SpellSchools
     * it should affect threat for.
     * \see SpellSchoolMask
     */
    SPELL_AURA_MOD_THREAT = 10,
    /**
     * Just applies a taunt which will change the threat a mob has
     * Taken care of in \ref Aura::HandleModThreat
     */
    SPELL_AURA_MOD_TAUNT = 11,
    /**
     * Stuns targets in different ways, taken care of in
     * \ref Aura::HandleAuraModStun
     */
    SPELL_AURA_MOD_STUN = 12,
    /**
     * Changes the damage done by a weapon in any hand, the \ref Modifier::m_miscvalue
     * will tell what school the damage is from, it's used as a bitmask
     * \see SpellSchoolMask
     */
    SPELL_AURA_MOD_DAMAGE_DONE = 13,
    /**
     * Not handled by the Aura class but instead this is implemented in
     * \ref Unit::MeleeDamageBonusTaken and \ref Unit::SpellBaseDamageBonusTaken
     */
    SPELL_AURA_MOD_DAMAGE_TAKEN = 14,
    /**
     * Not handled by the \ref Aura class, implemented in \ref Unit::DealMeleeDamage
     */
    SPELL_AURA_DAMAGE_SHIELD = 15,
    /**
     * Taken care of in \ref Aura::HandleModStealth, take note that this
     * is not the same thing as invisibility
     */
    SPELL_AURA_MOD_STEALTH = 16,
    /**
     * Not handled by the \ref Aura class, implemented in \ref Unit::IsVisibleForOrDetect
     * which does a lot of checks to determine whether the person is visible or not,
     * the \ref AuraType::SPELL_AURA_MOD_STEALTH seems to determine how in/visible ie a rogue is.
     */
    SPELL_AURA_MOD_STEALTH_DETECT = 17,
    /**
     * Handled by \ref Aura::HandleInvisibility, the \ref Modifier::m_miscvalue in the struct
     * seems to decide what kind of invisibility it is with a bitflag. the miscvalue
     * decides which bit is set, ie: 3 would make the 3rd bit be set.
     */
    SPELL_AURA_MOD_INVISIBILITY = 18,
    /**
     * Adds one of the kinds of detections to the possible detections.
     * As in \ref AuraType::SPEALL_AURA_MOD_INVISIBILITY the \ref Modifier::m_miscvalue seems to decide
     * what kind of invisibility the \ref Unit or \ref Player should be able to detect.
     */
    SPELL_AURA_MOD_INVISIBILITY_DETECTION = 19,
    SPELL_AURA_OBS_MOD_HEALTH = 20,                         // 20,21 unofficial
    SPELL_AURA_OBS_MOD_MANA = 21,
    /**
     * Handled by \ref Aura::HandleAuraModResistance, changes the resistance for a \ref Unit
     * the field \ref Modifier::m_miscvalue decides which kind of resistance that should
     * be changed, for possible values see \ref SpellSchools
     * \see SpellSchools
     */
    SPELL_AURA_MOD_RESISTANCE = 22,
    /**
     * Currently just sets \ref Aura::m_isPeriodic to apply and has a special case
     * for Curse of the Plaguebringer.
     */
    SPELL_AURA_PERIODIC_TRIGGER_SPELL = 23,
    /**
     * Just sets \ref Aura::m_isPeriodic to apply
     */
    SPELL_AURA_PERIODIC_ENERGIZE = 24,
    /**
     * Changes whether the target is pacified or not depending on the apply flag.
     * Pacify makes the target silenced and have all it's attack skill disabled.
     * See: http://www.wowhead.com/spell=6462/pacified
     */
    SPELL_AURA_MOD_PACIFY = 25,
    /**
     * Roots or unroots the target
     */
    SPELL_AURA_MOD_ROOT = 26,
    /**
     * Silences the target and stops and spell casts that should be stopped,
     * they have the flag \ref SpellPreventionType::SPELL_PREVENTION_TYPE_SILENCE
     */
    SPELL_AURA_MOD_SILENCE = 27,
    SPELL_AURA_REFLECT_SPELLS = 28,
    SPELL_AURA_MOD_STAT = 29,
    SPELL_AURA_MOD_SKILL = 30,
    SPELL_AURA_MOD_INCREASE_SPEED = 31,
    SPELL_AURA_MOD_INCREASE_MOUNTED_SPEED = 32,
    SPELL_AURA_MOD_DECREASE_SPEED = 33,
    SPELL_AURA_MOD_INCREASE_HEALTH = 34,
    SPELL_AURA_MOD_INCREASE_ENERGY = 35,
    SPELL_AURA_MOD_SHAPESHIFT = 36,
    SPELL_AURA_EFFECT_IMMUNITY = 37,
    SPELL_AURA_STATE_IMMUNITY = 38,
    SPELL_AURA_SCHOOL_IMMUNITY = 39,
    SPELL_AURA_DAMAGE_IMMUNITY = 40,
    SPELL_AURA_DISPEL_IMMUNITY = 41,
    SPELL_AURA_PROC_TRIGGER_SPELL = 42,
    SPELL_AURA_PROC_TRIGGER_DAMAGE = 43,
    SPELL_AURA_TRACK_CREATURES = 44,
    SPELL_AURA_TRACK_RESOURCES = 45,
    SPELL_AURA_46 = 46,                                     // Ignore all Gear test spells
    SPELL_AURA_MOD_PARRY_PERCENT = 47,
    SPELL_AURA_PERIODIC_TRIGGER_BY_CLIENT = 48,             // Client periodic trigger spell by self (3 spells in 3.3.5a)
    SPELL_AURA_MOD_DODGE_PERCENT = 49,
    SPELL_AURA_MOD_CRITICAL_HEALING_AMOUNT = 50,
    SPELL_AURA_MOD_BLOCK_PERCENT = 51,
    SPELL_AURA_MOD_CRIT_PERCENT = 52,
    SPELL_AURA_PERIODIC_LEECH = 53,
    SPELL_AURA_MOD_HIT_CHANCE = 54,
    SPELL_AURA_MOD_SPELL_HIT_CHANCE = 55,
    SPELL_AURA_TRANSFORM = 56,
    SPELL_AURA_MOD_SPELL_CRIT_CHANCE = 57,
    SPELL_AURA_MOD_INCREASE_SWIM_SPEED = 58,
    SPELL_AURA_MOD_DAMAGE_DONE_CREATURE = 59,
    SPELL_AURA_MOD_PACIFY_SILENCE = 60,
    SPELL_AURA_MOD_SCALE = 61,
    SPELL_AURA_PERIODIC_HEALTH_FUNNEL = 62,
    SPELL_AURA_63 = 63,                                     // old SPELL_AURA_PERIODIC_MANA_FUNNEL
    SPELL_AURA_PERIODIC_MANA_LEECH = 64,
    SPELL_AURA_MOD_CASTING_SPEED_NOT_STACK = 65,
    SPELL_AURA_FEIGN_DEATH = 66,
    SPELL_AURA_MOD_DISARM = 67,
    SPELL_AURA_MOD_STALKED = 68,
    SPELL_AURA_SCHOOL_ABSORB = 69,
    SPELL_AURA_EXTRA_ATTACKS = 70,
    SPELL_AURA_MOD_SPELL_CRIT_CHANCE_SCHOOL = 71,
    SPELL_AURA_MOD_POWER_COST_SCHOOL_PCT = 72,
    SPELL_AURA_MOD_POWER_COST_SCHOOL = 73,
    SPELL_AURA_REFLECT_SPELLS_SCHOOL = 74,
    SPELL_AURA_MOD_LANGUAGE = 75,
    SPELL_AURA_FAR_SIGHT = 76,
    SPELL_AURA_MECHANIC_IMMUNITY = 77,
    SPELL_AURA_MOUNTED = 78,
    SPELL_AURA_MOD_DAMAGE_PERCENT_DONE = 79,
    SPELL_AURA_MOD_PERCENT_STAT = 80,
    SPELL_AURA_SPLIT_DAMAGE_PCT = 81,
    SPELL_AURA_WATER_BREATHING = 82,
    SPELL_AURA_MOD_BASE_RESISTANCE = 83,
    SPELL_AURA_MOD_REGEN = 84,
    SPELL_AURA_MOD_POWER_REGEN = 85,
    SPELL_AURA_CHANNEL_DEATH_ITEM = 86,
    SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN = 87,
    SPELL_AURA_MOD_HEALTH_REGEN_PERCENT = 88,
    SPELL_AURA_PERIODIC_DAMAGE_PERCENT = 89,
    SPELL_AURA_90 = 90,                                     // old SPELL_AURA_MOD_RESIST_CHANCE
    SPELL_AURA_MOD_DETECT_RANGE = 91,
    SPELL_AURA_PREVENTS_FLEEING = 92,
    SPELL_AURA_MOD_UNATTACKABLE = 93,
    SPELL_AURA_INTERRUPT_REGEN = 94,
    SPELL_AURA_GHOST = 95,
    SPELL_AURA_SPELL_MAGNET = 96,
    SPELL_AURA_MANA_SHIELD = 97,
    SPELL_AURA_MOD_SKILL_TALENT = 98,
    SPELL_AURA_MOD_ATTACK_POWER = 99,
    SPELL_AURA_AURAS_VISIBLE = 100,
    SPELL_AURA_MOD_RESISTANCE_PCT = 101,
    SPELL_AURA_MOD_MELEE_ATTACK_POWER_VERSUS = 102,
    SPELL_AURA_MOD_TOTAL_THREAT = 103,
    SPELL_AURA_WATER_WALK = 104,
    SPELL_AURA_FEATHER_FALL = 105,
    SPELL_AURA_HOVER = 106,
    SPELL_AURA_ADD_FLAT_MODIFIER = 107,
    SPELL_AURA_ADD_PCT_MODIFIER = 108,
    SPELL_AURA_ADD_TARGET_TRIGGER = 109,
    SPELL_AURA_MOD_POWER_REGEN_PERCENT = 110,
    SPELL_AURA_ADD_CASTER_HIT_TRIGGER = 111,
    SPELL_AURA_OVERRIDE_CLASS_SCRIPTS = 112,
    SPELL_AURA_MOD_RANGED_DAMAGE_TAKEN = 113,
    SPELL_AURA_MOD_RANGED_DAMAGE_TAKEN_PCT = 114,
    SPELL_AURA_MOD_HEALING = 115,
    SPELL_AURA_MOD_REGEN_DURING_COMBAT = 116,
    SPELL_AURA_MOD_MECHANIC_RESISTANCE = 117,
    SPELL_AURA_MOD_HEALING_PCT = 118,
    SPELL_AURA_119 = 119,                                   // old SPELL_AURA_SHARE_PET_TRACKING
    SPELL_AURA_UNTRACKABLE = 120,
    SPELL_AURA_EMPATHY = 121,
    SPELL_AURA_MOD_OFFHAND_DAMAGE_PCT = 122,
    SPELL_AURA_MOD_TARGET_RESISTANCE = 123,
    SPELL_AURA_MOD_RANGED_ATTACK_POWER = 124,
    SPELL_AURA_MOD_MELEE_DAMAGE_TAKEN = 125,
    SPELL_AURA_MOD_MELEE_DAMAGE_TAKEN_PCT = 126,
    SPELL_AURA_RANGED_ATTACK_POWER_ATTACKER_BONUS = 127,
    SPELL_AURA_MOD_POSSESS_PET = 128,
    SPELL_AURA_MOD_SPEED_ALWAYS = 129,
    SPELL_AURA_MOD_MOUNTED_SPEED_ALWAYS = 130,
    SPELL_AURA_MOD_RANGED_ATTACK_POWER_VERSUS = 131,
    SPELL_AURA_MOD_INCREASE_ENERGY_PERCENT = 132,
    SPELL_AURA_MOD_INCREASE_HEALTH_PERCENT = 133,
    SPELL_AURA_MOD_MANA_REGEN_INTERRUPT = 134,
    SPELL_AURA_MOD_HEALING_DONE = 135,
    SPELL_AURA_MOD_HEALING_DONE_PERCENT = 136,
    SPELL_AURA_MOD_TOTAL_STAT_PERCENTAGE = 137,
    SPELL_AURA_MOD_MELEE_HASTE = 138,
    SPELL_AURA_FORCE_REACTION = 139,
    SPELL_AURA_MOD_RANGED_HASTE = 140,
    SPELL_AURA_MOD_RANGED_AMMO_HASTE = 141,
    SPELL_AURA_MOD_BASE_RESISTANCE_PCT = 142,
    SPELL_AURA_MOD_RESISTANCE_EXCLUSIVE = 143,
    SPELL_AURA_SAFE_FALL = 144,
    SPELL_AURA_MOD_PET_TALENT_POINTS = 145,
    SPELL_AURA_ALLOW_TAME_PET_TYPE = 146,
    SPELL_AURA_MECHANIC_IMMUNITY_MASK = 147,
    SPELL_AURA_RETAIN_COMBO_POINTS = 148,
    SPELL_AURA_REDUCE_PUSHBACK  = 149,                      //    Reduce Pushback
    SPELL_AURA_MOD_SHIELD_BLOCKVALUE_PCT = 150,
    SPELL_AURA_TRACK_STEALTHED  = 151,                      //    Track Stealthed
    SPELL_AURA_MOD_DETECTED_RANGE = 152,                    //    Mod Detected Range
    SPELL_AURA_SPLIT_DAMAGE_FLAT = 153,                     //    Split Damage Flat
    SPELL_AURA_MOD_STEALTH_LEVEL = 154,                     //    Stealth Level Modifier
    SPELL_AURA_MOD_WATER_BREATHING = 155,                   //    Mod Water Breathing
    SPELL_AURA_MOD_REPUTATION_GAIN = 156,                   //    Mod Reputation Gain
    SPELL_AURA_PET_DAMAGE_MULTI = 157,                      //    Mod Pet Damage
    SPELL_AURA_MOD_SHIELD_BLOCKVALUE = 158,
    SPELL_AURA_NO_PVP_CREDIT = 159,
    SPELL_AURA_MOD_AOE_AVOIDANCE = 160,                   ///< Reduces the hit chance for AOE spells
    SPELL_AURA_MOD_HEALTH_REGEN_IN_COMBAT = 161,
    SPELL_AURA_POWER_BURN_MANA = 162,
    SPELL_AURA_MOD_CRIT_DAMAGE_BONUS = 163,
    SPELL_AURA_164 = 164,
    SPELL_AURA_MELEE_ATTACK_POWER_ATTACKER_BONUS = 165,
    SPELL_AURA_MOD_ATTACK_POWER_PCT = 166,
    SPELL_AURA_MOD_RANGED_ATTACK_POWER_PCT = 167,
    SPELL_AURA_MOD_DAMAGE_DONE_VERSUS = 168,
    SPELL_AURA_MOD_CRIT_PERCENT_VERSUS = 169,
    SPELL_AURA_DETECT_AMORE = 170,
    SPELL_AURA_MOD_SPEED_NOT_STACK = 171,
    SPELL_AURA_MOD_MOUNTED_SPEED_NOT_STACK = 172,
    SPELL_AURA_173 = 173,                                   // old SPELL_AURA_ALLOW_CHAMPION_SPELLS
    SPELL_AURA_MOD_SPELL_DAMAGE_OF_STAT_PERCENT = 174,      // by defeult intelect, dependent from SPELL_AURA_MOD_SPELL_HEALING_OF_STAT_PERCENT
    SPELL_AURA_MOD_SPELL_HEALING_OF_STAT_PERCENT = 175,
    SPELL_AURA_SPIRIT_OF_REDEMPTION = 176,
    SPELL_AURA_AOE_CHARM = 177,
    SPELL_AURA_MOD_DEBUFF_RESISTANCE = 178,
    SPELL_AURA_MOD_ATTACKER_SPELL_CRIT_CHANCE = 179,
    SPELL_AURA_MOD_FLAT_SPELL_DAMAGE_VERSUS = 180,
    SPELL_AURA_181 = 181,                                   // old SPELL_AURA_MOD_FLAT_SPELL_CRIT_DAMAGE_VERSUS - possible flat spell crit damage versus
    SPELL_AURA_MOD_RESISTANCE_OF_STAT_PERCENT = 182,
    SPELL_AURA_MOD_CRITICAL_THREAT = 183,
    SPELL_AURA_MOD_ATTACKER_MELEE_HIT_CHANCE = 184,
    SPELL_AURA_MOD_ATTACKER_RANGED_HIT_CHANCE = 185,
    SPELL_AURA_MOD_ATTACKER_SPELL_HIT_CHANCE = 186,
    SPELL_AURA_MOD_ATTACKER_MELEE_CRIT_CHANCE = 187,
    SPELL_AURA_MOD_ATTACKER_RANGED_CRIT_CHANCE = 188,
    SPELL_AURA_MOD_RATING = 189,
    SPELL_AURA_MOD_FACTION_REPUTATION_GAIN = 190,
    SPELL_AURA_USE_NORMAL_MOVEMENT_SPEED = 191,
    SPELL_AURA_MOD_MELEE_RANGED_HASTE = 192,
    SPELL_AURA_HASTE_ALL = 193,
    SPELL_AURA_MOD_IGNORE_ABSORB_SCHOOL  = 194,
    SPELL_AURA_MOD_IGNORE_ABSORB_FOR_SPELL  = 195,
    SPELL_AURA_MOD_COOLDOWN = 196,                          // only 24818 Noxious Breath
    SPELL_AURA_MOD_ATTACKER_SPELL_AND_WEAPON_CRIT_CHANCE = 197,
    SPELL_AURA_198 = 198,                                   // old SPELL_AURA_MOD_ALL_WEAPON_SKILLS
    SPELL_AURA_MOD_INCREASES_SPELL_PCT_TO_HIT = 199,
    SPELL_AURA_MOD_KILL_XP_PCT = 200,
    SPELL_AURA_FLY = 201,
    SPELL_AURA_IGNORE_COMBAT_RESULT = 202,
    SPELL_AURA_MOD_ATTACKER_MELEE_CRIT_DAMAGE = 203,
    SPELL_AURA_MOD_ATTACKER_RANGED_CRIT_DAMAGE = 204,
    SPELL_AURA_MOD_ATTACKER_SPELL_CRIT_DAMAGE = 205,
    SPELL_AURA_MOD_FLIGHT_SPEED = 206,
    SPELL_AURA_MOD_FLIGHT_SPEED_MOUNTED = 207,
    SPELL_AURA_MOD_FLIGHT_SPEED_STACKING = 208,
    SPELL_AURA_MOD_FLIGHT_SPEED_MOUNTED_STACKING = 209,
    SPELL_AURA_MOD_FLIGHT_SPEED_NOT_STACKING = 210,
    SPELL_AURA_MOD_FLIGHT_SPEED_MOUNTED_NOT_STACKING = 211,
    SPELL_AURA_MOD_RANGED_ATTACK_POWER_OF_STAT_PERCENT = 212,
    SPELL_AURA_MOD_RAGE_FROM_DAMAGE_DEALT = 213,
    SPELL_AURA_214 = 214,
    SPELL_AURA_ARENA_PREPARATION = 215,
    SPELL_AURA_HASTE_SPELLS = 216,
    SPELL_AURA_217 = 217,
    SPELL_AURA_HASTE_RANGED = 218,
    SPELL_AURA_MOD_MANA_REGEN_FROM_STAT = 219,
    SPELL_AURA_MOD_RATING_FROM_STAT = 220,
    SPELL_AURA_221 = 221,
    SPELL_AURA_222 = 222,
    SPELL_AURA_223 = 223,
    SPELL_AURA_224 = 224,
    SPELL_AURA_PRAYER_OF_MENDING = 225,
    SPELL_AURA_PERIODIC_DUMMY = 226,
    SPELL_AURA_PERIODIC_TRIGGER_SPELL_WITH_VALUE = 227,
    SPELL_AURA_DETECT_STEALTH = 228,
    SPELL_AURA_MOD_AOE_DAMAGE_AVOIDANCE = 229,
    SPELL_AURA_230 = 230,
    SPELL_AURA_PROC_TRIGGER_SPELL_WITH_VALUE = 231,
    SPELL_AURA_MECHANIC_DURATION_MOD = 232,
    SPELL_AURA_233 = 233,
    SPELL_AURA_MECHANIC_DURATION_MOD_NOT_STACK = 234,
    SPELL_AURA_MOD_DISPEL_RESIST = 235,
    SPELL_AURA_CONTROL_VEHICLE = 236,
    SPELL_AURA_MOD_SPELL_DAMAGE_OF_ATTACK_POWER = 237,
    SPELL_AURA_MOD_SPELL_HEALING_OF_ATTACK_POWER = 238,
    SPELL_AURA_MOD_SCALE_2 = 239,
    SPELL_AURA_MOD_EXPERTISE = 240,
    SPELL_AURA_FORCE_MOVE_FORWARD = 241,
    SPELL_AURA_MOD_SPELL_DAMAGE_FROM_HEALING = 242,
    SPELL_AURA_FACTION_OVERRIDE = 243,
    SPELL_AURA_COMPREHEND_LANGUAGE = 244,
    SPELL_AURA_MOD_DURATION_OF_MAGIC_EFFECTS = 245,
    SPELL_AURA_MOD_DURATION_OF_EFFECTS_BY_DISPEL = 246,
    SPELL_AURA_MIRROR_IMAGE = 247,
    SPELL_AURA_MOD_COMBAT_RESULT_CHANCE = 248,
    SPELL_AURA_CONVERT_RUNE = 249,
    SPELL_AURA_MOD_INCREASE_HEALTH_2 = 250,
    SPELL_AURA_MOD_ENEMY_DODGE = 251,
    SPELL_AURA_SLOW_ALL = 252,
    SPELL_AURA_MOD_BLOCK_CRIT_CHANCE = 253,
    SPELL_AURA_MOD_DISARM_OFFHAND = 254,
    SPELL_AURA_MOD_MECHANIC_DAMAGE_TAKEN_PERCENT = 255,
    SPELL_AURA_NO_REAGENT_USE = 256,
    SPELL_AURA_MOD_TARGET_RESIST_BY_SPELL_CLASS = 257,
    SPELL_AURA_258 = 258,
    SPELL_AURA_MOD_PERIODIC_HEAL = 259,
    SPELL_AURA_SCREEN_EFFECT = 260,
    SPELL_AURA_PHASE = 261,
    SPELL_AURA_IGNORE_UNIT_STATE = 262,
    SPELL_AURA_ALLOW_ONLY_ABILITY = 263,
    SPELL_AURA_264 = 264,
    SPELL_AURA_265 = 265,
    SPELL_AURA_266 = 266,
    SPELL_AURA_MOD_IMMUNE_AURA_APPLY_SCHOOL = 267,
    SPELL_AURA_MOD_ATTACK_POWER_OF_STAT_PERCENT = 268,
    SPELL_AURA_MOD_IGNORE_DAMAGE_REDUCTION_SCHOOL = 269,
    SPELL_AURA_MOD_IGNORE_TARGET_RESIST = 270,              // Possibly need swap vs 195 aura used only in 1 spell Chaos Bolt Passive
    SPELL_AURA_MOD_DAMAGE_FROM_CASTER = 271,
    SPELL_AURA_MAELSTROM_WEAPON = 272,
    SPELL_AURA_X_RAY = 273,
    SPELL_AURA_274 = 274,
    SPELL_AURA_MOD_IGNORE_SHAPESHIFT = 275,
    SPELL_AURA_276 = 276,                                   // Only "Test Mod Damage % Mechanic" spell, possible mod damage done
    SPELL_AURA_MOD_MAX_AFFECTED_TARGETS = 277,
    SPELL_AURA_MOD_DISARM_RANGED = 278,
    SPELL_AURA_MIRROR_NAME = 279,
    SPELL_AURA_MOD_TARGET_ARMOR_PCT = 280,
    SPELL_AURA_MOD_HONOR_GAIN = 281,
    SPELL_AURA_MOD_BASE_HEALTH_PCT = 282,
    SPELL_AURA_MOD_HEALING_RECEIVED = 283,                  // Possibly only for some spell family class spells
    SPELL_AURA_TRIGGER_LINKED_AURA = 284,
    SPELL_AURA_MOD_ATTACK_POWER_OF_ARMOR = 285,
    SPELL_AURA_ABILITY_PERIODIC_CRIT = 286,
    SPELL_AURA_DEFLECT_SPELLS = 287,
    SPELL_AURA_MOD_PARRY_FROM_BEHIND_PERCENT = 288,
    SPELL_AURA_289 = 289,
    SPELL_AURA_MOD_ALL_CRIT_CHANCE = 290,
    SPELL_AURA_MOD_QUEST_XP_PCT = 291,
    SPELL_AURA_OPEN_STABLE = 292,
    SPELL_AURA_ADD_MECHANIC_ABILITIES = 293,
    SPELL_AURA_STOP_NATURAL_MANA_REGEN = 294,
    SPELL_AURA_295 = 295,
    SPELL_AURA_SET_VEHICLE_ID = 296,
    SPELL_AURA_297 = 297,
    SPELL_AURA_298 = 298,
    SPELL_AURA_299 = 299,
    SPELL_AURA_300 = 300,
    SPELL_AURA_HEAL_ABSORB = 301,
    SPELL_AURA_302 = 302,
    SPELL_AURA_303 = 303,
    SPELL_AURA_FAKE_INEBRIATE = 304,
    SPELL_AURA_MOD_MINIMUM_SPEED = 305,
    SPELL_AURA_306 = 306,
    SPELL_AURA_307 = 307,
    SPELL_AURA_308 = 308,
    SPELL_AURA_309 = 309,
    SPELL_AURA_MOD_PET_AOE_DAMAGE_AVOIDANCE = 310,
    SPELL_AURA_311 = 311,
    SPELL_AURA_312 = 312,
    SPELL_AURA_313 = 313,
    SPELL_AURA_PREVENT_RESURRECTION = 314,
    SPELL_AURA_315 = 315,
    SPELL_AURA_316 = 316,
    TOTAL_AURAS = 317
};

enum AreaAuraType
{
    AREA_AURA_PARTY,
    AREA_AURA_RAID,
    AREA_AURA_FRIEND,
    AREA_AURA_ENEMY,
    AREA_AURA_PET,
    AREA_AURA_OWNER
};
/** @} */
#endif
