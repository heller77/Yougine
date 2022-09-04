#include "Scene.h"

namespace yougine
{
    void Scene::CreateGameObject(std::string name, std::string name_parent)
    {
        GameObject* parent = GetGameObjectByName(name_parent);
        GameObject* gameobject = new GameObject(name, parent);

        //add list only top hierarchy gameobject
        if (parent == nullptr)
            gameobject_list.push_back(gameobject);
    }

    void Scene::RemoveGameObject(GameObject* gameobject)
    {
        std::list<GameObject*> new_list;

        for (GameObject* obj : gameobject_list)
        {
            if (gameobject == obj)
            {
                new_list.push_back(obj);
            }
        }

        gameobject_list = new_list;
    }

    std::list<GameObject*> Scene::GetGameObjects()
    {
        return gameobject_list;
    }

    GameObject* Scene::GetGameObjectByName(std::string name)
    {
        if (name.empty()) return nullptr;


        for (GameObject* obj_top : GetGameObjects())
        {
            for (GameObject* obj : obj_top->GetChildObjects()) //これの階層以下のオブジェクトどうやって参照すんの
            {
                if (obj->GetName() == name)
                    return obj;
            }
        }

        return nullptr;
    }
}