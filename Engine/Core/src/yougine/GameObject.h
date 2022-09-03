#pragma once
#include <vector>
#include <string>

namespace yougine
{
	namespace components { class Component; }

	class GameObject
	{
	private:
		std::vector<components::Component*> component_list;
		std::string name;

	private:
		void InitializeComponentList();

	public:
		GameObject(std::string);
		std::string GetName();
		void SetName(std::string);
		std::vector<components::Component*> GetComponents();
		template <class T> T* GetComponent();
		template <class T> T* AddComponent();
		template <class T> void RemoveComponent();
		bool operator==(const GameObject& rhs) const;
	};
}