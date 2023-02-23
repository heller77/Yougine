#include "TransformComponent.h"

namespace yougine::components
{
    TransformComponent::TransformComponent(float x, float y, float z) : Component(managers::ComponentName::kNone)
    {
        this->position = new utility::Vector3(x, y, z);
        accessable_properties_list.push_back(std::vector<std::any>{position, GETVALUENAME(position)});
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

}