/*
- mc/FixPigmanCD.cpp
*/
#include "mc.h"
#include "../hooks/HookPortalSpawnPigman.h"

#include "ll/api/memory/Hook.h"
#include "ll/api/service/Bedrock.h"

#include "mc/deps/core/math/Vec3.h"
#include "mc/world/actor/ActorDefinitionIdentifier.h"
#include "mc/world/level/BlockPos.h"
#include "mc/world/level/BlockSource.h"
#include "mc/world/level/Level.h"
#include "mc/world/level/Spawner.h"
#include "mc/world/level/block/Block.h"
#include "mc/world/level/block/BlockSupportType.h"
#include "mc/world/level/block/PortalBlock.h"
namespace nya_tools::mc
{
    void FixPigmanCD(bool bl)
    {
        nya_tools::hooks::RegisterFixPigmanCDHook(bl);
    }
}