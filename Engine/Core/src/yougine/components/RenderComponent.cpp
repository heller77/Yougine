#include "RenderComponent.h"
#include "./../managers/RenderManager.h"

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
        GLuint program, vao;
        program = yougine::managers::RenderManager::ShaderInitFromFilePath("./Resource/shader/test.vert", "./Resource/shader/test.frag");
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        this->SetProgram(program);
        this->SetVao(vao);

        //頂点バッファを作成
        GLuint vertexBuffer;
        glGenBuffers(1, &vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex),GetVertexVector().data(), GL_STATIC_DRAW);

        // //インデックスバッファ
        GLuint elementBuffer;
        glGenBuffers(1, &elementBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
        auto indices = GetIndexVector();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_STATIC_DRAW);

        //シェーダに値を渡す
        auto vertexShader_PositionAttribute = glGetAttribLocation(program, "position");

        glEnableVertexAttribArray(vertexShader_PositionAttribute);
        glVertexAttribPointer(vertexShader_PositionAttribute, 4, GL_FLOAT, GL_FALSE, 0, 0);
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
