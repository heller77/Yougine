#pragma once

#include <filesystem>
#include <map>
#include <memory>
#include <string>

#include "../../../../../utilitys/uuid/YougineUuid.h"
#include "AssetParameter/Parameter.h"


namespace editor::projectwindows::assets::elements::model
{

#define GETVALUENAME(name) (#name)
    /**
     * \brief アセットを表す
     */
    class Asset
    {
    protected:
        std::map<std::string, std::shared_ptr<assetparameters::Parameter>> parameter;
        std::filesystem::path path;
        std::shared_ptr<utility::youginuuid::YougineUuid> uuid;
    public:
        Asset(std::filesystem::path path, std::shared_ptr<utility::youginuuid::YougineUuid> uuid);
        Asset(const std::filesystem::path assetinfo_file_path);
        std::map<std::string, std::shared_ptr<assetparameters::Parameter>> GetParameter();
        virtual void Export() = 0;
        std::shared_ptr<utility::youginuuid::YougineUuid> GetAssetId();
        virtual std::string ToString() = 0;

    };
}
