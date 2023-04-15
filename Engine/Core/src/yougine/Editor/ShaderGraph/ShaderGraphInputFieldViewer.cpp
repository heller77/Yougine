#include "ShaderGraphInputFieldViewer.h"

namespace editor::shadergraph
{
    ShaderGraphInputFieldViewer::ShaderGraphInputFieldViewer()
    {
        properties_input_field = std::make_shared<PropertiesInputField>();
    }

    bool ShaderGraphInputFieldViewer::DrawView(std::any val, const char* val_name, bool enable_input, float field_width)
    {
        if (enable_input)
        {
            std::vector<std::any> propertie = { val, val_name };
            return properties_input_field->Draw(propertie, field_width);
        }
        else
        {
            ImGui::Text(val_name);
            return false;
        }
    }

}