#include "AssetViewOption.h"



// template <class T>
// editor::inspectorwindows::assetviews::options::AssetViewOption<T>::AssetViewOption(bool is_input_able, bool is_only_display_not_write, bool isAsset)
// {
// }


editor::inspectorwindows::assetviews::options::AssetViewOption::AssetViewOption(bool is_input_able, bool is_only_display_not_write, bool isAsset)
{
    this->is_input_able = is_input_able;
    this->is_only_display_not_write = is_only_display_not_write;
    this->isAsset = isAsset;
}

void editor::inspectorwindows::assetviews::options::AssetViewOption::SetInputAction(
    std::function<void(std::shared_ptr<editor::projectwindows::assets::elements::model::Asset>)> setAsset)
{
    this->setAsset = setAsset;
}

std::function<void(std::shared_ptr<editor::projectwindows::assets::elements::model::Asset>)> editor::inspectorwindows::
assetviews::options::AssetViewOption::GetInputAction_input_Asset()
{
    return this->setAsset;
}

// void editor::inspectorwindows::assetviews::options::AssetViewOption::FireInputAction(
//     std::shared_ptr<utility::youginuuid::YougineUuid> input)
// {
//     if (this->setAsset)
//     {
//         setAsset(std::move(input));
//     }
// }

bool editor::inspectorwindows::assetviews::options::AssetViewOption::AssetViewOption::GetInputAble()
{
    return this->is_input_able;
}



bool editor::inspectorwindows::assetviews::options::AssetViewOption::GetOnlyDisplayNotWrite()
{
    return this->is_only_display_not_write;
}

bool editor::inspectorwindows::assetviews::options::AssetViewOption::GetIsAsset()
{
    return this->isAsset;
}

