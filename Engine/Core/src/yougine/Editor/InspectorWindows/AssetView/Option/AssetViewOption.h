#pragma once
#include <functional>

#include "../../../../utilitys/uuid/YougineUuid.h"

namespace editor
{
    namespace projectwindows
    {
        namespace assets
        {
            namespace elements
            {
                namespace model
                {
                    class Asset;
                }
            }
        }
    }
}

namespace editor::inspectorwindows::assetviews::options
{

    class AssetViewOption
    {
    private:
        //入力可能か
        bool is_input_able;

        bool is_only_display_not_write;

        bool isAsset;
        std::function<void(std::shared_ptr<editor::projectwindows::assets::elements::model::Asset>)> setAsset;
    public:
        AssetViewOption(bool is_input_able = false, bool is_only_display_not_write = false, bool isAsset = false);


        void SetInputAction(std::function<void(std::shared_ptr<editor::projectwindows::assets::elements::model::Asset>)> setAsset);
        std::function<void(std::shared_ptr<editor::projectwindows::assets::elements::model::Asset>)> GetInputAction_input_Asset();
        // void FireInputAction(std::shared_ptr<utility::youginuuid::YougineUuid> input);

        bool GetInputAble();

        bool GetOnlyDisplayNotWrite();
        bool GetIsAsset();
    };


}
