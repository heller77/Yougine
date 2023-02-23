#include "ShaderGraphNode.h"

#include <iostream>

namespace editor::shadergraph
{
    ShaderGraphNode::ShaderGraphNode()
    {
        input_vals =
        {
            {std::make_pair("1", "1")},
        };

        output_vals =
        {
            {std::make_pair("1", "1")},
        };
    }

    void ShaderGraphNode::UpdateVal(ShaderGraphNode* linked_node, int input_attr, int output_attr)
    {
        //前連結は同期できている
        //後ろ連結は同期できていないが、前連結したら同期する
        SetInputVal(linked_node->GetOutputVal(output_attr), input_attr);

        UpdateOutputVal();
        linked_node->UpdateOutputVal();
    }

    void ShaderGraphNode::SetInputVal(std::string value, int attr)
    {
        const uint8_t index = attr - id - 1;
        input_vals[index].second = value;
    }

    std::string ShaderGraphNode::GetOutputVal(int attr)
    {
        const uint8_t size = (uint8_t)input_vals.size();
        const uint8_t index = attr - id - size - 1;
        return output_vals[index].second;
    }

    void ShaderGraphNode::ResetVal(int attr)
    {
        const uint8_t c_index = attr - id - 1;
        input_vals[c_index].second = input_vals[c_index].first;
    }

    void ShaderGraphNode::DisplayValues()
    {
        std::cout << "Node ID : " + std::to_string(id) + "'s ";
        std::cout << "Input Values ";
        for (int i = 0; i < input_vals.size(); i++)
        {
            std::cout << std::to_string(i) + " : " + input_vals[i].second + ", ";
        }
        std::cout << "" << std::endl;

        std::cout << "Output Values ";
        for (int i = 0; i < output_vals.size(); i++)
        {
            std::cout << std::to_string(i) + " : " + output_vals[i].second + ", ";
        }
        std::cout << "" << std::endl;
    }

    void ShaderGraphNode::UpdateOutputVal()
    {
        int c = 0;
        for (std::pair<std::string, std::string> input : input_vals)
        {
            c += stoi(input.second);
        }
        //この実装だとノードは一つのアウトプットしか出せない
        output_vals[0].second = std::to_string((c * 2));
    }

}
