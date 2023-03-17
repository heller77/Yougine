#pragma once
namespace editor::inspectorwindows::assetviews::options
{
    class AssetViewOption
    {
    private:
        //入力可能か
        bool is_input_able;
    public:
        AssetViewOption(bool is_input_able = false);

        bool GetInputAble();

    };
}
