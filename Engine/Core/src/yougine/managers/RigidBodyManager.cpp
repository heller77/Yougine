#include "RigidBodyManager.h"

#include "../components/TransformComponent.h"
#include "../components/RigidBodyComponent.h"

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
            auto force = rigidbody_component->GetForce();
            auto drag = rigidbody_component->GetDrag();
            auto freeze_position = rigidbody_component->GetFreezePosition();

            // 抵抗
            utility::Vector3* kv = new utility::Vector3(drag * verosity.x, drag * verosity.y, drag * verosity.z);

            if (force.x != 0) { // フォースが加えられている場合の抵抗計算
                float ma = force.x - (*kv).x;
                if (sign(force.x) == sign(acceleration.x + ma * dt)) {
                    acceleration.x += static_cast<float>(ma * dt * !freeze_position.x);
                }
                else acceleration.x = 0;
            }
            else { // フォースが加えられていない場合の抵抗計算
                if (sign(verosity.x) == sign(verosity.x + (acceleration.x - (*kv).x * dt) * dt)) {
                    acceleration.x += static_cast<float>(-(*kv).x * dt * !freeze_position.x);
                }
                else verosity.x = 0;
            }

            if (force.y != 0) {
                float ma = force.y - (*kv).y;
                if (sign(force.y) == sign(acceleration.y + ma * dt)) {
                    acceleration.y += static_cast<float>(ma * dt * !freeze_position.y);
                }
                else acceleration.y = 0;
            }
            else {
                if (sign(verosity.y) == sign(verosity.y + (acceleration.y - (*kv).y * dt) * dt)) {
                    acceleration.y += static_cast<float>(-(*kv).y * dt * !freeze_position.y);
                }
                else {
                    acceleration.y = 0;
                    verosity.y = 0;
                }
            }

            if (force.z != 0) {
                float ma = force.z - (*kv).z;
                if (sign(force.z) == sign(acceleration.z + ma * dt)) {
                    acceleration.z += static_cast<float>(ma * dt * !freeze_position.z);
                }
                else acceleration.z = 0;
            }
            else {
                if (sign(verosity.z) == sign(verosity.z + (acceleration.z - (*kv).z * dt) * dt)) {
                    acceleration.z += static_cast<float>(-(*kv).z * dt * !freeze_position.z);
                }
                else {
                    acceleration.y = 0;
                    verosity.y = 0;
                }
            }

            verosity.x += static_cast<float>(acceleration.x * dt * !freeze_position.x + 0);
            verosity.y += static_cast<float>(acceleration.y * dt * !freeze_position.y + 0);
            verosity.z += static_cast<float>(acceleration.z * dt * !freeze_position.z + 0);
            acceleration.x += 0;
            acceleration.y += 0;
            acceleration.z += 0;
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