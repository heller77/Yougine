#pragma once
#include "MainShaderGraphNode.h"

namespace editor::shadergraph
{
    class UnlitShaderGraphNode : public MainShaderGraphNode
    {
    private:
        std::string albedo = "vec3(0.0, 0.0, 0.0)";

        std::string color; //output

    public:
        UnlitShaderGraphNode();
        void UpdateOutputVal() override;
    };
}
