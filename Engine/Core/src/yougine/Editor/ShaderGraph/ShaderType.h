#pragma once

namespace editor::shadergraph
{
    enum class ShaderPropertyType
    {
        kVoid,
        kBool,
        kInt,
        kUint,
        kFloat,
        kDouble,
        kVec2,
        kVec3,
        kVec4,
        kDvec2,
        kDvec3,
        kDvec4,
        kBvec2,
        kBvec3,
        kBvec4,
        kIvec2,
        kIvec3,
        kIvec4,
        kUvec2,
        kUvec3,
        kUvec4,
        kMat2,
        kMat3,
        kMat4,
        kMat2x2,
        kMat2x3,
        kMat2x4,
        kMat3x2,
        kMat3x3,
        kMat3x4,
        kMat4x2,
        kMat4x3,
        kMat4x4,
        kDmat2,
        kDmat3,
        kDmat4,
        kDmat2x2,
        kDmat2x3,
        kDmat2x4,
        kDmat3x2,
        kDmat3x3,
        kDmat3x4,
        kDmat4x2,
        kDmat4x3,
        kDmat4x4,
        kSampler1D,
        kImage1D,
        kSampler2D,
        kImage2D,
        kSampler3D,
        kImage3D,

    };

    enum class ShaderQualifier
    {
        kConst,
        kIn,
        kOut,
        kAttribute,
        kUniform,
        kVarying,
        kBuffer,
        kShared,
    };

    enum class ShaderVersion
    {
        k430,
    };

    enum class ShaderStage
    {
        kFragment,
        kVertex,
    };
}
