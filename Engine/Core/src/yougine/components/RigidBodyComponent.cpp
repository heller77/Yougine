#include "RigidBodyComponent.h"

namespace yougine::components
{
    RigidBodyComponent::RigidBodyComponent() : Component(managers::ComponentName::kRigidBody)
    {
        this->velocity = new utility::Vector3(0, 0, 0); // x, y, z方向に関する速度
        this->angular_velocity = new utility::Vector3(0, 0, 0); // x, y, z方向に関する速度
        this->acceleration = new utility::Vector3(0, 0, 0); // x, y, z方向に関する加速度
        this->angular_acceleration = new utility::Vector3(0, 0, 0); // x, y, z方向に関する加速度
        this->mass = 1.00f; // オブジェクトの質量
        this->drag = 0.10f; // オブジェクトの抵抗
        this->angular_drag = 0.10f; // オブジェクトの回転に関する抵抗
        this->attraction = false; // 引力を受けるかどうか
        this->freeze_position = new utility::Bool3(false, false, false); // x, y, z方向に関して動きを無効化するかどうか
        this->freeze_rotation = new utility::Bool3(false, false, false); // 回転に関して動きを無効化するかどうか
        accessable_properties_list.push_back(std::vector<std::any>{velocity, GETVALUENAME(velocity)});
        accessable_properties_list.push_back(std::vector<std::any>{angular_velocity, GETVALUENAME(angular_velocity)});
        accessable_properties_list.push_back(std::vector<std::any>{acceleration, GETVALUENAME(acceleration)});
        accessable_properties_list.push_back(std::vector<std::any>{angular_acceleration, GETVALUENAME(angular_acceleration)});
        accessable_properties_list.push_back(std::vector<std::any>{&mass, GETVALUENAME(mass)});
        accessable_properties_list.push_back(std::vector<std::any>{&drag, GETVALUENAME(drag)});
        accessable_properties_list.push_back(std::vector<std::any>{&angular_drag, GETVALUENAME(angular_drag)});
        accessable_properties_list.push_back(std::vector<std::any>{&attraction, GETVALUENAME(attraction)});
        accessable_properties_list.push_back(std::vector<std::any>{freeze_position, GETVALUENAME(freeze_position)});
        accessable_properties_list.push_back(std::vector<std::any>{freeze_rotation, GETVALUENAME(freeze_rotation)});
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
        (*this->velocity).x = velocity.x;
        (*this->velocity).y = velocity.y;
        (*this->velocity).z = velocity.z;
    }

    /**
     * \brief velocityの実体を返す（参照ではないので変更しても、rigidbody.velocityそのものを変更できる訳ではない）
     * \return velocityの実体
     */
    utility::Vector3 RigidBodyComponent::GetAngularVelocity()
    {
        return *this->angular_velocity;
    }

    /**
     * \brief velocityのセッター
     * \param velocity セットする値
     */
    void RigidBodyComponent::SetAngularVelocity(utility::Vector3 angular_velocity)
    {
        (*this->angular_velocity).x = angular_velocity.x;
        (*this->angular_velocity).y = angular_velocity.y;
        (*this->angular_velocity).z = angular_velocity.z;
    }

    /**
     * \brief accelerationの実体を返す（参照ではないので変更しても、rigidbody.accelerationそのものを変更できる訳ではない）
     * \return accelerationの実体
     */
    utility::Vector3 RigidBodyComponent::GetAcceleration()
    {
        return *this->acceleration;
    }

    /**
     * \brief accelerationのセッター
     * \param acceleration セットする値
     */
    void RigidBodyComponent::SetAcceleration(utility::Vector3 acceleration)
    {
        (*this->acceleration).x = acceleration.x;
        (*this->acceleration).y = acceleration.y;
        (*this->acceleration).z = acceleration.z;
    }

    /**
     * \brief accelerationの実体を返す（参照ではないので変更しても、rigidbody.accelerationそのものを変更できる訳ではない）
     * \return accelerationの実体
     */
    utility::Vector3 RigidBodyComponent::GetAngularAcceleration()
    {
        return *this->angular_acceleration;
    }

    /**
     * \brief accelerationのセッター
     * \param acceleration セットする値
     */
    void RigidBodyComponent::SetAngularAcceleration(utility::Vector3 angular_acceleration)
    {
        (*this->angular_acceleration).x = angular_acceleration.x;
        (*this->angular_acceleration).y = angular_acceleration.y;
        (*this->angular_acceleration).z = angular_acceleration.z;
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
        (*this->freeze_position).x = freeze_position.x;
        (*this->freeze_position).y = freeze_position.y;
        (*this->freeze_position).z = freeze_position.z;
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
        (*this->freeze_rotation).x = freeze_rotation.x;
        (*this->freeze_rotation).y = freeze_rotation.y;
        (*this->freeze_rotation).z = freeze_rotation.z;
    }

}