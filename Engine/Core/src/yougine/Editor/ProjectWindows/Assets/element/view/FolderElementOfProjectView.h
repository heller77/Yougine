#pragma once
#include "IElementOfProjectView.h"
#include "../../../../EditorWindowsManager.h"
#include "imgui/imgui.h"

namespace editor::projectwindows::assets::elements::view {
    class FolderElementOfProjectView : public IElementOfProjectView
    {
    private:
        void Select();
        std::string folder_name;
        ImVec2 button_size;
        std::function<void()> selectEvent;

    public:
        FolderElementOfProjectView(const std::string& folder_name, const ImVec2& button_size);
        void DrawElement() override;
        std::string GetFolderName();

        void SetSelectEvent(std::function<void()> select_event) override;
    };
}
