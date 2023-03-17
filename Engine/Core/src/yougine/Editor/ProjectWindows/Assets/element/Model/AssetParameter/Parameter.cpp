#include "Parameter.h"

editor::projectwindows::assets::elements::model::assetparameters::Parameter::Parameter(std::any value,
    std::shared_ptr<inspectorwindows::assetviews::options::AssetViewOption> option)
{
    this->value = value;
    this->option = option;
}

std::any editor::projectwindows::assets::elements::model::assetparameters::Parameter::GetValue()
{
    return this->value;

}

std::shared_ptr<editor::inspectorwindows::assetviews::options::AssetViewOption> editor::projectwindows::assets::elements
::model::assetparameters::Parameter::GetOption()
{
    return this->option;
}
