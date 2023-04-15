#include "UnlitShaderGraphNode.h"

#include <iostream>

namespace editor::shadergraph
{
    UnlitShaderGraphNode::UnlitShaderGraphNode() : MainShaderGraphNode()
    {
        code_type = CodeType::kMain;

        Initialize();
    }

    void UnlitShaderGraphNode::Initialize()
    {
        std::vector<std::pair<std::any, std::string>> input_vals;
        input_vals.emplace_back(std::make_pair(&albedo, "albedo"));

        std::vector<std::pair<std::string*, std::string>> output_vals;
        color = stage_dictionary[ShaderStage::kFragment] + " = " + "glm::" + type_dictionary[ShaderPropertyType::kVec4] + "(" + albedo + ", 1.0)";
        output_vals.emplace_back(std::make_pair(&color, ""));

        input_field_width = 75.0f;

        InitializeInfos(input_vals, output_vals);

        SetInitializationCodes();
        shaderCodeListByOutputVal.push_back(codeMainFunction);
        shaderCodeListByOutputVal.push_back("{");
        shaderCodeListByOutputVal.push_back(color);
        shaderCodeListByOutputVal.push_back("}");
    }


    void UnlitShaderGraphNode::UpdateOutputVal()
    {
        color = stage_dictionary[ShaderStage::kFragment] + " = " + "glm::" + type_dictionary[ShaderPropertyType::kVec4] + "(" + CastValueToString(input_infos[0]->unique_vn) + ", 1.0)";
        output_infos[0]->val = &color;
    }

}
