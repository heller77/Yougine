#pragma once
#include  "ShaderGraphNode.h"

namespace editor::shadergraph
{
    class ShaderGraphAddNode : public  ShaderGraphNode
    {
    private:
        float value1 = 0.0;
        float value2 = 0.0;
        std::string output = "";

    protected:
        void UpdateOutputVal() override;
        std::string MakeupOutputCode(std::string output_code) override;

    public:
        ShaderGraphAddNode();
        void Initialize() override;
    };

    class ShaderGraphSubtractNode : public  ShaderGraphNode
    {
    private:
        float value1 = 0.0;
        float value2 = 0.0;
        std::string output = "";

    protected:
        void UpdateOutputVal() override;
        std::string MakeupOutputCode(std::string output_code) override;

    public:
        ShaderGraphSubtractNode();
        void Initialize() override;
    };

    class ShaderGraphSeparateVector3Node : public  ShaderGraphNode
    {
    private:
        std::string value = "vec3(0, 0, 0)";
        std::string output = "vec3(0, 0, 0)";

    protected:
        void UpdateOutputVal() override;
        std::string MakeupOutputCode(std::string output_code) override;

    public:
        ShaderGraphSeparateVector3Node();
        void Initialize() override;
    };
}