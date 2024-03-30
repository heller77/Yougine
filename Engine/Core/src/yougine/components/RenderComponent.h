#pragma once
#include "UserShare/components/Component.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../Editor/ProjectWindows/Assets/element/Model/Material/Material.h"

namespace yougine::components
{
    struct ShaderVector4
    {
        GLfloat position[4];
    };
    struct ShaderVector3
    {
        GLfloat position[3];
    };

    struct VBOList
    {
        GLuint vertexBuffer;
        GLuint elementBuffer;
        GLuint normalBuffer;
        void Release()
        {
            GLuint vboIDs[] = { vertexBuffer, elementBuffer, normalBuffer };
            glDeleteBuffers(3, vboIDs);
            vertexBuffer = -1;
            elementBuffer = -1;
            normalBuffer = -1;

        }
    };
    class RenderComponent : public components::Component
    {
        //マテリアル（シェーダー、シェーダに渡す値）、メッシュ。
    public:
        RenderComponent();

        void SetProgram(GLuint program);

        void SetVao(GLuint vao);

        void SetIndexBuffer(GLuint index_buffer);

        [[nodiscard]] GLuint GetProgram() const;

        [[nodiscard]] GLuint GetVao() const;

        [[nodiscard]] std::vector<ShaderVector4> GetVertexVector() const;

        void SetVertexVector(const std::vector<ShaderVector4>& vertex_vector);

        [[nodiscard]] std::vector<GLuint> GetIndexVector() const;

        void SetIndexVector(const std::vector<GLuint>& index_vector);

        std::shared_ptr<editor::projectwindows::assets::elements::model::materials::Material> GetMaterial();

        /**
         * \brief ドローコール時に頂点を何個あると伝えるか。頂点座標の数というよりインデックスの数が入ると思われる
         */
        int draw_point_count;

    private:

        std::shared_ptr<editor::projectwindows::assets::elements::model::materials::Material> material;
        GLuint program;

        GLuint vao;
        VBOList vbolist;

        std::vector<ShaderVector4> vertex_vector;

        std::vector<GLuint> index_vector;
        void ShaderCompile();
        void InitializeMesh();

    };
}
