#include "TextAsset.h"

editor::projectwindows::assets::elements::model::TextAsset::TextAsset()
{

}

void editor::projectwindows::assets::elements::model::TextAsset::SetPresenter(
    std::shared_ptr<presenter::ElementOfProjectWindowPresenter> presenter)
{
    this->presenter = presenter;
}
