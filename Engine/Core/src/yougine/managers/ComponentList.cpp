#include <vector>
#include "ComponentList.h"

#include "../components/Component.h"

namespace yougine::managers
{
    using std::vector;
    using std::map;

    ComponentList::ComponentList()
    {
        components_dictionary =
        {
            {components::ComponentName::kCollider, vector<components::Component*>()},
            {components::ComponentName::kRigidBody, vector<components::Component*>()},
            {components::ComponentName::kRender, vector<components::Component*>()},
            {components::ComponentName::kUIRender, vector<components::Component*>()},
            {components::ComponentName::kUICollider, vector<components::Component*>()},
            {components::ComponentName::kCustom, vector<components::Component*>()},
        };
    }

    map<components::ComponentName, vector<components::Component*>> ComponentList::GetObjectsDictionary()
    {
        return components_dictionary;
    }

    void ComponentList::AddObjectToDictionary(components::ComponentName component_name, components::Component* component)
    {
        components_dictionary[component_name].push_back(component);
    }

    vector<components::Component*> ComponentList::GetReferObjectList(components::ComponentName component_name)
    {
        return components_dictionary[component_name];
    }

    /**
     * \brief componentの登録を消す
     * \param component_name
     * \param component
     */
    void yougine::managers::ComponentList::RemoveComponentFromDictionary(components::ComponentName component_name,
        components::Component* component)
    {
        auto target_component_list = components_dictionary[component_name];
        vector<components::Component*> new_component_list;
        for (auto* c : target_component_list)
        {
            if (c != component)
            {
                new_component_list.push_back(c);
            }
        }
        components_dictionary[component_name] = new_component_list;
    }
}
