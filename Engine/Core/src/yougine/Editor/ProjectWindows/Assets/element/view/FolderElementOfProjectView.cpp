#include "FolderElementOfProjectView.h"

#include "Button/ButtonInProjectwindow.h"

editor::projectwindows::assets::elements::view::FolderElementOfProjectView::FolderElementOfProjectView(const std::string& folder_name, const ImVec2& button_size)
    : folder_name(folder_name),
    button_size(button_size)
{
}


void editor::projectwindows::assets::elements::view::FolderElementOfProjectView::Select()
{
    if (selectEvent) {
        this->selectEvent();
    }
}

void editor::projectwindows::assets::elements::view::FolderElementOfProjectView::DrawElement()
{
    float hue = 0.1;
    //
    // ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(hue, 0.6f, 0.6f));
    // ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(hue, 0.7f, 0.7f));
    // ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(hue, 0.8f, 0.8f));
    // if (ImGui::Button(folder_name.c_str(), button_size))
    // {
    //     // Select();
    // }
    //
    // ImGui::PopStyleColor(3);

    auto default_color = ImColor::HSV(hue, 0.6f, 0.6f);
    auto hover_color = ImColor::HSV(hue, 0.6f, 0.6f);
    auto buttonactive_color = ImColor::HSV(hue, 0.8f, 0.8f);
    // std::function<void()> selectfunc = [&]() {return Select(); };

    buttons::ButtonInProjectwindow::DrawButton(default_color, hover_color, buttonactive_color, this->folder_name, button_size,
        [&]() {Select(); });
}

std::string editor::projectwindows::assets::elements::view::FolderElementOfProjectView::GetFolderName()
{
    return this->folder_name;
}

void editor::projectwindows::assets::elements::view::FolderElementOfProjectView::SetSelectEvent(
    std::function<void()> select_event)
{
    this->selectEvent = select_event;
}
