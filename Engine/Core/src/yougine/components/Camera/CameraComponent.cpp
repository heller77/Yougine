#include "CameraComponent.h"

yougine::components::camera::CameraComponent* yougine::components::camera::CameraComponent::main_camera;
yougine::components::camera::CameraComponent::CameraComponent() : Component(components::ComponentName::kNone)
{
    CameraComponent::main_camera = this;

}

yougine::components::TransformComponent* yougine::components::camera::CameraComponent::GetTransform()
{
    return this->GetGameObject()->GetComponent<TransformComponent>();
}

yougine::components::camera::CameraComponent* yougine::components::camera::CameraComponent::GetMainCamera()
{
    return main_camera;
}
