#pragma once
#include <memory>
#include <string>

#include "../ShaderInputParameterType.h"

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
    public:
        ShaderInputAndTypeStruct(ShaderInputParameterType type, std::string name, float value);
        ShaderInputAndTypeStruct(ShaderInputParameterType type, std::string name, int value);
        ShaderInputParameterType GetValueType();
        std::string* GetName();
        float* Get_float_value();
        int* Get_int_value();
    };
}
