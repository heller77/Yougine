#pragma once
#include "ShaderGraphNode.h"

namespace editor::shadergraph
{
    class ShaderGraphVector3Node : public ShaderGraphNode
    {
    protected:
        void UpdateOutputVal() override;

    public:
        ShaderGraphVector3Node();
    };
}
