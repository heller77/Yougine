#pragma once
#include "ShaderGraphNode.h"

namespace editor::shadergraph
{
    class ShaderGraphVector3Node : public ShaderGraphNode
    {
    private:
        float x = 0.0;
        float y = 0.0;
        float z = 0.0;
        std::string output;

    protected:
        void UpdateOutputVal() override;

    public:
        ShaderGraphVector3Node();
    };
}
