#include "Material.h"

#include <iostream>
#include <tinygltf/json.hpp>

#include "../AssetInfoExporter/AssetInfoFileExporter.h"

void editor::projectwindows::assets::elements::model::materials::Material::Initialize()
{
    using option_type = inspectorwindows::assetviews::options::AssetViewOption;

    auto onlydisplay_option = std::make_shared<option_type>(false, true);
    this->parameter["path"] = std::make_shared<assetparameters::Parameter>(this->path.string(), onlydisplay_option);

    auto assetoption = std::make_shared<option_type>(false, false, true);
    assetoption->SetInputAction([&](std::shared_ptr<utility::youginuuid::YougineUuid> input)
        {
            std::cout << input->convertstring() << std::endl;
        });
    this->parameter[GETVALUENAME(frag_asset_uuid)] = std::make_shared<assetparameters::Parameter>(frag_asset_uuid, assetoption);
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
