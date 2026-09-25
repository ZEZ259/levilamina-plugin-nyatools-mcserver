#include "../Config.h"
namespace nya_tools::mc
{
    enum                    ActorGrowthMode{
                                Normal = 0, //正常生长
                                Disabled = 1, //禁止所有生物生长
                                Selected = 2, //命名带有"§:§!"的生物禁止生长
                                };

    void                    FixPigmanCD(bool bl);                                                       //处理传送门猪人CD
    void                    ActorGrowth(bool bl, ActorGrowthMode mode);                                 //处理生物成长
}