#include "HierarchyWindow.h"
#include <iostream>

namespace editor
{
    HierarchyWindow::HierarchyWindow(EditorWindowsManager* editor_windows_manager, yougine::Scene* scene) :EditorWindow(editor_windows_manager, EditorWindowName::HierarchyWindow)
    {
        this->scene = scene;

        MENU_ITEMS_LIST =
        {
            "GameObject",
        };

        tree_objects_list =
        {
        };

        SetSelectionInfo(STR_EMPTY, -1, -1); //initialize

        SetSelectionInfo(STR_EMPTY, 0, 0);
        CreateGameObject("Obj1", STR_EMPTY);
        SetSelectionInfo(STR_EMPTY, 0, 1);
        CreateGameObject("Obj1_c1", "Obj1");
        SetSelectionInfo(STR_EMPTY, 1, 0);
        CreateGameObject("Obj2", STR_EMPTY);
        SetSelectionInfo(STR_EMPTY, 1, 1);
        CreateGameObject("Obj2_c1", "Obj2");
        SetSelectionInfo(STR_EMPTY, 1, 2);
        CreateGameObject("Obj2_c2", "Obj2_c1");
        SetSelectionInfo(STR_EMPTY, 2, 0);
        CreateGameObject("Obj3", STR_EMPTY);
        SetSelectionInfo(STR_EMPTY, 2, 1);
        CreateGameObject("Obj3_c1", "Obj3");
    }

    void HierarchyWindow::SetSelectionInfo(std::string obj_name, int f_index, int b_index)
    {
        s_selection_info.obj_name = obj_name;
        s_selection_info.f_index = f_index;
        s_selection_info.b_index = b_index;
    }

    void HierarchyWindow::Draw()
    {
        ImGui::Begin(editor_windows_manager->GetWindowName(window_name).c_str(), nullptr, ImGuiWindowFlags_MenuBar);

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("Create"))
            {
                RenderMenuItems();
                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }

        RenderObjectsTree();

        ImGui::End();
    }

    void HierarchyWindow::RenderMenuItems()
    {
        for (std::string item : MENU_ITEMS_LIST)
        {
            if (ImGui::MenuItem(item.c_str()))
            {
                //CreateGameObject(s_selection_info.obj_name + "_" + std::to_string(s_selection_info.b_index+1), s_selection_info.obj_name);
            };
        }
    }

    void HierarchyWindow::RenderObjectsTree()
    {
        int n_p = 0, n = 0; //n_p, n Å® çsóÒ
        for (std::vector<std::string> list : tree_objects_list)
        {
            if (ImGui::TreeNode(list[0].c_str()))
            {
                SetSelectionInfo(list[0], n_p, 0);
                RecursiveTree(list, n_p, ++n);
                ImGui::TreePop();
            }

            n_p++;
            n = 0;
        }
    }

    void HierarchyWindow::RecursiveTree(std::vector<std::string> node_names, int n_p, int n)
    {
        if (n < node_names.size())
        {
            if (ImGui::TreeNode(node_names[n].c_str()))
            {
                SetSelectionInfo(node_names[n], n_p, n);
                RecursiveTree(node_names, n_p, ++n);
                ImGui::TreePop();
            }
        }
    }

    void HierarchyWindow::AddObjectToTreeList(std::string name, std::string name_top)
    {
        int tree_index = -1;


        for (int i = 0; i < tree_objects_list.size(); i++)
        {

            if (name_top == tree_objects_list[i][0])
            {
                tree_index = i;
            }
        }

        if (tree_index != -1)
        {
            tree_objects_list[tree_index].push_back(name);
        }
        else
        {
            tree_objects_list.push_back(std::vector<std::string>{ name });
        }
    }

    void HierarchyWindow::CreateGameObject(std::string name, std::string name_parent)
    {
        scene->CreateGameObject(name, name_parent);

        std::string name_top = STR_EMPTY;
        if (tree_objects_list.size() > s_selection_info.f_index)
            name_top = tree_objects_list[s_selection_info.f_index][0];
        AddObjectToTreeList(name, name_top);
    }
}