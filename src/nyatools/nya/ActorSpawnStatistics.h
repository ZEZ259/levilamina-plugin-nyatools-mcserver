#pragma once

#include "ll/api/mod/NativeMod.h"
#include <vector>
#include <string>

#include <ll/api/service/Bedrock.h>

#include "mc/world/level/Level.h"
#include "mc/deps/core/math/Vec3.h"

namespace nya_tools {

//用于储存生物的生成总数
struct ActorSpawnInfo
{
    std::string actorType;
    int count;
};

enum ActorSpawnCounterMode
{
    Auto,
    Check
};

//计数器
class ActorSpawnCounter 
{
public:
    //构造器
    ActorSpawnCounter() = default;
    ~ActorSpawnCounter() = default;

public:
    //成员变量
    std::vector<ActorSpawnInfo>                             actorInfo;
    Vec3                                                    posRangeBegin;
    Vec3                                                    posRangeEnd;
    ActorSpawnCounterMode                                   mode = Auto;
    int                                                     limitTime = -1;
    int                                                     ticks = 0;
    bool                                                    isInitialized = false;
    bool                                                    isRunning = false;
    bool                                                    isPause = false;
public:
    //成员函数
    std::vector<ActorSpawnInfo>&                            getActorInfo();                                     //获取生物生成信息
    ActorSpawnInfo                                          searchActor(std::string type);                      //查找指定生物
    int                                                     getRunTicks();                                      //获取运行游戏刻
    int                                                     getLimitTime();                                     //获取限制时间。
    bool                                                    addActor(const std::string& actorType);             //添加生物，出现重复返回false
    bool                                                    removeActor(const std::string& actorType);          //移除生物，若不存在返回false
    void                                                    clear();                                            //清空列表
    void                                                    setDetectRange(const Vec3& begin, const Vec3& end); //设置检测范围
    void                                                    setMode(ActorSpawnCounterMode Mode);                //设置统计模式
    void                                                    start(int limitTime);                               //开始计数
    void                                                    start();                                            //开始计数
    void                                                    stop();                                             //停止计数
    void                                                    pause();                                            //暂停
}; 

}