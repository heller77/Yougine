#include "GameObject.h"


namespace yougine
{
	GameObject::GameObject(std::string name)
	{
		this->name = name;
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

	//forbit same component duplication
	template <class T> T* GameObject::AddComponent()
	{
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