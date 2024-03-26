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

        /**
         * \brief ファイルパスからアセットを全探索。（全探索するのであまり使いたくない）
         * \param assetpath 探索対象のファイルパス
         * \return
         */
        std::shared_ptr<Asset> GetAssetFromFilePath(std::filesystem::path assetpath);
        std::unordered_map<std::string, std::shared_ptr<Asset>, utility::youginuuid::Hash> GetAssetList();
    };
}
