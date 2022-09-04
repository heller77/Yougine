#include "EditorWindow.h"

namespace editor
{
    EditorWindow::EditorWindow(EditorWindowsManager* editor_windows_manager, EditorWindowName editor_window_name)
    {
        this->editor_windows_manager = editor_windows_manager;
        window_name = editor_window_name;
    }

    void EditorWindow::Draw()
    {
        ImGui::Begin(editor_windows_manager->GetWindowName(window_name).c_str());
        ImGui::End();
        glClearColor(1.0, 0., 0., 1.0);

        glClear(GL_COLOR_BUFFER_BIT);
    }
}