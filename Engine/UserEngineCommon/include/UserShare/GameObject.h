﻿#pragma once
#include <vector>
#include <list>
#include <string>
#include "UserShare/Layer.h"

namespace yougine::components
{
    class Component;
}
namespace yougine
{
    class GameObject;
    class Scene;

    class EXPORT GameObject
    {
        friend Scene;

    private:
        GameObject(Scene*, std::string, GameObject*);
        Scene* scene;
        std::vector<std::shared_ptr<components::Component>> components;
        std::string name;
        Layer* layer;
        GameObject* gameobject_parent;
        std::list<GameObject*> gameobject_childs;

    private:
        void InitializeComponents();

    public:
        std::string GetName();
        void SetName(std::string);
        Layer* GetLayer();
        void SetLayer(Layer*);
        std::vector<components::Component*> GetComponents();
        void AddChild(GameObject*);
        GameObject* GetParentObject();
        std::list<GameObject*> GetChildObjects();
        bool operator==(const GameObject& rhs) const;
        Scene* GetScene();
        void Dispose();
        ~GameObject();
        void AddComponent(components::Component* component);
        void RemoveComponent(components::Component* component);
        template <class T> T* GetComponent()
        {
            T* component;

            for (auto& c : components)
            {
                auto c_ptr = c.get();
                component = dynamic_cast<T*>(c_ptr);
                if (component != nullptr)
                {
                    return component;
                }
            }

            return nullptr;
        }
    };
}