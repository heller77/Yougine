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
            {managers::ComponentName::kCollider, vector<components::Component*>()},
            {managers::ComponentName::kRigidBody, vector<components::Component*>()},
            {managers::ComponentName::kRender, vector<components::Component*>()},
            {managers::ComponentName::kUIRender, vector<components::Component*>()},
            {managers::ComponentName::kUICollider, vector<components::Component*>()},
            {managers::ComponentName::kCustom, vector<components::Component*>()},
        };
    }

    map<managers::ComponentName, vector<components::Component*>> ComponentList::GetObjectsDictionary()
    {
        return components_dictionary;
    }

    void ComponentList::AddObjectToDictionary(managers::ComponentName component_name, components::Component* component)
    {
        components_dictionary[component_name].push_back(component);
    }

    vector<components::Component*> ComponentList::GetReferObjectList(managers::ComponentName component_name)
    {
        return components_dictionary[component_name];
    }

    //TODO é¿ëïÇ∑ÇÈÅIéwíËÇµÇΩcomponentÇçÌèúÇ∑ÇÈ
    void yougine::managers::ComponentList::RemoveObjectFromDictionary(managers::ComponentName component_name,
                                                                      components::Component* component)
    {
        //ñ¢é¿ëï
    }
}
