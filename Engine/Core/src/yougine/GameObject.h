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
    class Scene;

    class GameObject
    {
    private:
        Scene* scene;
        std::vector<components::Component*> components;
        std::string name;
        GameObject* gameobject_parent;
        std::list<GameObject*> gameobject_childs;

    private:
        void InitializeComponents();

    public:
        GameObject(Scene*, std::string, GameObject*);
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

            for (components::Component* c : components)
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
            for (components::Component* c : components)
            {
                if (typeid(c) == typeid(T*))
                {
                    return nullptr;
                }
            }

            T* component = new T();
            components.push_back(component);
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

            components = new_list;
        }
    };
}