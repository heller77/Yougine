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
            for (std::pair<std::string, std::vector<MenuItem*>> menu : pulldown_menu_bar->menu_items)
            {
                if (ImGui::BeginMenu(menu.first.c_str()))
                {
                    RenderMenuItems(menu.second);
                    ImGui::EndMenu();
                }
            }

            ImGui::EndMenuBar();
        }
    }

    void EditorWindow::RenderMenuItems(std::vector<MenuItem*> menu_items)
    {
        for (MenuItem* menu_item : menu_items)
        {
            for (std::pair<std::string, std::vector<MenuItem*>> item : menu_item->items)
            {
                if (item.second.empty())
                {
                    SelectedItemProcess(item.first);
                }
                else
                {
                    if (ImGui::BeginMenu(item.first.c_str()))
                    {
                        RenderMenuItems(item.second);
                        ImGui::EndMenu();
                    }
                }
            }
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
