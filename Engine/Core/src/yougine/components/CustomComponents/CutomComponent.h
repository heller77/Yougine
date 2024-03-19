#pragma once
#include "UserShare/components/Component.h"

namespace yougine::components::customcomponents
{
    /**
     * \brief ユーザが書くことのできるコンポーネントが継承するコンポーネント
     */
    class CutomComponent : public yougine::components::Component
    {
    public:
        virtual void Update() = 0;
    };
}
