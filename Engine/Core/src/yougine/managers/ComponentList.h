#pragma once
#include <iostream>
#include <map>
#include "ComponentName.h"
#include "../GameObject.h"

namespace yougine::managers
{
    class ComponentList
    {
    private:
        std::map<ComponentName, std::vector<components::Component*>> components_dictionary;

    public:
        ComponentList();
        std::map<ComponentName, std::vector<components::Component*>> GetObjectsDictionary();
        void AddObjectToDictionary(ComponentName component_name, components::Component* component);
        std::vector<components::Component*> GetReferObjectList(ComponentName);
        void RemoveComponentFromDictionary(managers::ComponentName component_name, components::Component* component);
    };
}
