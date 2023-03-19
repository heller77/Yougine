#include "AssetView.h"

#include <iostream>

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
}
