#include "RenderComponent.h"
namespace yougine::comoponents
{
    RenderComponent::RenderComponent() : Component(managers::ComponentName::kRender), program(0), vao(0), colorBuffer(0), depthBuffer(0), frameBuferr(0)
    {
    }

    void RenderComponent::SetProgram(GLuint program)
    {
        this->program = program;
    }

    void RenderComponent::SetVao(GLuint vao)
    {
        this->vao = vao;
    }

    void RenderComponent::SetColorBuffer(GLuint color_buffer)
    {
        colorBuffer = color_buffer;
    }

    void RenderComponent::SetDepthBuffer(GLuint depth_buffer)
    {
        depthBuffer = depth_buffer;
    }

    void RenderComponent::SetFrameBuferr(GLuint frame_buferr)
    {
        frameBuferr = frame_buferr;
    }

    GLuint RenderComponent::GetProgram() const
    {
        return program;
    }

    GLuint RenderComponent::GetVao() const
    {
        return vao;
    }

    GLuint RenderComponent::GetColorBuffer() const
    {
        return colorBuffer;
    }

    GLuint RenderComponent::GetDepthBuffer() const
    {
        return depthBuffer;
    }

    GLuint RenderComponent::GetFrameBuferr() const
    {
        return frameBuferr;
    }

    GLuint RenderComponent::GetIndexBuffer() const
    {
        return index_buffer;
    }

    void RenderComponent::SetIndexBuffer(GLuint index_buffer)
    {
        this->index_buffer = index_buffer;
    }
}
