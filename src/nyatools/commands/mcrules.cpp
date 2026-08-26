/*
- commands/nyarules.cpp
- 指令:nyarules
- 说明:游戏规则指令
*/
#include "../Config.h"
#include "../mc/mc.h"

#include <ll/api/mod/NativeMod.h>
#include <ll/api/command/CommandHandle.h>
#include <ll/api/command/CommandRegistrar.h>
#include "ll/api/command/runtime/RuntimeOverload.h"
#include <ll/api/Config.h>

#include <mc/server/commands/CommandOrigin.h>
#include <mc/server/commands/CommandOutput.h>

namespace nya_tools::command
{
    enum mcrulesEnum
    {
        Unknown             = 0,                                    //未知规则
        FixPigmanCD         = 1,                                    //修复猪人CD
    };

    mcrulesEnum getMcrulesEnumFromString(const std::string& ruleName)
    {
        if (ruleName == "FixPigmanCD")
        {
            return FixPigmanCD;
        }
        else
        {
            return Unknown;
        }
    }

    void registerMcrules(Config& config)
    {
        auto& commandMcrules = ll::command::CommandRegistrar::getInstance(true)
                        .getOrCreateCommand("mcrules", "游戏规则指令", CommandPermissionLevel::Any);
        commandMcrules.runtimeOverload()
            .text("FixPigmanCD")
            .required("isEnable", ll::command::ParamKind::Bool)
            .execute([&config](CommandOrigin const& origin, CommandOutput& output, ll::command::RuntimeCommand const& self)
            {
                //指令实现
                //内容
                if (self["isEnable"].get<ll::command::ParamKind::Bool>())
                {
                    nya_tools::mc::FixPigmanCD(true);
                    output.success("已禁用僵尸猪人传送CD。");
                }
                else 
                {
                    nya_tools::mc::FixPigmanCD(false);
                    output.success("已恢复僵尸猪人传送CD。");
                }
            });
    }
}