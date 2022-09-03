#pragma once
#include <iostream>
#include <map>
#include "ComponentName.h"
#include "../GameObject.h"
//vector already included at GameObject.h

//SingletonInstance

namespace yougine::managers
{
    class ComponentList
    {
    private:
        //static ComponentList* m_instance;
        std::map<ComponentName, std::vector<GameObject>> gameobjects_dictionary;

        /*
        private:
            ComponentList();
            ~ComponentList();
        */

    public:
        //static void Create();
        //static void Destroy();
        //static ComponentList* GetInstance();
        std::map<ComponentName, std::vector<GameObject>> GetObjectsDictionary();
        void AddObjectToDictionary(ComponentName, GameObject);
        std::vector<GameObject> GetReferObjectList(ComponentName);
    };
}