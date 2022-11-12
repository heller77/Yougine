#pragma once
#include "../components/Component.h"
#include "ComponentList.h"
#include <vector>

namespace yougine::managers
{
    class RigidBodyManager
    {
    private:
        ComponentList* componentlist;
        ComponentName component_name = ComponentName::kRigidBody;

    public:
        RigidBodyManager(ComponentList*);
        void Update();
    };
}