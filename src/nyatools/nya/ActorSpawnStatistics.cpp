
//#include "Nyatools.h"
//#include "Config.h"
#include "ActorSpawnStatistics.h"

#include <ll/api/mod/NativeMod.h>
#include "ll/api/event/ListenerBase.h"
#include "ll/api/mod/RegisterHelper.h"
#include <ll/api/Config.h>
#include <ll/api/command/CommandHandle.h>
#include <ll/api/command/CommandRegistrar.h>
#include <ll/api/data/KeyValueDB.h>
#include <ll/api/event/EventBus.h>
#include <ll/api/event/player/PlayerJoinEvent.h>
#include <ll/api/event/player/PlayerUseItemEvent.h>
#include <ll/api/event/player/PlayerDisconnectEvent.h>
#include <ll/api/event/player/PlayerConnectEvent.h>
#include <ll/api/event/world/SpawnMobEvent.h>
#include <ll/api/service/Bedrock.h>
#include <ll/api/Expected.h>
#include <vector>

#include "mc/world/level/Level.h"
#include "mc\server\commands\MinecraftCommands.h"
#include "mc\server\commands\CommandContext.h"
#include "mc\server\commands\CommandOrigin.h"
#include "mc/world/level/storage/GameRules.h"
#include "mc/world/level/storage/GameRule.h"
#include <mc/server/commands/CommandOrigin.h>
#include <mc/server/commands/CommandOutput.h>
#include <mc/world/actor/player/Player.h>

namespace nya_tools{

    //实现
    std::vector<ActorSpawnInfo>&                            ActorSpawnCounter::getActorInfo()
    {
        return actorInfo;
    }
    ActorSpawnInfo                                          ActorSpawnCounter::searchActor(std::string type) {
        for (auto& info : actorInfo)
        {
            if (info.actorType == type)
            {
                return info;
            }
        }
        return {"",0};
    }
    int                                                     ActorSpawnCounter::getRunTicks(){
        return ticks;
    }
    int                                                     ActorSpawnCounter::getLimitTime(){
        return limitTime;
    }
    bool                                                    ActorSpawnCounter::addActor(const std::string& actorType) {
        // 查找是否已存在该生物类型
        for (auto& info : actorInfo)
        {
            if (info.actorType == actorType)
            {
                if(mode==Check) return false;
                info.count++;
                return true;
            }    
        }
        // 如果不存在，则添加新的生物类型
        actorInfo.push_back({ actorType, 1 });
        return true;
    }
    bool                                                    ActorSpawnCounter::removeActor(const std::string& actorType) {
        for (auto it = actorInfo.begin(); it != actorInfo.end(); ++it)
        {
            if (it->actorType == actorType)
            {
                actorInfo.erase(it);
                return true; // 成功移除，返回 true
            }
        }
        return false; // 未找到该生物类型，返回 false
    }
    void                                                    ActorSpawnCounter::clear(){
        if(isRunning) return;//正在运行不予清空。
        actorInfo.clear();
        ticks=0;
    }
    void                                                    ActorSpawnCounter::setDetectRange(const Vec3& begin, const Vec3& end) {
        posRangeBegin = begin;
        posRangeEnd = end;
        isInitialized=true;
    }
    void                                                    ActorSpawnCounter::setMode(ActorSpawnCounterMode Mode){
        mode = Mode;
    }
    void                                                    ActorSpawnCounter::start(int limittime) {
        //检查列表是否为空
        if(!isInitialized) return;
        if(mode==Check&&!actorInfo.size())
        {
            //指令层面
            return;
        }
        // 清空之前的计数
        if(!isRunning){
            for (auto& info : actorInfo)
            {
                info.count = 0;
            }
            ticks=0;//重置时间
        }
        //更新状态
        isRunning=true;
        limitTime=limittime;
    }
    void                                                    ActorSpawnCounter::start(){
        start(-1);
    }
    void                                                    ActorSpawnCounter::stop(){
        isRunning=false;
    }
    void                                                    ActorSpawnCounter::pause(){
        if(isPause) isPause=false;
        else isPause=true;
    }
}