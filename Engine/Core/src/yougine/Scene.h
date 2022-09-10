#pragma once
#include "GameObject.h"
#include "managers/ComponentList.h"
#include <list>

namespace yougine
{
    class GameObject;

    class Scene
    {
    private:
        std::list<GameObject*> gameobject_list;
        managers::ComponentList* component_list;
        std::string name;

    private:
        void RemoveGameObject(GameObject*);
        GameObject* RecursiveGameObjects(std::list<GameObject*>, std::string);

    public:
        Scene(std::string);
        managers::ComponentList* GetComponentList();
        std::list<GameObject*> GetGameObjects();
        std::string GetName();
        void SetName(std::string);
        void CreateGameObject(std::string, GameObject*);
        GameObject* GetGameObjectByName(std::string);
    };

}