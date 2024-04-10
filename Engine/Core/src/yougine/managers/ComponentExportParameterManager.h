#pragma once
#include <any>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "UserShare/components/Component.h"
#include "UserShare/utilitys/uuid/YougineUuid.h"
#include "./../components/ComponentExportParameters/ComponentExportParameter.h"
#include "./../Editor/ProjectWindows/Assets/element/Model/Asset.h"

namespace assetnamespace = editor::projectwindows::assets::elements::model;
namespace yougine::managers
{


    /*
     * シーンにあるcomponent全てのSerializefieldのリストを使う
     */
    class ComponentExportParameterManager
    {
    private:
        /*
         * \brief uuid（コンポーネントのuuid）とそのコンポーネントのエクスポートしたいパラメータ(ComponentExportParameter)
         */
        std::map<std::shared_ptr<utility::youginuuid::YougineUuid>, std::shared_ptr<components::componentexportparameter::ComponentExportParameter>> serializefield_list;
    public:
        void Add(std::shared_ptr<utility::youginuuid::YougineUuid> uuid, std::shared_ptr<components::componentexportparameter::ComponentExportParameter> serializefield);
        std::shared_ptr<components::componentexportparameter::ComponentExportParameter> GetSerializeField(std::shared_ptr<utility::youginuuid::YougineUuid> uuid);
        /**
         * \brief AssetのサブクラスのフィールドをInspectorに露出するときに、uiから変更したときにフィールドにuiで選択した値を代入する為の関数を作る
         * \tparam fieldType
         * \param field
         * \param paramter_name
         * \return
         */
        template <class fieldType>
        static std::function<void(std::shared_ptr<assetnamespace::Asset>)> Generate_AssetTypeField_Switch_Function(components::Component* component, std::shared_ptr<fieldType>* field, std::string paramter_name) {
            std::function<void(std::shared_ptr<assetnamespace::Asset>)> function
                = [=](std::shared_ptr<assetnamespace::Asset> input)
            {
                std::shared_ptr<fieldType> input_cast_ptr = std::dynamic_pointer_cast<fieldType>(input);
                // std::shared_ptr<fieldType> input_cast_shared_ptr = std::shared_ptr<fieldType>(input_cast_ptr);
                // std::cout << typeid(field).name() << std::endl;

                if (input_cast_ptr)
                {
                    *field = input_cast_ptr;
                    for (int i = 0; i < component->GetAccessablePropertiesList().size(); i++)
                    {
                        auto element = component->GetAccessablePropertiesList()[i];
                        auto name = std::any_cast<const char*>(element[1]);
                        if (name == paramter_name)
                        {
                            std::vector<std::vector<std::any>>* accessablePropertiesList = component->GetPtrAccessablePropertiesList();
                            (*accessablePropertiesList)[i][0] = std::static_pointer_cast<editor::projectwindows::assets::elements::model::Asset>(input_cast_ptr);;
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

    };
}
