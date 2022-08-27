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
		template <class T> T* GetComponent();
		template <class T> T* AddComponent();
		template <class T> void RemoveComponent();
		bool operator==(const GameObject& rhs) const;
	};
}