#pragma once
#include <memory>
#include <string>

#include "../ShaderInputParameterType.h"
#include "UserShare/utilitys/YougineMath.h"
#include "../../../../../../../utilitys/view/parameters/AssetReference.h"
#include "../../Image/ImageAsset.h"

namespace editor::projectwindows::assets::elements::model::materials::shaderinputparameters
{
    /**
     * \brief シェーダに入力する値一個と型を示す
     */
    class ShaderInputAndTypeStruct
    {
        ShaderInputParameterType type;
        std::string name;

        float float_value;
        int int_value;
        std::unique_ptr<utility::Vector3> vec3_value;
        image::ImageAsset* image;
    public:
        ShaderInputAndTypeStruct(ShaderInputParameterType type, std::string name, float value);
        ShaderInputAndTypeStruct(ShaderInputParameterType type, std::string name, int value);
        ShaderInputAndTypeStruct(ShaderInputParameterType type, std::string name, utility::Vector3 value);
        ShaderInputAndTypeStruct(ShaderInputParameterType type, std::string name, image::ImageAsset* value);

        void Export();
        ShaderInputParameterType GetValueType();
        std::string* GetName();
        float* Get_float_value();
        int* Get_int_value();
        utility::Vector3* Get_vec3_value();
        image::ImageAsset* Get_image_value();

        void SetValueType(ShaderInputParameterType type);
        static std::shared_ptr<ShaderInputAndTypeStruct> GenerateDefaultInstance(ShaderInputParameterType type, std::string name);
    };
}
