#include "PropertiesInputField.h"
#include "../utilitys/view/parameters/AssetReference.h"
#include "../utilitys/view/parameters/ShaderInputParameterView.h"

#include <iostream>

namespace editor
{
    bool PropertiesInputField::Draw(std::vector<std::any> propertie, float field_width)
    {
        auto val = propertie[0];
        const char* val_name = std::any_cast<const char*>(propertie[1]);

        if (field_width > 0) ImGui::PushItemWidth(field_width);//Field幅を変更

        bool is_updated_value = false;

        if (val.type() == typeid(int*))
        {
            is_updated_value = IntView(std::any_cast<int*>(val), val_name);
        }
        if (val.type() == typeid(float*))
        {
            is_updated_value = FloatView(std::any_cast<float*>(val), val_name);
        }
        if (val.type() == typeid(std::string*))
        {
            is_updated_value = StringView(std::any_cast<std::string*>(val), val_name); /////////
        }
        if (val.type() == typeid(bool*))
        {
            is_updated_value = BoolView(std::any_cast<bool*>(val), val_name);
        }
        if (typeid(val) == typeid(std::any))
        {
            std::string typename_ = val.type().name();
            std::string str_type = utility::Split::SplitStr(utility::Split::SplitStr(val.type().name(), ' ')[1], '::').back();

            if (str_type == "Vector3")
            {
                is_updated_value = Vector3View(std::any_cast<utility::Vector3*>(val), val_name);
            }
            else if (str_type == "Bool3")
            {
                is_updated_value = Bool3View(std::any_cast<utility::Bool3*>(val), val_name);
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
                    is_updated_value = QuaternionView(std::any_cast<std::shared_ptr<utility::Quaternion>>(val), val_name);
                }
                else if (contentOfsharedptr == "class editor::projectwindows::assets::elements::model::Asset")
                {
                    // std::cout << "asset!!" << std::endl;
                    auto asset = std::any_cast<std::shared_ptr<projectwindows::assets::elements::model::Asset>>(val);
                    auto func = std::any_cast<std::function<void(std::shared_ptr<editor::projectwindows::assets::elements::model::Asset>)>>(propertie[2]);
                    ImGui::Text(asset->GetAssetId()->convertstring().c_str());
                    asset->GetParameter();


                    std::make_shared<utility::view::parameters::AssetReference>(val_name, asset->GetAssetId(), [&](std::shared_ptr<editor::projectwindows::assets::elements::model::Asset> input)
                        {
                            func(input);
                        })->Draw();
                }
            }
        }

        if (field_width > 0) ImGui::PopItemWidth();//幅をデフォルトに戻す

        return is_updated_value;
    }

    bool PropertiesInputField::Bool3View(utility::Bool3* value, const char* name)
    {
        bool is_updated_value = false;

        if (ImGui::TreeNode(name)) {
            is_updated_value = ImGui::Checkbox("x ", &value->x);
            ImGui::SameLine();
            // ImGui::Spacing();

            is_updated_value = ImGui::Checkbox("y ", &value->y);
            ImGui::SameLine();
            // ImGui::Spacing();

            is_updated_value = ImGui::Checkbox("z ", &value->z);

            ImGui::TreePop();
        }
        // ImGui::TreePop();

        return is_updated_value;

    }

    bool PropertiesInputField::IntView(int* value, const char* name)
    {
        return (ImGui::InputInt(name, value));
    }

    bool PropertiesInputField::FloatView(float* value, const char* name)
    {
        return (ImGui::InputFloat(name, value));
    }

    bool PropertiesInputField::Vector3View(utility::Vector3* value, const char* name)
    {
        float values[3] = { value->x, value->y, value->z };
        if (ImGui::InputFloat3(name, values, "%.3f"))
        {
            value->x = values[0];
            value->y = values[1];
            value->z = values[2];

            return true;
        }

        return false;
    }

    bool PropertiesInputField::QuaternionView(std::shared_ptr<utility::Quaternion> value, const char* name)
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

            return true;
        }

        return false;
    }

    bool PropertiesInputField::StringView(std::string* value, const char* name)
    {
        const int size_str = 32; //ここのサイズが小さいからエラーになっている(Vector3ノードとUnlitのAlbedoを繋げたとき)
        char temp_s[size_str];
        strcpy_s(temp_s, size_str, (*value).c_str());

        char* temp_c = temp_s;
        if (ImGui::InputText(name, temp_c, 32))
        {
            *value = temp_c;
            return true;
        }

        return false;
    }

    bool PropertiesInputField::BoolView(bool* value, const char* name)
    {
        return ImGui::Checkbox(name, value);
    }

}
