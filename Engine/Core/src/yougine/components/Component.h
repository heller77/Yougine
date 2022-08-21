#pragma once
#include "GameObject.h"

namespace yougine::components
{
	class Component
	{
	private:
		GameObject gameobject;

	public:
		void excute();
	};
}