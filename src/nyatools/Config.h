#pragma once

namespace nya_tools
{

struct Config {
    int     version = 1;                                                // 版本号
    
    bool    enableFixPigmanCD = false;                                  // 是否启用去除猪人传送延迟
    bool    enablePauseGameWhenNoPlayers = true;                        // 当服务器没有玩家时关闭昼夜更替
    bool    enableDisablePhantomSpawn = true;                           // 禁止幻翼生成
};
}