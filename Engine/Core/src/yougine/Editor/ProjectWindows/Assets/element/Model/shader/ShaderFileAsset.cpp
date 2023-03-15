#include "ShaderFileAsset.h"

#include <fstream>
#include <memory>
#include <tinygltf/json.hpp>

#include "../AssetInfoExporter/AssetInfoFileExporter.h"

editor::projectwindows::assets::elements::model::shader::ShaderFileAsset::ShaderFileAsset(
    const std::filesystem::path path, std::shared_ptr<utility::youginuuid::YougineUuid> uuid) : Asset(path, uuid)
{
    this->shader_kind = "fragment or vertex";
    auto assetoption = std::make_shared<inspectorwindows::assetviews::options::AssetViewOption>();
    this->parameter["shader_kind"] = std::make_shared<assetparameters::Parameter>(&shader_kind, assetoption);
}

editor::projectwindows::assets::elements::model::shader::ShaderFileAsset::ShaderFileAsset(
    const std::filesystem::path assetinfo_file_path) :Asset(assetinfo_file_path)
{
    this->shader_kind = "fragment or vertex";
    auto assetoption = std::make_shared<inspectorwindows::assetviews::options::AssetViewOption>();
    this->parameter["shader_kind"] = std::make_shared<assetparameters::Parameter>(&shader_kind, assetoption);
}

void editor::projectwindows::assets::elements::model::shader::ShaderFileAsset::Export()
{
    nlohmann::json json;
    json[GETVALUENAME(shader_kind)] = shader_kind;

    auto exporter = std::make_shared<assetinfofileexporter::AssetInfoFileExporter>();
    exporter->ExportAssetInfoFile(this->path, json);
}
