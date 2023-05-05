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

std::shared_ptr<editor::projectwindows::assets::elements::model::Asset> editor::projectwindows::assets::elements::model
::assetdatabases::AssetDatabase::GetAsset(std::string assetid)
{
    //[]でvalueのないkeyを指定するとnullがvalueのpairが生成されるので、チェック
    if (this->asset_map.find(assetid) == asset_map.end())
    {
        std::cout << assetid << " : assetid is null" << std::endl;
        return nullptr;
    }
    return this->asset_map[assetid];
}

std::unordered_map<std::string, std::shared_ptr<editor::projectwindows::assets::elements::model::Asset>, utility::
    youginuuid::Hash> editor::projectwindows::assets::elements::model::assetdatabases::AssetDatabase::GetAssetList()
{
    return this->asset_map;
}

// void editor::projectwindows::assets::elements::model::assetdatabases::AssetDatabase::AddAsset(int asset_id,
//                                                                                               std::shared_ptr<Asset> asset)
// {
//     this->asset_map[asset_id] = asset;
// }
