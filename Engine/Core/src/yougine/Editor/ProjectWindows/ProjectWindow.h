#pragma once
#include "../EditorWindow.h"
#include "../../Project/Project.h"

namespace editor::projectwindows
{
    class ProjectWindow : public editor::EditorWindow
    {
    private:
        /**
         * \brief 今ProjectWindowで表示している絶対パス
         */
        std::string now_display_folderpath;
    public:
        void Draw() override;

        ProjectWindow(editor::EditorWindowsManager* editor_windows_manager, yougine::Scene* scene)
            : EditorWindow(editor_windows_manager, editor::EditorWindowName::ProjectWindow)
        {
            now_display_folderpath = projects::Project::GetInstance()->projectFolderPath;
        }
    };
}