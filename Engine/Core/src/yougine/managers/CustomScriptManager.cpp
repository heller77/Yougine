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
        for (GameObject* gameobject : componentlist->GetReferObjectList(ComponentName::kCustom))
        {
            for (components::Component* component : gameobject->GetComponents())
            {
                component->InitializeOnPlayBack();
            }
        }
    }

    void CustomScriptManager::ExcuteCoponents()
    {
        for (GameObject* gameObject : componentlist->GetObjectsDictionary()[ComponentName::kCustom])
        {
            for (components::Component* component : gameObject->GetComponents())
            {
                component->Excute();
            }
        }
    }
}
