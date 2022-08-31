#pragma once
#include "Component.h"
#include "./../Vector3.h"

namespace yougine::components
{
	class TransformComponent : public yougine::components::Component
	{
	private:
		Vector3* position;
	public:
		TransformComponent(float x, float y, float z);
		Vector3 GetPosition();
		void SetPosition(Vector3 position);

	};
}

