#include "MeshAsset.h"

#include "../AssetInfos/AssetInfoFileExporter.h"

editor::projectwindows::assets::elements::model::mesh::MeshAsset::MeshAsset(const std::filesystem::path path,
    std::shared_ptr<utility::youginuuid::YougineUuid> asset_id) : Asset(path, asset_id)
{
}

editor::projectwindows::assets::elements::model::mesh::MeshAsset::MeshAsset(
    const std::filesystem::path assetinfo_file_path) : Asset(assetinfo_file_path)
{
}

void editor::projectwindows::assets::elements::model::mesh::MeshAsset::Export()
{
    nlohmann::json json;
    json[GETVALUENAME(uuid)] = uuid->convertstring();

    auto exporter = std::make_shared<assetinfos::AssetInfoFileExporter>();
    exporter->ExportAssetInfoFile(this->path, json);
}

std::string editor::projectwindows::assets::elements::model::mesh::MeshAsset::ToString()
{
    return this->path.filename().string() + "(MeshAsset)";
}

void editor::projectwindows::assets::elements::model::mesh::MeshAsset::InitializeParameter()
{

}
