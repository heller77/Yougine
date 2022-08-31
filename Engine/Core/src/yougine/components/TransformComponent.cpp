#include "TransformComponent.h"

TransformComponent::TransformComponent(float x, float y, float z)
{
	this->position = new Vector3(x, y, z);
}

/**
 * \return position‚ÌŽÀ‘Ì‚ð•Ô‚·B
 */
Vector3 TransformComponent::GetPosition()
{
	return *this->position;
}

void TransformComponent::SetPosition(Vector3 position)
{
	this->position = &position;
}

