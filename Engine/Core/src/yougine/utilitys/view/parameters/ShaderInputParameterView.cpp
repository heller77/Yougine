#include "ShaderInputParameterView.h"

#include <iostream>
#include <memory>

#include "../../../Editor/ShaderGraph/ShaderType.h"
#include "imgui/stblib/imgui_stdlib.h"

void utility::view::parameters::ShaderInputParameterView::Draw()
{
    ImGui::Separator();
    ImGui::Text("shader input parameterview");
    int index = 0;
    for (auto element : *vec_shaderinput)
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
        ImGui::InputText("name", element->GetName());

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
        case materials::ShaderInputParameterType::kVec3: {
            ImGui::SameLine();
            auto value = element->Get_vec3_value();
            float tmpvalue[3] = { value->x,value->y,value->z };
            if (ImGui::ColorEdit3("value", tmpvalue))
            {
                value->x = tmpvalue[0];
                value->y = tmpvalue[1];
                value->z = tmpvalue[2];
            }
            break;
        }
        default:
            ImGui::SameLine();
            ImGui::Text("Type not supported");
            break;
        }
        ImGui::PopItemWidth();
        ImGui::PopID();
    }
    //追加ボタン
    ImGui::PushID(index++);
    ImGui::PushItemWidth(80);
    ImGui::Text("new input paramter ");
    ImGui::SameLine();
    if (ImGui::BeginCombo(this->label.c_str(), this->type2text[new_value->GetValueType()].c_str()))
    {
        for (auto pair : type2text)
        {
            auto target_type = pair.first;
            const bool is_selected = (target_type == new_value->GetValueType());
            auto typetext = type2text[target_type];
            //選んだ時
            if (ImGui::Selectable(typetext.c_str(), is_selected))
            {
                new_value = shaderinputparameters::ShaderInputAndTypeStruct::GenerateDefaultInstance(target_type, "newvalue");
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
    ImGui::InputText("name", new_value->GetName());


    switch (new_value->GetValueType())
    {
    case materials::ShaderInputParameterType::kFloat:
        ImGui::SameLine();
        if (ImGui::InputFloat("value", new_value->Get_float_value()))
        {
        }
        break;
    case materials::ShaderInputParameterType::kInt:
        ImGui::SameLine();
        if (ImGui::InputInt("value", new_value->Get_int_value()))
        {
        }
        break;
    case materials::ShaderInputParameterType::kVec3: {
        ImGui::SameLine();
        auto value = new_value->Get_vec3_value();
        float tmpvalue[3] = { value->x,value->y,value->z };
        if (ImGui::ColorEdit3("value", tmpvalue))
        {
            value->x = tmpvalue[0];
            value->y = tmpvalue[1];
            value->z = tmpvalue[2];
        }
        break;
    }
    default:
        ImGui::SameLine();
        ImGui::Text("Type not supported");
        break;
    }

    if (ImGui::Button("shader input parameter add"))
    {
        //newvalueを追加
        this->vec_shaderinput->push_back(this->new_value);
        this->new_value = shaderinputparameters::ShaderInputAndTypeStruct::GenerateDefaultInstance(materials::ShaderInputParameterType::kInt, "valuename");
    }
    ImGui::PopItemWidth();
    ImGui::PopID();

    ImGui::NewLine();
    ImGui::Separator();
}

utility::view::parameters::ShaderInputParameterView::ShaderInputParameterView(
    std::vector<std::shared_ptr<shaderinputparameters::ShaderInputAndTypeStruct>>* vec_shaderinput)
{
    // this->type_list = { "float", "vec3" };
    // label = "type";
    this->vec_shaderinput = vec_shaderinput;
    this->type2text = {
        {materials::ShaderInputParameterType::kFloat, "float"},
        {materials::ShaderInputParameterType::kInt, "int"},
        {materials::ShaderInputParameterType::kVec3, "vec3"}
    };
    this->new_value = shaderinputparameters::ShaderInputAndTypeStruct::GenerateDefaultInstance(materials::ShaderInputParameterType::kInt, "valuename");
}
