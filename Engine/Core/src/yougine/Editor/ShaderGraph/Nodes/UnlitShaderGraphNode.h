#pragma once
#include "MainShaderGraphNode.h"

namespace editor::shadergraph
{
    class UnlitShaderGraphNode : public MainShaderGraphNode
    {
    public:
        UnlitShaderGraphNode();
        void UpdateOutputVal() override;
    };
}
