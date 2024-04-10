#include "ComponentViewer.h"
#include "UserShare/utilitys/Quaternion.h"

namespace editor
{
    ComponentViewer::ComponentViewer(yougine::components::Component* component)
    {
        this->component = component;

        switch (component->GetComponentName())
        {
        case yougine::components::ComponentName::kRender:
            component_name = "RenderComponent";
            break;
        case yougine::components::ComponentName::kRigidBody:
            component_name = "RigidBodyComponent";
            break;
        case yougine::components::ComponentName::kCollider:
            component_name = "ColliderComponent";
            break;
        case yougine::components::ComponentName::kUIRender:
            component_name = "UIRenderComponent";
            break;
        case yougine::components::ComponentName::kUICollider:
            component_name = "UIColliderComponent";
            break;
        case yougine::components::ComponentName::kCustom:
            component_name = "CustomComponent";
            break;
        case yougine::components::ComponentName::kNone:
            component_name = typeid(*component).name();
            break;
        default:
            break;
        }

        properties_input_field = std::make_shared<PropertiesInputField>();
    }

    ComponentViewer::~ComponentViewer()
    {
        std::cout << component_name + "のComponentViewerがリセットされました" << std::endl;
    }

    void ComponentViewer::DrawViews()
    {
        for (std::vector<std::any> propertie : component->GetAccessablePropertiesList())
        {
            properties_input_field->Draw(propertie);
        }
    }

    std::string ComponentViewer::GetComponentName()
    {
        return component_name;
    }

    yougine::components::Component* ComponentViewer::GetComponent()
    {
        return this->component;
    }
}
