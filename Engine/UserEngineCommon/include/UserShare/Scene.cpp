#include "Scene.h"

#include <memory>
#include <memory>

namespace yougine
{
    Scene::Scene(std::string name)
    {
        LayerManager::Create();
        this->name = name;
        component_list = new managers::ComponentList();

        this->user_script_component_entry_point_manager = std::make_shared<managers::UserScriptComponentEntryPointManager>();
        this->input_manager = std::make_shared<InputManager>();
    }

    GameObject* Scene::CreateGameObject(std::string name, GameObject* parent)
    {
        GameObject* gameobject = new GameObject(this, name, parent);

        if (parent == nullptr)
        {
            gameobject_list.push_back(gameobject);
        }
        else
        {
            parent->AddChild(gameobject);
        }

        return gameobject;
    }

    void Scene::RemoveGameObjcect(GameObject* remove_target)
    {

        auto it = std::find(gameobject_list.begin(), gameobject_list.end(), remove_target);
        if (it != gameobject_list.end()) {
            std::cout << "Found: " << *it << std::endl;
            this->gameobject_list.remove_if([&](GameObject* x) {
                bool to_remove = x->name == remove_target->name;

                return to_remove;
                });
            delete remove_target;
        }
        else {
            std::cout << "Not found" << std::endl;
        }
    }

    //処理変える
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

    managers::ComponentList* Scene::GetComponentList()
    {
        return component_list;
    }


    std::string Scene::GetName()
    {
        return name;
    }

    void Scene::SetName(std::string name)
    {
        this->name = name;
    }

    std::list<GameObject*> Scene::GetGameObjects()
    {
        return gameobject_list;
    }

    GameObject* Scene::GetGameObjectByName(std::string name)
    {
        if (name.empty()) return nullptr;

        GameObject* r_obj = nullptr;
        for (GameObject* game_object : gameobject_list)
        {
            r_obj = RecursiveGameObjects({ game_object }, name);
            if (r_obj != nullptr)
            {
                break;
            }
        }

        return r_obj;
    }

    void Scene::InitializeAllGameObjcts()
    {
        for (auto gameobject : this->gameobject_list)
        {
            gameobject->InitializeComponents();
        }
    }

    void Scene::RegisterOnlyUpdate(components::userscriptcomponents::IUpdatable* i_updatable)
    {
        this->user_script_component_entry_point_manager->SetUpdate(i_updatable);
    }


    void Scene::Update()
    {
        this->input_manager->UpdateInput();


        this->user_script_component_entry_point_manager->Update();
    }

    GameObject* Scene::RecursiveGameObjects(std::list<GameObject*> game_objects, std::string name)
    {
        for (GameObject* obj : game_objects)
        {
            if (obj->GetName() == name)
            {
                return obj;
            }

            RecursiveGameObjects(obj->GetChildObjects(), name);
        }

        return nullptr;
    }

}
