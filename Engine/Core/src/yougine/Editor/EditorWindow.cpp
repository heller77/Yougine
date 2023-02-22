#include "EditorWindow.h"

#include "HierarchyWindow.h"

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
    }

    void EditorWindow::RenderMenuBar()
    {
        if (ImGui::BeginMenuBar())
        {
            for (std::string bar_label : menu_bar_list)
                if (ImGui::BeginMenu(bar_label.c_str()))
                {
                    RenderMenuItems();
                    ImGui::EndMenu();
                }

            ImGui::EndMenuBar();
        }
    }

    void EditorWindow::RenderMenuItems()
    {
        for (std::string item : menu_item_list)
        {
            SelectedItemProcess(item);
        }
    }

    void EditorWindow::SelectedItemProcess(std::string item)
    {
        std::cout << item + " Selected" << std::endl;
    }

    void EditorWindow::InitializeMenuLists()
    {
        //この関数をオーバーライドしてmenu_bar_list, menu_item_listを初期化する
    }



}
