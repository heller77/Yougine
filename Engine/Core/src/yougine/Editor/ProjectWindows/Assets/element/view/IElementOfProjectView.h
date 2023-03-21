#pragma once
#include <functional>

#include "../Model/Asset.h"

namespace editor::projectwindows::assets::elements::view {
    /**
     * \brief プロジェクトビューで表示される一要素を表すインターフェイス
     */
    class IElementOfProjectView
    {

    public:
        virtual void DrawElement() = 0;
        virtual void SetSelectEvent(std::function<void()> select_event) = 0;
        virtual std::shared_ptr<model::Asset> GetAsset() = 0;
    };

}
