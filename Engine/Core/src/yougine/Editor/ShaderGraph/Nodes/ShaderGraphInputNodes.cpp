#include "ShaderGraphInputNodes.h"

namespace editor::shadergraph
{
    ShaderGraphVector3Node::ShaderGraphVector3Node()
    {
        std::vector<std::pair<std::string, std::string>> input_vals;
        input_vals.emplace_back(std::make_pair("0.0", "0.0"));
        input_vals.emplace_back(std::make_pair("0.0", "0.0"));
        input_vals.emplace_back(std::make_pair("0.0", "0.0"));

        std::vector<std::pair<std::string, std::string>> output_vals;
        output_vals.emplace_back(std::make_pair("vec3(0.0, 0.0, 0.0)", "vec3(0.0, 0.0, 0.0)"));
    }

    void ShaderGraphVector3Node::UpdateOutputVal()
    {
        output_info[0].second.second = "vec3(" + input_info[0].second.second + ", " + input_info[1].second.second + ", " + input_info[2].second.second + ")";
    }


}
