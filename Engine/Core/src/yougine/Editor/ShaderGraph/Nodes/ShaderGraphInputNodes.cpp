#include "ShaderGraphInputNodes.h"

#include <iostream>

namespace editor::shadergraph
{
    ShaderGraphFloatNode::ShaderGraphFloatNode()
    {
        code_type = CodeType::kVariable;

        std::vector<std::pair<std::any, std::string>> input_vals;
        input_vals.emplace_back(std::make_pair(&value, "float"));

        std::vector<std::pair<std::string*, std::string>> output_vals;
        std::string init_output = (CastValueToString(&value));
        output = init_output;
        output_vals.emplace_back(std::make_pair(&output, ""));

        input_field_width = 50.0f;

        Initialize(input_vals, output_vals);
    }

    void ShaderGraphFloatNode::UpdateOutputVal()
    {
        *output_infos[0]->val = MakeupOutputCode(CastValueToString(input_infos[0]->val));
    }

    std::string ShaderGraphFloatNode::MakeupOutputCode(std::string output_code)
    {
        return type_dictionary[ShaderPropertyType::kFloat] + " unique_name" + " = " + output_code;
    }


    ShaderGraphVector3Node::ShaderGraphVector3Node()
    {
        code_type = CodeType::kVariable;

        std::vector<std::pair<std::any, std::string>> input_vals;

        input_vals.emplace_back(std::make_pair(&x, "x"));
        input_vals.emplace_back(std::make_pair(&y, "y"));
        input_vals.emplace_back(std::make_pair(&z, "z"));

        utility::Vector3* init_vec3 = new utility::Vector3(x, y, z);

        std::vector<std::pair<std::string*, std::string>> output_vals;
        std::string init_output = (CastValueToString(init_vec3));
        output = init_output;
        output_vals.emplace_back(std::make_pair(&output, ""));

        input_field_width = 50.0f;

        Initialize(input_vals, output_vals);
    }

    void ShaderGraphVector3Node::UpdateOutputVal()
    {
        *output_infos[0]->val = MakeupOutputCode("vec3(" + CastValueToString(input_infos[0]->val) + ", " + CastValueToString(input_infos[1]->val) + ", " + CastValueToString(input_infos[2]->val) + ")");
    }

    std::string ShaderGraphVector3Node::MakeupOutputCode(std::string output_code)
    {
        return type_dictionary[ShaderPropertyType::kVec3] + " unique_name" + " = " + output_code;
    }

}
