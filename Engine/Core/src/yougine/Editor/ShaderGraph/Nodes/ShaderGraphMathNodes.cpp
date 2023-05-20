#include  "ShaderGraphMethNodes.h"

#include <iostream>

namespace  editor::shadergraph
{
    ShaderGraphAddNode::ShaderGraphAddNode()
    {
        code_type = CodeType::kVariable;

        Initialize();
    }

    void ShaderGraphAddNode::Initialize()
    {
        std::vector<std::pair<std::any, std::string>> input_vals;
        input_vals.emplace_back(std::make_pair(&value1, "float1"));
        input_vals.emplace_back(std::make_pair(&value2, "float2"));

        std::vector<std::pair<std::string*, std::string>> output_vals;
        std::string init_output = (CastValueToString(&value1)) + " + " + (CastValueToString(&value2));
        output = MakeupOutputCode(init_output);
        output_vals.emplace_back(std::make_pair(&output, ""));

        input_field_width = 50.0f;

        InitializeInfos(input_vals, output_vals);
    }

    void ShaderGraphAddNode::UpdateOutputVal()
    {
        std::string v1 = CheckExistLinkedInput(input_infos[0]->unique_vn) ? input_infos[0]->unique_vn : (CastValueToString(&value1));
        std::string v2 = CheckExistLinkedInput(input_infos[1]->unique_vn) ? input_infos[1]->unique_vn : (CastValueToString(&value2));
        std::string output = v1 + " + " + v2;
        *output_infos[0]->val = MakeupOutputCode(output);
    }

    std::string ShaderGraphAddNode::MakeupOutputCode(std::string output_code)
    {
        std::cout << type_dictionary[ShaderPropertyType::kFloat] + " " + unique_vn + " = " + output_code << std::endl;
        return type_dictionary[ShaderPropertyType::kFloat] + " " + unique_vn + " = " + output_code;
    }

    ShaderGraphSubtractNode::ShaderGraphSubtractNode()
    {
        code_type = CodeType::kVariable;

        Initialize();
    }

    void ShaderGraphSubtractNode::Initialize()
    {
        std::vector<std::pair<std::any, std::string>> input_vals;
        input_vals.emplace_back(std::make_pair(&value1, "float1"));
        input_vals.emplace_back(std::make_pair(&value2, "float2"));

        std::vector<std::pair<std::string*, std::string>> output_vals;
        std::string init_output = (CastValueToString(&value1)) + " - " + (CastValueToString(&value2));
        output = MakeupOutputCode(init_output);
        output_vals.emplace_back(std::make_pair(&output, ""));

        input_field_width = 50.0f;

        InitializeInfos(input_vals, output_vals);
    }

    void ShaderGraphSubtractNode::UpdateOutputVal()
    {
        std::string v1 = CheckExistLinkedInput(input_infos[0]->unique_vn) ? input_infos[0]->unique_vn : (CastValueToString(&value1));
        std::string v2 = CheckExistLinkedInput(input_infos[1]->unique_vn) ? input_infos[1]->unique_vn : (CastValueToString(&value2));
        std::string output = v1 + " - " + v2;
        *output_infos[0]->val = MakeupOutputCode(output);
    }

    std::string ShaderGraphSubtractNode::MakeupOutputCode(std::string output_code)
    {
        std::cout << type_dictionary[ShaderPropertyType::kFloat] + " " + unique_vn + " = " + output_code << std::endl;
        return type_dictionary[ShaderPropertyType::kFloat] + " " + unique_vn + " = " + output_code;
    }

    ShaderGraphSeparateVector3Node::ShaderGraphSeparateVector3Node()
    {
        code_type = CodeType::kVariable;

        Initialize();
    }

    void ShaderGraphSeparateVector3Node::Initialize()
    {
        std::vector<std::pair<std::any, std::string>> input_vals;
        input_vals.emplace_back(std::make_pair(&value, "vec3"));

        std::vector<std::pair<std::string*, std::string>> output_vals;
        std::string init_output = utility::Split::SplitStr((utility::Split::SplitStr(CastValueToString(&value), ',')[0]), '(')[0];
        output = MakeupOutputCode(init_output);
        output_vals.emplace_back(std::make_pair(&output, ""));

        input_field_width = 50.0f;

        InitializeInfos(input_vals, output_vals);
    }

    void ShaderGraphSeparateVector3Node::UpdateOutputVal()
    {
        std::string output = CheckExistLinkedInput(input_infos[0]->unique_vn) ? input_infos[0]->unique_vn : utility::Split::SplitStr((utility::Split::SplitStr(CastValueToString(&value), ',')[0]), '(')[0];
        *output_infos[0]->val = MakeupOutputCode(output);
    }

    std::string ShaderGraphSeparateVector3Node::MakeupOutputCode(std::string output_code)
    {
        std::cout << type_dictionary[ShaderPropertyType::kFloat] + " " + unique_vn + " = " + output_code << std::endl;
        return type_dictionary[ShaderPropertyType::kFloat] + " " + unique_vn + " = " + output_code;
    }
}
