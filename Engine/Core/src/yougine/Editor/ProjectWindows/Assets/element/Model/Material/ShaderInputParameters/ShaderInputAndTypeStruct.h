#pragma once
#include <memory>

#include "../ShaderInputParameterType.h"

namespace editor::projectwindows::assets::elements::model::materials::shaderinputparameters
{
    /**
     * \brief シェーダに入力する値一個と型を示す
     */
    class ShaderInputAndTypeStruct
    {
        ShaderInputParameterType type;


        float float_value;
        int int_value;
    public:
        ShaderInputAndTypeStruct(ShaderInputParameterType type, float value);
        ShaderInputAndTypeStruct(ShaderInputParameterType type, int value);
        ShaderInputParameterType GetValueType();
        float* Get_float_value();
        int* Get_int_value();
    };
}
