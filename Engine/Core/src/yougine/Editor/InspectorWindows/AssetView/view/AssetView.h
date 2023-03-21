#pragma once
#include "../../../ProjectWindows/Assets/element/Model/Asset.h"

namespace AssetView
{
    class AssetView
    {
    private:
        std::shared_ptr<editor::projectwindows::assets::elements::model::Asset> asset;

    public:
        void DrawAssetParameter();

        AssetView(std::shared_ptr<editor::projectwindows::assets::elements::model::Asset> asset);
    };
}
