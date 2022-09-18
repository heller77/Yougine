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

        void SetColorBuffer(GLuint color_buffer);

        void SetDepthBuffer(GLuint depth_buffer);

        void SetFrameBuferr(GLuint frame_buferr);
        void SetIndexBuffer(GLuint index_buffer);

        [[nodiscard]] GLuint GetProgram() const;

        [[nodiscard]] GLuint GetVao() const;

        [[nodiscard]] GLuint GetColorBuffer() const;

        [[nodiscard]] GLuint GetDepthBuffer() const;

        [[nodiscard]] GLuint GetFrameBuferr() const;
        [[nodiscard]] GLuint GetIndexBuffer() const;

    private:
        GLuint program;
        GLuint vao;
        GLuint colorBuffer;
        GLuint depthBuffer;
        GLuint frameBuferr;
        GLuint index_buffer;
    };
}