#pragma once
#include <filesystem>
#include <tinygltf/json.hpp>

namespace editor::projectwindows::assets::elements::model::assetinfos
{
    class AssetInfoFileExporter
    {
    public:
        /**
         * \brief
         * \param targetAssetFilePath
         */
        void ExportAssetInfoFile(std::filesystem::path targetAssetFilePath, nlohmann::json target_json);
    };
}
