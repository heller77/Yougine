#include "ShaderGraphNode.h"

#include <iostream>

namespace editor::shadergraph
{
    ShaderGraphNode::ShaderGraphNode()
    {
        input_vals =
        {
            std::vector < std::string>{"1", "1"},
        };

        output_vals =
        {
            std::vector < std::string>{"2", "2"},
        };
    }

    void ShaderGraphNode::SetInputVal(std::string value, int attr)
    {
        const uint8_t index = attr - id - 1;
        input_vals[index][1] = value;
    }

    std::string ShaderGraphNode::GetOutputVal(int attr)
    {
        const uint8_t size = (uint8_t)input_vals.size();
        const uint8_t index = attr - id - size - 1;
        return output_vals[index][1];
    }

    void ShaderGraphNode::ResetVal(int attr)
    {
        const uint8_t c_index = attr - id - 1;
        input_vals[c_index][1] = input_vals[c_index][0];
    }

    void ShaderGraphNode::DisplayValues()
    {
        std::cout << "Node ID : " + std::to_string(id) + "'s ";
        std::cout << "Input Values ";
        for (int i = 0; i < input_vals.size(); i++)
        {
            std::cout << std::to_string(i) + " : " + input_vals[i][1] + ", ";
        }
        std::cout << "" << std::endl;

        std::cout << "Output Values ";
        for (int i = 0; i < output_vals.size(); i++)
        {
            std::cout << std::to_string(i) + " : " + output_vals[i][1] + ", ";
        }
        std::cout << "" << std::endl;
    }
}
