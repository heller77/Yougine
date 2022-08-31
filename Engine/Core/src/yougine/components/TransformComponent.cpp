#include "TransformComponent.h"

TransformComponent::TransformComponent(float x, float y, float z)
{
	this->position = new Vector3(x, y, z);
}
