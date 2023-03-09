#pragma once
#include <string>

#include "IElementOfProjectView.h"
#include "../Presenter/ElementOfProjectWindowPresenter.h"
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
        std::shared_ptr<presenter::ElementOfProjectWindowPresenter> presenter;

    public:
        void DrawElement() override;

        DefaultFileElementOfProjectView(std::string filename, ImVec2 size);

        void SetSelectEvent(std::function<void()> select_event) override;
        void SetPresenter(std::shared_ptr<presenter::ElementOfProjectWindowPresenter> presenter);

    };
}
