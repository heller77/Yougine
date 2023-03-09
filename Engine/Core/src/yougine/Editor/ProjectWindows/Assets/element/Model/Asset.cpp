#include "Asset.h"

editor::projectwindows::assets::elements::model::Asset::Asset()
{

}

std::map<std::string, std::any> editor::projectwindows::assets::elements::model::Asset::GetParameter()
{
    return this->parameter;
}
