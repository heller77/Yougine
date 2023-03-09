#pragma once
#include "Asset.h"
#include "../Presenter/ElementOfProjectWindowPresenter.h"

namespace editor::projectwindows::assets::elements::model
{
    class TextAsset :public Asset
    {
    private:
        std::shared_ptr<presenter::ElementOfProjectWindowPresenter> presenter;
    public:
        TextAsset();
        void SetPresenter(std::shared_ptr<presenter::ElementOfProjectWindowPresenter> presenter);
    };
}
