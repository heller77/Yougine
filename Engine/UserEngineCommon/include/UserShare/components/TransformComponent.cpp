#include "TransformComponent.h"

namespace yougine::components
{
    TransformComponent::TransformComponent(float x, float y, float z) : Component(components::ComponentName::kNone)
    {
        this->position = new utility::Vector3(x, y, z);
        this->rotation = utility::Quaternion::GenerateQuartanionFromEuler(0, 0, 0);
        this->scale = new utility::Vector3(1, 1, 1);
        accessable_properties_list.push_back(std::vector<std::any>{position, GETVALUENAME(position)});
        accessable_properties_list.push_back(std::vector<std::any>{rotation, GETVALUENAME(rotation)});
        accessable_properties_list.push_back(std::vector<std::any>{scale, GETVALUENAME(scale)});
    }

    /**
     * \brief positionの実体を返す（参照ではないので変更しても、transform.positionそのものを変更できる訳ではない）
     * \return positionの実体
     */
    utility::Vector3 TransformComponent::GetPosition()
    {
        return *this->position;
    }

    /**
     * \brief positionのセッター
     * \param position セットする値
     */
    void TransformComponent::SetPosition(utility::Vector3 position)
    {
        //this->position = &position;
        (*this->position).x = position.x;
        (*this->position).y = position.y;
        (*this->position).z = position.z;
    }

    std::shared_ptr<utility::Quaternion> TransformComponent::GetRotation()
    {
        return this->rotation;
    }

    void TransformComponent::SetRotation(std::shared_ptr<utility::Quaternion> quat)
    {
        *this->rotation = quat;
    }

    utility::Vector3 TransformComponent::GetScale()
    {
        return *this->scale;
    }

    void TransformComponent::SetScale(utility::Vector3 scale)
    {
        (*this->scale).x = scale.x;
        (*this->scale).y = scale.y;
        (*this->scale).z = scale.z;
    }
}
