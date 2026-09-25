/*
- commands/nyarules.cpp
- 指令:nyarules
- 说明:游戏规则指令
*/
#include "../Config.h"
#include "../nya/PauseNoPlayers.h"

#include <ll/api/mod/NativeMod.h>
#include <ll/api/i18n/I18n.h>
#include <ll/api/command/CommandHandle.h>
#include <ll/api/command/CommandRegistrar.h>
#include "ll/api/command/runtime/RuntimeOverload.h"
#include <ll/api/Config.h>

#include <mc/server/commands/CommandOrigin.h>
#include <mc/server/commands/CommandOutput.h>

using namespace ll::i18n_literals;

namespace nya_tools::command
{
    void registerNyarules(Config& config)
    {
        auto& commandNyarules = ll::command::CommandRegistrar::getInstance(true)
                        .getOrCreateCommand("nyarules", "descriptionNyarule"_tr(), CommandPermissionLevel::Any);
        commandNyarules.runtimeOverload()
            .text("PauseWhenNoPlayers")
            .required("isEnable", ll::command::ParamKind::Bool)
            .execute([&config](CommandOrigin const& origin, CommandOutput& output, ll::command::RuntimeCommand const& self)
            {
                //指令实现
                //内容
                //func1:空闲关闭昼夜更替
                if (self["isEnable"].get<ll::command::ParamKind::Bool>())
                {
                    nya_tools::funcs::func1Enable();
                    config.enablePauseGameWhenNoPlayers = true;
                }
                else 
                {
                    nya_tools::funcs::func1Disable();
                    config.enablePauseGameWhenNoPlayers = false;
                }
                output.success("infoNyarulesSuccess"_tr("PauseWhenNoPlayers",self["isEnable"].get<ll::command::ParamKind::Bool>()));
            });

    }
}