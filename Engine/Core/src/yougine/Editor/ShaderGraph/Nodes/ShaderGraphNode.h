#pragma once
#include <any>

#include "../ShaderType.h"
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace editor::shadergraph
{
    /**
     * \brief type ... 型(文字列 ex/float型の場合 ... float
     * attr ... ノードの接続ID
     * is_linked ... 他ノードに接続しているか
     * init_val ... 初期値
     * val ... 現在値
     *
     */
    struct InputInfo
    {
        std::string type;
        std::string label;
        int attr;
        bool is_linked = false;
        std::any init_val;
        std::any val;
    };

    struct OutputInfo
    {
        std::string type;
        std::string label;
        int attr;
        bool is_linked;
        std::any init_val;
        std::any val;
    };

    class ShaderGraphNode
    {
    protected:
        std::map<ShaderPropertyType, std::string> type_dictionary = {
            {ShaderPropertyType::kBool, "bool"},
            {ShaderPropertyType::kInt, "int"},
            {ShaderPropertyType::kUint, "uint"},
            {ShaderPropertyType::kFloat, "float"},
            {ShaderPropertyType::kDouble, "double" },
            {ShaderPropertyType::kVec2, "vec2"},
            {ShaderPropertyType::kVec3, "vec3"},
            {ShaderPropertyType::kVec4, "vec4"},
            {ShaderPropertyType::kDvec2, "dvec2"},
            {ShaderPropertyType::kDvec3, "dvec3"},
            {ShaderPropertyType::kDvec4, "dvec4"},
            {ShaderPropertyType::kBvec2, "bvec2"},
            {ShaderPropertyType::kBvec3, "bvec3"},
            {ShaderPropertyType::kBvec4, "bvec4"},
            {ShaderPropertyType::kIvec2, "ivec2"},
            {ShaderPropertyType::kIvec3, "ivec3"},
            {ShaderPropertyType::kIvec4, "ivec4"},
            {ShaderPropertyType::kUvec2, "uvec2"},
            {ShaderPropertyType::kUvec3, "uvec3"},
            {ShaderPropertyType::kUvec4, "uvec4"},
            {ShaderPropertyType::kMat2, "mat2"},
            {ShaderPropertyType::kMat3, "mat3"},
            {ShaderPropertyType::kMat4, "mat4"},
            {ShaderPropertyType::kMat2x2, "mat2x2"},
            {ShaderPropertyType::kMat2x3, "mat2x3"},
            {ShaderPropertyType::kMat2x4, "mat2x4"},
            {ShaderPropertyType::kMat3x2, "mat3x2"},
            {ShaderPropertyType::kMat3x3, "mat3x3"},
            {ShaderPropertyType::kMat3x4, "mat3x4"},
            {ShaderPropertyType::kMat4x2, "mat4x2"},
            {ShaderPropertyType::kMat4x3, "mat4x3"},
            {ShaderPropertyType::kMat4x4, "mat4x4"},
            {ShaderPropertyType::kDmat2, "dmat2"},
            {ShaderPropertyType::kDmat3, "dmat3"},
            {ShaderPropertyType::kDmat4, "dmat4"},
            {ShaderPropertyType::kDmat2x2, "dmat2x2"},
            {ShaderPropertyType::kDmat2x3, "dmat2x3"},
            {ShaderPropertyType::kDmat2x4, "dmat2x4"},
            {ShaderPropertyType::kDmat3x2, "dmat3x2"},
            {ShaderPropertyType::kDmat3x3, "dmat3x3"},
            {ShaderPropertyType::kDmat3x4, "dmat3x4"},
            {ShaderPropertyType::kDmat4x2, "dmat4x2"},
            {ShaderPropertyType::kDmat4x3, "dmat4x3"},
            {ShaderPropertyType::kDmat4x4, "dmat4x4"},
            {ShaderPropertyType::kSampler1D, "sampler1"},
            {ShaderPropertyType::kImage1D, "image1D"},
            {ShaderPropertyType::kSampler2D, "sampler2D"},
            {ShaderPropertyType::kImage2D, "image2D"},
            {ShaderPropertyType::kSampler3D, "sampler3D"},
            {ShaderPropertyType::kImage3D, "image3D"},
        };
        std::map<ShaderQualifier, std::string> qualifier_dictionary = {
            {ShaderQualifier::kConst, "const"},
            {ShaderQualifier::kIn, "in"},
            {ShaderQualifier::kOut, "out"},
            {ShaderQualifier::kAttribute, "attribute"},
            {ShaderQualifier::kUniform, "uniform" },
            {ShaderQualifier::kVarying, "varying" },
            {ShaderQualifier::kBuffer, "buffer"},
            {ShaderQualifier::kShared, "shared"},
        };

        std::vector < std::any > init_input_vals;
        std::vector < std::any > init_output_vals;
        ShaderGraphNode* parent_nodes = nullptr; //単体でええんか？

    public:
        int id;
        std::vector<std::shared_ptr<InputInfo>> input_infos;
        std::vector<std::shared_ptr<OutputInfo>> output_infos;
        std::string name;

    protected:
        void Initialize(std::vector<std::any> init_input_vals, std::vector<std::any> init_output_vals);
        void SetInputVal(std::any value, int input_index);
        std::any GetOutputVal(int output_index);
        void DisplayValues();
        virtual void UpdateOutputVal();
        int FindLinkedInputIndex(int input_attr);
        int FindLinkedOutputIndex(int output_attr);
        void ResetInputVal(int input_index);
        void ResetOutputVal(int output_index);
        void CastValueToString(std::any val);

    public:
        ShaderGraphNode();
        void SetParentNode(ShaderGraphNode* parent_node, std::pair<int, int> attr_pair);
        bool UpdateParentNodeValue(std::pair<int, int> attr_pair);
        ShaderGraphNode* GetParentNode();
        std::vector<std::any> GetInitInputVals();
        std::vector<std::any> GetInitOutputVals();
        void DisLinkNode(std::pair<int, int> attr_pair);
    };
}
