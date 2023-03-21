#include "AssetInfoFileExporter.h"

#include <fstream>
#include <tinygltf/json.hpp>

void editor::projectwindows::assets::elements::model::assetinfofileexporter::AssetInfoFileExporter::AssetInfoFileExporter::ExportAssetInfoFile(std::filesystem::path targetAssetFilePath, nlohmann::json target_json)
{
    std::ofstream writing_file;
    auto assetfilename = targetAssetFilePath.filename().string() + ".assetinfo";
    std::string assetinfo_filepath = targetAssetFilePath.remove_filename().string() + assetfilename;
    writing_file.open(assetinfo_filepath, std::ios::out);
    writing_file << target_json.dump(2) << std::endl;
    writing_file.close();
}
