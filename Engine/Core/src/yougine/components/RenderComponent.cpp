#include "RenderComponent.h"

namespace yougine::comoponents
{
    RenderComponent::RenderComponent() : Component(managers::ComponentName::kRender), program(0), vao(0)
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

    GLuint RenderComponent::GetProgram() const
    {
        return program;
    }

    GLuint RenderComponent::GetVao() const
    {
        return vao;
    }
}
