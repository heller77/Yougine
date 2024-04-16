#include "MeshAsset.h"

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

}

std::string editor::projectwindows::assets::elements::model::mesh::MeshAsset::ToString()
{
    return this->path.filename().string() + "(MeshAsset)";
}

void editor::projectwindows::assets::elements::model::mesh::MeshAsset::InitializeParameter()
{

}
