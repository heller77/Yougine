#pragma once
namespace yougine::components
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
