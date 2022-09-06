#pragma once
#include "GameObject.h"
#include <list>

namespace yougine
{
    class GameObject;

    class Scene
    {
    private:
        std::list<GameObject*> gameobject_list;

    private:
        void RemoveGameObject(GameObject*);
        GameObject* RecursiveGameObjects(std::vector<GameObject*>, std::string);

    public:
        std::list<GameObject*> GetGameObjects();
        void CreateGameObject(std::string, GameObject*);
        GameObject* GetGameObjectByName(std::string);
    };

}