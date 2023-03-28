#include "PropertiesInputField.h"

#include <iostream>

namespace editor
{
    void PropertiesInputField::Draw(std::any val, const char* val_name)
    {
        if (val.type() == typeid(int*))
        {
            IntView(std::any_cast<int*>(val), val_name);
        }
        if (val.type() == typeid(float*))
        {
            FloatView(std::any_cast<float*>(val), val_name);
        }
        if (val.type() == typeid(std::string*))
        {
            StringView(std::any_cast<std::string*>(val), val_name); /////////
        }
        if (val.type() == typeid(bool*))
        {
            BoolView(std::any_cast<bool*>(val), val_name);
        }
        if (typeid(val) == typeid(std::any))
        {
            std::string typename_ = val.type().name();
            std::string str_type = utility::Split::SplitStr(utility::Split::SplitStr(val.type().name(), ' ')[1], '::').back();

            if (str_type == "Vector3")
            {
                Vector3View(std::any_cast<utility::Vector3*>(val), val_name);
            }
            else if (str_type == "Bool3")
            {
                Bool3View(std::any_cast<utility::Bool3*>(val), val_name);
            }
            //sharedptrかどうか
            auto sharedptrIndex = typename_.find("shared_ptr");
            int typename_len = typename_.length();
            if (typename_.find("shared_ptr") != std::string::npos)
            {
                sharedptrIndex += 10;
                sharedptrIndex += 1;
                std::string contentOfsharedptr = typename_.
                    substr(sharedptrIndex, typename_len - sharedptrIndex - 1);
                // std::cout << contentOfsharedptr << std::endl;
                if (contentOfsharedptr == "class utility::Quaternion")
                {
                    QuaternionView(std::any_cast<std::shared_ptr<utility::Quaternion>>(val), val_name);
                }
            }
        }
    }

    void PropertiesInputField::Bool3View(utility::Bool3* value, const char* name)
    {
        if (ImGui::TreeNode(name)) {
            ImGui::Checkbox("x ", &value->x);
            ImGui::SameLine();
            // ImGui::Spacing();

            ImGui::Checkbox("y ", &value->y);
            ImGui::SameLine();
            // ImGui::Spacing();

            ImGui::Checkbox("z ", &value->z);


            ImGui::TreePop();
        }
        // ImGui::TreePop();

    }

    void PropertiesInputField::IntView(int* value, const char* name)
    {
        if (ImGui::InputInt(name, value));
    }

    void PropertiesInputField::FloatView(float* value, const char* name)
    {
        if (ImGui::InputFloat(name, value));
    }

    void PropertiesInputField::Vector3View(utility::Vector3* value, const char* name)
    {
        float values[3] = { value->x, value->y, value->z };
        if (ImGui::InputFloat3(name, values, "%.3f", ImGuiInputTextFlags_EnterReturnsTrue))
        {
            value->x = values[0];
            value->y = values[1];
            value->z = values[2];
        }
    }

    void PropertiesInputField::QuaternionView(std::shared_ptr<utility::Quaternion> value, const char* name)
    {
        // float qvalue[4] = {value->x, value->y, value->z, value->w};
        // if (ImGui::InputFloat4("quaternion", qvalue, "%.3f", ImGuiInputTextFlags_EnterReturnsTrue))
        // {
        //     value->x = qvalue[0];
        //     value->y = qvalue[1];
        //     value->z = qvalue[2];
        //     value->w = qvalue[3];
        // }

        auto radian = value->CalculateEuler();
        float values[3] = { radian.x, radian.y, radian.z };
        // float values[4] = {value->x,value->y,value->z,value->w};
        if (ImGui::InputFloat3(name, values, "%.3f", ImGuiInputTextFlags_EnterReturnsTrue))
        {
            // std::cout << "euler " << values[0] << " " << values[1] << " " << values[2] << std::endl;
            auto q = utility::Quaternion::GenerateQuartanionFromEuler(values[0], values[1], values[2]);
            auto qeuler = q->CalculateEuler();
            // std::cout << qeuler.x<<" " << qeuler.y<<" "<<qeuler.z << std::endl;
            // value->x = values[0];
            // value->y = values[1];
            // value->z = values[2];
            // value->w = values[3];

            *value = q;
            // value->x = q->x;
            // value->y = q->y;
            // value->z = q->z;
            // value->w = q->w;
        }
    }

    void PropertiesInputField::StringView(std::string* value, const char* name)
    {
        const int size_str = 32; //ここのサイズが小さいからエラーになっている(Vector3ノードとUnlitのAlbedoを繋げたとき)
        char temp_s[size_str];
        strcpy_s(temp_s, size_str, (*value).c_str());

        char* temp_c = temp_s;
        if (ImGui::InputText(name, temp_c, 32))
        {
            *value = temp_c;
        }
    }

    void PropertiesInputField::BoolView(bool* value, const char* name)
    {
        ImGui::Checkbox(name, value);
    }

}
