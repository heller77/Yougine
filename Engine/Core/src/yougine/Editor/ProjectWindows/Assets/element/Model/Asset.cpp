﻿#include "Asset.h"

#include <tinygltf/json.hpp>
#include <filesystem>
#include <fstream>
#include <memory>

editor::projectwindows::assets::elements::model::Asset::Asset(std::filesystem::path path, std::shared_ptr<utility::youginuuid::YougineUuid> uuid)
{
    this->path = path;
    this->uuid = uuid;
}

editor::projectwindows::assets::elements::model::Asset::Asset(const std::filesystem::path assetinfo_file_path)
{
    using json = nlohmann::ordered_json;

    std::ifstream reading(assetinfo_file_path.string(), std::ios::in);

    json o_json;
    reading >> o_json;

    if (o_json.contains("uuid")) {
        std::string asset_id = o_json["uuid"];
        this->uuid = std::shared_ptr<utility::youginuuid::YougineUuid>(new utility::youginuuid::YougineUuid(asset_id));
    }
    else
    {
        //file not has uuid
        this->uuid = std::shared_ptr<utility::youginuuid::YougineUuid>(new utility::youginuuid::YougineUuid());
    }


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

