/*
 * =====================================================================================
 *
 *       Filename: actormessage.hpp
 *        Created: 05/03/2016 13:19:07
 *  Last Modified: 09/13/2017 19:45:42
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
#include <cstdint>
enum MessagePackType: int
{
    MPK_NONE = 0,
    MPK_OK,
    MPK_ERROR,
    MPK_BADACTORPOD,
    MPK_TIMEOUT,
    MPK_UID,
    MPK_PING,
    MPK_LOGIN,
    MPK_METRONOME,
    MPK_TRYMOVE,
    MPK_TRYSPACEMOVE,
    MPK_MOVEOK,
    MPK_SPACEMOVEOK,
    MPK_TRYLEAVE,
    MPK_LOGINOK,
    MPK_ADDRESS,
    MPK_LOGINQUERYDB,
    MPK_NETPACKAGE,
    MPK_ADDCHAROBJECT,
    MPK_BINDSESSION,
    MPK_ACTION,
    MPK_PULLCOINFO,
    MPK_NEWCONNECTION,
    MPK_QUERYMAPLIST,
    MPK_MAPLIST,
    MPK_MAPSWITCH,
    MPK_MAPSWITCHOK,
    MPK_TRYMAPSWITCH,
    MPK_QUERYMAPUID,
    MPK_QUERYLOCATION,
    MPK_LOCATION,
    MPK_PATHFIND,
    MPK_PATHFINDOK,
    MPK_ATTACK,
    MPK_UPDATEHP,
    MPK_DEADFADEOUT,
    MPK_QUERYCORECORD,
    MPK_QUERYCOCOUNT,
    MPK_COCOUNT,
    MPK_QUERYRECTUIDV,
    MPK_UIDV,
    MPK_EXP,
    MPK_NEWDROPITEM,
    MPK_SHOWDROPITEM,
    MPK_NOTIFYDEAD,
};

struct AMBadActorPod
{
    int      Type;
    uint32_t ID;
    uint32_t Respond;
};

struct AMTryLeave
{
    uint32_t UID;
    uint32_t MapID;

    int X;
    int Y;
};

union AMAddCharObject
{
    uint8_t Type;

    struct _Common
    {
        uint8_t Type;

        uint32_t MapID;
        int X;
        int Y;

        bool Random;
    }Common;

    struct _Monster
    {
        struct _Common _MemoryAlign;
        uint32_t MonsterID;
        uint32_t MasterUID;
    }Monster;

    struct _Player
    {
        struct _Common _MemoryAlign;
        uint32_t DBID;
        uint32_t JobID;
        int Level;
        int Direction;
        uint32_t SessionID;
    }Player;

    struct _NPC
    {
        struct _Common _MemoryAlign;
        uint32_t NPCID;
    }NPC;
};

struct AMLogin
{
    uint32_t DBID;
    uint32_t UID;
    uint32_t SID;
    uint32_t MapID;
    uint64_t Key;

    int X;
    int Y;
};

struct AMTrySpaceMove
{
    uint32_t UID;

    int X;
    int Y;

    bool StrictMove;
};

struct AMSpaceMoveOK
{
    void *Data;
};

struct AMTryMove
{
    uint32_t UID;
    uint32_t MapID;

    int X;
    int Y;

    int EndX;
    int EndY;

    bool AllowHalfMove;
};

struct AMMoveOK
{
    uint32_t UID;
    uint32_t MapID;

    int X;
    int Y;

    int EndX;
    int EndY;
};

struct AMLoginQueryDB
{
    uint32_t SessionID;

    uint32_t DBID;
    uint32_t MapID;
    int      MapX;
    int      MapY;
    int      Level;
    int      JobID;
    int      Direction;
};

struct AMNetPackage
{
    uint32_t SessionID;
    uint8_t  Type;

    const uint8_t *Data;
    size_t DataLen;
};

struct AMBindSession
{
    uint32_t SessionID;
};

struct AMAction
{
    uint32_t UID;
    uint32_t MapID;

    int Action;
    int ActionParam;

    int Speed;
    int Direction;

    int X;
    int Y;
    
    int AimX;
    int AimY;
};

struct AMPullCOInfo
{
    uint32_t SessionID;
};

struct AMNewConnection
{
    uint32_t SessionID;
};

struct AMMapList
{
    uint32_t MapList[256];
};

struct AMMapSwitch
{
    uint32_t MapID;
    uint32_t UID;

    int X;
    int Y;
};

struct AMTryMapSwitch
{
    uint32_t UID;
    uint32_t MapID;
    uint32_t MapUID;

    int X;
    int Y;

    int EndX;
    int EndY;
};

struct AMQueryMapUID
{
    uint32_t MapID;
};

struct AMUID
{
    uint32_t UID;
};

struct AMMapSwitchOK
{
    void *Data;

    int X;
    int Y;
};

struct AMQueryLocation
{
    uint32_t UID;
    uint32_t MapID;
};

struct AMLocation
{
    uint32_t UID;
    uint32_t MapID;
    uint32_t RecordTime;
    
    int X;
    int Y;
    int Direction;
};

struct AMPathFind
{
    uint32_t UID;
    uint32_t MapID;

    int MaxStep;
    bool CheckCO;

    int X;
    int Y;
    int EndX;
    int EndY;
};

struct AMPathFindOK
{
    uint32_t UID;
    uint32_t MapID;

    struct _Point
    {
        int X;
        int Y;
    }Point[4];
};

struct AMAttack
{
    uint32_t UID;
    uint32_t MapID;

    int X;
    int Y;

    int Type;
    int Damage;
    int Element;
    int Effect[32];
};

struct AMUpdateHP
{
    uint32_t UID;
    uint32_t MapID;

    int X;
    int Y;

    uint32_t HP;
    uint32_t HPMax;
};

struct AMDeadFadeOut
{
    uint32_t UID;
    uint32_t MapID;

    int X;
    int Y;
};

struct AMQueryCORecord
{
    uint32_t UID;
    uint32_t MapID;

    int X;
    int Y;

    uint32_t SessionID;
};

struct AMQueryCOCount
{
    uint32_t MapID;
    struct _Check
    {
        bool NPC;
        bool Player;
        bool Monster;
    }Check;

    struct _CheckParam
    {
        // initialize and use it as needed
        // collection to put all checking paramters here
        bool     Male;
        uint32_t MonsterID;
    }CheckParam;
};

struct AMCOCount
{
    uint32_t Count;
};

struct AMQueryRectUIDV
{
    uint32_t MapID;

    int X;
    int Y;
    int W;
    int H;
};

struct AMUIDV
{
    uint32_t UIDV[128];
};

struct AMExp
{
    int Exp;
};

struct AMNewDropItem
{
    uint32_t UID;
    int X;
    int Y;

    uint32_t ID;
    int Value;
};

struct AMShowDropItem
{
    uint32_t ID;
    int X;
    int Y;
};

struct AMNotifyDead
{
    uint32_t UID;
};
