#include "RigidBodyManager.h"

#include "../components/TransformComponent.h"
#include "../components/RigidBodyComponent.h"

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
            auto verosity = rigidbody_component->GetVelocity();
            auto freeze_position = rigidbody_component->GetFreezePosition();
            position.x += verosity.x * !freeze_position.x;
            position.y += verosity.y * !freeze_position.y;
            position.z += verosity.z * !freeze_position.z;
            transform_compornent->SetPosition(position);
            //std::cout << "TEST" << position.x << "\n";
        }
    }
}