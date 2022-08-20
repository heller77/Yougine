#include "CustomScriptManager.h"
#include "../../GameObject.h"

namespace yougine::managers
{
	CustomScriptManager::CustomScriptManager()
	{
		InitializeMembers();
	}

	void CustomScriptManager::InitializeMembers()
	{
		/*
		componentList = Singleton.getInstance();

		for each (component Components::Component in ComponentList.getReferObjectList(ComponentName::Custom).getComponent())
		{
			components.push_back(component);
		}
		*/
	}

	void CustomScriptManager::ExcuteCoponents()
	{
		for(GameObject gameObject : component_list.GetObjectsDictionary()[ComponentName::kCustom])
		{
			for(components::Component component : gameObject.GetComponents())
			{
				component.excute();
			}
		}
	}
}