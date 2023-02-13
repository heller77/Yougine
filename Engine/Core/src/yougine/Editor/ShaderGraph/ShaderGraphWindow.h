#pragma once
#include "imnodes/imnodes.h"
#include "imgui/imgui.h"
#include "../EditorWindow.h"

namespace editor::shadergraph
{
    class ShaderGraphWindow : public EditorWindow
    {
    public:
        ShaderGraphWindow(EditorWindowsManager* editor_windows_manager);
        void Draw() override;
    };
}
