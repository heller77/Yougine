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
        for (auto& component : this->components)
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
        std::vector<components::Component*> component_ptr_vec;
        for (auto& component : components)
        {
            component_ptr_vec.push_back(component.get());
        }
        return component_ptr_vec;
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

    void GameObject::Dispose()
    {
        //componentsが破棄される
        components.clear();
    }

    GameObject::~GameObject()
    {
        Dispose();
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
        this->components.push_back(std::unique_ptr<components::Component>(component));
    }

    void GameObject::RemoveComponent(components::Component* component)
    {
        components.erase(std::remove_if(components.begin(), components.end(),
            [component](const std::shared_ptr<components::Component>& v) {return v.get() == component; })
            , components.end());

    }
}
