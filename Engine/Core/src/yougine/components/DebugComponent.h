#pragma once
#include "Component.h"
#include "../utilitys/YougineMath.h"

namespace yougine::components
{
    class DebugComponent : public components::Component
    {
    public:
        int intval = 1;
        float floatval = 1.0;
        utility::Vector3* vec3val;
        std::string strval = "aaa";
        bool boolval = false;
        int intval2 = 2;

        DebugComponent();
    };
}
