#include "ShaderGraphNode.h"

namespace editor::shadergraph
{
    std::string ShaderGraphNode::GetPropertyType(ShaderPropertyType shaderPropertyType)
    {
        return type_dictionary[shaderPropertyType];
    }

    std::vector<std::vector<std::string>> ShaderGraphNode::GetProperties()
    {
        return properties;
    }

    void ShaderGraphNode::AddValToProperty(std::vector<std::string> val)
    {
        properties.push_back(val);
    }

}
