#include <vector>
#include "ComponentList.h"

namespace yougine::managers
{
    using std::vector;
    using std::map;

    map<managers::ComponentName, vector<GameObject*>> gameobjects_dictionary =
    {
        { managers::ComponentName::kCollider, vector<GameObject*>() },
        { managers::ComponentName::kRigidBody, vector<GameObject*>() },
        { managers::ComponentName::kRender, vector<GameObject*>() },
        { managers::ComponentName::kUIRender , vector<GameObject*>() },
        { managers::ComponentName::kUICollider, vector<GameObject*>() },
        { managers::ComponentName::kCustom, vector<GameObject*>() },
    };

    map<managers::ComponentName, vector<GameObject*>> ComponentList::GetObjectsDictionary()
    {
        return gameobjects_dictionary;
    }

    void ComponentList::AddObjectToDictionary(managers::ComponentName component_name, GameObject* gameobject)
    {
        gameobjects_dictionary[component_name].push_back(gameobject);
    }

    vector<GameObject*> ComponentList::GetReferObjectList(managers::ComponentName component_name)
    {
        return gameobjects_dictionary[component_name];
    }
    //TODO é¿ëïÇ∑ÇÈÅIéwíËÇµÇΩcomponentÇçÌèúÇ∑ÇÈ
    void yougine::managers::ComponentList::RemoveObjectFromDictionary(managers::ComponentName component_name, components::Component* component)
    {
        //ñ¢é¿ëï
    }
}