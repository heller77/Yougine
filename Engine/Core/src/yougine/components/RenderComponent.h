#pragma once
#include "Component.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace yougine::comoponents
{
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

    private:
        GLuint program;

        GLuint vao;
    };
}
