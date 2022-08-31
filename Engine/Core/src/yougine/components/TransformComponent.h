#pragma once
#include "Component.h"
#include "./../Vector3.h"

class TransformComponent : public yougine::components::Component
{
private:
	Vector3* position;
public:
	TransformComponent(float x, float y, float z);

};

