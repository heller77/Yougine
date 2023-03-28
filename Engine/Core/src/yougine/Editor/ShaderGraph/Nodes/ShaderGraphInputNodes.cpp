#include "ShaderGraphInputNodes.h"

#include <iostream>

namespace editor::shadergraph
{
    ShaderGraphFloatNode::ShaderGraphFloatNode()
    {
        std::vector<std::pair<std::any, std::string>> input_vals;
        input_vals.emplace_back(std::make_pair(&value, "float"));

        std::vector<std::pair<std::any, std::string>> output_vals;
        output_vals.emplace_back(std::make_pair(&value, ""));

        Initialize(input_vals, output_vals);
    }

    void ShaderGraphFloatNode::UpdateOutputVal()
    {

    }


    ShaderGraphVector3Node::ShaderGraphVector3Node()
    {
        std::vector<std::pair<std::any, std::string>> input_vals;

        input_vals.emplace_back(std::make_pair(&x, "x"));
        input_vals.emplace_back(std::make_pair(&y, "y"));
        input_vals.emplace_back(std::make_pair(&z, "z"));

        utility::Vector3* init_vec3 = new utility::Vector3(x, y, z);

        std::vector<std::pair<std::any, std::string>> output_vals;

        output = CastValueToString(init_vec3);

        output_vals.emplace_back(std::make_pair(&output, ""));

        Initialize(input_vals, output_vals);
    }

    void ShaderGraphVector3Node::UpdateOutputVal()
    {
        float x = *std::any_cast<float*> (input_infos[0]->val);
        float y = *std::any_cast<float*> (input_infos[1]->val);
        float z = *std::any_cast<float*> (input_infos[2]->val);
        output_infos[0]->val = "vec3(" + CastValueToString(&x) + ", " + CastValueToString(&y) + ", " + CastValueToString(&z) + ")";
        std::cout << "UpdateOutputVal : " + CastValueToString(output_infos[0]->val) << std::endl;
    }
}
