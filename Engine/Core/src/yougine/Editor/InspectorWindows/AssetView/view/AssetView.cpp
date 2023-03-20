#include "AssetView.h"

#include <iostream>
#include <valarray>

#include "../../../ProjectWindows/Assets/element/Model/shader/ShaderFileAsset.h"
#include "imgui/stblib/imgui_stdlib.h"

void AssetView::AssetView::DrawAssetParameter()
{
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
            if (option->GetOnlyDisplayNotWrite())
            {
                std::string display_text = key + " : " + *value_str;
                ImGui::Text(display_text.c_str());
                continue;
            }

            ImGui::InputText(key.c_str(), value_str);
        }
        else if (value.type() == typeid(std::string))
        {
            if (option->GetOnlyDisplayNotWrite())
            {
                std::string value_str = std::any_cast<std::string>(value);
                std::string display_text = key + " : " + value_str;
                ImGui::Text(display_text.c_str());
                continue;
            }
        }
        else if (value.type() == typeid(int*))
        {
            int* value_int = std::any_cast<int*>(value);
            ImGui::InputInt(key.c_str(), value_int);
        }
        else if (value.type() == typeid(float*))
        {
            float* value_float = std::any_cast<float*>(value);
            ImGui::InputFloat(key.c_str(), value_float);
        }
        else if (value.type() == typeid(double*))
        {
            double* value_double = std::any_cast<double*>(value);
            ImGui::InputDouble(key.c_str(), value_double);
        }
        if (option->GetIsAsset())
        {
            //assetであることは分かる
            // editor::projectwindows::assets::elements::model::Asset* asset = std::any_cast<editor::projectwindows::assets::elements::model::Asset*>(value);
            //アセット一覧を表示
            //選んだらvalueなりにセットする
            // option->FireInputAction(utility::youginuuid::YougineUuid("fd"));
        }

        // bool is_badanycast = false;
        // try
        // {
        //     auto id = std::any_cast<std::shared_ptr<editor::projectwindows::assets::elements::model::shader::ShaderFileAsset>>(value);
        // }
        // catch (...)
        // {
        //     is_badanycast = true;
        // }
        //
        // if (!is_badanycast)
        // {
        //     std::cout << "asset !!" << std::endl;
        // }
        // // if (std::shared_ptr<BaseClass> basePtr = std::dynamic_pointer_cast<BaseClass>(std::any_cast<std::shared_ptr<DerivedClass>>(anyVar))) {
        // //     std::cout << "DerivedClass is derived from BaseClass." << std::endl;
        // // }
        // // std::any_cast<editor::projectwindows::assets::elements::model::Asset>(value)==nullptr;
        // // if (std::shared_ptr<editor::projectwindows::assets::elements::model::Asset> derivedPtr2 == std::dynamic_pointer_cast<editor::projectwindows::assets::elements::model::Asset>(std::any_cast<editor::projectwindows::assets::elements::model::Asset>(value))) {
        // //     std::cout << "DerivedClass is derived from AbstractClass." << std::endl;
        // // }

        if (enumtext == "enum")
        {
            std::cout << "enum!" << std::endl;
        }

    }
    if (ImGui::Button("save"))
    {
        this->asset->Export();
    }
}

AssetView::AssetView::AssetView(std::shared_ptr<editor::projectwindows::assets::elements::model::Asset> asset) : asset(asset)
{
    this->asset = asset;

    // this->class_func_vec.emplace("editor::projectwindows::assets::elements::model::shader::ShaderFileAsset")
}
