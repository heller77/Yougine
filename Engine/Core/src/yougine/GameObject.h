#pragma once
#include <vector>
#include <list>
#include <string>

namespace yougine::components
{
    class Component;
}
namespace yougine
{
    class GameObject;

    class GameObject
    {
    private:
        std::vector<components::Component*> component_list;
        std::string name;
        GameObject* gameobject_parent;
        std::list<GameObject*> gameobject_childs;

    private:
        void InitializeComponentList();

    public:
        GameObject(std::string, GameObject*);
        std::string GetName();
        void SetName(std::string);
        std::vector<components::Component*> GetComponents();
        void AddChild(GameObject*);
        GameObject* GetParentObject();
        std::list<GameObject*> GetChildObjects();
        bool operator==(const GameObject& rhs) const;

        template <class T> T* GetComponent()
        {
            T* component;

            for (components::Component* c : component_list)
            {
                component = dynamic_cast<T*>(c);
                if (component != nullptr)
                {
                    return component;
                }
            }

            return nullptr;
        }

        //component already exist on component_list, not add & return nullptr
        template <class T> T* AddComponent()
        {
            for (components::Component* c : component_list)
            {
                if (typeid(c) == typeid(T*))
                {
                    return nullptr;
                }
            }

            T* component = new T();
            component_list.push_back(component);
            return component;
        }

        template <class T> void RemoveComponent()
        {
            T* component;
            std::vector<components::Component*> new_list;

            for (components::Component* c : GetComponents())
            {
                component = dynamic_cast<T*>(c);
                if (component == nullptr)
                {
                    new_list.push_back(c);
                }
            }

            component_list = new_list;
        }
    };
}