#pragma once
#include <vector>
#include "Yougine/Components/Component.h"

namespace yougine
{
	class GameObject
	{
	private:
		std::vector<components::Component> component_list;

	private:
		void InitializeComponentList();

	public:
		GameObject();
		std::vector<components::Component> GetComponents();
	};
}