#include "CustomScriptManager.h"

namespace yougine::managers
{
    CustomScriptManager::CustomScriptManager(ComponentList* component_list)
    {
        this->componentlist = component_list;
        InitializeMembers();
    }

    void CustomScriptManager::InitializeMembers()
    {
        for (components::Component* component : componentlist->GetReferObjectList(ComponentName::kCustom))
        {
            for (components::Component* component : component->GetGameObject()->GetComponents())
            {
                component->InitializeOnPlayBack();
            }
        }
    }

    void CustomScriptManager::ExcuteCoponents()
    {
        for (components::Component* component : componentlist->GetObjectsDictionary()[ComponentName::kCustom])
        {
            for (components::Component* component : component->GetGameObject()->GetComponents())
            {
                component->Excute();
            }
        }
    }
}
