#include "AssetViewOption.h"

editor::inspectorwindows::assetviews::options::AssetViewOption::AssetViewOption::AssetViewOption(bool is_input_able)
{
    this->is_input_able = is_input_able;
}

bool editor::inspectorwindows::assetviews::options::AssetViewOption::AssetViewOption::GetInputAble()
{
    return this->is_input_able;
}

