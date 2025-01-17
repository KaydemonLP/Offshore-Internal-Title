//========= Copyright � 1996-2005, Valve Corporation, All rights reserved. ============//
// Authors: 
// Iv�n Bravo Bravo (linkedin.com/in/ivanbravobravo), 2017

#include "cbase.h"
#include "bots\bot_manager.h"

#include "bots\bot.h"

#ifdef INSOURCE_DLL
#include "in_utils.h"
#else
#include "bots\in_utils.h"
#endif

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

CBotManager g_BotManager;
CBotManager *TheBots = &g_BotManager;

void Bot_RunAll() {
    for ( int it = 0; it <= gpGlobals->maxClients; ++it ) {
        CPlayer *pPlayer = ToInPlayer( UTIL_PlayerByIndex(it) );

        if ( !pPlayer )
            continue;

        if ( !pPlayer->IsBot() )
            continue;

        pPlayer->GetBotController()->Update();
    }
}

//================================================================================
//================================================================================
CBotManager::CBotManager() : CAutoGameSystemPerFrame("BotManager")
{
}

//================================================================================
//================================================================================
bool CBotManager::Init()
{
    Utils::InitBotTrig();
    return true;
}

//================================================================================
//================================================================================
void CBotManager::LevelInitPostEntity()
{
    
}

//================================================================================
//================================================================================
void CBotManager::LevelShutdownPreEntity()
{
#if defined( INSOURCE_DLL ) || defined( OFFSHORE_DLL )
    for ( int it = 0; it <= gpGlobals->maxClients; ++it ) {
        CPlayer *pPlayer = ToInPlayer( UTIL_PlayerByIndex( it ) );

        if ( !pPlayer )
            continue;

        if ( !pPlayer->IsBot() )
            continue;
#ifdef INSOURCE_DLL
        pPlayer->Kick();
#else
		pPlayer->GetBotController()->Kick();
#endif
    }

    engine->ServerExecute();
#endif
}

//================================================================================
//================================================================================
void CBotManager::FrameUpdatePreEntityThink()
{
// This is literally the entire bot system  think, why is it disabled by default?
#if defined( INSOURCE_DLL ) || defined( OFFSHORE_DLL )
    Bot_RunAll();
#endif
}

//================================================================================
//================================================================================
void CBotManager::FrameUpdatePostEntityThink()
{

}