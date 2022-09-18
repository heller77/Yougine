#include "RenderComponent.h"

namespace yougine::comoponents
{
    RenderComponent::RenderComponent() : Component(managers::ComponentName::kRender), program(0), vao(0)
    {
        this->vertex_vector =  {
            {0.5, 0.5, 0.0, 1},
            {0.5, -0.5, 0.0, 1},
            {-0.5, -0.5, 0.0, 1},
            {-0.5, 0.5, 0.0, 1},
        };
        this->index_vector= {
            // note that we start from 0!
            0, 1, 3, // first triangle
            1, 2, 3 // second triangle
        };
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

    std::vector<Vertex> RenderComponent::GetVertexVector() const
    {
        return vertex_vector;
    }

    void RenderComponent::SetVertexVector(const std::vector<Vertex>& vertex_vector)
    {
        this->vertex_vector = vertex_vector;
    }

    std::vector<GLuint> RenderComponent::GetIndexVector() const
    {
        return index_vector;
    }

    void RenderComponent::SetIndexVector(const std::vector<GLuint>& index_vector)
    {
        this->index_vector = index_vector;
    }
}
