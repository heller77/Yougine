#pragma once
#include <functional>
#include <string>

#include "imgui/imgui.h"

namespace editor::projectwindows::Assets::elements::buttons {
    class ButtonInProjectwindow
    {
    public:
        static void DrawButton(ImColor default_color, ImColor hover_color, ImColor active_color, std::string display_name, ImVec2 button_size, std::
            function<void()> clickEvent);
    };
}