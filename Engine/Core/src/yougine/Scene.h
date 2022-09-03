#pragma once
#include "GameObject.h"
#include <list>

namespace yougine
{
	class Scene
	{
	private:
		/*
		top hierarchy gameobject list

		obj
		 - o_c1
		 - o_c2

		if access obj->o_c2, gameobject_list[0].GetChildsObject()
		GetChildsObject return obj's child objects
		*/
		std::list<GameObject*> gameobject_list;

	private:
		void CreateGameObject(std::string, GameObject*);
		void RemoveGameObject(GameObject*);

	public:
		std::list<GameObject*> GetGameObjects();
	};
}