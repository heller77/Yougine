#include "ComponentViewer.h"
#include <typeinfo>

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
            component_name = "None";
            break;
        default:
            break;
        }
    }

    ComponentViewer::~ComponentViewer()
    {
        std::cout << component_name + "のComponentViewerがリセットされました" << std::endl;
    }


    void ComponentViewer::DrawViews()
    {
        for (std::any propertie : accessable_properties)
        {
            if (typeid(propertie).name() == "int") //int
            {
                IntView(std::any_cast<int*>(propertie));
            }
            if (typeid(propertie).name() == "float")
            {
                FloatView(std::any_cast<float*>(propertie));
            }
            if (typeid(propertie).name() == "Vector3")
            {
                Vector3View(std::any_cast<utility::Vector3*>(propertie));
            }
            if (typeid(propertie).name() == "string")
            {
                StringView(std::any_cast<std::string*>(propertie));
            }
            if (typeid(propertie).name() == "bool")
            {
                BoolView(std::any_cast<bool*>(propertie));
            }
        }
    }


    std::string ComponentViewer::GetComponentName()
    {
        return component_name;
    }

    void ComponentViewer::IntView(int* value)
    {
        ImGui::InputInt(GETVALUENAME(value), value);
    }

    void ComponentViewer::FloatView(float* value)
    {
        ImGui::InputFloat(GETVALUENAME(value), value);
    }

    void ComponentViewer::Vector3View(utility::Vector3* value)
    {
        float values[3] = { value->x, value->y, value->z };
        ImGui::InputFloat3(GETVALUENAME(value), values);
    }

    void ComponentViewer::StringView(std::string* value)
    {
        ImGui::InputText(GETVALUENAME(value), const_cast<char*>(value->c_str()), IM_ARRAYSIZE(value));
    }

    void ComponentViewer::BoolView(bool* value)
    {
        ImGui::Checkbox(GETVALUENAME(value), value);
    }



}