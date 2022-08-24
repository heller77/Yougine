#include "CustomScriptManager.h"

namespace yougine::managers
{
	CustomScriptManager::CustomScriptManager()
	{
		componentlist_instance = ComponentList();
		InitializeMembers();
	}

	void CustomScriptManager::InitializeMembers()
	{
		for(GameObject gameobject : componentlist_instance.GetReferObjectList(ComponentName::kCustom))
		{
			for (components::Component* component : gameobject.GetComponents())
			{
				component->InitializeOnPlayBack();
			}
		}
	}

	void CustomScriptManager::ExcuteCoponents()
	{
		for (GameObject gameObject : componentlist_instance.GetObjectsDictionary()[ComponentName::kCustom])
		{
			for (components::Component* component : gameObject.GetComponents())
			{
				component->Excute();
			}
		}
	}
}