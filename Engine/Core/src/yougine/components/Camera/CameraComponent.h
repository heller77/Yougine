#pragma once
#include <memory>

#include "../Component.h"
#include "../TransformComponent.h"

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
