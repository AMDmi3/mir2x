/*
 * =====================================================================================
 *
 *       Filename: processrunnet.cpp
 *        Created: 08/31/2015 03:43:46
 *  Last Modified: 09/26/2017 00:17:45
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

#include <memory>
#include <cstring>

#include "log.hpp"
#include "game.hpp"
#include "monster.hpp"
#include "sysconst.hpp"
#include "pngtexdbn.hpp"
#include "sdldevice.hpp"
#include "sdldevice.hpp"
#include "processrun.hpp"
#include "dbcomrecord.hpp"

// we get all needed initialization info for init the process run
void ProcessRun::Net_LOGINOK(const uint8_t *pBuf, size_t nLen)
{
    if(pBuf && nLen && (nLen == sizeof(SMLoginOK))){
        SMLoginOK stSMLOK;
        std::memcpy(&stSMLOK, pBuf, nLen);

        LoadMap(stSMLOK.MapID);
        m_MyHero = new MyHero(stSMLOK.UID, stSMLOK.DBID, (bool)(stSMLOK.Male), 0, this, 
                {
                    ACTION_STAND,
                    0,
                    stSMLOK.Direction,
                    stSMLOK.X,
                    stSMLOK.Y,
                    stSMLOK.MapID
                });

        CenterMyHero();
        m_CreatureRecord[m_MyHero->UID()] = m_MyHero;
    }
}

void ProcessRun::Net_ACTION(const uint8_t *pBuf, size_t)
{
    SMAction stSMA;
    std::memcpy(&stSMA, pBuf, sizeof(stSMA));

    ActionNode stAction
    {
        stSMA.Action,
        stSMA.ActionParam,
        stSMA.Speed,
        stSMA.Direction,
        stSMA.X,
        stSMA.Y,
        stSMA.AimX,
        stSMA.AimY,
        stSMA.AimUID,
        stSMA.MapID
    };

    if(stSMA.MapID == MapID()){
        if(auto pCreature = RetrieveUID(stSMA.UID)){
            pCreature->ParseNewAction(stAction, true);
            switch(stAction.Action){
                case ACTION_SPACEMOVE:
                    {
                        if(stSMA.UID == m_MyHero->UID()){
                            CenterMyHero();
                        }
                        break;
                    }
                default:
                    {
                        break;
                    }
            }
        }else{
            // can't find it
            // we have to create a new actor but need more information
            CMQueryCORecord stCMQCOR;
            stCMQCOR.UID   = stSMA.UID;
            stCMQCOR.MapID = stSMA.MapID;
            stCMQCOR.X     = stSMA.X;
            stCMQCOR.Y     = stSMA.Y;

            extern Game *g_Game;
            g_Game->Send(CM_QUERYCORECORD, stCMQCOR);
        }
    }else{
        if(m_MyHero && m_MyHero->UID() == stSMA.UID){
            LoadMap(stSMA.MapID);

            auto nUID       = m_MyHero->UID();
            auto nDBID      = m_MyHero->DBID();
            auto bGender    = m_MyHero->Gender();
            auto nDress     = m_MyHero->Dress();
            auto nDirection = m_MyHero->CurrMotion().Direction;

            ClearCreature();
            m_MyHero = new MyHero(nUID, nDBID, bGender, nDress, this, {ACTION_STAND, 0, nDirection, stSMA.X, stSMA.Y, stSMA.MapID});
            m_CreatureRecord[m_MyHero->UID()] = m_MyHero;

            CenterMyHero();
            m_MyHero->ParseNewAction(stAction, true);
        }
    }
}

void ProcessRun::Net_CORECORD(const uint8_t *pBuf, size_t)
{
    SMCORecord stSMCOR;
    std::memcpy(&stSMCOR, pBuf, sizeof(stSMCOR));

    if(stSMCOR.Common.MapID == MapID()){
        ActionNode stAction
        {
            stSMCOR.Common.Action,
            stSMCOR.Common.ActionParam,
            stSMCOR.Common.Speed,
            stSMCOR.Common.Direction,
            stSMCOR.Common.X,
            stSMCOR.Common.Y,
            stSMCOR.Common.EndX,
            stSMCOR.Common.EndY,
            stSMCOR.Common.MapID,
        };

        auto pRecord = m_CreatureRecord.find(stSMCOR.Common.UID);
        if(pRecord == m_CreatureRecord.end()){
            switch(stSMCOR.Type){
                case CREATURE_MONSTER:
                    {
                        if(auto pMonster = Monster::Create(stSMCOR.Common.UID, stSMCOR.Monster.MonsterID, this, stAction)){
                            m_CreatureRecord[stSMCOR.Common.UID] = pMonster;
                        }
                        break;
                    }
                case CREATURE_PLAYER:
                    {
                        auto pHero = new Hero(stSMCOR.Common.UID, stSMCOR.Player.DBID, true, 0, this, stAction);
                        m_CreatureRecord[stSMCOR.Common.UID] = pHero;
                        break;
                    }
                default:
                    {
                        break;
                    }
            }
        }else{
            if(pRecord->second){
                pRecord->second->ParseNewAction(stAction, true);
            }
        }
    }
}

void ProcessRun::Net_UPDATEHP(const uint8_t *pBuf, size_t)
{
    SMUpdateHP stSMUHP;
    std::memcpy(&stSMUHP, pBuf, sizeof(stSMUHP));

    if(stSMUHP.MapID == MapID()){
        auto pRecord = m_CreatureRecord.find(stSMUHP.UID);
        if((pRecord != m_CreatureRecord.end()) && pRecord->second){
            pRecord->second->UpdateHP(stSMUHP.HP, stSMUHP.HPMax);
        }
    }
}

void ProcessRun::Net_DEADFADEOUT(const uint8_t *pBuf, size_t)
{
    SMDeadFadeOut stSMDFO;
    std::memcpy(&stSMDFO, pBuf, sizeof(stSMDFO));

    if(stSMDFO.MapID == MapID()){
        auto pRecord = m_CreatureRecord.find(stSMDFO.UID);
        if((pRecord != m_CreatureRecord.end()) && pRecord->second){
            pRecord->second->DeadFadeOut();
        }
    }
}

void ProcessRun::Net_EXP(const uint8_t *pBuf, size_t)
{
    SMExp stSME;
    std::memcpy(&stSME, pBuf, sizeof(stSME));

    if(stSME.Exp){
        AddOPLog(OUTPORT_CONTROLBOARD, 2, "", u8"你获得了经验值%d", (int)(stSME.Exp));
    }
}

void ProcessRun::Net_SHOWDROPITEM(const uint8_t *pBuf, size_t)
{
    SMShowDropItem stSMSDI;
    std::memcpy(&stSMSDI, pBuf, sizeof(stSMSDI));

    m_GroundItemList.emplace_back(stSMSDI.ID, stSMSDI.X, stSMSDI.Y);
    AddOPLog(OUTPORT_CONTROLBOARD, 2, "", u8"发现(%d, %d): %s", stSMSDI.X, stSMSDI.Y, DBCOM_ITEMRECORD(stSMSDI.ID).Name);
}

void ProcessRun::Net_FIREMAGIC(const uint8_t *pBuf, size_t)
{
    SMFireMagic stSMFM;
    std::memcpy(&stSMFM, pBuf, sizeof(stSMFM));

    if(auto &rstMR = DBCOM_MAGICRECORD(stSMFM.Magic)){
        AddOPLog(OUTPORT_CONTROLBOARD, 2, "", u8"使用魔法: %s", rstMR.Name);

        const GfxEntry *pEntry = nullptr;
        if(stSMFM.UID != m_MyHero->UID()){
            if(!(pEntry && *pEntry)){ pEntry = &(rstMR.GetGfxEntry(u8"启动")); }
            if(!(pEntry && *pEntry)){ pEntry = &(rstMR.GetGfxEntry(u8"开始")); }
            if(!(pEntry && *pEntry)){ pEntry = &(rstMR.GetGfxEntry(u8"运行")); }
            if(!(pEntry && *pEntry)){ pEntry = &(rstMR.GetGfxEntry(u8"结束")); }
        }else{
            if(!(pEntry && *pEntry)){ pEntry = &(rstMR.GetGfxEntry(u8"开始")); }
            if(!(pEntry && *pEntry)){ pEntry = &(rstMR.GetGfxEntry(u8"运行")); }
            if(!(pEntry && *pEntry)){ pEntry = &(rstMR.GetGfxEntry(u8"结束")); }
        }

        if(pEntry && *pEntry){
            switch(pEntry->Type){
                case EGT_BOUND:
                    {
                        if(auto pCreature = RetrieveUID(stSMFM.AimUID)){
                            pCreature->AddAttachMagic(stSMFM.Magic, 0, pEntry->Stage);
                        }
                        break;
                    }
                case EGT_FIXED:
                    {
                        auto pMagic = new IndepMagic
                        {
                            stSMFM.UID,
                            stSMFM.Magic,
                            stSMFM.MagicParam,
                            pEntry->Stage,
                            stSMFM.Direction,
                            stSMFM.X,
                            stSMFM.Y,
                            stSMFM.AimX,
                            stSMFM.AimY,
                            stSMFM.AimUID
                        };

                        m_IndepMagicList.emplace_back(pMagic);
                        break;
                    }
                case EGT_SHOOT:
                    {
                        break;
                    }
                case EGT_FOLLOW:
                    {
                        break;
                    }
                default:
                    {
                        break;
                    }
            }
        }
    }
}
