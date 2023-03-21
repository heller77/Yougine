#include "AssetView.h"

#include <iostream>
#include <valarray>

#include "../../../../Projects/Project.h"
#include "../../../../utilitys/view/parameters/CustomParameter.h"
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


        if (enumtext == "enum")
        {
            std::cout << "enum!" << std::endl;
        }

    }
}

