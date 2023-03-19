#include "AssetViewOption.h"


editor::inspectorwindows::assetviews::options::AssetViewOption::AssetViewOption(bool is_input_able,
    bool is_only_display_not_write)
{
    this->is_input_able = is_input_able;
    this->is_only_display_not_write = is_only_display_not_write;
}

bool editor::inspectorwindows::assetviews::options::AssetViewOption::AssetViewOption::GetInputAble()
{
    return this->is_input_able;
}

bool editor::inspectorwindows::assetviews::options::AssetViewOption::GetOnlyDisplayNotWrite()
{
    return this->is_only_display_not_write;
}

