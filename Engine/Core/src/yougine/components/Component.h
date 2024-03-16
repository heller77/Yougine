#pragma once
#include "../Scene.h"
#include "../managers/ComponentName.h"
#include <any>
#include <functional>
#include "./../Editor/ProjectWindows/Assets/element/Model/Asset.h"

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
        managers::ComponentName component_name;
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

        /**
         * \brief AssetのサブクラスのフィールドをInspectorに露出するときに、uiから変更したときにフィールドにuiで選択した値を代入する為の関数を作る
         * \tparam fieldType
         * \param field
         * \param paramter_name
         * \return
         */
        template <class fieldType>
        std::function<void(std::shared_ptr<editor::projectwindows::assets::elements::model::Asset>)> Generate_AssetTypeField_Switch_Function(std::shared_ptr<fieldType>* field, std::string paramter_name) {
            std::function<void(std::shared_ptr<editor::projectwindows::assets::elements::model::Asset>)> function
                = [=](std::shared_ptr<editor::projectwindows::assets::elements::model::Asset> input)
            {
                std::shared_ptr<fieldType> input_cast_ptr = std::dynamic_pointer_cast<fieldType>(input);
                // std::shared_ptr<fieldType> input_cast_shared_ptr = std::shared_ptr<fieldType>(input_cast_ptr);
                // std::cout << typeid(field).name() << std::endl;
                if (input_cast_ptr)
                {
                    *field = input_cast_ptr;
                    for (int i = 0; i < accessable_properties_list.size(); i++)
                    {
                        auto element = accessable_properties_list[i];
                        auto name = std::any_cast<const char*>(element[1]);
                        if (name == paramter_name)
                        {
                            accessable_properties_list[i][0] = std::static_pointer_cast<editor::projectwindows::assets::elements::model::Asset>(input_cast_ptr);
                        }
                    }
                }
                else
                {
                    std::cout << "cast failed!! in Field_SwitchFunction" << std::endl;
                }
            };
            return function;
        }

    private:
        void InitializeProperties();

    public:
        Component(managers::ComponentName componentname);
        ~Component();
        virtual void Excute();
        managers::ComponentName GetComponentName();
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
