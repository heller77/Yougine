#pragma once
#include "EditorWindow.h"
#include "./../managers/RenderManager.h"
namespace editor
{
    class SceneWindow : public editor::EditorWindow
    {
    public:
        SceneWindow(editor::EditorWindowsManager* editor_windows_manager, yougine::Scene*);
        void Draw() override;
    private:
        yougine::managers::RenderManager* renderManager;
    };
}
