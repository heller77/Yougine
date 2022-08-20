#pragma once
#include <iostream>
#include <map>
#include "ComponentName.h"
#include "GameObject.h"
//vector already included at GameObject.h

namespace Managers
{
	using std::cout;
	using std::endl;
	using std::map; //dictionary library
	using std::vector;

	class ComponentList
	{
	private:
		map < ComponentName, vector<GameObject>> gameObjectListDictionary;
	};
}