#include "Asset.h"

#include <tinygltf/json.hpp>

editor::projectwindows::assets::elements::model::Asset::Asset(std::filesystem::path path)
{
    this->path = path;
}

std::map<std::string, std::shared_ptr<editor::projectwindows::assets::elements::model::assetparameters::Parameter>>
editor::projectwindows::assets::elements::model::Asset::GetParameter()
{
    return this->parameter;
}


