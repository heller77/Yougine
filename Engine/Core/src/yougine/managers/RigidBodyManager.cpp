#include "RigidBodyManager.h"

#include "../components/TransformComponent.h"

namespace yougine::managers
{
    RigidBodyManager::RigidBodyManager(ComponentList* component_list)
    {
        this->componentlist = component_list;
    }

    void RigidBodyManager::Update()
    {
        for (components::Component* rigidbody_component : componentlist->GetObjectsDictionary()[ComponentName::kRigidBody])
        {
            yougine::components::TransformComponent* transform_compornent = rigidbody_component->GetGameObject()->GetComponent<components::TransformComponent>();
        }
    }
}