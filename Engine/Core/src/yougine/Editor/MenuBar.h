#pragma once
#include "EditorWindow.h"
namespace editor
{
    class MenuBar : public editor::EditorWindow
    {
    public:
        MenuBar(EditorWindowsManager* editor_windows_manager,yougine::Scene* scene);

        void Draw() override;
    private:
        char buildexportpath[256];
        char sceenfilepath[256];
        yougine::Scene* scene;//editor上でシーンを指定したいが、今はできないのでとりあえず参照をもたせる
        void Build();
    };
}