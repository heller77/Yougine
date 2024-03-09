#pragma once
#include "Component.h"
#include "UserShare/utilitys/YougineMath.h"

namespace yougine::components
{
    class RigidBodyComponent : public yougine::components::Component
    {
    private:
        utility::Vector3* velocity; // 速度
        utility::Vector3* angular_velocity; // 回転速度
        utility::Vector3* acceleration; // 加速度
        utility::Vector3* angular_acceleration; // 回転加速度
        float mass; // 質量
        float drag; // 抵抗係数
        float angular_drag; // トルク抵抗係数
        bool attraction; // 引力の有無

        utility::Bool3* freeze_position; // 各軸の移動を固定する
        utility::Bool3* freeze_rotation; // 各回転軸の移動を固定する

    public:
        RigidBodyComponent();

        utility::Vector3 GetVelocity();
        void SetVelocity(utility::Vector3 velocity);

        utility::Vector3 GetAngularVelocity();
        void SetAngularVelocity(utility::Vector3 angular_velocity);

        utility::Vector3 GetAcceleration();
        void SetAcceleration(utility::Vector3 acceleration);

        utility::Vector3 GetAngularAcceleration();
        void SetAngularAcceleration(utility::Vector3 angular_acceleration);

        float GetMass();
        void SetMass(float mass);

        float GetDrag();
        void SetDrag(float drag);

        float GetAngularDrag();
        void SetAngularDrag(float angular_drag);

        bool GetAttraction();
        void SetAttraction(bool attraction);

        utility::Bool3 GetFreezePosition();
        void SetFreezePosition(utility::Bool3 freeze_position);

        utility::Bool3 GetFreezeRotation();
        void SetFreezeRotation(utility::Bool3 freeze_rotation);

    };
}

