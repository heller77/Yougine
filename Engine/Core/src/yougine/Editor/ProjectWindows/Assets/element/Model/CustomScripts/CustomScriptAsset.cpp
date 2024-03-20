#include "CustomScriptAsset.h"

#include <tinygltf/json.hpp>

#include "../AssetInfoExporter/AssetInfoFileExporter.h"

void editor::projectwindows::assets::elements::model::customscript::CustomScriptAsset::Export()
{
    nlohmann::json json;
    json[GETVALUENAME(uuid)] = uuid->convertstring();
    json[GETVALUENAME(scriptname)] = scriptname;

    auto exporter = std::make_shared<assetinfofileexporter::AssetInfoFileExporter>();
    exporter->ExportAssetInfoFile(this->path, json);
}

std::string editor::projectwindows::assets::elements::model::customscript::CustomScriptAsset::ToString()
{
    return "CustomScriptAsset";
}

void editor::projectwindows::assets::elements::model::customscript::CustomScriptAsset::InitializeParameter()
{
    this->scriptname = "";
    auto assetoption = std::make_shared<inspectorwindows::assetviews::options::AssetViewOption>();
    this->parameter["scriptname"] = std::make_shared<assetparameters::Parameter>(&scriptname, assetoption);
}
