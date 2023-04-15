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
        //std::cout << "TEST" << rigidbody_componentlist.size() << "\n";
        //for (components::Component* rigidbody_component : componentlist->GetObjectsDictionary()[ComponentName::kRigidBody])
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
            utility::Vector3 kv = *(new utility::Vector3(drag * verosity.x, drag * verosity.y, drag * verosity.z));

            verosity.x += static_cast<float>((acceleration.x - kv.x) * dt * !freeze_position.x + 0);
            verosity.y += static_cast<float>((acceleration.y - kv.y) * dt * !freeze_position.y + 0);
            verosity.z += static_cast<float>((acceleration.z - kv.z) * dt * !freeze_position.z + 0);

            position.x += static_cast<float>(verosity.x * dt * !freeze_position.x + 0);
            position.y += static_cast<float>(verosity.y * dt * !freeze_position.y + 0);
            position.z += static_cast<float>(verosity.z * dt * !freeze_position.z + 0);

            rigidbody_component->SetAcceleration(acceleration);
            rigidbody_component->SetVelocity(verosity);
            transform_compornent->SetPosition(position);
            //std::cout << "TEST" << position.x << "\n";
        }
    }

}