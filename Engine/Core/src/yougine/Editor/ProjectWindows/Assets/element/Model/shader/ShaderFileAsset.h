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
        explicit ShaderFileAsset(const std::filesystem::path& path);

        void Export() override;
    };
}
