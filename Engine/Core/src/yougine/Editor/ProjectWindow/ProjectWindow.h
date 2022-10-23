#pragma once
#include "../EditorWindow.h"

class ProjectWindow : public editor::EditorWindow
{
public:
    void Draw() override;

    ProjectWindow(editor::EditorWindowsManager* editor_windows_manager ,yougine::Scene* scene)
        : EditorWindow(editor_windows_manager, editor::EditorWindowName::ProjectWindow)
    {
    }
};
