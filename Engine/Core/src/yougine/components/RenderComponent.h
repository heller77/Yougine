#pragma once
#include "Component.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace yougine::comoponents
{
    struct Vertex
    {
        GLfloat position[4];
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

        [[nodiscard]] std::vector<Vertex> GetVertexVector() const;

        void SetVertexVector(const std::vector<Vertex>& vertex_vector);

        [[nodiscard]] std::vector<GLuint> GetIndexVector() const;

        void SetIndexVector(const std::vector<GLuint>& index_vector);

    private:
        GLuint program;

        GLuint vao;

        std::vector<Vertex> vertex_vector;

        std::vector<GLuint> index_vector;
    };
}
