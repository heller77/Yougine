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
            auto dt = 0.016; // デルタタイム
            auto verosity = rigidbody_component->GetVelocity();
            auto acceleration = rigidbody_component->GetAcceleration();
            auto mass = rigidbody_component->GetMass();
            auto drag = rigidbody_component->GetDrag();
            auto freeze_position = rigidbody_component->GetFreezePosition();

            // 抵抗
            utility::Vector3 resistance = *(new utility::Vector3(drag * verosity.x, drag * verosity.y, drag * verosity.z));

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

            rigidbody_component->SetAcceleration(acceleration);
            rigidbody_component->SetVelocity(verosity);
            transform_compornent->SetPosition(position);
            //std::cout << "TEST" << position.x << "\n";
        }
    }

}