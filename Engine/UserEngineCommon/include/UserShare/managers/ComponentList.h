#pragma once
#include <iostream>
#include <map>
#include "./../components/ComponentName.h"
#include "../GameObject.h"
namespace yougine::managers
{
    class EXPORT ComponentList
    {
    private:
        std::map<components::ComponentName, std::vector<components::Component*>> components_dictionary;

    public:
        ComponentList();
        std::map<components::ComponentName, std::vector<components::Component*>> GetObjectsDictionary();
        void AddObjectToDictionary(components::ComponentName component_name, components::Component* component);
        std::vector<components::Component*> GetReferObjectList(components::ComponentName);
        void RemoveComponentFromDictionary(components::ComponentName component_name, components::Component* component);
    };
}
