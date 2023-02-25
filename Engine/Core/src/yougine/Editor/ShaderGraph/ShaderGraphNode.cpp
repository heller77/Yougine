#include "ShaderGraphNode.h"

#include <iostream>

namespace editor::shadergraph
{
    ShaderGraphNode::ShaderGraphNode()
    {
        init_input_val = std::make_pair("0", "0");
        init_output_val = std::make_pair("2", "2");
    }

    void ShaderGraphNode::SetInputVal(std::string value, int index)
    {
        input_info[index].second.second = value;
    }

    std::string ShaderGraphNode::GetOutputVal(int index)
    {
        return output_info[index].second.second;
    }

    void ShaderGraphNode::ResetVal(int index)
    {
        input_info[index].second.second = input_info[index].second.first;
    }

    void ShaderGraphNode::DisplayValues()
    {
        std::cout << "Node ID : " + std::to_string(id) + "'s ";
        std::cout << "Input Values ";
        for (int i = 0; i < input_info.size(); i++)
        {
            std::cout << std::to_string(i) + " : " + input_info[i].second.second + ", ";
        }
        std::cout << "" << std::endl;

        std::cout << "Output Values ";
        for (int i = 0; i < output_info.size(); i++)
        {
            std::cout << std::to_string(i) + " : " + output_info[i].second.second + ", ";
        }
        std::cout << "" << std::endl;
    }

    void ShaderGraphNode::UpdateOutputVal()
    {
        int c = 0;
        for (std::pair<int, std::pair<std::string, std::string>> input : input_info)
        {
            c += stoi(input.second.second);
        }
        for (int i = 0; i < output_info.size(); i++)
        {
            output_info[i].second.second = std::to_string((c * 2));
        }
    }

    void ShaderGraphNode::SetParentNode(ShaderGraphNode* parent_node)
    {
        this->parent_node = parent_node;
    }

    bool ShaderGraphNode::UpdateParentNodeValue(std::pair<int, int> attr_pair)
    {
        if (this->parent_node == nullptr) return false;

        int input_index = parent_node->FindLinkedInputIndex(attr_pair.first), output_index = FindLinkedOutputIndex(attr_pair.second);

        this->parent_node->SetInputVal(this->GetOutputVal(output_index), input_index);
        this->parent_node->UpdateOutputVal();
        this->parent_node->DisplayValues();

        return true;
    }

    int ShaderGraphNode::FindLinkedInputIndex(int input_attr)
    {
        for (int i = 0; i < input_info.size(); i++)
        {
            std::cout << input_attr << std::endl;
            std::cout << input_info[i].first << std::endl;
            if (input_info[i].first == input_attr) return i;
        }

        return -1;
    }

    int ShaderGraphNode::FindLinkedOutputIndex(int output_attr)
    {
        for (int i = 0; i < output_info.size(); i++)
        {
            if (output_info[i].first == output_attr) return i;

        }

        return -1;
    }

    ShaderGraphNode* ShaderGraphNode::GetParentNode()
    {
        return parent_node;
    }

    std::pair<std::string, std::string> ShaderGraphNode::GetInitInputVal()
    {
        return init_input_val;
    }

    std::pair<std::string, std::string> ShaderGraphNode::GetInitOutputVal()
    {
        return init_output_val;
    }
}
