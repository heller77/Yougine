#pragma once
#include <map>
#include <memory>

#include "../Asset.h"
#include "UserShare/utilitys/uuid/YougineUuid.h"

namespace editor::projectwindows::assets::elements::model::assetdatabases
{
    class AssetDatabase
    {
    private:
        std::unordered_map<std::string, std::shared_ptr<Asset>, utility::youginuuid::Hash> asset_map;
    public:
        AssetDatabase();
        void AddAsset(std::shared_ptr<utility::youginuuid::YougineUuid> uuid, std::shared_ptr<Asset> asset);
        std::shared_ptr<Asset> GetAsset(std::string assetid);
        std::unordered_map<std::string, std::shared_ptr<Asset>, utility::youginuuid::Hash> GetAssetList();
    };
}
