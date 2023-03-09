#include "DefaultFileElementOfProjectView.h"

#include "Button/ButtonInProjectwindow.h"
#include "imgui/imgui.h"

void editor::projectwindows::assets::elements::view::DefaultFileElementOfProjectView::Select()
{
    if (selectEvent)
    {
        selectEvent();
    }
}

void editor::projectwindows::assets::elements::view::DefaultFileElementOfProjectView::DrawElement()
{
    float hue = 0.5;

    auto default_color = ImColor::HSV(hue, 0.6f, 0.6f);
    auto hover_color = ImColor::HSV(hue, 0.6f, 0.6f);
    auto buttonactive_color = ImColor::HSV(hue, 0.8f, 0.8f);
    // std::function<void()> selectfunc = [&]() {return Select(); };

    editor::projectwindows::assets::elements::buttons::ButtonInProjectwindow::DrawButton(default_color, hover_color, buttonactive_color, this->filename, size,
        [&]() {Select(); });
}

editor::projectwindows::assets::elements::view::DefaultFileElementOfProjectView::DefaultFileElementOfProjectView(
    std::string filename, ImVec2 size, std::shared_ptr<model::Asset> asset)
{
    this->filename = filename;
    this->size = size;
    this->asset = asset;
}

void editor::projectwindows::assets::elements::view::DefaultFileElementOfProjectView::SetSelectEvent(
    std::function<void()> select_event)
{
    this->selectEvent = select_event;
}

std::shared_ptr<editor::projectwindows::assets::elements::model::Asset> editor::projectwindows::assets::elements::view::
DefaultFileElementOfProjectView::GetAsset()
{
    return this->asset;
}


