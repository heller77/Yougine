#include "ShaderGraphInputNodes.h"

namespace editor::shadergraph
{
    ShaderGraphVector3Node::ShaderGraphVector3Node()
    {
        std::vector<std::any> input_vals;
        input_vals.emplace_back(0.0);
        input_vals.emplace_back(0.0);
        input_vals.emplace_back(0.0);

        std::vector<std::any> output_vals;
        std::string init_output_val = "vec3(" + input_vals[0] + ", " + input_vals[1] + ", " + input_vals[2] + ")";
        output_vals.emplace_back(std::make_pair(init_output_val, init_output_val));

        Initialize(input_vals, output_vals);
    }

    void ShaderGraphVector3Node::UpdateOutputVal()
    {
        output_infos[0]->val = "vec3(" + input_infos[0]->val + ", " + input_infos[1]->val + ", " + input_infos[2]->val + ")";
    }


}
