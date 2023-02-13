#include "ShaderGraphWindow.h"

namespace editor::shadergraph
{
    ShaderGraphWindow::ShaderGraphWindow(EditorWindowsManager* editor_windows_manager) : EditorWindow(editor_windows_manager, editor::EditorWindowName::ShaderGraphWindow)
    {

    }

    void ShaderGraphWindow::Draw()
    {
        ImGui::Begin("simple node editor");

        ImNodes::BeginNodeEditor();
        ImNodes::BeginNode(1);

        ImNodes::BeginNodeTitleBar();
        ImGui::TextUnformatted("simple node :)");
        ImNodes::EndNodeTitleBar();

        ImNodes::BeginInputAttribute(2);
        ImGui::Text("input");
        ImNodes::EndInputAttribute();

        ImNodes::BeginOutputAttribute(3);
        ImGui::Indent(40);
        ImGui::Text("output");
        ImNodes::EndOutputAttribute();

        ImNodes::EndNode();
        ImNodes::EndNodeEditor();

        ImGui::End();
    }


}
