#include "ShaderInputAndTypeStruct.h"

#include <memory>
#include <memory>

#include "../../../../../../../Projects/Project.h"
#include "../../AssetDataBases/AssetDatabase.h"

editor::projectwindows::assets::elements::model::materials::shaderinputparameters::ShaderInputAndTypeStruct::
ShaderInputAndTypeStruct(ShaderInputParameterType type, std::string name, float value) :type(type), name(name), float_value(value)
{

}

editor::projectwindows::assets::elements::model::materials::shaderinputparameters::ShaderInputAndTypeStruct::
ShaderInputAndTypeStruct(ShaderInputParameterType type, std::string name, int value) : type(type), name(name), int_value(value)
{


}

editor::projectwindows::assets::elements::model::materials::shaderinputparameters::ShaderInputAndTypeStruct::
ShaderInputAndTypeStruct(ShaderInputParameterType type, std::string name, utility::Vector3 value) : type(type), name(name)
{
    vec3_value = std::make_unique<utility::Vector3>(value);
}

editor::projectwindows::assets::elements::model::materials::shaderinputparameters::ShaderInputAndTypeStruct::
ShaderInputAndTypeStruct(ShaderInputParameterType type, std::string name, image::ImageAsset* value) : type(type), name(name)
{
    image = value;
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

utility::Vector3* editor::projectwindows::assets::elements::model::materials::shaderinputparameters::
ShaderInputAndTypeStruct::Get_vec3_value()
{
    return vec3_value.get();
}

editor::projectwindows::assets::elements::model::image::ImageAsset* editor::projectwindows::assets::elements::model::
materials::shaderinputparameters::ShaderInputAndTypeStruct::Get_image_value()
{
    return this->image;
}

void editor::projectwindows::assets::elements::model::materials::shaderinputparameters::ShaderInputAndTypeStruct::
SetValueType(ShaderInputParameterType type)
{
    this->type = type;
}

std::shared_ptr<editor::projectwindows::assets::elements::model::materials::shaderinputparameters::
    ShaderInputAndTypeStruct> editor::projectwindows::assets::elements::model::materials::shaderinputparameters::
    ShaderInputAndTypeStruct::GenerateDefaultInstance(ShaderInputParameterType type, std::string name)
{
    switch (type)
    {
    case ShaderInputParameterType::kInt:
        return std::make_shared<ShaderInputAndTypeStruct>(ShaderInputParameterType::kInt, name, 1);
    case ShaderInputParameterType::kFloat:
        return std::make_shared<ShaderInputAndTypeStruct>(ShaderInputParameterType::kFloat, name, 1.0f);
    case  ShaderInputParameterType::kVec3:
        return std::make_shared<ShaderInputAndTypeStruct>(ShaderInputParameterType::kVec3, name, utility::Vector3(1, 1, 1));
    case  ShaderInputParameterType::kImage:
        auto dafaultimage = projects::Project::GetInstance()->GetDataBase()->GetAsset("40b8bed2-3d20-4f0f-9a9f-2411227d5df4");
        image::ImageAsset* image = dynamic_cast<image::ImageAsset*>(dafaultimage.get());
        return std::make_shared<ShaderInputAndTypeStruct>(ShaderInputParameterType::kImage, name, image);
    }
}
