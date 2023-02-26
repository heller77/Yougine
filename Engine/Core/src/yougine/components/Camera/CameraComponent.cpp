#include "CameraComponent.h"

yougine::components::camera::CameraComponent::CameraComponent() : Component(managers::ComponentName::kNone)
{
    CameraComponent::main = std::unique_ptr<CameraComponent>(this);
}
