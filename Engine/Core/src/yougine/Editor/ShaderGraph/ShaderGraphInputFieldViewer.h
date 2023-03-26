#pragma once
#include "../PropertiesInputField.h"

namespace editor::shadergraph
{
    class ShaderGraphInputFieldViewer
    {
    private:
        std::shared_ptr<PropertiesInputField> properties_input_field;

    public:
        ShaderGraphInputFieldViewer();
        void DrawView(std::any val, const char* val_name);
    };
}
