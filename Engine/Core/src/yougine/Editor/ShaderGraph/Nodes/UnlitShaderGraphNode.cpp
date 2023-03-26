#include "UnlitShaderGraphNode.h"

namespace editor::shadergraph
{
    UnlitShaderGraphNode::UnlitShaderGraphNode() : MainShaderGraphNode()
    {
        std::vector<std::pair<std::string, std::string>> input_vals;
        std::string vector_zero = "vec3(0.0, 0.0, 0.0)";
        input_vals.emplace_back(std::make_pair(vector_zero, vector_zero));

        std::vector<std::pair<std::string, std::string>> output_vals;
        output_vals.emplace_back(std::make_pair(input_vals[0].first, input_vals[0].first));

        Initialize(input_vals, output_vals);

        shaderCodeListByOutputVal.push_back(qualifier_dictionary[ShaderQualifier::kOut] + " " + type_dictionary[ShaderPropertyType::kVec3] + " " + stage_dictionary[ShaderStage::kFragment]);
        shaderCodeListByOutputVal.push_back(type_dictionary[ShaderPropertyType::kVec3] + " " + "color");
        shaderCodeListByOutputVal.push_back(codeMainFunction);
        shaderCodeListByOutputVal.push_back("{");
        shaderCodeListByOutputVal.push_back(stage_dictionary[ShaderStage::kFragment] + " = " + "glm::" + type_dictionary[ShaderPropertyType::kVec4] + "(" + init_input_vals[0].first + ", 1.0);");
        shaderCodeListByOutputVal.push_back("}");
    }

    void UnlitShaderGraphNode::UpdateOutputVal()
    {
        output_infos[0]->val = input_infos[0]->val;
        shaderCodeListByOutputVal[5] = stage_dictionary[ShaderStage::kFragment] + " = " + "glm::" + type_dictionary[ShaderPropertyType::kVec4] + "(" + output_infos[0]->val + ", 1.0);";
    }

}
