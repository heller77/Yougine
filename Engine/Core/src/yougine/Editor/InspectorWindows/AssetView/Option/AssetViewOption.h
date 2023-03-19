#pragma once
namespace editor::inspectorwindows::assetviews::options
{
    class AssetViewOption
    {
    private:
        //入力可能か
        bool is_input_able;

        bool is_only_display_not_write;
    public:
        AssetViewOption(bool is_input_able = false, bool is_only_display_not_write = false);

        bool GetInputAble();

        bool GetOnlyDisplayNotWrite();
    };
}
