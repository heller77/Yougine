#include "TextAsset.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <memory>
#include <tinygltf/json.hpp>

editor::projectwindows::assets::elements::model::TextAsset::TextAsset(std::filesystem::path path) : Asset(path)
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

void editor::projectwindows::assets::elements::model::TextAsset::Export()
{

    nlohmann::json json;
    json[GETVALUENAME(text)] = text;

    std::ofstream writing_file;
    auto assetfilename = path.filename().string() + ".assetinfo";
    std::string assetinfo_filepath = this->path.remove_filename().string() + assetfilename;
    writing_file.open(assetinfo_filepath, std::ios::out);
    writing_file << json.dump(2) << std::endl;
    writing_file.close();

}

