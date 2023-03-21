#pragma once
#include "../../../../utilitys/view/parameters/AssetReference.h"
#include "../../../ProjectWindows/Assets/element/Model/Asset.h"

namespace AssetView
{

    class AssetView
    {
    private:
        std::shared_ptr<editor::projectwindows::assets::elements::model::Asset> asset;
        std::vector<std::shared_ptr<utility::view::parameters::ParameterView>> parameter_vec;
    public:
        void DrawAssetParameter();

        AssetView(std::shared_ptr<editor::projectwindows::assets::elements::model::Asset> asset);
    };
}
