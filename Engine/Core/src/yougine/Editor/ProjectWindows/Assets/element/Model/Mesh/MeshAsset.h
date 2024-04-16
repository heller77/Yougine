#pragma once
#include "../Asset.h"

namespace editor::projectwindows::assets::elements::model::mesh
{
    class MeshAsset :public Asset
    {
    public:
        MeshAsset(const std::filesystem::path path, std::shared_ptr<utility::youginuuid::YougineUuid> asset_id);
        MeshAsset(const std::filesystem::path assetinfo_file_path);

        void Export() override;

        std::string ToString() override;

        void InitializeParameter() override;
    };
}
