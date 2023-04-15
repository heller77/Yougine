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
            component_name = typeid(*component).name();
            break;
        default:
            break;
        }

        accessable_properties = component->GetAccessablePropertiesList();
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
}
