#include "Asset.h"

editor::projectwindows::assets::elements::model::Asset::Asset()
{
}

std::map<std::string, std::shared_ptr<editor::projectwindows::assets::elements::model::assetparameters::Parameter>>
editor::projectwindows::assets::elements::model::Asset::GetParameter()
{
    return this->parameter;
}
