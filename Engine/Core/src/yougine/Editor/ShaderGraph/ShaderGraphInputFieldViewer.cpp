#include "ShaderGraphInputFieldViewer.h"

namespace editor::shadergraph
{
    ShaderGraphInputFieldViewer::ShaderGraphInputFieldViewer()
    {
        properties_input_field = std::make_shared<PropertiesInputField>();
    }

    void ShaderGraphInputFieldViewer::DrawView(std::any val, const char* val_name)
    {
        properties_input_field->Draw(val, val_name);
    }

}