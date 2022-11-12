#include "RigidBodyComponent.h"

namespace yougine::components
{
    RigidBodyComponent::RigidBodyComponent() : Component(managers::ComponentName::kNone)
    {
        this->velocity = new utility::Vector3(0, 0, 0);
        *this->mass = 1.00f;
        *this->drag = 1.00f;
        *this->angular_drag = 1.00f;
        *this->attraction = false;
        this->freeze_position = new utility::Bool3(false, false, false);
        this->freeze_rotation = new utility::Bool3(false, false, false);
    }

    RigidBodyComponent::RigidBodyComponent(utility::Vector3 velocity, float mass, float drag, float angular_drag, bool attraction, utility::Bool3 freeze_position, utility::Bool3 freeze_rotation) : Component(managers::ComponentName::kNone)
    {
        this->velocity = &velocity;
        this->mass = &mass;
        this->drag = &drag;
        this->angular_drag = &angular_drag;
        this->attraction = &attraction;
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
        return *this->mass;
    }

    /**
     * \brief massのセッター
     * \param mass セットする値
     */
    void RigidBodyComponent::SetMass(float mass)
    {
        this->mass = &mass;
    }

    /**
     * \brief dragの実体を返す
     * \return dragの実体
     */
    float RigidBodyComponent::GetDrag()
    {
        return *this->drag;
    }

    /**
     * \brief dragのセッター
     * \param drag セットする値
     */
    void RigidBodyComponent::SetDrag(float drag)
    {
        this->drag = &drag;
    }

    /**
     * \brief angular_dragの実体を返す
     * \return angular_dragの実体
     */
    float RigidBodyComponent::GetAngularDrag()
    {
        return *this->angular_drag;
    }

    /**
     * \brief velocityのセッター
     * \param velocity セットする値
     */
    void RigidBodyComponent::SetAngularDrag(float angular_drag)
    {
        this->angular_drag = &angular_drag;
    }

    /**
     * \brief attractionの実体を返す
     * \return attractionの実体
     */
    bool RigidBodyComponent::GetAttraction()
    {
        return *this->attraction;
    }

    /**
     * \brief attractionのセッター
     * \param attraction セットする値
     */
    void RigidBodyComponent::SetAttraction(bool attraction)
    {
        this->attraction = &attraction;
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