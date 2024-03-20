#include "CameraComponent.h"
std::shared_ptr<yougine::components::camera::CameraComponent> yougine::components::camera::CameraComponent::main_camera;
yougine::components::camera::CameraComponent::CameraComponent() : Component(components::ComponentName::kNone)
{
    CameraComponent::main_camera = std::shared_ptr<CameraComponent>(this);
}

yougine::components::TransformComponent* yougine::components::camera::CameraComponent::GetTransform()
{
    return this->GetGameObject()->GetComponent<TransformComponent>();
}

std::shared_ptr<yougine::components::camera::CameraComponent> yougine::components::camera::CameraComponent::GetMainCamera()
{
    return main_camera;
}
