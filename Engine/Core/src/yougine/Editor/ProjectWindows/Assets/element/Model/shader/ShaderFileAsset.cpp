#include "ShaderFileAsset.h"

#include <fstream>
#include <tinygltf/json.hpp>

editor::projectwindows::assets::elements::model::shader::ShaderFileAsset::ShaderFileAsset(
    const std::filesystem::path& path) : Asset(path)
{
    this->shader_kind = "fragment or vertex";
    auto assetoption = std::make_shared<inspectorwindows::assetviews::options::AssetViewOption>();
    this->parameter["shader_kind"] = std::make_shared<assetparameters::Parameter>(&shader_kind, assetoption);
}

void editor::projectwindows::assets::elements::model::shader::ShaderFileAsset::Export()
{
    nlohmann::json json;
    json[GETVALUENAME(shader_kind)] = shader_kind;

    std::ofstream writing_file;
    auto assetfilename = path.filename().string() + ".assetinfo";
    std::string assetinfo_filepath = this->path.remove_filename().string() + assetfilename;
    writing_file.open(assetinfo_filepath, std::ios::out);
    writing_file << json.dump(2) << std::endl;
    writing_file.close();
}
