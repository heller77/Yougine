#include "Material.h"

#include <tinygltf/json.hpp>

#include "../AssetInfoExporter/AssetInfoFileExporter.h"

void editor::projectwindows::assets::elements::model::materials::Material::Initialize()
{
    auto assetoption = std::make_shared<inspectorwindows::assetviews::options::AssetViewOption>(false, true);
    this->parameter["path"] = std::make_shared<assetparameters::Parameter>(this->path.string(), assetoption);
}

editor::projectwindows::assets::elements::model::materials::Material::Material(const std::filesystem::path& path,
    const std::shared_ptr<utility::youginuuid::YougineUuid>& uuid) :Asset(path, uuid)
{
    // this->frag_asset_uuid = utility::youginuuid::YougineUuid::GenerateNullUuid();
    // this->vert_asset_uuid = utility::youginuuid::YougineUuid::GenerateNullUuid();
    Initialize();
}
editor::projectwindows::assets::elements::model::materials::Material::Material(
    const std::filesystem::path& assetinfo_file_path) :Asset(assetinfo_file_path)
{
    // this->frag_asset_uuid = utility::youginuuid::YougineUuid::GenerateNullUuid();
    // this->vert_asset_uuid = utility::youginuuid::YougineUuid::GenerateNullUuid();
    Initialize();
}

void editor::projectwindows::assets::elements::model::materials::Material::Export()
{
    nlohmann::json json;
    json[GETVALUENAME(uuid)] = uuid->convertstring();

    auto exporter = std::make_shared<assetinfofileexporter::AssetInfoFileExporter>();
    exporter->ExportAssetInfoFile(this->path, json);

}
