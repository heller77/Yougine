#include "Component.h"
#include <iostream>

namespace yougine::components
{
    Component::Component()
    {
        this->parent_gameobject = nullptr;
    }

    Component::~Component()
    {

    }

    //private
    void Component::InitializeProperties()
    {

    }

    //public
    void Component::Excute()
    {
        std::cout << "excute" << std::endl;
    }

    void Component::InitializeOnPlayBack()
    {
        std::cout << "initialize component" << std::endl;
    }

    bool Component::operator==(const Component& rhs) const
    {
        return *this == rhs;
    }

    GameObject* Component::GetGameObject()
    {
        return parent_gameobject;
    }
}