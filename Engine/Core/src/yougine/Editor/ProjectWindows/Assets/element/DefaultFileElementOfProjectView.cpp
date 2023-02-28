#include "DefaultFileElementOfProjectView.h"

#include "Button/ButtonInProjectwindow.h"
#include "imgui/imgui.h"

void editor::projectwindows::Assets::elements::DefaultFileElementOfProjectView::Select()
{

}

void editor::projectwindows::Assets::elements::DefaultFileElementOfProjectView::DrawElement()
{
    float hue = 0.5;

    auto default_color = ImColor::HSV(hue, 0.6f, 0.6f);
    auto hover_color = ImColor::HSV(hue, 0.6f, 0.6f);
    auto buttonactive_color = ImColor::HSV(hue, 0.8f, 0.8f);
    // std::function<void()> selectfunc = [&]() {return Select(); };

    buttons::ButtonInProjectwindow::DrawButton(default_color, hover_color, buttonactive_color, this->filename, size,
        [&]() {Select(); });
}

editor::projectwindows::Assets::elements::DefaultFileElementOfProjectView::DefaultFileElementOfProjectView(
    std::string filename, ImVec2 size)
{
    this->filename = filename;
    this->size = size;
}
