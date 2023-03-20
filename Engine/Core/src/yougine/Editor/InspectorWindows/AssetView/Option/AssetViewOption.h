#pragma once
#include <functional>

#include "../../../../utilitys/uuid/YougineUuid.h"

namespace editor::inspectorwindows::assetviews::options
{

    class AssetViewOption
    {
    private:
        //入力可能か
        bool is_input_able;

        bool is_only_display_not_write;

        bool isAsset;
        std::function<void(std::shared_ptr<utility::youginuuid::YougineUuid>)> setAsset;
    public:
        AssetViewOption(bool is_input_able = false, bool is_only_display_not_write = false, bool isAsset = false);


        void SetInputAction(std::function<void(std::shared_ptr<utility::youginuuid::YougineUuid>)> setAsset);
        void FireInputAction(std::shared_ptr<utility::youginuuid::YougineUuid> input);

        bool GetInputAble();

        bool GetOnlyDisplayNotWrite();
        bool GetIsAsset();
    };


}
