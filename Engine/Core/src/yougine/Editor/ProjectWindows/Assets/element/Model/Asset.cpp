#include "Asset.h"

#include <tinygltf/json.hpp>

editor::projectwindows::assets::elements::model::Asset::Asset(std::filesystem::path path, int asset_id)
{
    this->path = path;
    this->asset_id = asset_id;
}

std::map<std::string, std::shared_ptr<editor::projectwindows::assets::elements::model::assetparameters::Parameter>>
editor::projectwindows::assets::elements::model::Asset::GetParameter()
{
    return this->parameter;
}


