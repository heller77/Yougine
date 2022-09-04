#include "SceneWindow.h"

editor::SceneWindow::SceneWindow(editor::EditorWindowsManager* editor_windows_manager,
    yougine::Scene*) : EditorWindow(editor_windows_manager, editor::EditorWindowName::SceneWindow)
{
}
