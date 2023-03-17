#pragma once
#include <any>
#include <memory>

#include "../../../../../InspectorWindows/AssetView/Option/AssetViewOption.h"

namespace editor::projectwindows::assets::elements::model::assetparameters
{
    class Parameter
    {
        //パラメータで表す値そのもの
    private:
        std::any value;
        std::shared_ptr<inspectorwindows::assetviews::options::AssetViewOption> option;
    public:
        Parameter(std::any value, std::shared_ptr<inspectorwindows::assetviews::options::AssetViewOption> option);
        std::any GetValue();
        std::shared_ptr<inspectorwindows::assetviews::options::AssetViewOption> GetOption();
    };
}
