#include "Component.h"
#include <iostream>

namespace yougine::components
{
	//private
	void InitializeProperties()
	{

	}

	//public
	void Component::Excute()
	{
		std::cout << "excute" << std::endl;
	}

	void Component::InitializeOnPlayBack()
	{
		std::cout << "initialize component" << std::endl;
	}

	bool Component::operator==(const Component& rhs) const
	{
		return *this == rhs;
	}
}