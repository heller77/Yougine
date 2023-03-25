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

    public:
        MainShaderGraphNode();
        std::vector < std::string > GetShaderCodeByOutputVal();
    };
}