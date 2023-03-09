#include "ElementOfProjectWindowPresenter.h"

void editor::projectwindows::assets::elements::presenter::ElementOfProjectWindowPresenter::SetView(
    std::shared_ptr<view::IElementOfProjectView> view)
{
    this->view = view;
}

void editor::projectwindows::assets::elements::presenter::ElementOfProjectWindowPresenter::SetModel(
    std::shared_ptr<model::Asset> model)
{
    this->model = model;
}
