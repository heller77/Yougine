#include "LoopInfoManager.h"

#include <iostream>

yougine::LoopInfoManager::LoopInfoManager()
{
    this->loop_info = std::make_unique<LoopInfo>();
    loop_info->delta_time = 0;

}

yougine::LoopInfo* yougine::LoopInfoManager::GetLoopInfo()
{
    return this->loop_info.get();
}

void yougine::LoopInfoManager::Update()
{
    //1フレーム前との時間差分を計算
    auto now = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = now - preframe_time;
    this->loop_info->delta_time = diff.count();
    preframe_time = now;
}
