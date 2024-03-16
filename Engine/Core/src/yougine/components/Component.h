#pragma once
#include "../Scene.h"
#include "ComponentName.h"
#include <any>
#include <functional>

#include "./../utilitys/uuid/YougineUuid.h"
namespace yougine
{
    class GameObject;
}

namespace yougine::components
{
    class Component
    {
#define GETVALUENAME(name) (#name)
    private:
        GameObject* parent_gameobject;
        components::ComponentName component_name;
        // bool isRegisterdToComponentList;
        /**
         * \brief 登録しているComponentList
         */
        managers::ComponentList* register_component_list;

        /**
         * \brief uuid
         */
        std::shared_ptr<utility::youginuuid::YougineUuid> yougine_uuid;

    protected:
        std::vector<std::vector<std::any>> accessable_properties_list;


    private:
        void InitializeProperties();

    public:
        Component(components::ComponentName componentname);
        ~Component();
        virtual void Excute();
        components::ComponentName GetComponentName();
        void InitializeOnPlayBack();
        bool operator==(const Component& rhs) const;
        GameObject* GetGameObject();
        void SetParentGameObject(GameObject* parent_gameobject);
        bool RegisterThisComponentToComponentList(Scene* scene);
        void UnregisterThisComponentFromComponentList();
        bool isAlradyRegisterComponentList();
        std::vector<std::vector<std::any>> GetAccessablePropertiesList();
        std::vector<std::vector<std::any>>* GetPtrAccessablePropertiesList();

        /**
         * \brief uuidを返す
         * \return
         */
        std::shared_ptr<utility::youginuuid::YougineUuid> GetUUid();


    };
}
