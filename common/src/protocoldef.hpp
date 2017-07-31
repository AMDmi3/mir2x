/*
 * =====================================================================================
 *
 *       Filename: protocoldef.hpp
 *        Created: 06/03/2016 11:40:51
 *  Last Modified: 07/30/2017 20:51:36
 *
 *    Description: 
 *
 *        Version: 1.0
 *       Revision: none
 *       Compiler: gcc
 *
 *         Author: ANHONG
 *          Email: anhonghe@gmail.com
 *   Organization: USTC
 *
 * =====================================================================================
 */
#pragma once
#include "motion.hpp"

// define of directioin
//
//               0
//            7     1
//          6    +--> 2
//            5  |  3
//               V
//               4
//
enum DirectionType: int
{
    DIR_NONE = 0,
    DIR_UP,
    DIR_UPRIGHT,
    DIR_RIGHT,
    DIR_DOWNRIGHT,
    DIR_DOWN,
    DIR_DOWNLEFT,
    DIR_LEFT,
    DIR_UPLEFT,
    DIR_MAX,
};

enum ActionType: int
{
    ACTION_NONE = 0,
    ACTION_STAND,
    ACTION_MOVE,
    ACTION_ATTACK,
    ACTION_UNDERATTACK,
    ACTION_DIE,
    ACTION_EXTENSION,
    ACTION_MAX,
};

enum ActExtType: int
{
    ACTEXT_NONE = 0,

    ACTEXT_FLYIN,
    ACTEXT_FLYOUT,

    ACTEXT_FADEIN,
    ACTEXT_FADEOUT,
};

enum CreatureType: int
{
    CREATURE_NONE = 0,
    CREATURE_PLAYER,
    CREATURE_MONSTER,
    CREATURE_NPC,
};

enum LookIDType: int
{
    LID_MIN = 0,
    LID_MAX = 2048,
};

enum DCType: int
{
    DC_NONE = 0,

    DC_PHY             = (1 << 8),
    DC_PHY_PLAIN       = (1 << 8) | 0,
    DC_PHY_WIDESWORD   = (1 << 8) | 1,
    DC_PHY_FIRE        = (1 << 8) | 2,

    DC_MAG             = (2 << 8),
    DC_MAG_FIRE        = (2 << 8) | 0,
    DC_MAG_EXPLODE     = (2 << 8) | 1,

    DC_PHY_MON         = (3 << 8),
    DC_PHY_MON_PLAIN   = (3 << 8) | 0,
    DC_PHY_MON_DUALAXE = (3 << 8) | 1,

    DC_MAG_MON         = (4 << 8),
    DC_MAG_MON_FIRE    = (4 << 8) | 0,
};

enum ECType: int
{
    EC_NONE = 0,
    EC_PLAIN,
    EC_FIRE,
    EC_ICE,
    EC_LIGHT,
    EC_WIND,
    EC_HOLY,
    EC_DARK,
    EC_PHANTOM,
    EC_MAX,
};

enum EffectType: int
{
    EFF_NONE = 0,

    EFF_HPSTEAL = (1 << 8),
    EFF_MPSTEAL = (2 << 8),
    EFF_PUNCH   = (3 << 8),
    EFF_STONE   = (4 << 8),
};

enum GenType: int
{
    GT_NONE = 0,
    GT_MALE,
    GT_FEMALE,
};

enum MonsterAttackType: int
{
    MA_NONE = 0,
    MA_NORMAL,
    MA_DOGZ,
    MA_ATTACKALL,
};

enum WeaponIDType: int
{
    WEAPON_NONE =   0,
    WEAPON_MAX  = 256,
};

enum DressIDType : int
{
    DRESS_NONE =   0,
    DRESS_MAX  = 256,
};
