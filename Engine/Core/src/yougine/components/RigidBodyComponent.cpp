#include "RigidBodyComponent.h"

namespace yougine::components
{
    RigidBodyComponent::RigidBodyComponent() : Component(managers::ComponentName::kRigidBody)
    {
        this->velocity = new utility::Vector3(0, 0, 0); // x, y, z方向に関する速度
        this->mass = 1.00f; // オブジェクトの質量
        this->drag = 1.00f; // オブジェクトの抵抗
        this->angular_drag = 1.00f; // オブジェクトの回転に関する抵抗
        this->attraction = false; // 引力を受けるかどうか
        this->freeze_position = new utility::Bool3(false, false, false); // x, y, z方向に関して動きを無効化するかどうか
        this->freeze_rotation = new utility::Bool3(false, false, false); // 回転に関して動きを無効化するかどうか
        accessable_properties_list.push_back(std::vector<std::any>{velocity, GETVALUENAME(velocity)});
        accessable_properties_list.push_back(std::vector<std::any>{&mass, GETVALUENAME(mass)});
        accessable_properties_list.push_back(std::vector<std::any>{&drag, GETVALUENAME(drag)});
        accessable_properties_list.push_back(std::vector<std::any>{&angular_drag, GETVALUENAME(angular_drag)});
        accessable_properties_list.push_back(std::vector<std::any>{&attraction, GETVALUENAME(attraction)});
        accessable_properties_list.push_back(std::vector<std::any>{freeze_position, GETVALUENAME(freeze_position)});
        accessable_properties_list.push_back(std::vector<std::any>{freeze_rotation, GETVALUENAME(freeze_rotation)});
    }

    RigidBodyComponent::RigidBodyComponent(utility::Vector3 velocity, float mass, float drag, float angular_drag, bool attraction, utility::Bool3 freeze_position, utility::Bool3 freeze_rotation) : Component(managers::ComponentName::kRigidBody)
    {
        this->velocity = &velocity;
        this->mass = mass;
        this->drag = drag;
        this->angular_drag = angular_drag;
        this->attraction = attraction;
        this->freeze_position = &freeze_position;
        this->freeze_rotation = &freeze_rotation;
    }

    /**
     * \brief velocityの実体を返す（参照ではないので変更しても、rigidbody.velocityそのものを変更できる訳ではない）
     * \return velocityの実体
     */
    utility::Vector3 RigidBodyComponent::GetVelocity()
    {
        return *this->velocity;
    }

    /**
     * \brief velocityのセッター
     * \param velocity セットする値
     */
    void RigidBodyComponent::SetVelocity(utility::Vector3 velocity)
    {
        this->velocity = &velocity;
    }

    /**
     * \brief massの実体を返す
     * \return massの実体
     */
    float RigidBodyComponent::GetMass()
    {
        return this->mass;
    }

    /**
     * \brief massのセッター
     * \param mass セットする値
     */
    void RigidBodyComponent::SetMass(float mass)
    {
        this->mass = mass;
    }

    /**
     * \brief dragの実体を返す
     * \return dragの実体
     */
    float RigidBodyComponent::GetDrag()
    {
        return this->drag;
    }

    /**
     * \brief dragのセッター
     * \param drag セットする値
     */
    void RigidBodyComponent::SetDrag(float drag)
    {
        this->drag = drag;
    }

    /**
     * \brief angular_dragの実体を返す
     * \return angular_dragの実体
     */
    float RigidBodyComponent::GetAngularDrag()
    {
        return this->angular_drag;
    }

    /**
     * \brief velocityのセッター
     * \param velocity セットする値
     */
    void RigidBodyComponent::SetAngularDrag(float angular_drag)
    {
        this->angular_drag = angular_drag;
    }

    /**
     * \brief attractionの実体を返す
     * \return attractionの実体
     */
    bool RigidBodyComponent::GetAttraction()
    {
        return this->attraction;
    }

    /**
     * \brief attractionのセッター
     * \param attraction セットする値
     */
    void RigidBodyComponent::SetAttraction(bool attraction)
    {
        this->attraction = attraction;
    }

    /**
     * \brief freeze_positionの実体を返す
     * \return freeze_positionの実体
     */
    utility::Bool3 RigidBodyComponent::GetFreezePosition()
    {
        return *this->freeze_position;
    }

    /**
     * \brief freeze_positionのセッター
     * \param freeze_position セットする値
     */
    void RigidBodyComponent::SetFreezePosition(utility::Bool3 freeze_position)
    {
        this->freeze_position = &freeze_position;
    }

    /**
     * \brief freeze_rotationの実体を返す
     * \return freeze_rotationの実体
     */
    utility::Bool3 RigidBodyComponent::GetFreezeRotation()
    {
        return *this->freeze_rotation;
    }

    /**
     * \brief freeze_rotationのセッター
     * \param freeze_rotation セットする値
     */
    void RigidBodyComponent::SetFreezeRotation(utility::Bool3 freeze_rotation)
    {
        this->freeze_rotation = &freeze_rotation;
    }

}