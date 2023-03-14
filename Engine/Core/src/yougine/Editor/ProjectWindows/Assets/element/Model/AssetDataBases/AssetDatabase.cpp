#include "AssetDatabase.h"

#include <iostream>

editor::projectwindows::assets::elements::model::assetdatabases::AssetDatabase::AssetDatabase()
{

}

void editor::projectwindows::assets::elements::model::assetdatabases::AssetDatabase::AddAsset(
    std::shared_ptr<utility::youginuuid::YougineUuid> uuid, std::shared_ptr<Asset> asset)
{
    if (asset == nullptr)
    {
        std::cerr << "asset is null";
        return;
    }
    this->asset_map[uuid->convertstring()] = asset;
}

// void editor::projectwindows::assets::elements::model::assetdatabases::AssetDatabase::AddAsset(int asset_id,
//                                                                                               std::shared_ptr<Asset> asset)
// {
//     this->asset_map[asset_id] = asset;
// }
