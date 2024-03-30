#pragma once
#include <map>
#include <string>
#include <vector>

#include "ParameterView.h"
#include "../../../Editor/ProjectWindows/Assets/element/Model/Material/ShaderInputParameters/ShaderInputAndTypeStruct.h"

namespace utility::view::parameters
{
    namespace materials = editor::projectwindows::assets::elements::model::materials;
    namespace shaderinputparameters = materials::shaderinputparameters;


    class ShaderInputParameterView : public ParameterView
    {
        // std::vector<std::string> type_list;
        const std::string label = "type";;

        std::string name;

        float value;

        std::map<materials::ShaderInputParameterType, std::string> type2text;

        std::vector<std::shared_ptr<shaderinputparameters::ShaderInputAndTypeStruct>>* vec_shaderinput;

        std::shared_ptr<shaderinputparameters::ShaderInputAndTypeStruct> new_value;

        // std::shared_ptr<>

    public:
        void Draw() override;

        ShaderInputParameterView(
            std::vector<std::shared_ptr<shaderinputparameters::ShaderInputAndTypeStruct>>* vec_shaderinput);
    };
}
