#pragma once
#include "../GameObject.h"

namespace yougine::components
{
	class Component
	{
	private:
		GameObject gameobject;

	private:
		void InitializeProperties();

	public:
		void Excute();
		void InitializeOnPlayBack();
		bool operator==(const Component& rhs) const;
	};
}