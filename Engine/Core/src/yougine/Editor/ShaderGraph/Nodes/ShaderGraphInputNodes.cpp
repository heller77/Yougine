#include "ShaderGraphInputNodes.h"

namespace editor::shadergraph
{
    ShaderGraphVector3Node::ShaderGraphVector3Node()
    {
        std::vector<std::pair<std::string, std::string>> input_vals;
        input_vals.emplace_back(std::make_pair("1.0", "1.0"));
        input_vals.emplace_back(std::make_pair("0.0", "0.0"));
        input_vals.emplace_back(std::make_pair("0.0", "0.0"));

        std::vector<std::pair<std::string, std::string>> output_vals;
        std::string init_output_val = "vec3(" + input_vals[0].first + ", " + input_vals[1].first + ", " + input_vals[2].first + ")";
        output_vals.emplace_back(std::make_pair(init_output_val, init_output_val));

        Initialize(input_vals, output_vals);
    }

    void ShaderGraphVector3Node::UpdateOutputVal()
    {
        output_info[0].second.second = "vec3(" + input_info[0].second.second + ", " + input_info[1].second.second + ", " + input_info[2].second.second + ")";
    }


}
