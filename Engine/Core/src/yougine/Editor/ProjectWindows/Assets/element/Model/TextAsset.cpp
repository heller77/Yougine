#include "TextAsset.h"

#include <memory>

editor::projectwindows::assets::elements::model::TextAsset::TextAsset()
{
    this->text = "hello";
    auto assetoption = std::make_shared<inspectorwindows::assetviews::options::AssetViewOption>();
    this->parameter["text"] = std::make_shared<assetparameters::Parameter>(&text, assetoption);
}

