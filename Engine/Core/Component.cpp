#include "Component.h"
#include <iostream>

namespace yougine::components
{
	void Component::Excute()
	{
		std::cout << "excute" << std::endl;
	}

	void Component::Initialize()
	{
		std::cout << "initialize component" << std::endl
	}
}