#pragma once
#include "../shader/ShaderFileAsset.h"

namespace editor::projectwindows::assets::elements::model::materials
{
    class Material :public  Asset
    {
    private:
        std::shared_ptr<shader::ShaderFileAsset> vert_asset_uuid;
        std::shared_ptr < shader::ShaderFileAsset> frag_asset_uuid;
        void Initialize();
    public:
        Material(const std::filesystem::path& path, const std::shared_ptr<utility::youginuuid::YougineUuid>& uuid);

        Material(const std::filesystem::path& assetinfo_file_path);

        void Export() override;

        std::string ToString() override;
    };
}
