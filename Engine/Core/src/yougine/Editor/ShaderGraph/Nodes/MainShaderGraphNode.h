#pragma once
#include "ShaderGraphNode.h"

namespace editor::shadergraph
{
    class MainShaderGraphNode : public ShaderGraphNode
    {
    protected:
        std::map<ShaderVersion, std::string> version_dictionary = {
            {ShaderVersion::k430, "#version 430"},
        };
        std::map<ShaderStage, std::string> stage_dictionary = {
            {ShaderStage::kFragment, "fragment"},
            {ShaderStage::kVertex, "vertex"},
        };

        std::vector<std::string> shaderCodeListByOutputVal;
        std::string codeMainFunction = "void main()";

    protected:
        void SetFunctionCodes(std::vector<std::shared_ptr<OutputInfo>> function_outputs);
        void SetVariableCodes(std::vector<std::shared_ptr<OutputInfo>> variable_outputs);
        void SetInitializationCodes();

    public:
        void Initialize() override;
        MainShaderGraphNode();
        std::vector < std::string > GetShaderCodeByOutputVal();
        void UpdateShaderCode(std::vector<std::shared_ptr<OutputInfo>> function_codes, std::vector<std::shared_ptr<OutputInfo>> variable_codes);
    };
}