#include "TextAsset.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <memory>
#include <tinygltf/json.hpp>


#include "AssetInfoExporter/AssetInfoFileExporter.h"

editor::projectwindows::assets::elements::model::TextAsset::TextAsset(std::filesystem::path path, std::shared_ptr<utility::youginuuid::YougineUuid> uuid) : Asset(path, uuid)
{
    std::ifstream ifs(path.string());
    if (ifs.fail()) {
        std::cerr << "Failed to open file." << std::endl;
        return;
    }
    //入力
    std::string input;
    while (getline(ifs, input)) {
        this->text += input + "\n";
    }

    auto assetoption = std::make_shared<inspectorwindows::assetviews::options::AssetViewOption>();
    this->parameter["text"] = std::make_shared<assetparameters::Parameter>(&text, assetoption);
}

editor::projectwindows::assets::elements::model::TextAsset::TextAsset(std::filesystem::path assetinfofile_path) :Asset(assetinfofile_path)
{

}

void editor::projectwindows::assets::elements::model::TextAsset::Export()
{

    nlohmann::json json;
    json[GETVALUENAME(text)] = text;

    auto exporter = std::make_shared<assetinfofileexporter::AssetInfoFileExporter>();
    exporter->ExportAssetInfoFile(this->path, json);

}

