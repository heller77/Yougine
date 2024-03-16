#pragma once
#include "../components/Component.h"
#include "ComponentList.h"
#include <vector>

#include "IManager.h"

namespace yougine::managers
{
    class CustomScriptManager : public IManager
    {
    public:
        void Update() override;

    private:
        ComponentList* componentlist;

        components::ComponentName component_name = components::ComponentName::kCustom;

    private:
        void InitializeMembers();

    public:
        CustomScriptManager(ComponentList*);
        void ExcuteCoponents();
    };
}
