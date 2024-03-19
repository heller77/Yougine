#pragma once
#include "UserShare/MacroDifHeader.h"
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
