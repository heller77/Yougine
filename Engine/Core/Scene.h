#pragma once
#include "GameObject.h"
#include <list>

namespace yougine
{
	class Scene
	{
	private:
		std::list<GameObject*> gameobject_list;

	private:
		void CreateGameObject();
		void RemoveGameObject(GameObject*);
	};
}