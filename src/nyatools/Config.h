#pragma once

namespace nya_tools
{

struct Config {
    int     version = 1;                                                    // 版本号
    
    bool    enableFixPigmanCD               = false;                        // 是否启用去除猪人传送延迟
    bool    enablePauseGameWhenNoPlayers    = true;                         // 当服务器没有玩家时关闭昼夜更替
    bool    enableDisablePhantomSpawn       = false;                        // 禁止幻翼生成
    bool    enableFakePeaceful              = false;                        // 伪和平
    int     actorGrowthMode                 = 0;                            // 伪和平难度
            /*
            0:正常生长 
            1:禁止所有生物生长 
            2:命名带有"§:§!"的生物禁止生长
            */ 

};
}