#pragma once
#include "ShaderGraphNode.h"

namespace editor::shadergraph
{
    class ShaderGraphFloatNode : public ShaderGraphNode
    {
    private:
        float value = 1.0; //値(ポインタ)
        std::string output = ""; //変数名を含んだ値(変数)

    protected:
        void UpdateOutputVal() override;
        std::string MakeupOutputCode(std::string output_code) override;

    public:
        ShaderGraphFloatNode();
        void Initialize() override;
    };

    class ShaderGraphVector3Node : public ShaderGraphNode
    {
    private:
        float x = 1.0;
        float y = 1.0;
        float z = 1.0;
        std::string output = "";

    protected:
        void UpdateOutputVal() override;
        std::string MakeupOutputCode(std::string output_code) override;

    public:
        ShaderGraphVector3Node();
        void Initialize() override;
    };
}
