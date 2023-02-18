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
        ComponentName component_name = ComponentName::kCustom;

    private:
        void InitializeMembers();

    public:
        CustomScriptManager(ComponentList*);
        void ExcuteCoponents();
    };
}
