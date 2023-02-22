#include "ShaderGraphNode.h"

namespace editor::shadergraph
{
    void ShaderGraphNode::SetInputVal(std::string value, int attr)
    {
        input_vals[attr - id - 1] = value;
    }

    std::string ShaderGraphNode::GetOutputVal(int attr)
    {
        return output_vals[attr - id - input_vals.size() - 1];
    }


}
