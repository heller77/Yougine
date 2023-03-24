#include "ShaderInputParameterView.h"

#include <iostream>

#include "../../../Editor/ShaderGraph/ShaderType.h"
#include "imgui/stblib/imgui_stdlib.h"

void utility::view::parameters::ShaderInputParameterView::Draw()
{
    ImGui::Text("shader input parameterview");
    int index = 0;
    for (auto element : this->vec_shaderinput)
    {
        ImGui::PushID(index++);
        ImGui::PushItemWidth(80);

        auto type = element->GetValueType();
        std::string combo_preview_value = this->type2text[type];
        std::string labelname = label;
        index++;
        if (ImGui::BeginCombo(labelname.c_str(), combo_preview_value.c_str()))
        {
            for (auto pair : type2text)
            {
                auto target_type = pair.first;
                const bool is_selected = (target_type == type);
                auto typetext = type2text[target_type];
                //選んだ時
                if (ImGui::Selectable(typetext.c_str(), is_selected))
                {
                    std::cout << "select" << std::endl;
                }
                if (is_selected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }

        ImGui::SameLine();

        // //名前入力
        ImGui::InputText("name", &name);

        // ImGui::SameLine();
        switch (type)
        {
        case materials::ShaderInputParameterType::kFloat:
            ImGui::SameLine();
            if (ImGui::InputFloat("value", element->Get_float_value()))
            {
            }
            break;
        case materials::ShaderInputParameterType::kInt:
            ImGui::SameLine();
            if (ImGui::InputInt("value", element->Get_int_value()))
            {
            }
            break;
        default:
            ImGui::SameLine();
            ImGui::Text("Type not supported");
            break;
        }
        ImGui::PopItemWidth();
        ImGui::PopID();
    }
}

utility::view::parameters::ShaderInputParameterView::ShaderInputParameterView(
    std::vector<std::shared_ptr<shaderinputparameters::ShaderInputAndTypeStruct>> vec_shaderinput)
{
    // this->type_list = { "float", "vec3" };
    label = "type";
    this->vec_shaderinput = vec_shaderinput;
    this->type2text = {
        {materials::ShaderInputParameterType::kFloat, "float"},
        {materials::ShaderInputParameterType::kInt, "int"}
    };
}
