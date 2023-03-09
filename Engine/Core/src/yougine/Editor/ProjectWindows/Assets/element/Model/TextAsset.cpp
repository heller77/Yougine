#include "TextAsset.h"

editor::projectwindows::assets::elements::model::TextAsset::TextAsset()
{
    this->text = "hello";
    this->parameter["text"] = text;
}

