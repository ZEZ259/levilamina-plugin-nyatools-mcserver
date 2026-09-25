#include <string>
#include <cmath>

#include "../Nyatools.h"

#include <mc/world/actor/mob.h>

namespace nya_tools
{
    std::string tickToTime(int ticks);
    bool isMobMonster(Mob& mob);
    void putLog(std::string message);
}