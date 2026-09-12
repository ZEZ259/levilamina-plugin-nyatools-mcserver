#include <string>
#define MOD_DEVELOPING

#include "../event.h"
#include "../../config.h"
#include "../../nyatools.h"
#include "../../base/Utils.h"

#include "ll/api/event/EventBus.h"
#include "ll/api/event/ListenerBase.h"
#include <ll/api/event/world/SpawnMobEvent.h>

namespace nya_tools::events::listeners
{
    auto& bus = ll::event::EventBus::getInstance();
    ll::event::ListenerPtr listenerActorSpawn;
    void registerListenerActorSpawn(bool bl,Config& config)
    {
        if (!bl)
        {
            bus.removeListener(listenerActorSpawn);
            return;
        }
        listenerActorSpawn = bus.emplaceListener<ll::event::world::SpawnedMobEvent>([&config](ll::event::world::SpawnedMobEvent& event)
        {
            auto mob = event.mob();
            if (mob == nullptr) 
            {
                return;
            }
            //DisablePhantomSpawn:禁用幻翼生成
            if(config.enableDisablePhantomSpawn)
            {
                if (mob->getEntityTypeId() == ActorType::Phantom) 
                {
                    mob->remove();

                #ifdef MOD_DEVELOPING
                    NyaTools::getInstance().getSelf().getLogger().info("检测到幻翼生成，已移除。");
                #endif
                }
            }

            //FakePeaceful:伪和平
            if(config.enableFakePeaceful)
            {
                //2816:Monster
                if (isMobMonster(mob) && mob->getEntityTypeId() != ActorType::Phantom) 
                {
                    mob->remove();

                #ifdef MOD_DEVELOPING
                    NyaTools::getInstance().getSelf().getLogger().info("检测到怪物生成，已移除。");
                #endif
                }
            }
        });
    }
}