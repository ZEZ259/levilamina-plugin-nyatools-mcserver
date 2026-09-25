/*
- commands/nyarules.cpp
- 指令:nyarules
- 说明:游戏规则指令
*/
#include "../Config.h"
#include "../mc/mc.h"

#include <ll/api/mod/NativeMod.h>
#include <ll/api/i18n/I18n.h>
#include <ll/api/command/CommandHandle.h>
#include <ll/api/command/CommandRegistrar.h>
#include "ll/api/command/runtime/ParamKind.h"
#include "ll/api/command/runtime/RuntimeOverload.h"
#include <ll/api/Config.h>

#include <mc/server/commands/CommandOrigin.h>
#include <mc/server/commands/CommandOutput.h>
#include <string>

using namespace ll::i18n_literals;

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
                    nya_tools::mc::FixPigmanCD(true);
                else 
                    nya_tools::mc::FixPigmanCD(false);
                output.success("infoMcrulesSuccess"_tr("FixPigmanCD",std::to_string(self["isEnabled"].get<ll::command::ParamKind::Bool>())));
            });

        commandMcrules.runtimeOverload()
            .text("DisablePhantomSpawn")
            .required("isEnabled", ll::command::ParamKind::Bool)
            .execute([&config](CommandOrigin const& origin, CommandOutput& output, ll::command::RuntimeCommand const& self)
            {
                //指令实现
                //内容
                if (self["isEnabled"].get<ll::command::ParamKind::Bool>())
                    config.enableDisablePhantomSpawn = true;
                else
                    config.enableDisablePhantomSpawn = false;
                output.success("infoMcrulesSuccess"_tr("DisablePhantomSpawn",std::to_string(self["isEnabled"].get<ll::command::ParamKind::Bool>())));
            });

        commandMcrules.runtimeOverload()
            .text("FakePeaceful")
            .required("isEnabled", ll::command::ParamKind::Bool)
            .execute([&config](CommandOrigin const& origin, CommandOutput& output, ll::command::RuntimeCommand const& self)
            {
                //指令实现
                //内容
                if (self["isEnabled"].get<ll::command::ParamKind::Bool>())
                    config.enableFakePeaceful=true;
                else 
                    config.enableFakePeaceful=false;
                output.success("infoMcrulesSuccess"_tr("FakePeaceful",std::to_string(self["isEnabled"].get<ll::command::ParamKind::Bool>())));
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
                output.success("infoMcrulesSuccess"_tr("ActorGrowth",std::to_string(param.mode)));
            });
    }
}