#include "ShaderInputAndTypeStruct.h"

editor::projectwindows::assets::elements::model::materials::shaderinputparameters::ShaderInputAndTypeStruct::
ShaderInputAndTypeStruct(ShaderInputParameterType type, float value) :type(type), float_value(value)
{

}

editor::projectwindows::assets::elements::model::materials::ShaderInputParameterType editor::projectwindows::assets::
elements::model::materials::shaderinputparameters::ShaderInputAndTypeStruct::GetValueType()
{
    return this->type;
}

float editor::projectwindows::assets::elements::model::materials::shaderinputparameters::ShaderInputAndTypeStruct::
Get_float_value()
{
    return this->float_value;
}
