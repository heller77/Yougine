#include "CustomScriptManager.h"

namespace yougine::managers
{
    CustomScriptManager::CustomScriptManager(ComponentList* component_list)
    {
        this->componentlist = component_list;
        InitializeMembers();
    }

    void CustomScriptManager::Update()
    {
        // std::cout << "customscript update" << std::endl;
    }

    void CustomScriptManager::InitializeMembers()
    {
        for (components::Component* component : componentlist->GetReferObjectList(components::ComponentName::kCustom))
        {
            for (components::Component* component : component->GetGameObject()->GetComponents())
            {
                component->InitializeOnPlayBack();
            }
        }
    }

    void CustomScriptManager::ExcuteCoponents()
    {
        for (components::Component* component : componentlist->GetObjectsDictionary()[components::ComponentName::kCustom])
        {
            for (components::Component* component : component->GetGameObject()->GetComponents())
            {
                component->Excute();
            }
        }
    }
}
