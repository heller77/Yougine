#include "GameObject.h"


namespace yougine
{
	std::vector<components::Component> component_list;

	GameObject::GameObject()
	{
		InitializeComponentList();
	}

	void GameObject::InitializeComponentList()
	{
		for (components::Component component : component_list)
		{
		}

		//parentObject‰Šú‰»
	}

	std::vector<components::Component> GameObject::GetComponents()
	{
		return component_list;
	}
}