#pragma once
#include "EditorWindow.h"
namespace editor
{
    class MenuBar : public editor::EditorWindow
    {
    public:
        MenuBar(EditorWindowsManager* editor_windows_manager);

        void Draw() override;
    private:
        char buildexportpath[256];
        char sceenfilepath[256];
        void Build();
    };
}