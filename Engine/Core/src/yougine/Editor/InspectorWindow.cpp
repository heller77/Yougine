#include "InspectorWindow.h"

namespace editor
{
    InspectorWindow::InspectorWindow(EditorWindowsManager* editor_windows_manager, yougine::Scene* scene, yougine::InputManager* input_manager) :EditorWindow(editor_windows_manager, EditorWindowName::InspectorWindow)
    {
        this->scene = scene;
        this->input_manager = input_manager;
        selection_info = SelectionInfo::GetInstance();
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
         * GameObject‚Ì–¼‘O‚ÌInputTextBox‚ÌŽÀ‘•
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
         * Layerî•ñ
         */
        ImGui::Text("Layer");
        ImGui::Button(selection_info->GetSelectObject()->GetLayer()->GetName().c_str());
    }
}