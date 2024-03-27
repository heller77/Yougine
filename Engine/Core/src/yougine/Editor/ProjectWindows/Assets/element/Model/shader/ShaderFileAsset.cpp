#include "ShaderFileAsset.h"

#include <fstream>
#include <memory>
#include <memory>
#include <tinygltf/json.hpp>
#include <filesystem>
#include <memory>

#include "../../../../../../Projects/Project.h"
#include "../AssetInfos//AssetInfoFileExporter.h"

void editor::projectwindows::assets::elements::model::shader::ShaderFileAsset::InitializeCode(
    std::filesystem::path shaderfile_path)
{
    std::ifstream ifs(shaderfile_path.string());
    if (ifs.fail()) {
        std::cerr << "Failed to open file." << std::endl;
        return;
    }
    //入力
    std::string input;
    while (getline(ifs, input)) {
        this->code += input + "\n";
    }
    std::cout << shaderfile_path << ": " << code << std::endl;
    std::shared_ptr<inspectorwindows::assetviews::options::AssetViewOption> option = std::make_shared<inspectorwindows::assetviews::options::AssetViewOption>(false, true);
    this->parameter[GETVALUENAME(code)] = std::make_shared<assetparameters::Parameter>(&code, option);
}

editor::projectwindows::assets::elements::model::shader::ShaderFileAsset::ShaderFileAsset(
    const std::filesystem::path path, std::shared_ptr<utility::youginuuid::YougineUuid> uuid) : Asset(path, uuid)
{
    InitializeCode(this->path);
}

editor::projectwindows::assets::elements::model::shader::ShaderFileAsset::ShaderFileAsset(
    const std::filesystem::path assetinfo_file_path) : Asset(assetinfo_file_path)
{
    InitializeCode(this->path);
}

std::shared_ptr<editor::projectwindows::assets::elements::model::shader::ShaderFileAsset> editor::projectwindows::assets
::elements::model::shader::ShaderFileAsset::GetDefaultVertexShader()
{
    if (vert_default == nullptr)
    {
        auto engineresouce_shaderinfo = projects::Project::GetInstance()->GetParameterFromEngineResourceJson("shader");
        auto vertshaderfilePath = projects::Project::GetInstance()->GetEngineResouceFolderPath() / engineresouce_shaderinfo["default"]["vert"];


        // vert_default = std::make_shared<ShaderFileAsset>(vertshaderfilePath.string(), id);
        std::shared_ptr<Asset> vertdefaultasset = projects::Project::GetInstance()->GetDataBase()->GetAssetFromFilePath(vertshaderfilePath);
        std::shared_ptr<editor::projectwindows::assets::elements::model::shader::ShaderFileAsset> asset
            = std::dynamic_pointer_cast<editor::projectwindows::assets::elements::model::shader::ShaderFileAsset>(vertdefaultasset);
        if (asset == nullptr)
        {
            throw "vertexshaderのデフォルトアセットが見つからない。エンジンリソースの初期化が上手くいっていない可能性がある。";
        }

        vert_default = asset;
    }
    return vert_default;
}

std::shared_ptr<editor::projectwindows::assets::elements::model::shader::ShaderFileAsset> editor::projectwindows::assets
::elements::model::shader::ShaderFileAsset::GetDefaultFragmentShader()
{
    if (frag_default == nullptr)
    {
        auto engineresouce_shaderinfo = projects::Project::GetInstance()->GetParameterFromEngineResourceJson("shader");
        auto vertshaderfilePath = projects::Project::GetInstance()->GetEngineResouceFolderPath() / engineresouce_shaderinfo["default"]["frag"];


        // vert_default = std::make_shared<ShaderFileAsset>(vertshaderfilePath.string(), id);
        std::shared_ptr<Asset> vertdefaultasset = projects::Project::GetInstance()->GetDataBase()->GetAssetFromFilePath(vertshaderfilePath);
        std::shared_ptr<editor::projectwindows::assets::elements::model::shader::ShaderFileAsset> asset
            = std::dynamic_pointer_cast<editor::projectwindows::assets::elements::model::shader::ShaderFileAsset>(vertdefaultasset);
        if (asset == nullptr)
        {
            throw "fragmentshaderのデフォルトアセットが見つからない。エンジンリソースの初期化が上手くいっていない可能性がある。";
        }

        frag_default = asset;
    }
    return frag_default;
}

void editor::projectwindows::assets::elements::model::shader::ShaderFileAsset::Export()
{
    nlohmann::json json;
    json[GETVALUENAME(uuid)] = uuid->convertstring();
    json[GETVALUENAME(shader_kind)] = shader_kind;

    auto exporter = std::make_shared<assetinfos::AssetInfoFileExporter>();
    exporter->ExportAssetInfoFile(this->path, json);
}

void editor::projectwindows::assets::elements::model::shader::ShaderFileAsset::InitializeParameter()
{
    if (is_assetinfo_file_exist)
    {
        this->shader_kind = asset_info->GetParameter(GETVALUENAME(shader_kind));
    }
    else {
        this->shader_kind = "fragment or vertex";
    }
    auto assetoption = std::make_shared<inspectorwindows::assetviews::options::AssetViewOption>();
    this->parameter["shader_kind"] = std::make_shared<assetparameters::Parameter>(&shader_kind, assetoption);

}

std::string editor::projectwindows::assets::elements::model::shader::ShaderFileAsset::GetCode()
{
    return this->code;
}

std::string editor::projectwindows::assets::elements::model::shader::ShaderFileAsset::ToString()
{
    return this->path.string() + "(ShaderAsset)";
}

std::shared_ptr<editor::projectwindows::assets::elements::model::shader::ShaderFileAsset> editor::projectwindows::assets::elements::model::shader::ShaderFileAsset::vert_default;
std::shared_ptr<editor::projectwindows::assets::elements::model::shader::ShaderFileAsset> editor::projectwindows::assets::elements::model::shader::ShaderFileAsset::frag_default;