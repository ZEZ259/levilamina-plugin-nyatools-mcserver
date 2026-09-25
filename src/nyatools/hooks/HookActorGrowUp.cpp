//#define NYA_DEBUG
#include "../Config.h"
#include "../Nyatools.h"
#include "../base/Utils.h"


#include <ll/api/i18n/I18n.h>
#include "mc/world/actor/Actor.h"
#include "ll/api/memory/Hook.h"

#include "mc/entity/components/AgeableComponent.h"
#include "mc/entity/components/ActorOwnerComponent.h"
#include "mc/world/events/BlockEventDispatcherToken.h"
#include <string>

using namespace ll::i18n_literals;
using namespace ll::literals::memory_literals;

namespace nya_tools::hooks
{
int _mode=0;
LL_STATIC_HOOK(
    HookActorGrowUp,
    ll::memory::HookPriority::Normal,
    "48 89 5C 24 ?? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ?? ?? ?? ?? 48 81 EC ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 85 ?? ?? ?? ?? 48 8B FA 4C 8B 31"_sig,
        //void tickAgeableComponent(const struct ActorOwnerComponent *a1, BlockEventDispatcherToken *a2)
    void,
    const ActorOwnerComponent* actorOwnerComponent,
    BlockEventDispatcherToken* dispatcherToken
) {
    if (_mode==1) return;
    auto& actor = *actorOwnerComponent->mActor.get();
    if(_mode==2 && actor.getNameTag().substr(0,6) == "§:§!") {
        #ifdef NYA_DEBUG
        putLog("已阻止生物成长，生物名称标签为："+actor.getNameTag());
        #endif
        return;
    }
    return origin(actorOwnerComponent, dispatcherToken);
}

void RegisterActorGrowUpHook(bool bl, int mode) {
    _mode = mode;
    bl ? HookActorGrowUp::hook() : HookActorGrowUp::unhook();
}
}
