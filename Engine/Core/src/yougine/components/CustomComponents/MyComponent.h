#pragma once
#include "CutomComponent.h"

namespace yougine::components::customcomponents
{
    class MyComponent : public CutomComponent
    {
    public:
        void Update() override;
    };
}
