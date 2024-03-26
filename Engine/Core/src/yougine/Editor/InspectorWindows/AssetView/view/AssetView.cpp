#include "AssetView.h"

#include <iostream>
#include <memory>
#include <valarray>

#include "../../../../Projects/Project.h"
#include "../../../../utilitys/view/parameters/CustomParameter.h"
#include "../../../../utilitys/view/parameters/ShaderInputParameterView.h"
#include "../../../ProjectWindows/Assets/element/Model/Material/ShaderInputParameters/ShaderInputAndTypeStruct.h"
#include "../../../ProjectWindows/Assets/element/Model/shader/ShaderFileAsset.h"
#include "imgui/stblib/imgui_stdlib.h"

void AssetView::AssetView::DrawAssetParameter()
{
    for (auto parameter : this->parameter_vec)
    {
        parameter->Draw();
    }
    if (ImGui::Button("save"))
    {
        this->asset->Export();
    }
}



AssetView::AssetView::AssetView(std::shared_ptr<editor::projectwindows::assets::elements::model::Asset> asset)
{
    this->asset = asset;

    auto parametermap = asset->GetParameter();
    for (auto pair : parametermap)
    {
        auto key = pair.first;
        auto value = pair.second->GetValue();
        auto option = pair.second->GetOption();

        std::string type_name = value.type().name();
        //string int float 

        //enumならenumという文字列が入る。
        auto enumtext = type_name.substr(0, 4);
        // std::string typename = std::string(value.type().name());
        if (value.type() == typeid(std::string*))
        {
            std::string* value_str = std::any_cast<std::string*>(value);
            std::function<void()> func = [=]()
            {

                if (option->GetOnlyDisplayNotWrite())
                {
                    std::string display_text = key + " : " + *value_str;
                    ImGui::Text(display_text.c_str());
                }

                ImGui::InputText(key.c_str(), value_str);
            };

            this->parameter_vec.emplace_back(std::make_shared<utility::view::parameters::CustomParameter>(func));

        }
        else if (value.type() == typeid(std::string))
        {

            std::function<void()> func = [=]()
            {
                if (option->GetOnlyDisplayNotWrite())
                {
                    std::string value_str = std::any_cast<std::string>(value);
                    std::string display_text = key + " : " + value_str;
                    ImGui::Text(display_text.c_str());
                }
            };
            this->parameter_vec.emplace_back(std::make_shared<utility::view::parameters::CustomParameter>(func));
        }
        else if (value.type() == typeid(int*))
        {

            std::function<void()> func = [=]()
            {
                int* value_int = std::any_cast<int*>(value);
                ImGui::InputInt(key.c_str(), value_int);
            };
            this->parameter_vec.emplace_back(std::make_shared<utility::view::parameters::CustomParameter>(func));
        }
        else if (value.type() == typeid(float*))
        {

            std::function<void()> func = [=]()
            {
                float* value_float = std::any_cast<float*>(value);
                ImGui::InputFloat(key.c_str(), value_float);
            };
            this->parameter_vec.emplace_back(std::make_shared<utility::view::parameters::CustomParameter>(func));
        }
        else if (value.type() == typeid(double*))
        {

            std::function<void()> func = [=]()
            {
                double* value_double = std::any_cast<double*>(value);
                ImGui::InputDouble(key.c_str(), value_double);
            };
            this->parameter_vec.emplace_back(std::make_shared<utility::view::parameters::CustomParameter>(func));
        }
        if (option->GetIsAsset())
        {
            //assetであることは分かる
            // editor::projectwindows::assets::elements::model::Asset* asset = std::any_cast<editor::projectwindows::assets::elements::model::Asset*>(value);
            //アセット一覧を表示
            //選んだらvalueなりにセットする
            // option->FireInputAction(utility::youginuuid::YougineUuid("fd"));
            auto yougineuuid = std::any_cast<std::shared_ptr < utility::youginuuid::YougineUuid >> (value);

            this->parameter_vec.emplace_back(std::make_shared<utility::view::parameters::AssetReference>(key.c_str(), yougineuuid, option->GetInputAction_input_Asset()));
        }

        auto template_start_pos = type_name.find("<");

        if (template_start_pos != std::string::npos) {
            //最後の>
            auto template_end_pos = type_name.rfind(">", template_start_pos);
            auto edge_template_and_allocator = type_name.find(",", template_start_pos);//これより前がvecに入っている型

            //vec
            auto classname = type_name.substr(0, template_start_pos);
            auto template_name = type_name.substr(template_start_pos + 1, edge_template_and_allocator - template_start_pos - 1);

            // std::cout << template_start_pos << " : " << template_end_pos << std::endl;
            // std::cout << "template before" << classname << std::endl;
            // std::cout << "template name : " << template_name << std::endl;
            if (classname == "class std::vector")
            {
                std::cout << "vec!!" << std::endl;
                if (template_name == "class std::shared_ptr<class editor::projectwindows::assets::elements::model::materials::shaderinputparameters::ShaderInputAndTypeStruct>")
                {
                    namespace  shaderinputstruct_namespace = editor::projectwindows::assets::elements::model::materials::shaderinputparameters;
                    std::vector<std::shared_ptr<shaderinputstruct_namespace::ShaderInputAndTypeStruct>>* vec_shaderinput
                        = std::any_cast<std::vector<std::shared_ptr<shaderinputstruct_namespace::ShaderInputAndTypeStruct>>*>(value);
                    std::cout << "class std::shared_ptr<class editor::projectwindows::assets::elements::model::materials::shaderinputparameters::ShaderInputAndTypeStruct>!!" << std::endl;
                    this->parameter_vec.emplace_back(std::make_shared <utility::view::parameters::ShaderInputParameterView>(vec_shaderinput));
                }
            }
        }

        if (enumtext == "enum")
        {
            std::cout << "enum!" << std::endl;
        }

    }
}

