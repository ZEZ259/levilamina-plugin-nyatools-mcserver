#include "Nyatools.h"
#include "Config.h"
#include "commands/command.h"
#include "mc/mc.h"
#include "nya/PauseNoPlayers.h"

#include <cstddef>
#include <ll/api/mod/NativeMod.h>
#include "ll/api/event/ListenerBase.h"
#include "ll/api/mod/RegisterHelper.h"
#include <ll/api/Config.h>
#include <ll/api/command/CommandHandle.h>
#include <ll/api/command/CommandRegistrar.h>
#include <ll/api/data/KeyValueDB.h>
#include <ll/api/event/EventBus.h>
#include <ll/api/event/player/PlayerJoinEvent.h>
#include <ll/api/event/player/PlayerUseItemEvent.h>
#include <ll/api/event/player/PlayerDisconnectEvent.h>
#include <ll/api/event/player/PlayerConnectEvent.h>
#include <ll/api/event/world/SpawnMobEvent.h>
#include <ll/api/service/Bedrock.h>
#include <ll/api/chrono/GameChrono.h>

#include "mc/world/level/Level.h"
#include "mc\server\commands\MinecraftCommands.h"
#include "mc\server\commands\CommandContext.h"
#include "mc\server\commands\CommandOrigin.h"
#include "mc/world/level/storage/GameRules.h"
#include "mc/world/level/storage/GameRule.h"
#include <mc/server/commands/CommandOrigin.h>
#include <mc/server/commands/CommandOutput.h>
#include <mc/world/actor/player/Player.h>
#include <mc/world/actor/monster/PigZombie.h>
#include <mc/world/actor/item/ItemActor.h>
#include <mc/world/item/ItemStack.h>
#include <string>


namespace nya_tools
{
    Config config;

    //初始化
    NyaTools& NyaTools::getInstance() 
    {
    static NyaTools instance;
    return instance;
    }
    bool NyaTools::load() {
        getSelf().getLogger().debug("Loading...");
        return true;
    }

    void applyConfig()
    {
        //config.enablePauseGameWhenNoPlayers
        if(config.enablePauseGameWhenNoPlayers && ll::service::bedrock::getLevel()->getPlayerList().size() == 0)
            nya_tools::funcs::func1Enable();
        //config.enableDisablePhantomSpawn
        if(config.enableDisablePhantomSpawn)
            nya_tools::mc::DisablePhantomSpawn(true, config);
        //config.enableFixPigmanCD
        if(config.enableFixPigmanCD)
            nya_tools::mc::FixPigmanCD(true);
    }

    //启用模组
    bool NyaTools::enable() 
    {
        getSelf().getLogger().debug("Enabling...");
        auto commandRegistry = ll::service::getCommandRegistry();
        if (!commandRegistry) 
        {
            throw std::runtime_error("failed to get command registry");
        }
        
        //载入指令
        command::registerNyarules(config);  //设置模组规则
        command::registerMcrules(config);   //设置游戏规则
        applyConfig();
        return true;
    }

    bool NyaTools::disable() {
        getSelf().getLogger().debug("Disabling...");
        auto& eventBus = ll::event::EventBus::getInstance();
        const auto& configFilePath = getSelf().getConfigDir() / "config.json";
        if (!ll::config::loadConfig(config, configFilePath)) 
        {
            getSelf().getLogger().warn("Cannot load configurations from {}", configFilePath);
            getSelf().getLogger().info("Saving default configurations");

            if (!ll::config::saveConfig(config, configFilePath)) {
            getSelf().getLogger().error("Cannot save default configurations to {}", configFilePath);
            }
        }
        return true;
    }

}   //namespace nya_tools

LL_REGISTER_MOD(nya_tools::NyaTools, nya_tools::NyaTools::getInstance());//加载