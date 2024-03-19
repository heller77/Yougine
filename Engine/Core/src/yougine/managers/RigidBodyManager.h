#pragma once
#include "UserShare/components/Component.h"
#include "UserShare/managers/ComponentList.h"
#include <vector>

#include "IManager.h"

namespace yougine::managers
{
    class RigidBodyManager : public IManager
    {
    public:
        void Update() override;

    private:
        ComponentList* componentlist;

        components::ComponentName component_name = components::ComponentName::kRigidBody;
    public:
        RigidBodyManager(ComponentList*);
        //void ExcuteCoponents();
    };
}