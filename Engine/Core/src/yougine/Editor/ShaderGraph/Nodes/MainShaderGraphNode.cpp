#include "MainShaderGraphNode.h"

#include <iostream>

namespace editor::shadergraph
{
    MainShaderGraphNode::MainShaderGraphNode()
    {
        shaderCodeListByOutputVal.push_back(version_dictionary[ShaderVersion::k430]);
    }

    void MainShaderGraphNode::Initialize()
    {

    }


    std::vector<std::string> MainShaderGraphNode::GetShaderCodeByOutputVal()
    {
        return shaderCodeListByOutputVal;
    }

    void MainShaderGraphNode::SetFunctionCodes(std::vector<std::shared_ptr<OutputInfo>> function_outputs)
    {
        if (function_outputs.size() == 0) return;

        for (int r_i = function_outputs.size() - 1; r_i >= 0; r_i--)
        {
            shaderCodeListByOutputVal.push_back(CastValueToString(function_outputs[r_i]->val));
        }
    }

    void MainShaderGraphNode::SetVariableCodes(std::vector<std::shared_ptr<OutputInfo>> variable_outputs)
    {
        if (variable_outputs.size() == 0) return;

        for (int r_i = variable_outputs.size() - 1; r_i >= 0; r_i--)
        {
            shaderCodeListByOutputVal.push_back(CastValueToString(variable_outputs[r_i]->val) + ";");
        }
    }

    void MainShaderGraphNode::SetInitializationCodes()
    {
        shaderCodeListByOutputVal.push_back(version_dictionary[ShaderVersion::k430]);
        shaderCodeListByOutputVal.push_back(qualifier_dictionary[ShaderQualifier::kOut] + " " + type_dictionary[ShaderPropertyType::kVec4] + " " + stage_dictionary[ShaderStage::kFragment] + ";");
        shaderCodeListByOutputVal.push_back(qualifier_dictionary[ShaderQualifier::kIn] + " " + type_dictionary[ShaderPropertyType::kVec3] + " " + "vNormal" + ";");
        shaderCodeListByOutputVal.push_back(qualifier_dictionary[ShaderQualifier::kUniform] + " " + type_dictionary[ShaderPropertyType::kFloat] + " " + "c" + ";");
    }


    void MainShaderGraphNode::UpdateShaderCode(std::vector<std::shared_ptr<OutputInfo>> function_codes, std::vector<std::shared_ptr<OutputInfo>> variable_codes)
    {
        shaderCodeListByOutputVal.clear();
        shaderCodeListByOutputVal.shrink_to_fit();

        //èâä˙êÈåæ
        SetInitializationCodes();

        //ä÷êîíËã`
        SetFunctionCodes(function_codes);

        //mainä÷êî
        shaderCodeListByOutputVal.push_back(codeMainFunction);
        shaderCodeListByOutputVal.push_back("{");
        SetVariableCodes(variable_codes);
        shaderCodeListByOutputVal.push_back("}");
    }

}
