#include "ShaderInputAndTypeStruct.h"

editor::projectwindows::assets::elements::model::materials::shaderinputparameters::ShaderInputAndTypeStruct::
ShaderInputAndTypeStruct(ShaderInputParameterType type, std::string name, float value) :type(type), name(name), float_value(value)
{

}

editor::projectwindows::assets::elements::model::materials::shaderinputparameters::ShaderInputAndTypeStruct::
ShaderInputAndTypeStruct(ShaderInputParameterType type, std::string name, int value) : type(type), name(name), int_value(value)
{


}

editor::projectwindows::assets::elements::model::materials::ShaderInputParameterType editor::projectwindows::assets::
elements::model::materials::shaderinputparameters::ShaderInputAndTypeStruct::GetValueType()
{
    return this->type;
}

std::string* editor::projectwindows::assets::elements::model::materials::shaderinputparameters::ShaderInputAndTypeStruct
::GetName()
{
    return &this->name;
}

float* editor::projectwindows::assets::elements::model::materials::shaderinputparameters::ShaderInputAndTypeStruct::
Get_float_value()
{
    return &float_value;
}

int* editor::projectwindows::assets::elements::model::materials::shaderinputparameters::ShaderInputAndTypeStruct::
Get_int_value()
{
    return &int_value;
}
