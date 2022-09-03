#include "GameObject.h"


namespace yougine
{
    GameObject::GameObject(std::string name, GameObject* gameobject_parent)
    {
        this->name = name;
        this->gameobject_parent = gameobject_parent;
        InitializeComponentList();
    }

    void GameObject::InitializeComponentList()
    {

    }

    std::string GameObject::GetName()
    {
        return name;
    }

    void GameObject::SetName(std::string name)
    {
        this->name = name;
    }

    std::vector<components::Component*> GameObject::GetComponents()
    {
        return component_list;
    }

    void GameObject::AddChild(GameObject* gameobject)
    {
        gameobject_childs.push_back(gameobject);
    }

    GameObject* GameObject::GetParentObject()
    {
        return gameobject_parent;
    }

    std::vector<GameObject*> GameObject::GetChildObjects()
    {
        return gameobject_childs;
    }



    bool GameObject::operator==(const GameObject& rhs) const
    {
        return *this == rhs;
    }
}