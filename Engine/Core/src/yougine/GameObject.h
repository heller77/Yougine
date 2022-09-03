#pragma once
#include <vector>
#include <string>

namespace yougine::components
{
	class Component;
}
namespace yougine
{
	class GameObject;

	class GameObject
	{
	private:
		std::vector<components::Component*> component_list;
		std::string name;
		GameObject* gameobject_parent;
		std::vector<GameObject*> gameobject_childs;

	private:
		void InitializeComponentList();

	public:
		GameObject(std::string, GameObject*);
		std::string GetName();
		void SetName(std::string);
		std::vector<components::Component*> GetComponents();
		void AddChild(GameObject*);
		GameObject* GetParentObject();
		std::vector<GameObject*> GetChildObjects();
		template <class T> T* GetComponent();
		template <class T> T* AddComponent();
		template <class T> void RemoveComponent();
		bool operator==(const GameObject& rhs) const;
	};
}