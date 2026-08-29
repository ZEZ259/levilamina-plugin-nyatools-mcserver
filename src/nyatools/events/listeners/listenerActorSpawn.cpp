#define MOD_DEVELOPING

#include "../event.h"
#include "../../config.h"
#include "../../nyatools.h"

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
        listenerActorSpawn = bus.emplaceListener<ll::event::world::SpawnedMobEvent>([config](ll::event::world::SpawnedMobEvent& event)
        {
            //DisablePhantomSpawn:禁用幻翼生成
            if(config.enableDisablePhantomSpawn)
            {
                auto mob = event.mob();
                if (mob == nullptr) 
                {
                    return;
                }
                if (mob->getEntityTypeId() == ActorType::Phantom) 
                {
                    mob->remove();

                #ifdef MOD_DEVELOPING
                    NyaTools::getInstance().getSelf().getLogger().info("检测到幻翼生成，已移除。");
                #endif
                }
            }    
        });
    }
}