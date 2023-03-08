﻿#pragma once
#include <functional>

namespace editor::projectwindows::assets::elements::view {
    /**
     * \brief プロジェクトビューで表示される一要素を表すインターフェイス
     */
    class IElementOfProjectView
    {

    public:
        virtual void DrawElement() = 0;
        virtual void SetSelectEvent(std::function<void()> select_event) = 0;
    };

}
