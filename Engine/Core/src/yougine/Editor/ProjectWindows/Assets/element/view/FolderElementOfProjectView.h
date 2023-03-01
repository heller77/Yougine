#pragma once
#include "IElementOfProjectView.h"
#include "../../../../EditorWindowsManager.h"
#include "imgui/imgui.h"

namespace editor::projectwindows::Assets::elements::view {
    class FolderElementOfProjectView : public IElementOfProjectView
    {
    private:
        void Select();
        std::string folder_name;
        ImVec2 button_size;
        std::function<void()> selectEvent;

    public:
        FolderElementOfProjectView(const std::string& folder_name, const ImVec2& button_size);
        void SetSelctEvent(std::function<void()> selectEvent);
        void DrawElement() override;
        std::string GetFolderName();
    };
}
