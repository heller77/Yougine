#include "AssetInfoFile.h"
#include <tinygltf/json.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <memory>

editor::projectwindows::assets::elements::model::assetinfos::AssetInfoFile::AssetInfoFile(const std::filesystem::path assetinfofilePath)
{
    std::ifstream reading(assetinfofilePath.string(), std::ios::in);

    json = std::make_shared<nlohmann::json>();
    nlohmann::json o_json;
    reading >> o_json;
    json = std::make_shared<nlohmann::json>(o_json);

}

std::string editor::projectwindows::assets::elements::model::assetinfos::AssetInfoFile::GetParameter(
    std::string parameterName)
{
    return (*json)[parameterName];
}

bool editor::projectwindows::assets::elements::model::assetinfos::AssetInfoFile::IsContainValue(
    std::string parameterName)
{
    return json->contains(parameterName);
}
