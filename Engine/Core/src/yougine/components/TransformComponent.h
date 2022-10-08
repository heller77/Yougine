#pragma once
#include "Component.h"
#include "../utilitys/YougineMath.h"

namespace yougine::components
{
    class TransformComponent : public yougine::components::Component
    {
    private:
        utility::Vector3* position;
    public:
        TransformComponent(float x, float y, float z);
        utility::Vector3 GetPosition();
        void SetPosition(utility::Vector3 position);

    };
}

