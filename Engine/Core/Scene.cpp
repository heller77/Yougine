#include "Scene.h"

namespace yougine
{
	void Scene::CreateGameObject()
	{
		GameObject *gameobject = new GameObject();

		gameobject_list.push_back(gameobject);
	}

	void Scene::RemoveGameObject(GameObject* gameobject)
	{
		std::list<GameObject*> new_list;

		for (GameObject* obj : gameobject_list)
		{
			if (gameobject == obj)
			{
				new_list.push_back(obj);
			}
		}

		gameobject_list = new_list;
	}
}