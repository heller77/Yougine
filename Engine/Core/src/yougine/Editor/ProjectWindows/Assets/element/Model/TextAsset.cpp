#include "TextAsset.h"

#include <fstream>
#include <memory>
#include <memory>
#include <tinygltf/json.hpp>

editor::projectwindows::assets::elements::model::TextAsset::TextAsset(std::filesystem::path path) : Asset(path)
{
    this->text = "hello";
    auto assetoption = std::make_shared<inspectorwindows::assetviews::options::AssetViewOption>();
    this->parameter["text"] = std::make_shared<assetparameters::Parameter>(&text, assetoption);
}

void editor::projectwindows::assets::elements::model::TextAsset::Export()
{

    nlohmann::json json;
    json[GETVALUENAME(text)] = text;

    // std::ofstream writing_file;
    // writing_file.open(filepath.path(), std::ios::out);
    // writing_file << json.dump(2) << std::endl;
    // writing_file.close();

}

