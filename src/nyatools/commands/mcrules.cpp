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
#include "ll/api/command/runtime/ParamKind.h"
#include "ll/api/command/runtime/RuntimeOverload.h"
#include <ll/api/Config.h>

#include <mc/server/commands/CommandOrigin.h>
#include <mc/server/commands/CommandOutput.h>
#include <string>

namespace nya_tools::command
{
    void registerMcrules(Config& config)
    {
        auto& commandMcrules = ll::command::CommandRegistrar::getInstance(true)
                        .getOrCreateCommand("mcrules", "游戏规则指令", CommandPermissionLevel::Any);
        commandMcrules.runtimeOverload()
            .text("FixPigmanCD")
            .required("isEnabled", ll::command::ParamKind::Bool)
            .execute([&config](CommandOrigin const& origin, CommandOutput& output, ll::command::RuntimeCommand const& self)
            {
                //指令实现
                //内容
                if (self["isEnabled"].get<ll::command::ParamKind::Bool>())
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

        commandMcrules.runtimeOverload()
            .text("DisablePhantomSpawn")
            .required("isEnabled", ll::command::ParamKind::Bool)
            .execute([&config](CommandOrigin const& origin, CommandOutput& output, ll::command::RuntimeCommand const& self)
            {
                //指令实现
                //内容
                if (self["isEnabled"].get<ll::command::ParamKind::Bool>())
                {
                    config.enableDisablePhantomSpawn = true;
                    output.success("已禁用幻翼生成。");
                }
                else 
                {
                    config.enableDisablePhantomSpawn = true;
                    output.success("已恢复幻翼生成。");
                }
            });

        commandMcrules.runtimeOverload()
            .text("FakePeaceful")
            .required("isEnabled", ll::command::ParamKind::Bool)
            .execute([&config](CommandOrigin const& origin, CommandOutput& output, ll::command::RuntimeCommand const& self)
            {
                //指令实现
                //内容
                if (self["isEnabled"].get<ll::command::ParamKind::Bool>())
                {
                    config.enableFakePeaceful=true;
                    output.success("已启用伪和平。");
                }
                else 
                {
                    config.enableFakePeaceful=false;
                    output.success("已禁用伪和平。");
                }
            });

        struct mcrulesActorGrowth
        {
            mc::ActorGrowthMode mode;
        };
        
        commandMcrules.overload<mcrulesActorGrowth>()
            .text("ActorGrowth")
            .required("mode")
            .execute([&config](CommandOrigin const& origin, CommandOutput& output, mcrulesActorGrowth const& param)
            {
                //指令实现
                //内容
                mc::ActorGrowth(true,param.mode);
                config.actorGrowthMode=param.mode;
                output.success("已将ActorGrowth设置为{}",std::to_string(param.mode));
            });
    }
}