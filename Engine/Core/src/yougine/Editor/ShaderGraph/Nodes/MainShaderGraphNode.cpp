#include "MainShaderGraphNode.h"

namespace editor::shadergraph
{
    MainShaderGraphNode::MainShaderGraphNode()
    {
        shaderCodeListByOutputVal.push_back(version_dictionary[ShaderVersion::k430]);
    }

    std::vector<std::string> MainShaderGraphNode::GetShaderCodeByOutputVal()
    {
        return shaderCodeListByOutputVal;
    }


}
