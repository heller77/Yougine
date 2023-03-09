#pragma once
#include "../Model/Asset.h"
#include "../view/IElementOfProjectView.h"

namespace editor::projectwindows::assets::elements::presenter
{
    class ElementOfProjectWindowPresenter
    {
    private:
        std::shared_ptr<view::IElementOfProjectView> view;
        std::shared_ptr<model::Asset> model;
    public:
        void SetView(std::shared_ptr<view::IElementOfProjectView> view);
        void SetModel(std::shared_ptr<model::Asset> model);
    };
}
