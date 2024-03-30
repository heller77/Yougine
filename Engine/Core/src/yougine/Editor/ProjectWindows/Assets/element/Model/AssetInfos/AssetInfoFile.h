#pragma once
#include <filesystem>
#include <string>
#include <tinygltf/json.hpp>

namespace editor::projectwindows::assets::elements::model::assetinfos
{
    class AssetInfoFile
    {
    private:
        std::shared_ptr<nlohmann::json> json;

    public:
        AssetInfoFile(const std::filesystem::path assetinfofilePath);
        nlohmann::basic_json<> GetParameter(std::string parameterName);

        /**
         * \brief parameterNameというパラメータがあるかを返す
         */
        bool IsContainValue(std::string parameterName);
    };
}
