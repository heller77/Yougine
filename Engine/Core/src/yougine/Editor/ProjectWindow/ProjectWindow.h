#pragma once
#include "../EditorWindow.h"
#include "../../Project/Project.h"

class ProjectWindow : public editor::EditorWindow
{
private:
    std::string now_display_folderpath;
public:
    void Draw() override;

    ProjectWindow(editor::EditorWindowsManager* editor_windows_manager ,yougine::Scene* scene)
        : EditorWindow(editor_windows_manager, editor::EditorWindowName::ProjectWindow)
    {
        now_display_folderpath = Projects::Project::GetInstance()->projectFolderPath;
    }
};
