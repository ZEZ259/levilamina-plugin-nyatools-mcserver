/*
- commands/nyarules.cpp
- 指令:nyarules
- 说明:游戏规则指令
*/
#include "../Config.h"
#include "../nya/PauseNoPlayers.h"

#include <ll/api/mod/NativeMod.h>
#include <ll/api/command/CommandHandle.h>
#include <ll/api/command/CommandRegistrar.h>
#include "ll/api/command/runtime/RuntimeOverload.h"
#include <ll/api/Config.h>

#include <mc/server/commands/CommandOrigin.h>
#include <mc/server/commands/CommandOutput.h>

namespace nya_tools::command
{
    void registerNyarules(Config& config)
    {
        auto& commandNyarules = ll::command::CommandRegistrar::getInstance(true)
                        .getOrCreateCommand("nyarules", "游戏规则指令", CommandPermissionLevel::Any);
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
                    output.success("已开启服务器空闲时关闭昼夜更替。");
                    config.enablePauseGameWhenNoPlayers = true;
                }
                else 
                {
                    nya_tools::funcs::func1Disable();
                    output.success("已禁用服务器空闲时关闭昼夜更替。");
                    config.enablePauseGameWhenNoPlayers = false;
                }
            });

    }
}