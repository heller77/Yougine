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
        std::string label;

        std::string name;

        float value;

        std::map<materials::ShaderInputParameterType, std::string> type2text;

        std::vector<std::shared_ptr<shaderinputparameters::ShaderInputAndTypeStruct>> vec_shaderinput;

    public:
        void Draw() override;

        ShaderInputParameterView(
            std::vector<std::shared_ptr<shaderinputparameters::ShaderInputAndTypeStruct>> vec_shaderinput);
    };
}
