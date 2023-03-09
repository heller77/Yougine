#pragma once
#include <string>

#include "IElementOfProjectView.h"
#include "../Model/Asset.h"
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
        std::shared_ptr<model::Asset> asset;

    public:
        void DrawElement() override;

        DefaultFileElementOfProjectView(std::string filename, ImVec2 size, std::shared_ptr<model::Asset> asset);

        void SetSelectEvent(std::function<void()> select_event) override;
        std::shared_ptr<model::Asset> GetAsset();

    };
}
