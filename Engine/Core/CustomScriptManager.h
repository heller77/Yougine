#pragma once
#include "ComponentName.h"
#include "ComponentList.h"
#include <vector>

namespace yougine::managers
{
	class CustomScriptManager
	{
	private:
		static ComponentList componentlist_instance;
		ComponentName component_name = ComponentName::kCustom;

	private:
		void InitializeMembers();

	public:
		CustomScriptManager();
		void ExcuteCoponents();
	};
}