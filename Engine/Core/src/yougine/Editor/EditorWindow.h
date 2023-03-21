#pragma once
#include "EditorWindowsManager.h"
#include "../Scene.h"

namespace editor
{
    class EditorWindowsManager;
    enum class EditorWindowName;

    class EditorWindow
    {
    protected:
        EditorWindowsManager* editor_windows_manager;
        EditorWindowName window_name;
        bool is_selected = false;
        std::vector<std::string> menu_bar_list;
        std::vector<std::string> menu_item_list;

    public:
        EditorWindow(EditorWindowsManager*, EditorWindowName);
        virtual void Draw();

    protected:
        void Setup();
        void RenderMenuBar();
        virtual void RenderMenuItems();
        virtual void SelectedItemProcess(std::string item);
        virtual void InitializeMenuLists();
    };
}
