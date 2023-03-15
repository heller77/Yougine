#pragma once
#include "../Asset.h"

namespace editor::projectwindows::assets::elements::model::shader
{
    class ShaderFileAsset :public Asset
    {
    private:
        //fragment or vertex (enumが本当は使いたいがviewでenumが表示出来ないのでstring)
        std::string shader_kind;
    public:
        ShaderFileAsset(const std::filesystem::path path, std::shared_ptr<utility::youginuuid::YougineUuid> asset_id);
        ShaderFileAsset(const std::filesystem::path assetinfo_file_path);
        void Export() override;
    };
}
