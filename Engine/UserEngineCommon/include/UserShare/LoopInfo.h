#pragma once
#include "UserShare/MacroDifHeader.h"
namespace yougine
{
    class LoopInfoManager;
}

namespace yougine
{
    class EXPORT LoopInfo
    {
        friend yougine::LoopInfoManager;
    private:
        float delta_time;
    public:
        /**
         * \brief 1フレーム前からの経過時間を返す(秒)
         * \return
         */
        float GetDeltaTime();
    };
}
