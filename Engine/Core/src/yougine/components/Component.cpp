#include "Component.h"
#include <iostream>

namespace yougine::components
{
    Component::Component(managers::ComponentName componentname)
    {
        this->parent_gameobject = nullptr;
        this->component_name = componentname;

        this->register_component_list = nullptr;
        this->yougine_uuid = std::shared_ptr<utility::youginuuid::YougineUuid>();
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

    managers::ComponentName Component::GetComponentName()
    {
        return component_name;
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
        if (this->component_name == managers::ComponentName::kNone)
        {
            //componentnameがkNoneなのでComponentListに追加しない
            return false;
        }
        scene->GetComponentList()->AddObjectToDictionary(this->component_name, this);
        this->register_component_list = scene->GetComponentList();
        return true;
    }

    void Component::UnregisterThisComponentFromComponentList()
    {
        this->register_component_list->RemoveComponentFromDictionary(this->component_name, this);
        this->register_component_list = nullptr;
    }

    //登録されているかどうか
    bool Component::isAlradyRegisterComponentList()
    {
        return !(register_component_list == nullptr);
    }

    std::vector<std::vector<std::any>> Component::GetAccessablePropertiesList()
    {
        return accessable_properties_list;
    }

    std::vector<std::vector<std::any>>* Component::GetPtrAccessablePropertiesList()
    {
        return &accessable_properties_list;
    }

    std::shared_ptr<utility::youginuuid::YougineUuid> Component::GetUUid()
    {
        return this->yougine_uuid;
    }
}
