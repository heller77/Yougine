#pragma once
#include "Component.h"
namespace yougine::comoponents
{
    class RenderComponent : public components::Component
    {
        //マテリアル（シェーダー、シェーダに渡す値）、メッシュ。
    public:
        RenderComponent();
    };

}