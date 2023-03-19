#pragma once
#include "../../../../../../utilitys/uuid/YougineUuid.h"
#include "../shader/ShaderFileAsset.h"

namespace editor::projectwindows::assets::elements::model::materials
{
    class Material :public  Asset
    {
    private:
        shader::ShaderFileAsset vert_asset_uuid;
        shader::ShaderFileAsset frag_asset_uuid;
    public:

    };
}
