#pragma once
#include "Component.h"

class TransformComponent : public yougine::components::Component
{
private:
	float x, y, z;
public:
	TransformComponent(float x, float y, float z);

};

