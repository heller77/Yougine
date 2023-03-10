#include "Parameter.h"

std::any editor::projectwindows::assets::elements::model::assetparameters::Parameter::GetValue()
{
    return this->value;

}

std::shared_ptr<editor::inspectorwindows::assetviews::options::AssetViewOption> editor::projectwindows::assets::elements
::model::assetparameters::Parameter::GetOption()
{
    return this->option;
}
