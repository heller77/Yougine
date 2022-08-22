#include "GameObject.h"


namespace yougine
{
	GameObject::GameObject()
	{
		InitializeComponentList();
	}

	void GameObject::InitializeComponentList()
	{

	}

	std::vector<components::Component*> GameObject::GetComponentsPtr()
	{
		return component_list;
	}

	void GameObject::AddComponent(components::Component* component)
	{
		GameObject::component_list.push_back(component);
	}

	void GameObject::RemoveComponent(components::Component* component)
	{
		std::vector<components::Component*> new_list;

		for (components::Component* c : component_list)
		{
			if (c == component)
			{
				new_list.push_back(c);
			}
		}

		component_list = new_list;
	}
}