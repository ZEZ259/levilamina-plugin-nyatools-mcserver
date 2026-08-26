#include <string>
#include <cmath>

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
}