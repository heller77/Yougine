#include "InspectorWindow.h"

namespace editor
{
    InspectorWindow::InspectorWindow(EditorWindowsManager* editor_windows_manager, yougine::Scene* scene, yougine::InputManager* input_manager) :EditorWindow(editor_windows_manager, EditorWindowName::InspectorWindow)
    {
        this->scene = scene;
        this->input_manager = input_manager;
        selection_info = SelectionInfo::GetInstance();
        layer_manager = yougine::LayerManager::GetInstance();
    }

    void InspectorWindow::Draw()
    {
        ImGuiWindowFlags_ flag = (ImGuiWindowFlags_NoCollapse);
        ImGui::Begin(editor_windows_manager->GetWindowName(window_name).c_str(), nullptr, flag);

        if (selection_info->GetSelectObject() != nullptr)
        {
            ShowGameObjectData();
        }

        ImGui::End();
    }

    void InspectorWindow::ShowGameObjectData()
    {
        /*
         * GameObjectの名前のInputTextBoxの実装
         */
        const int size_str = sizeof(selection_info->GetSelectObject()->GetName());
        char temp_s[size_str];
        strcpy_s(temp_s, size_str, selection_info->GetSelectObject()->GetName().c_str());

        char* temp_c = temp_s;
        bool is_input = ImGui::InputText("name", temp_c, MAX_SIZE_OBJ_NAME, ImGuiInputTextFlags_EnterReturnsTrue);
        if (is_input)
        {
            selection_info->GetSelectObject()->SetName(temp_c);
        }

        /*
         * Layer情報 未実装
         */
        ImGui::Text("Layer");
        const char* items[2] = { "Default", "GameObject" };
        static int item_current = 0;
        ImGui::Combo("Layer", &item_current, items, IM_ARRAYSIZE(items));
        ImGui::SameLine();

        /*
         * Componentのビュー表示
         *
         * (koko
         * ComponentName1
         *  (componentviewer::drawviews
         *  - Prop1s
         *  - Prop2
         *
         * ComponentName2
         *  - Prop1
         *  - Prop2
         *  - Prop3
         */
         /*
         for (ComponentViewer* c_viewer : selection_info->GetComponentViewers())
         {
             bool c_tree = ImGui::TreeNode(c_viewer->GetComponentName().c_str());
             if (c_tree)
             {
                 c_viewer->DrawViews();
                 ImGui::TreePop();
             }
         }
         */
    }
}