#pragma once
#include <memory>

#include "UserShare/components/Component.h"
#include "UserShare/components/TransformComponent.h"

namespace yougine::components::camera
{
    class CameraComponent : public yougine::components::Component
    {
    private:
        static CameraComponent* main_camera;

    public:
        CameraComponent();
        ~CameraComponent();
        TransformComponent* GetTransform();
        static yougine::components::camera::CameraComponent* GetMainCamera();
    };
}
