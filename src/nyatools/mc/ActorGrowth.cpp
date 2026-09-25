#include "mc.h"
#include "../Config.h"
#include "../hooks/Hooks.h"
namespace nya_tools::mc
{
    void ActorGrowth(bool bl, ActorGrowthMode mode)
    {
        mode == Normal?nya_tools::hooks::RegisterActorGrowUpHook(false,0):nya_tools::hooks::RegisterActorGrowUpHook(bl,(int)mode);
    }
}