#pragma once
namespace yougine::managers
{
    enum class ComponentName
    {
        kCollider,
        kRigidBody,
        kRender,
        kUIRender,
        kUICollider,
        kCustom,
        kNone//ComponentListに所属しないやつ
    };
}
