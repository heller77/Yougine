#pragma once
#include "imnodes/imnodes.h"
#include "imgui/imgui.h"
#include "../EditorWindow.h"

namespace editor::shadergraph
{
    struct Link
    {
        int id;
        int start_attr, end_attr;
    };

    class ShaderGraphWindow : public EditorWindow
    {
    private:
        std::vector<Link> links;
        int currentLinks = 0;
        int currentSelectedNodeID = 0;

    private:
        void SearchSelectingNodeID();
        void PhaseLink();
        void PhaseAddLink();
        void PhaseDisLink();

    public:
        ShaderGraphWindow(EditorWindowsManager* editor_windows_manager);
        void Draw() override;
    };
}
