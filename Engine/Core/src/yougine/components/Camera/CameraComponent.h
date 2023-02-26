#pragma once
#include <memory>

#include "../Component.h"

namespace yougine::components::camera
{
    class CameraComponent : public yougine::components::Component
    {
    private:
         std::unique_ptr<CameraComponent> main;

    public:
        CameraComponent();
    };
}
