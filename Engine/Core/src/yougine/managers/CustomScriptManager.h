#pragma once
#include "../components/Component.h"
#include "ComponentList.h"
#include <vector>

namespace yougine::managers
{
    class CustomScriptManager
    {
    private:
        ComponentList* componentlist;
        ComponentName component_name = ComponentName::kCustom;

    private:
        void InitializeMembers();

    public:
        CustomScriptManager(ComponentList*);
        void ExcuteCoponents();
    };
}