﻿#pragma once
#include "UserShare/GameObject.h"
#include "managers/ComponentList.h"
#include <list>

#include "InputManager.h"
#include "managers/UserScriptComponentEntryPointManager.h"
#include "UserShare/Layer.h"
#include "UserShare/MacroDifHeader.h"

namespace yougine
{
    class GameObject;

    class EXPORT Scene
    {
    private:
        std::list<GameObject*> gameobject_list;
        managers::ComponentList* component_list;
        std::string name;
        std::shared_ptr<managers::UserScriptComponentEntryPointManager> user_script_component_entry_point_manager;
        std::shared_ptr<InputManager> input_manager;
    private:
        void RemoveGameObject(GameObject*);
        GameObject* RecursiveGameObjects(std::list<GameObject*>, std::string);

    public:
        Scene(std::string);
        managers::ComponentList* GetComponentList();
        std::list<GameObject*> GetGameObjects();
        std::string GetName();
        void SetName(std::string);
        GameObject* CreateGameObject(std::string, GameObject*);
        GameObject* GetGameObjectByName(std::string);
        void InitializeAllGameObjcts();

        std::shared_ptr<InputManager> GetInputManager();

        void AddRegisterUpdate(std::function<void()> method);
        /*
         *ユーザが呼ばない!!
         *
         */
        void Update();
    };

    inline std::shared_ptr<InputManager> Scene::GetInputManager()
    {
        return this->input_manager;
    }
}
