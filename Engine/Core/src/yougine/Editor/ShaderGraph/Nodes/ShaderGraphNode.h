#pragma once
#include <any>

#include "../ShaderType.h"
#include <map>
#include <memory>
#include <string>
#include <vector>
#include "UserShare/utilitys/YougineMath.h"
#include "../../../utilitys/Quaternion.h"
#include "UserShare/utilitys/Split.h"
#include <any>

namespace editor::shadergraph
{
    class ShaderGraphNode;

#define GET_VALUE_NAME(VariableName) VariableName

    /**
     * \brief
     * label ... InputFieldに表示される変数名
     * attr ... ノードの接続ID
     * is_linked ... 他ノードに接続しているか
     * init_val ... 初期値
     * val ... 現在値
     */
    struct InputInfo
    {
        std::string label;
        int attr;
        bool is_linked = false;
        std::any init_val;
        std::any val;
        std::string unique_vn = "";
        float field_width = 0;
        int linked_output_attr;
        ShaderGraphNode* child_node;
    };

    struct OutputInfo
    {
        std::string label;
        int attr;
        bool is_linked;
        std::string* init_val;
        std::string* val;
        std::string unique_vn = "";
        int linked_input_attr;
        int stack_index = 0;
    };

    enum class CodeType
    {
        kVariable,
        kFunction,
        kMain,
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

        std::map<ShaderUniqueValue, std::string> unique_type_dictionary = {
            {ShaderUniqueValue::kTrue, "true"},
            {ShaderUniqueValue::kFalse, "false"},
        };

        ShaderGraphNode* parent_nodes = nullptr; //単体でええんか？
        std::vector<std::shared_ptr<InputInfo>> input_infos;
        std::vector<std::shared_ptr<OutputInfo>> output_infos;
        float input_field_width = 0;
        CodeType code_type;
        std::string unique_vn;

    public:
        int id;
        std::string name;

    protected:
        void InitializeInfos(std::vector<std::pair<std::any, std::string>> init_input_vals, std::vector<std::pair<std::string*, std::string>> init_output_vals);
        void SetInputVal(std::any value, std::string unique_vn, int input_index);
        std::any GetOutputVal(int output_index);
        std::string GetOutputUniqueVN(int output_index);
        void DisplayValues();
        int FindLinkedInputIndex(int input_attr);
        int FindLinkedOutputIndex(int output_attr);
        void ResetInputVal(int input_index);
        void InitInputInfoLinkedOutputAttr(int index);
        virtual std::string MakeupOutputCode(std::string output_code);
        bool CheckExistLinkedInput(std::string vn);

    public:
        virtual void Initialize();
        ShaderGraphNode();
        void SetParentNode(ShaderGraphNode* parent_node, std::pair<int, int> attr_pair);
        bool UpdateParentNodeValue(std::pair<int, int> attr_pair);
        ShaderGraphNode* GetParentNode();
        std::vector<std::shared_ptr<InputInfo>> GetInputInfos();
        std::vector<std::shared_ptr<OutputInfo>> GetOutputInfos();
        void DisLinkNode(std::pair<int, int> attr_pair);
        std::string CastValueToString(std::any val);
        virtual void SetInputInfoAttr(int index, int attr);
        virtual void SetOutputInfoAttr(int index, int attr);
        float GetInputFieldWidth();
        virtual void UpdateOutputVal();
        void InitOutputInfoLinkedInputAttr();
        CodeType GetCodeType();
        void SetChildNode(std::shared_ptr<InputInfo> input_info, ShaderGraphNode* child_node);
        ShaderGraphNode* GetChildNode(std::shared_ptr<InputInfo> input_info);
        void SetVN(int vn_n);
        void SetID(int id);
    };
}
