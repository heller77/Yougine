#include "ShaderGraphInputFieldViewer.h"

namespace editor::shadergraph
{
    ShaderGraphInputFieldViewer::ShaderGraphInputFieldViewer()
    {
        properties_input_field = std::make_shared<PropertiesInputField>();
    }

    void ShaderGraphInputFieldViewer::DrawView(std::any val, const char* val_name, bool enable_input, float field_width)
    {
        if (enable_input)
        {
            properties_input_field->Draw(val, val_name, field_width);
        }
        else
        {
            ImGui::Text(val_name);
        }
    }

}