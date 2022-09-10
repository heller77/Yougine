#include "HierarchyWindow.h"
#include <iostream>

namespace editor
{
    HierarchyWindow::HierarchyWindow(EditorWindowsManager* editor_windows_manager, yougine::Scene* scene, yougine::InputManager* input_manager) :EditorWindow(editor_windows_manager, EditorWindowName::HierarchyWindow)
    {
        this->scene = scene;
        this->input_manager = input_manager;

        MENU_ITEMS_LIST =
        {
            "GameObject",
        };

        SetSelectionInfo(nullptr);

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

    void HierarchyWindow::SetSelectionInfo(yougine::GameObject* game_object, bool flame_selected)
    {
        s_selection_info.game_object = game_object;
        s_selection_info.flame_selected = flame_selected;
    }

    void HierarchyWindow::Draw()
    {
        InitializeFlameProperties();

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
                std::string o_name = s_selection_info.game_object != nullptr ? s_selection_info.game_object->GetName() + "_c" + std::to_string((s_selection_info.game_object->GetChildObjects().size() + 1)) : "Obj" + std::to_string(scene->GetGameObjects().size() + 1);
                std::cout << "create : " + o_name << std::endl;
                CreateGameObject(o_name, s_selection_info.game_object);
            };
        }
    }

    void HierarchyWindow::RenderObjectsTree()
    {
        RecursiveTree(scene->GetGameObjects());
    }

    void HierarchyWindow::RecursiveTree(std::list<yougine::GameObject*> game_objects)
    {
        for (yougine::GameObject* game_object : game_objects)
        {
            bool is_leaf = game_object->GetChildObjects().size() == 0;
            if (s_selection_info.game_object == game_object)
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0., 1., 0., 1.));
            ImGuiTreeNodeFlags node_flag = (ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow | (is_leaf ? ImGuiTreeNodeFlags_Leaf : 0));
            bool is_open_tree = ImGui::TreeNodeEx(game_object->GetName().c_str(), node_flag);
            if (s_selection_info.game_object == game_object)
                ImGui::PopStyleColor();

            if (ImGui::IsItemClicked())
            {
                SetSelectionInfo(game_object, true);
                std::cout << "select : " + s_selection_info.game_object->GetName() << std::endl;
            }
            else if (!ImGui::IsAnyItemHovered() && flame_click_trigger && !s_selection_info.flame_selected)
            {
                SetSelectionInfo(nullptr, true);
                std::cout << "select - ‰ðœ -" << std::endl;
            }

            if (is_open_tree)
            {
                RecursiveTree(game_object->GetChildObjects());
                ImGui::TreePop();
            }
        }
    }

    void HierarchyWindow::CreateGameObject(std::string name, yougine::GameObject* parent)
    {
        scene->CreateGameObject(name, parent);
    }

    void HierarchyWindow::InitializeFlameProperties()
    {
        flame_click_trigger = input_manager->IsPushKey(yougine::KeyBind::LeftClick);
        s_selection_info.flame_selected = false;
    }

}