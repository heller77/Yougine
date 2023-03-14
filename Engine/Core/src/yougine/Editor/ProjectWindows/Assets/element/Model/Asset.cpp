#include "Asset.h"

#include <tinygltf/json.hpp>

editor::projectwindows::assets::elements::model::Asset::Asset(std::filesystem::path path, std::shared_ptr<utility::youginuuid::YougineUuid> uuid)
{
    this->path = path;
    this->uuid = uuid;
}

std::map<std::string, std::shared_ptr<editor::projectwindows::assets::elements::model::assetparameters::Parameter>>
editor::projectwindows::assets::elements::model::Asset::GetParameter()
{
    return this->parameter;
}

std::shared_ptr<utility::youginuuid::YougineUuid> editor::projectwindows::assets::elements::model::Asset::GetAssetId()
{
    return this->uuid;
}


