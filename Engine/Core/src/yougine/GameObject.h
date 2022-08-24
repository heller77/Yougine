#pragma once
#include <vector>

namespace yougine
{
	namespace components { class Component; }

	class GameObject
	{
	private:
		std::vector<components::Component*> component_list;

	private:
		void InitializeComponentList();

	public:
		GameObject();
		std::vector<components::Component*> GetComponents();
		void AddComponent(components::Component*);
		void RemoveComponent(components::Component*);
		bool operator==(const GameObject& rhs) const;
	};
}