#pragma once
#include "EditorWindow.h"
namespace editor
{
    class SceneWindow : public editor::EditorWindow
    {
    public:
        SceneWindow(editor::EditorWindowsManager* editor_windows_manager, yougine::Scene*);
    };
}
