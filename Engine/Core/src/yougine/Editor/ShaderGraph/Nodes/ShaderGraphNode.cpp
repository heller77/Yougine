#include "ShaderGraphNode.h"

#include <iostream>

namespace editor::shadergraph
{
    ShaderGraphNode::ShaderGraphNode()
    {
        std::vector<std::pair<std::string, std::string>> input_vals;
        input_vals.emplace_back(std::make_pair("1", "1"));

        std::vector<std::pair<std::string, std::string>> output_vals;
        output_vals.emplace_back(std::make_pair("2", "2"));

        Initialize(input_vals, output_vals);
    }

    void ShaderGraphNode::Initialize(std::vector<std::pair<std::string, std::string>> init_input_vals, std::vector<std::pair<std::string, std::string>> init_output_vals)
    {
        this->init_input_vals = init_input_vals;
        this->init_output_vals = init_output_vals;
    }


    void ShaderGraphNode::SetInputVal(std::string value, int index)
    {
        input_info[index].second.second = value;
    }

    std::string ShaderGraphNode::GetOutputVal(int index)
    {
        return output_info[index].second.second;
    }

    void ShaderGraphNode::ResetInputVal(int input_index)
    {
        input_info[input_index].first.second = false;
        input_info[input_index].second.second = input_info[input_index].second.first;
    }

    void ShaderGraphNode::ResetOutputVal(int output_index)
    {
        output_info[output_index].first.second = false;
        output_info[output_index].second.second = output_info[output_index].second.first;
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
        for (std::pair<std::pair<int, bool>, std::pair<std::string, std::string>> input : input_info)
        {
            c += stoi(input.second.second);
        }
        for (int i = 0; i < output_info.size(); i++)
        {
            output_info[i].second.second = std::to_string((c * 2));
        }
    }

    void ShaderGraphNode::SetParentNode(ShaderGraphNode* parent_node, std::pair<int, int> attr_pair)
    {
        this->parent_nodes = parent_node;
        this->parent_nodes->input_info[this->parent_nodes->FindLinkedInputIndex(attr_pair.first)].first.second = true;
    }

    bool ShaderGraphNode::UpdateParentNodeValue(std::pair<int, int> attr_pair)
    {
        if (this->parent_nodes == nullptr) return false;

        int input_index = parent_nodes->FindLinkedInputIndex(attr_pair.first), output_index = FindLinkedOutputIndex(attr_pair.second);

        if (this->parent_nodes->input_info[input_index].first.second)
        {
            this->parent_nodes->SetInputVal(this->GetOutputVal(output_index), input_index);
        }
        this->parent_nodes->UpdateOutputVal();
        this->parent_nodes->DisplayValues();

        return true;
    }

    int ShaderGraphNode::FindLinkedInputIndex(int input_attr)
    {
        for (int i = 0; i < input_info.size(); i++)
        {
            if (input_info[i].first.first == input_attr) return i;
        }

        return -1;
    }

    int ShaderGraphNode::FindLinkedOutputIndex(int output_attr)
    {
        for (int i = 0; i < output_info.size(); i++)
        {
            if (output_info[i].first.first == output_attr) return i;

        }

        return -1;
    }

    ShaderGraphNode* ShaderGraphNode::GetParentNode()
    {
        return this->parent_nodes;
    }

    std::vector<std::pair<std::string, std::string>> ShaderGraphNode::GetInitInputVals()
    {
        return init_input_vals;
    }

    std::vector<std::pair<std::string, std::string>> ShaderGraphNode::GetInitOutputVals()
    {
        return init_output_vals;
    }

    void ShaderGraphNode::DisLinkNode(std::pair<int, int> attr_pair)
    {
        ResetInputVal(FindLinkedInputIndex(attr_pair.first));
        UpdateOutputVal();
        DisplayValues();
    }

}
