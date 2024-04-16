#pragma once
#include <chrono>
#include <memory>

#include "UserShare/LoopInfo.h"
#include "UserShare/MacroDifHeader.h"

namespace yougine
{
    /**
     * \brief ループにまつわる情報を管理
     */
    class EXPORT LoopInfoManager
    {
    private:
        std::unique_ptr<LoopInfo> loop_info;
        std::chrono::system_clock::time_point pre_time;
    public:
        LoopInfoManager();
        LoopInfo* GetLoopInfo();

        /**
         * \brief 毎フレームloopinfoを更新
         */
        void Update();
    };
}
