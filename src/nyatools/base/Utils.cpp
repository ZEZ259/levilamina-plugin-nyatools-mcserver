#include <string>
#include <cmath>

#include "../Nyatools.h"

#include <mc/world/actor/mob.h>

namespace nya_tools
{
    std::string tickToTime(int ticks)
    {
        double time = double(ticks) / 20;
        double sec = std::fmod(time,60);
        int min = int(time/60)%60;
        int hour = int(time/60/60);
        return(std::to_string(hour)+"h "+std::to_string(min)+"min "+std::to_string(sec)+"s");
    }
    bool isMobMonster(Mob& mob)
    {
        //2816:Monster
        return ((int)mob.getEntityTypeId() & 2816) == 2816 ? true : false;
    }
    void putLog(std::string message)
    {
        NyaTools::getInstance().getSelf().getLogger().info("[Nyatools][Log]" + message);
    }
}