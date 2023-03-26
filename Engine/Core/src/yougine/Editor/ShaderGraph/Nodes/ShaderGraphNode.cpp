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
        input_infos[index]->val = value;
    }

    std::string ShaderGraphNode::GetOutputVal(int index)
    {
        return output_infos[index]->val;
    }

    void ShaderGraphNode::ResetInputVal(int input_index)
    {
        input_infos[input_index]->is_linked = false;
        input_infos[input_index]->val = input_infos[input_index]->init_val;
    }

    void ShaderGraphNode::ResetOutputVal(int output_index)
    {
        output_infos[output_index]->is_linked = false;
        output_infos[output_index]->val = output_infos[output_index]->init_val;
    }

    void ShaderGraphNode::DisplayValues()
    {
        std::cout << "Node ID : " + std::to_string(id) + "'s ";
        std::cout << "Input Values ";
        for (int i = 0; i < input_infos.size(); i++)
        {
            std::cout << std::to_string(i) + " : " + input_infos[i]->val + ", ";
        }
        std::cout << "" << std::endl;

        std::cout << "Output Values ";
        for (int i = 0; i < output_infos.size(); i++)
        {
            std::cout << std::to_string(i) + " : " + output_infos[i]->val + ", ";
        }
        std::cout << "" << std::endl;
    }

    void ShaderGraphNode::UpdateOutputVal()
    {
        int c = 0;
        for (std::shared_ptr<InputInfo> input_info : input_infos)
        {
            c += stoi(input_info->val);
        }
        for (int i = 0; i < output_infos.size(); i++)
        {
            output_infos[i]->val = std::to_string((c * 2));
        }
    }

    void ShaderGraphNode::SetParentNode(ShaderGraphNode* parent_node, std::pair<int, int> attr_pair)
    {
        this->parent_nodes = parent_node;
        this->parent_nodes->input_infos[this->parent_nodes->FindLinkedInputIndex(attr_pair.first)]->is_linked = true;
    }

    bool ShaderGraphNode::UpdateParentNodeValue(std::pair<int, int> attr_pair)
    {
        if (this->parent_nodes == nullptr) return false;

        int input_index = parent_nodes->FindLinkedInputIndex(attr_pair.first), output_index = FindLinkedOutputIndex(attr_pair.second);

        if (this->parent_nodes->input_infos[input_index]->is_linked)
        {
            this->parent_nodes->SetInputVal(this->GetOutputVal(output_index), input_index);
        }
        this->parent_nodes->UpdateOutputVal();
        this->parent_nodes->DisplayValues();

        return true;
    }

    int ShaderGraphNode::FindLinkedInputIndex(int input_attr)
    {
        for (int i = 0; i < input_infos.size(); i++)
        {
            if (input_infos[i]->attr == input_attr) return i;
        }

        return -1;
    }

    int ShaderGraphNode::FindLinkedOutputIndex(int output_attr)
    {
        for (int i = 0; i < output_infos.size(); i++)
        {
            if (output_infos[i]->attr == output_attr) return i;

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
