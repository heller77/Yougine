#include "TransformComponent.h"

TransformComponent::TransformComponent(float x, float y, float z)
{
	this->position = new Vector3(x, y, z);
}

/**
 * \brief positionの実体を返す（参照ではないので変更しても、transform.positionそのものを変更できる訳ではない）
 * \return positionの実体
 */
Vector3 TransformComponent::GetPosition()
{
	return *this->position;
}

/**
 * \brief positionのセッター
 * \param position セットする値
 */
void TransformComponent::SetPosition(Vector3 position)
{
	this->position = &position;
}

