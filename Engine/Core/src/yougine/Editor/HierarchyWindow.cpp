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

        SetSelectionInfo(nullptr); //initialize

        SetSelectionInfo(nullptr);
        CreateGameObject("Obj1", nullptr);
        SetSelectionInfo(nullptr);
        CreateGameObject("Obj1_c1", scene->GetGameObjectByName("Obj1"));
        SetSelectionInfo(nullptr);
        CreateGameObject("Obj2", nullptr);
        SetSelectionInfo(nullptr);
        CreateGameObject("Obj2_c1", scene->GetGameObjectByName("Obj2"));
        SetSelectionInfo(nullptr);
        CreateGameObject("Obj2_c2", scene->GetGameObjectByName("Obj2"));
        SetSelectionInfo(nullptr);
        CreateGameObject("Obj3", nullptr);
        SetSelectionInfo(nullptr);
        CreateGameObject("Obj3_c1", scene->GetGameObjectByName("Obj3"));
    }

    void HierarchyWindow::SetSelectionInfo(yougine::GameObject* game_object)
    {
        s_selection_info.game_object = game_object;
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
                CreateGameObject(s_selection_info.game_object->GetName() + "_" + std::to_string((s_selection_info.game_object->GetChildObjects().size() + 1)), s_selection_info.game_object);
            };
        }
    }

    void HierarchyWindow::RenderObjectsTree()
    {
        for (yougine::GameObject* game_object : scene->GetGameObjects())
        {
            if (ImGui::TreeNode(game_object->GetName().c_str()))
            {
                SetSelectionInfo(game_object);
                RecursiveTree(game_object->GetChildObjects());
                ImGui::TreePop();
            }
        }
    }

    void HierarchyWindow::RecursiveTree(std::vector<yougine::GameObject*> game_objects)
    {
        for (yougine::GameObject* game_object : game_objects)
        {
            if (ImGui::TreeNode(game_object->GetName().c_str()))
            {
                SetSelectionInfo(game_object);
                RecursiveTree(game_object->GetChildObjects());
                ImGui::TreePop();
            }
        }
    }

    void HierarchyWindow::CreateGameObject(std::string name, yougine::GameObject* parent)
    {
        scene->CreateGameObject(name, parent);
    }
}