#include "mc.h"
#include "../events/listeners/listeners.h"

namespace nya_tools::mc
{
    void DisablePhantomSpawn(bool bl, Config& config)
    {
        nya_tools::events::listeners::registerListenerActorSpawn(bl, config);
    }
}