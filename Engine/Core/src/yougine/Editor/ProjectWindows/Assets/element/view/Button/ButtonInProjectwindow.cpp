
#include "ButtonInProjectwindow.h"

#include <functional>

#include "imgui/imgui.h"

void editor::projectwindows::assets::elements::buttons::ButtonInProjectwindow::DrawButton(ImColor default_color, ImColor hover_color, ImColor active_color, std::string display_name, ImVec2 button_size, std::function<void()> clickEvent)
{
    float hue = 0.1;

    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)default_color);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)hover_color);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)active_color);
    if (ImGui::Button(display_name.c_str(), button_size))
    {
        clickEvent();
    }

    ImGui::PopStyleColor(3);
}
