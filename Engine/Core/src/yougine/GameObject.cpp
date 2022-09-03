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

	template <class T> T* GameObject::GetComponent()
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
	template <class T> T* GameObject::AddComponent()
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

	template <class T> void GameObject::RemoveComponent()
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

	bool GameObject::operator==(const GameObject& rhs) const
	{
		return *this == rhs;
	}
}