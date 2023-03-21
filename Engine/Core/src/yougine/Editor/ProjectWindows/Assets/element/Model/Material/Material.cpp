#include "Material.h"

#include <iostream>
#include <memory>
#include <tinygltf/json.hpp>

#include "../AssetInfoExporter/AssetInfoFileExporter.h"

void editor::projectwindows::assets::elements::model::materials::Material::Initialize()
{
    using option_type = inspectorwindows::assetviews::options::AssetViewOption;

    auto onlydisplay_option = std::make_shared<option_type>(false, true);
    this->parameter["path"] = std::make_shared<assetparameters::Parameter>(this->path.string(), onlydisplay_option);

    auto fragment_assetoption = std::make_shared<option_type>(false, false, true);
    fragment_assetoption->SetInputAction([&, fragment_assetoption](std::shared_ptr<editor::projectwindows::assets::elements::model::Asset> input)
        {
            std::cout << "input tostring " << input->ToString() << std::endl;
            std::shared_ptr<shader::ShaderFileAsset> input_asset;
            input_asset = std::dynamic_pointer_cast<shader::ShaderFileAsset>(input);

            if (input_asset) {
                // this->frag_asset_uuid = input_asset;
                InputInject(this->frag_asset_uuid, input_asset);
                auto parameter = std::make_shared<assetparameters::Parameter>(frag_asset_uuid->GetAssetId(), fragment_assetoption);
                this->SwapParameter(GETVALUENAME(frag_asset_uuid), std::make_shared<assetparameters::Parameter>(frag_asset_uuid->GetAssetId(), fragment_assetoption));
            }
        });
    frag_asset_uuid = shader::ShaderFileAsset::GetDefaultFragmentShader();
    this->parameter[GETVALUENAME(frag_asset_uuid)] = std::make_shared<assetparameters::Parameter>(frag_asset_uuid->GetAssetId(), fragment_assetoption);

    auto vertex_assetoption = std::make_shared<option_type>(false, false, true);
    vertex_assetoption->SetInputAction([&, vertex_assetoption](std::shared_ptr<editor::projectwindows::assets::elements::model::Asset> input)
        {
            std::cout << "input tostring " << input->ToString() << std::endl;
            std::shared_ptr<shader::ShaderFileAsset> input_asset = std::dynamic_pointer_cast<shader::ShaderFileAsset>(input);

            if (input_asset) {
                // this->vert_asset_uuid = input_asset;
                InputInject(this->vert_asset_uuid, input_asset);
                auto parameter = std::make_shared<assetparameters::Parameter>(vert_asset_uuid->GetAssetId(), fragment_assetoption);
                this->SwapParameter(GETVALUENAME(vert_asset_uuid), std::make_shared<assetparameters::Parameter>(vert_asset_uuid->GetAssetId(), fragment_assetoption));
            }
        });
    vert_asset_uuid = shader::ShaderFileAsset::GetDefaultVertexShader();
    this->parameter[GETVALUENAME(vert_asset_uuid)] = std::make_shared<assetparameters::Parameter>(vert_asset_uuid->GetAssetId(), vertex_assetoption);
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

void editor::projectwindows::assets::elements::model::materials::Material::SwapParameter(std::string parameter_name, std::shared_ptr<assetparameters::Parameter> parameter)
{
    bool is_parameter_exist = this->parameter.find(parameter_name) != this->parameter.end();
    if (is_parameter_exist)
    {
        this->parameter[parameter_name] = parameter;
    }
    else
    {
        std::cout << "not exist" << std::endl;
    }

}

void editor::projectwindows::assets::elements::model::materials::Material::Export()
{
    nlohmann::json json;
    json[GETVALUENAME(uuid)] = uuid->convertstring();

    auto exporter = std::make_shared<assetinfofileexporter::AssetInfoFileExporter>();
    exporter->ExportAssetInfoFile(this->path, json);

}

void editor::projectwindows::assets::elements::model::materials::Material::InputInject(
    std::shared_ptr<shader::ShaderFileAsset>& inputed, std::shared_ptr<shader::ShaderFileAsset>& new_value)
{
    inputed = new_value;
}

std::string editor::projectwindows::assets::elements::model::materials::Material::ToString()
{
    return this->path.filename().string() + "(Material)";
}
