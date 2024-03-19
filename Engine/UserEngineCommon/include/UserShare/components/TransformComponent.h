#pragma once
#include "UserShare/components/Component.h"
#include "UserShare/utilitys/YougineMath.h"
#include "../utilitys/Quaternion.h"
#include "UserShare/MacroDifHeader.h"
namespace yougine::components
{
    class EXPORT TransformComponent : public yougine::components::Component
    {
    private:
        utility::Vector3* position;
        std::shared_ptr<utility::Quaternion> rotation;
    public:
        TransformComponent(float x, float y, float z);
        utility::Vector3 GetPosition();
        void SetPosition(utility::Vector3 position);
        std::shared_ptr<utility::Quaternion> GetRotation();
        void SetRotation(std::shared_ptr<utility::Quaternion> quat);

    };
}

