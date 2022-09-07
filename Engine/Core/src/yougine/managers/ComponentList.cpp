#include <vector>
#include "ComponentList.h"

namespace yougine::managers
{
    using std::vector;
    using std::map;

    map<managers::ComponentName, vector<GameObject>> gameobjects_dictionary =
    {
        { managers::ComponentName::kCollider, vector<GameObject>() },
        { managers::ComponentName::kRigidBody, vector<GameObject>() },
        { managers::ComponentName::kRender, vector<GameObject>() },
        { managers::ComponentName::kUIRender , vector<GameObject>() },
        { managers::ComponentName::kUICollider, vector<GameObject>() },
    };

    map<managers::ComponentName, vector<GameObject>> ComponentList::GetObjectsDictionary()
    {
        return gameobjects_dictionary;
    }

    void ComponentList::AddObjectToDictionary(managers::ComponentName component_name, GameObject gameobject)
    {
        gameobjects_dictionary[component_name].push_back(gameobject);
    }

    vector<GameObject> ComponentList::GetReferObjectList(managers::ComponentName component_name)
    {
        return gameobjects_dictionary[component_name];
    }
}