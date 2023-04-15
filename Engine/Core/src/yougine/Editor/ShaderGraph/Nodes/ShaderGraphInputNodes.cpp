#include "ShaderGraphInputNodes.h"

#include <iostream>

namespace editor::shadergraph
{
    ShaderGraphFloatNode::ShaderGraphFloatNode()
    {
        code_type = CodeType::kVariable;

        Initialize();
    }

    void ShaderGraphFloatNode::Initialize()
    {
        std::vector<std::pair<std::any, std::string>> input_vals;
        input_vals.emplace_back(std::make_pair(&value, "float"));

        std::vector<std::pair<std::string*, std::string>> output_vals;
        std::string init_output = (CastValueToString(&value));
        output = MakeupOutputCode(init_output);
        output_vals.emplace_back(std::make_pair(&output, ""));

        input_field_width = 50.0f;

        InitializeInfos(input_vals, output_vals);
    }


    void ShaderGraphFloatNode::UpdateOutputVal()
    {
        std::string output = CheckExistLinkedInput(input_infos[0]->unique_vn) ? input_infos[0]->unique_vn : CastValueToString(&(this->value));
        *output_infos[0]->val = MakeupOutputCode(output);
    }

    std::string ShaderGraphFloatNode::MakeupOutputCode(std::string output_code)
    {
        return type_dictionary[ShaderPropertyType::kFloat] + " " + unique_vn + " = " + output_code;
    }


    ShaderGraphVector3Node::ShaderGraphVector3Node()
    {
        code_type = CodeType::kVariable;

        Initialize();
    }

    void ShaderGraphVector3Node::Initialize()
    {
        std::vector<std::pair<std::any, std::string>> input_vals;

        input_vals.emplace_back(std::make_pair(&x, "x"));
        input_vals.emplace_back(std::make_pair(&y, "y"));
        input_vals.emplace_back(std::make_pair(&z, "z"));

        utility::Vector3* init_vec3 = new utility::Vector3(x, y, z);

        std::vector<std::pair<std::string*, std::string>> output_vals;
        std::string init_output = (CastValueToString(init_vec3));
        output = MakeupOutputCode(init_output);
        output_vals.emplace_back(std::make_pair(&output, ""));

        input_field_width = 50.0f;

        InitializeInfos(input_vals, output_vals);

    }


    void ShaderGraphVector3Node::UpdateOutputVal()
    {
        std::string x = CheckExistLinkedInput(input_infos[0]->unique_vn) ? input_infos[0]->unique_vn : CastValueToString(&(this->x));
        std::string y = CheckExistLinkedInput(input_infos[1]->unique_vn) ? input_infos[1]->unique_vn : CastValueToString(&(this->y));
        std::string z = CheckExistLinkedInput(input_infos[2]->unique_vn) ? input_infos[2]->unique_vn : CastValueToString(&(this->z));
        *output_infos[0]->val = MakeupOutputCode("vec3(" + x + ", " + y + ", " + z + ")");
    }

    std::string ShaderGraphVector3Node::MakeupOutputCode(std::string output_code)
    {
        return type_dictionary[ShaderPropertyType::kVec3] + " " + unique_vn + " = " + output_code;
    }

}
