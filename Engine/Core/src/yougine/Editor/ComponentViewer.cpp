#include "ComponentViewer.h"
#include "../utilitys/Quaternion.h"

namespace editor
{
    ComponentViewer::ComponentViewer(yougine::components::Component* component)
    {
        this->component = component;

        switch (component->GetComponentName())
        {
        case yougine::managers::ComponentName::kRender:
            component_name = "RenderComponent";
            break;
        case yougine::managers::ComponentName::kRigidBody:
            component_name = "RigidBodyComponent";
            break;
        case yougine::managers::ComponentName::kCollider:
            component_name = "ColliderComponent";
            break;
        case yougine::managers::ComponentName::kUIRender:
            component_name = "UIRenderComponent";
            break;
        case yougine::managers::ComponentName::kUICollider:
            component_name = "UIColliderComponent";
            break;
        case yougine::managers::ComponentName::kCustom:
            component_name = "CustomComponent";
            break;
        case yougine::managers::ComponentName::kNone:
            component_name = "TransformComponent";
            break;
        default:
            break;
        }

        accessable_properties = component->GetAccessablePropertiesList();
    }

    ComponentViewer::~ComponentViewer()
    {
        std::cout << component_name + "のComponentViewerがリセットされました" << std::endl;
    }

    void ComponentViewer::DrawViews()
    {
        for (std::vector<std::any> propertie : accessable_properties)
        {
            auto var = propertie[0];
            const char* v_name = std::any_cast<const char*>(propertie[1]);

            if (var.type() == typeid(int*))
            {
                IntView(std::any_cast<int*>(propertie[0]), v_name);
            }
            if (var.type() == typeid(float*))
            {
                FloatView(std::any_cast<float*>(propertie[0]), v_name);
            }
            if (var.type() == typeid(std::string*))
            {
                StringView(std::any_cast<std::string*>(propertie[0]), v_name);
            }
            if (var.type() == typeid(bool*))
            {
                BoolView(std::any_cast<bool*>(propertie[0]), v_name);
            }
            if (typeid(var) == typeid(std::any))
            {
                std::string typename_ = var.type().name();
                std::string str_type = utility::Split::SplitStr(utility::Split::SplitStr(var.type().name(), ' ')[1], '::').back();

                if (str_type == "Vector3")
                {
                    Vector3View(std::any_cast<utility::Vector3*>(propertie[0]), v_name);
                }
                else if (str_type == "Bool3")
                {
                    Bool3View(std::any_cast<utility::Bool3*>(propertie[0]), v_name);
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
                        QuaternionView(std::any_cast<std::shared_ptr<utility::Quaternion>>(propertie[0]), v_name);
                    }
                }
            }
        }
    }

    std::string ComponentViewer::GetComponentName()
    {
        return component_name;
    }

    void ComponentViewer::Bool3View(utility::Bool3* value, const char* name)
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

    void ComponentViewer::IntView(int* value, const char* name)
    {
        if (ImGui::InputInt(name, value));
    }

    void ComponentViewer::FloatView(float* value, const char* name)
    {
        if (ImGui::InputFloat(name, value));
    }

    void ComponentViewer::Vector3View(utility::Vector3* value, const char* name)
    {
        float values[3] = { value->x, value->y, value->z };
        if (ImGui::InputFloat3(name, values, "%.3f", ImGuiInputTextFlags_EnterReturnsTrue))
        {
            value->x = values[0];
            value->y = values[1];
            value->z = values[2];
        }
    }

    void ComponentViewer::QuaternionView(std::shared_ptr<utility::Quaternion> value, const char* name)
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

    void ComponentViewer::StringView(std::string* value, const char* name)
    {
        const int size_str = 32;
        char temp_s[size_str];
        strcpy_s(temp_s, size_str, (*value).c_str());

        char* temp_c = temp_s;
        if (ImGui::InputText(name, temp_c, 32))
        {
            *value = temp_c;
        }
    }

    void ComponentViewer::BoolView(bool* value, const char* name)
    {
        ImGui::Checkbox(name, value);
    }
}
