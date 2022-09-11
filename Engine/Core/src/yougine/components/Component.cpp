#include "Component.h"
#include <iostream>

namespace yougine::components
{
    Component::Component(managers::ComponentName componentname)
    {
        this->parent_gameobject = nullptr;
        this->component_name = componentname;
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
    void Component::SetParentGameObject(GameObject* parent_gameobject)
    {
        this->parent_gameobject = parent_gameobject;
    }

    /**
     * \brief parentgameobjectがnullの場合エラーを出す（SetParentGameObject関数を先に呼ばないとエラーになる）
     * \param scene parentGameobjectが所属するシーン
     */
    void Component::SetThisComponentToComponentList(Scene* scene)
    {
        if (this->parent_gameobject == nullptr)
        {
            //parent_gameobjectが
            throw "exception,this compoent does not have parentGameobject";
            return;
        }
        else if (this->component_name == managers::ComponentName::kNone)
        {
            throw "throw,this component can not register to ComponentList";
            return;
        }
        scene->GetComponentList()->AddObjectToDictionary(this->component_name, this->parent_gameobject);
    }
}