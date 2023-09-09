#pragma once
namespace CutomComponent
{
    /**
     * \brief ユーザが書くことのできるコンポーネントが継承するコンポーネント
     */
    class CutomComponent
    {
    public:
        virtual void Update() = 0;
    };
}
