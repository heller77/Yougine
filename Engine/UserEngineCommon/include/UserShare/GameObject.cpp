#include "GameObject.h"

#include "components/Component.h"

namespace yougine
{
    GameObject::GameObject(Scene* scene, std::string name, GameObject* gameobject_parent)
    {
        this->scene = scene;
        this->name = name;
        this->gameobject_parent = gameobject_parent;
        layer = LayerManager::GetInstance()->GetLayerByName("Default");
        InitializeComponents();
    }

    void GameObject::InitializeComponents()
    {
        for (auto component : this->components)
        {
            component->InitializeOnPlayBack();
        }
    }

    std::string GameObject::GetName()
    {
        return name;
    }

    void GameObject::SetName(std::string name)
    {
        this->name = name;
    }

    Layer* GameObject::GetLayer()
    {
        return layer;
    }

    void GameObject::SetLayer(Layer* layer)
    {
        this->layer = layer;
    }

    std::vector<components::Component*> GameObject::GetComponents()
    {
        return components;
    }

    void GameObject::AddChild(GameObject* gameobject)
    {
        gameobject_childs.push_back(gameobject);
    }

    GameObject* GameObject::GetParentObject()
    {
        return gameobject_parent;
    }

    std::list<GameObject*> GameObject::GetChildObjects()
    {
        return gameobject_childs;
    }

    bool GameObject::operator==(const GameObject& rhs) const
    {
        return *this == rhs;
    }

    Scene* GameObject::GetScene()
    {
        return this->scene;
    }

    void yougine::GameObject::AddComponent(components::Component* component)
    {
        if (component == nullptr)
        {
            return;
        }
        //componentが既に登録されていれば、AddComponentしない
        if (component->isAlradyRegisterComponentList())
        {
            return;
        }
        //componentの親として自分を設定
        component->SetParentGameObject(this);
        //componentlistにcomponentを登録
        component->RegisterThisComponentToComponentList(this->scene);
        //componentをこのGameObjectに追加
        this->components.push_back(component);
    }

    void GameObject::RemoveComponent(components::Component* component)
    {
        std::cout << "call RemoveComponent" << std::endl;
        std::vector<components::Component*> new_components;
        for (components::Component* c : GetComponents())
        {
            if (c != component)
            {
                new_components.push_back(c);
            }
            else
            {
                component->UnregisterThisComponentFromComponentList();
                std::cout << "componentをリムーブ！　" << std::endl;
            }
        }
        this->components = new_components;
    }
}
