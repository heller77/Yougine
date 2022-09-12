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
    bool Component::RegisterThisComponentToComponentList(Scene* scene)
    {
        if (register_component_list != nullptr)
        {
            throw"this component is already registerd";
            return false;
        }
        if (this->parent_gameobject == nullptr)
        {
            //parent_gameobjectがnullならエラー
            throw "exception,this compoent does not have parentGameobject";
            return false;
        }
        else if (this->component_name == managers::ComponentName::kNone)
        {
            //componentnameがkNoneなのにComponentListに追加しようとしているのでエラー
            throw "throw,this component can not register to ComponentList";
            return false;
        }
        scene->GetComponentList()->AddObjectToDictionary(this->component_name, this->parent_gameobject);
        this->register_component_list = scene->GetComponentList();
        return true;
    }

    void Component::UnregisterThisComponentFromComponentList()
    {
        this->register_component_list->RemoveObjectFromDictionary(this->component_name, this);
        this->register_component_list = nullptr;
    }
}
