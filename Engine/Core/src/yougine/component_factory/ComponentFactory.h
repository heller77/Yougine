#pragma once
#include "UserShare//components/Component.h"

namespace yougine::componentfactorys
{
    class ComponentFacotory
    {
    public:
        /**
         * \brief
         * \param component_class_name 生成するコンポーネントのクラスの名前
         * \return
         */
        components::Component* CreateComponent(std::string component_class_name);

    };
}