/*
- nya/PauseNoPlayers.cpp
*/
#include "../Nyatools.h"

#include <ll/api/event/ListenerBase.h>
#include <ll/api/mod/NativeMod.h>
#include <ll/api/event/EventBus.h>
#include <ll/api/event/ListenerBase.h>
#include <ll/api/event/player/PlayerJoinEvent.h>
#include <ll/api/event/player/PlayerDisconnectEvent.h>
#include <ll/api/event/player/PlayerConnectEvent.h>
#include <ll/api/service/Bedrock.h>
#include <ll/api/i18n/I18n.h>

#include <mc/world/level/Level.h>
#include <mc/world/level/storage/GameRules.h>
#include <mc/world/level/storage/GameRule.h>

using namespace ll::i18n_literals;

namespace nya_tools::funcs
{
    auto& eventBus = ll::event::EventBus::getInstance();
    ll::event::ListenerPtr listenerPlayerJoin; 
    ll::event::ListenerPtr listenerPlayerDisconnect;

    void func1Enable()
    {
        if(ll::service::bedrock::getLevel()->getPlayerList().size() == 0)
        {
            ll::service::bedrock::getLevel()->getGameRules().mGameRules->at(1).mValue = false;
            nya_tools::NyaTools::getInstance().getSelf().getLogger().info("infoPauseNoPlayersDisconnect"_tr());
        }
        listenerPlayerJoin = eventBus.emplaceListener<ll::event::PlayerConnectEvent>([](ll::event::PlayerConnectEvent& event)
        { 
            //启用昼夜更替
            ll::service::bedrock::getLevel()->getGameRules().mGameRules->at(1).mValue = true;
            nya_tools::NyaTools::getInstance().getSelf().getLogger().info("infoPauseNoPlayersJoin"_tr());
        });
        listenerPlayerDisconnect = eventBus.emplaceListener<ll::event::PlayerDisconnectEvent>([](ll::event::PlayerDisconnectEvent& event)
        { 
            //当服务器空闲时禁用昼夜更替
            if(ll::service::bedrock::getLevel()->getPlayerList().size() == 1)
            {
                ll::service::bedrock::getLevel()->getGameRules().mGameRules->at(1).mValue = false;
                nya_tools::NyaTools::getInstance().getSelf().getLogger().info("infoPauseNoPlayersDisconnect"_tr());
            }
        });
    }
    void func1Disable()
    {
        ll::service::bedrock::getLevel()->getGameRules().mGameRules->at(1).mValue = true;
        eventBus.removeListener(listenerPlayerJoin);
        eventBus.removeListener(listenerPlayerDisconnect);
    }
}