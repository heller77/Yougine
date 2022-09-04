#include "RenderManager.h"

#include <fstream>
#include <iostream>
#include <vector>
#include "./../GameObject.h"

#include "../components/TransformComponent.h"

namespace yougine
{
    namespace components
    {
        class TransformComponent;
    }
}
namespace yougine::managers
{

    /**
     * \brief 初期化
     */
    void RenderManager::Initialize()
    {
    }

    /**
     * \brief レンダリング
     */
    void RenderManager::RenderScene()
    {
        glClearColor(1, 1, 1, 0);
        glClear(GL_COLOR_BUFFER_BIT);

        //オブジェクトそれぞれ描画
    }

    struct Vertex
    {
        GLfloat position[4];
    };

    /**
     * \brief ゲームオブジェクトを描画する
     * \param render_component 描画対象のレンダーコンポーネント
     */
    void RenderManager::RenderOneGameObject(comoponents::RenderComponent render_component)
    {
        Vertex vertex[] = {
            {-0.5, -0.5, 0.0, 1},
            {0.5, -0.5, 0.0, 1},
            {-0.5, 0.5, 0.0, 1},
        };

        auto program = ShaderInit("", "");
        GLuint vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        //頂点バッファを作成
        GLuint vertexBuffer;
        glGenBuffers(1, &vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex), vertex, GL_STATIC_DRAW);

        //シェーダに値を渡す
        auto vertexShader_PositionAttribute = glGetAttribLocation(program, "position");
        glEnableVertexAttribArray(vertexShader_PositionAttribute);
        glVertexAttribPointer(vertexShader_PositionAttribute, 4, GL_FLAT, GL_FALSE, 0, 0);

        GameObject* gameobject = render_component.GetGameObject();
        components::TransformComponent* transform;
        transform = gameobject->GetComponent<components::TransformComponent>();
    }

    GLuint RenderManager::ShaderInit(const std::string& vs_shader_source, const std::string& fs_shader_source)
    {
        const auto program = glCreateProgram();

        //シェーダオブジェクト生成
        const auto vsShader = glCreateShader(GL_VERTEX_SHADER);
        const auto fsShader = glCreateShader(GL_FRAGMENT_SHADER);

        //シェーダコードをオブジェクトに渡す
        const char* vsShaderSource_char = vs_shader_source.c_str();
        glShaderSource(vsShader, 1, &vsShaderSource_char, nullptr);
        const char* fsShaderSource_char = fs_shader_source.c_str();
        glShaderSource(fsShader, 1, &fsShaderSource_char, nullptr);

        //コンパイル
        glCompileShader(vsShader);
        glCompileShader(fsShader);

        //エラー
        PrintShaderInfoLog(vsShader, "vertex shader");
        PrintShaderInfoLog(fsShader, "fragment shader");


        //programにアタッチ
        glAttachShader(program, vsShader);
        glDeleteShader(vsShader);
        glAttachShader(program, fsShader);
        glDeleteShader(fsShader);

        glLinkProgram(program);

        return program;
    }

    void RenderManager::MeshBufferInit()
    {
    }

    GLboolean RenderManager::PrintShaderInfoLog(GLuint shader, const char* str)
    {
        GLint status;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
        if (status == GL_FALSE)
        {
            std::cerr << "Compile error in" << str << std::endl;
        }

        GLsizei bufferSize;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &bufferSize);

        if (bufferSize > 1)
        {
            std::vector<GLchar> infoLog(bufferSize);
            GLsizei length;
            glGetShaderInfoLog(shader, bufferSize, &length, &infoLog[0]);
            std::cerr << &infoLog[0] << std::endl;
            return false;
        }
        return true;
    }

    std::string RenderManager::ReadFile(std::string filepath)
    {
        std::string content;
        std::ifstream reading_file(filepath, std::ios::in);
        if (!reading_file.is_open())
        {
            std::cerr << "Could not read file " << filepath << ". File does not exist." << std::endl;
            return "";
        }
        std::string line = "";
        while (reading_file.eof())
        {
            std::getline(reading_file, line);
            content.append(line + "\n");
        }
        reading_file.close();

        return content;
    }
}
