#pragma once
#include <memory>

#include "../ShaderInputParameterType.h"
#include "ShaderInputs/ShaderInput.h"

namespace editor::projectwindows::assets::elements::model::materials::shaderinputparameters
{
    /**
     * \brief シェーダに入力する値一個と型を示す
     */
    class ShaderInputAndTypeStruct
    {
        ShaderInputParameterType type;
        float float_value;
    public:
        ShaderInputAndTypeStruct(ShaderInputParameterType type, float value);
        ShaderInputParameterType GetValueType();
        float Get_float_value();
    };
}
