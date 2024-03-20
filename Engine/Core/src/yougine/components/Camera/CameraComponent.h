#pragma once
#include <memory>

#include "UserShare/components/Component.h"
#include "UserShare/components/TransformComponent.h"

namespace yougine::components::camera
{
    class CameraComponent : public yougine::components::Component
    {
    private:
        static std::shared_ptr<CameraComponent> main_camera;

    public:
        CameraComponent();
        TransformComponent* GetTransform();
        static std::shared_ptr<CameraComponent> GetMainCamera();
    };
}
