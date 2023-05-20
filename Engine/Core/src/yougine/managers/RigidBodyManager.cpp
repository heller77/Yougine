#include "RigidBodyManager.h"

#include "../components/TransformComponent.h"
#include "../components/RigidBodyComponent.h"

/**
* 符号を判定する関数
*/
int sign(double A) {
    return static_cast<int>((A > 0) - (A < 0));
}

namespace yougine::managers
{
    RigidBodyManager::RigidBodyManager(ComponentList* component_list)
    {
        this->componentlist = component_list;
    }

    void RigidBodyManager::Update()
    {
        auto rigidbody_componentlist = componentlist->GetObjectsDictionary()[ComponentName::kRigidBody];
        for (components::Component* component : rigidbody_componentlist)
        {
            yougine::components::TransformComponent* transform_compornent = component->GetGameObject()->GetComponent<components::TransformComponent>();
            yougine::components::RigidBodyComponent* rigidbody_component = component->GetGameObject()->GetComponent<components::RigidBodyComponent>();
            utility::Vector3 position = transform_compornent->GetPosition();
            std::shared_ptr<utility::Quaternion> rotation = transform_compornent->GetRotation();
            auto euler_rotation = rotation->CalculateEuler();
            auto dt = 0.016; // デルタタイム
            auto verosity = rigidbody_component->GetVelocity();
            auto angular_verosity = rigidbody_component->GetAngularVelocity();
            auto acceleration = rigidbody_component->GetAcceleration();
            auto angular_acceleration = rigidbody_component->GetAngularAcceleration();
            auto mass = rigidbody_component->GetMass();
            auto drag = rigidbody_component->GetDrag();
            auto angular_drag = rigidbody_component->GetAngularDrag();
            auto freeze_position = rigidbody_component->GetFreezePosition();
            auto freeze_rotation = rigidbody_component->GetFreezeRotation();

            // 抵抗
            utility::Vector3 resistance = *(new utility::Vector3(drag * verosity.x, drag * verosity.y, drag * verosity.z));
            utility::Vector3 angular_resistance = *(new utility::Vector3(drag * angular_verosity.x, drag * angular_verosity.y, drag * angular_verosity.z));

            if (!freeze_position.x) {
                verosity.x += static_cast<float>((acceleration.x - resistance.x) * dt + 0);
                position.x += static_cast<float>(verosity.x * dt + 0);
            }
            if (!freeze_position.y) {
                verosity.y += static_cast<float>((acceleration.y - resistance.y) * dt + 0);
                position.y += static_cast<float>(verosity.y * dt + 0);
            }
            if (!freeze_position.z) {
                verosity.z += static_cast<float>((acceleration.z - resistance.z) * dt + 0);
                position.z += static_cast<float>(verosity.z * dt + 0);
            }

            if (!freeze_rotation.x) {
                angular_verosity.x += static_cast<float>((angular_acceleration.x - angular_resistance.x) * dt + 0);
                euler_rotation.x += static_cast<float>(angular_verosity.x * dt + 0);
            }
            if (!freeze_rotation.y) {
                angular_verosity.y += static_cast<float>((angular_acceleration.y - angular_resistance.y) * dt + 0);
                euler_rotation.y += static_cast<float>(angular_verosity.y * dt + 0);
            }
            if (!freeze_rotation.z) {
                angular_verosity.z += static_cast<float>((angular_acceleration.z - angular_resistance.z) * dt + 0);
                euler_rotation.z += static_cast<float>(angular_verosity.z * dt + 0);
            }

            rigidbody_component->SetAcceleration(acceleration);
            rigidbody_component->SetAngularAcceleration(angular_acceleration);
            rigidbody_component->SetVelocity(verosity);
            rigidbody_component->SetAngularVelocity(angular_verosity);
            transform_compornent->SetPosition(position);
            rotation = utility::Quaternion::GenerateQuartanionFromEuler(euler_rotation.x, euler_rotation.y, euler_rotation.z);
            transform_compornent->SetRotation(rotation);
            //std::cout << "TEST" << position.x << "\n";
        }
    }

}