#pragma once

namespace nya_tools
{

struct Config {
    int version = 1;                                                // 版本号

    float posPigmanSpwanX = 0.0f;                                   // 猪人生成位置
    float posPigmanSpwanY = 0.0f;
    float posPigmanSpwanZ = 0.0f;
    
    bool isEnableRemovePigmanTeleportDelay = false;                 // 是否启用去除猪人传送延迟
    bool enablePauseGameWhenNoPlayers = true;                       // 当服务器没有玩家时关闭昼夜更替
};

}