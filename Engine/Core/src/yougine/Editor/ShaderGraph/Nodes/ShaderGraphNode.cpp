#include "ShaderGraphNode.h"
#include <iostream>


namespace editor::shadergraph
{
    ShaderGraphNode::ShaderGraphNode()
    {

    }

    void ShaderGraphNode::Initialize(std::vector<std::pair<std::any, std::string>> init_input_vals, std::vector<std::pair<std::any, std::string>> init_output_vals)
    {
        for (std::pair<std::any, std::string> input_val : init_input_vals)
        {
            std::shared_ptr<InputInfo> input_info = std::make_shared<InputInfo>();
            input_info->init_val = input_val.first;
            input_info->val = input_info->init_val;
            input_info->label = input_val.second;
            input_info->field_width = input_field_width;
            input_infos.emplace_back(input_info);
        }
        for (std::pair<std::any, std::string> output_val : init_output_vals)
        {
            std::shared_ptr<OutputInfo> output_info = std::make_shared<OutputInfo>();
            output_info->init_val = output_val.first;
            output_info->val = output_info->init_val;
            output_info->label = output_val.second;
            output_infos.emplace_back(output_info);
        }
    }


    void ShaderGraphNode::SetInputVal(std::any value, int index)
    {
        input_infos[index]->val = value;
    }

    std::any ShaderGraphNode::GetOutputVal(int index)
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
        std::cout << "" << std::endl;
        std::cout << "----------" + name + " Node Info ----------" << std::endl;
        std::cout << "Input :";
        for (int i = 0; i < input_infos.size(); i++)
        {
            std::cout << std::to_string(i) + " : " + CastValueToString((input_infos[i]->val)) + ", ";
        }
        std::cout << "" << std::endl;

        std::cout << "Output :";
        for (int i = 0; i < output_infos.size(); i++)
        {
            std::cout << std::to_string(i) + " : " + CastValueToString((output_infos[i]->val)) + ", ";
        }
        std::cout << "" << std::endl;
    }

    void ShaderGraphNode::UpdateOutputVal()
    {
        /*
        int c = 0;
        for (std::shared_ptr<InputInfo> input_info : input_infos)
        {
            //c += stoi(input_info->val);
        }
        for (int i = 0; i < output_infos.size(); i++)
        {
            //output_infos[i]->val = std::to_string((c * 2));
        }
        */
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

    std::vector<std::shared_ptr<InputInfo>> ShaderGraphNode::GetInputInfos()
    {
        return input_infos;
    }

    std::vector<std::shared_ptr<OutputInfo>> ShaderGraphNode::GetOutputInfos()
    {
        return output_infos;
    }

    void ShaderGraphNode::DisLinkNode(std::pair<int, int> attr_pair)
    {
        ResetInputVal(FindLinkedInputIndex(attr_pair.first));
        UpdateOutputVal();
        DisplayValues();
    }

    /*
     * ‚±‚ê‚È‚ñ‚Æ‚©‚È‚ç‚ñ‚Ì
     */
    std::string ShaderGraphNode::CastValueToString(std::any val)
    {
        std::string casted_val = "";

        if (val.type() == typeid(int*))
        {
            int v = *std::any_cast<int*>(val);
            casted_val = std::to_string(v);
        }
        if (val.type() == typeid(float*))
        {
            float v = *std::any_cast<float*>(val);
            casted_val = std::to_string(v);
        }
        /*
         * string‚Ì”»’è‚ª‚¤‚Ü‚­‚¢‚Á‚Ä‚¢‚È‚¢
         *
         * —á) val‚ªstring‚Ì‚Æ‚«true‚É‚È‚ç‚È‚¢
         */
        if (val.type() == typeid(std::string))
        {
            std::string v = std::any_cast<std::string> (val);
            casted_val = v;
        }
        if (val.type() == typeid(std::string*))
        {
            std::string v = *std::any_cast<std::string*> (val);
            casted_val = v;
        }
        if (val.type() == typeid(bool*))
        {
            bool v = *std::any_cast<bool*>(val);
            if (v) casted_val = unique_type_dictionary[ShaderUniqueValue::kTrue];
            else casted_val = unique_type_dictionary[ShaderUniqueValue::kFalse];
        }
        if (typeid(val) == typeid(std::any))
        {
            std::string typename_ = val.type().name();
            std::string str_type = utility::Split::SplitStr(utility::Split::SplitStr(val.type().name(), ' ')[1], '::').back();

            if (str_type == "Vector2")
            {
                float v[2];
                utility::Vector2 vec2 = *std::any_cast<utility::Vector2*> (val);
                v[0] = vec2.x;
                v[1] = vec2.y;
                casted_val = "vec2(" + std::to_string(v[0]) + ", " + std::to_string(v[1]) + ")";
            }
            if (str_type == "Vector3")
            {
                float v[3];
                utility::Vector3 vec3 = *std::any_cast<utility::Vector3*> (val);
                v[0] = vec3.x;
                v[1] = vec3.y;
                v[2] = vec3.z;
                casted_val = "vec3(" + std::to_string(v[0]) + ", " + std::to_string(v[1]) + ", " + std::to_string(v[2]) + ")";
            }
        }

        return casted_val;
    }

    void ShaderGraphNode::SetInputInfoAttr(int index, int attr)
    {
        input_infos[index]->attr = attr;
    }

    void ShaderGraphNode::SetOutputInfoAttr(int index, int attr)
    {
        output_infos[index]->attr = attr;
    }

    float ShaderGraphNode::GetInputFieldWidth()
    {
        return input_field_width;
    }


}
