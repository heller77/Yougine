#pragma once
#include <string>

#include "IElementOfProjectView.h"
#include "imgui/imgui.h"

namespace editor::projectwindows::assets::elements::view {
    /**
     * \brief プロジェクトビューで特に扱えないファイル
     */
    class DefaultFileElementOfProjectView :public IElementOfProjectView
    {
        void Select();
        std::string filename;
        ImVec2 size;
        std::function<void()> selectEvent;

    public:
        void DrawElement() override;

        DefaultFileElementOfProjectView(std::string filename, ImVec2 size);
    };
}
