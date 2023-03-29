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
            return properties_input_field->Draw(val, val_name, field_width);
        }
        else
        {
            ImGui::Text(val_name);
            return false;
        }
    }

}