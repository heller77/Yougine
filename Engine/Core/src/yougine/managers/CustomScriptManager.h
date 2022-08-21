#pragma once
#include "ComponentName.h"
#include "ComponentList.h"
#include <vector>

namespace yougine::managers
{
	class CustomScriptManager
	{
	private:
		ComponentList component_list;
		ComponentName component_name = ComponentName::kCustom;

	private:
		void InitializeMembers();

	public:
		CustomScriptManager();
		void ExcuteCoponents();
	};
}