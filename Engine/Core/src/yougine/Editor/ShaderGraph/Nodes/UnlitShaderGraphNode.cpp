#include "UnlitShaderGraphNode.h"

#include <iostream>

namespace editor::shadergraph
{
    UnlitShaderGraphNode::UnlitShaderGraphNode() : MainShaderGraphNode()
    {
        std::vector<std::pair<std::any, std::string>> input_vals;
        input_vals.emplace_back(std::make_pair(&albedo, "albedo"));

        std::vector<std::pair<std::any, std::string>> output_vals;
        color = albedo;
        output_vals.emplace_back(std::make_pair(&color, ""));

        Initialize(input_vals, output_vals);

        shaderCodeListByOutputVal.push_back(qualifier_dictionary[ShaderQualifier::kOut] + " " + type_dictionary[ShaderPropertyType::kVec3] + " " + stage_dictionary[ShaderStage::kFragment]);
        shaderCodeListByOutputVal.push_back(type_dictionary[ShaderPropertyType::kVec3] + " " + "color");
        shaderCodeListByOutputVal.push_back(codeMainFunction);
        shaderCodeListByOutputVal.push_back("{");
        shaderCodeListByOutputVal.push_back(stage_dictionary[ShaderStage::kFragment] + " = " + "glm::" + type_dictionary[ShaderPropertyType::kVec4] + "(" + CastValueToString(input_infos[0]->init_val) + ", 1.0);");
        shaderCodeListByOutputVal.push_back("}");
    }

    void UnlitShaderGraphNode::UpdateOutputVal()
    {
        std::cout << "00000" << std::endl;
        output_infos[0]->val = input_infos[0]->val;
        std::cout << "111111" << std::endl;
        shaderCodeListByOutputVal[5] = stage_dictionary[ShaderStage::kFragment] + " = " + "glm::" + type_dictionary[ShaderPropertyType::kVec4] + "(" + CastValueToString(output_infos[0]->val) + ", 1.0);";
        std::cout << "2222222" << std::endl;
    }

}
