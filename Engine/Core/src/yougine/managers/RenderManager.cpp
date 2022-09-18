#include "RenderManager.h"

#include <fstream>
#include <iostream>
#include <vector>
#include "./../GameObject.h"

#include "../components/TransformComponent.h"

#include "glm/glm.hpp"
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
namespace yougine
{
    namespace components
    {
        class TransformComponent;
    }
}
namespace yougine::managers
{
    struct Vertex
    {
        GLfloat position[4];
    };

    RenderManager::RenderManager(int width, int height, ComponentList* component_list)
    {
        this->renderComponent = new comoponents::RenderComponent();
        GLenum err;
        this->width = width;
        this->height = height;
        //カラーバッファ
        GLuint colorBuffer;
        glGenTextures(1, &colorBuffer);
        glBindTexture(GL_TEXTURE_2D, colorBuffer);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // this->renderComponent->SetColorBuffer(colorBuffer);
        this->colorBuffer = colorBuffer;

        //デプスバッファ
        GLuint depthBuffer;
        glGenRenderbuffers(1, &depthBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
        // this->renderComponent->SetDepthBuffer(depthBuffer);
        this->depthBuffer = depthBuffer;

        //フレームバッファ
        GLuint frameBuffer;
        glGenFramebuffers(1, &frameBuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
            this->colorBuffer, 0);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER,
            this->depthBuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        this->frameBuffer=frameBuffer;

        while ((err = glGetError()) != GL_NO_ERROR)
        {
            std::cout << err << " というエラーがある in constructer" << std::endl;
        }
    }

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
        glBindFramebuffer(GL_FRAMEBUFFER, this->frameBuffer);
        glViewport(0, 0, this->width, this->height);
        constexpr GLfloat color[]{ 0.0f, 0.3f, 0.5f, 0.8f }, depth(1.0f);
        glClearBufferfv(GL_COLOR, 0, color);
        glClearBufferfv(GL_DEPTH, 0, &depth);

        //オブジェクトそれぞれ描画
        RenderOneGameObject(renderComponent);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        GLenum err;
        while ((err = glGetError()) != GL_NO_ERROR)
        {
            std::cout << err << " というエラーがある in renderscene" << std::endl;
        }
    }
    float cValue = 0;
    float diff = 0.01f;
    float cameradiff = 0.01f;
    float camerax = 1;
    void SetFloatUniform(GLint program, const char* name, float value)
    {
        GLuint loc = glGetUniformLocation(program, name);
        // Send the float data
        glUniform1f(loc, value);
        GLuint err;
        while ((err = glGetError()) != GL_NO_ERROR)
        {
            std::cout << err << " というエラーがある in setfloatuniform" << std::endl;
        }
    }
    /**
     * \brief ゲームオブジェクトを描画する
     * \param render_component 描画対象のレンダーコンポーネント
     */
    void RenderManager::RenderOneGameObject(comoponents::RenderComponent* render_component)
    {
        // GameObject* gameobject = render_component->GetGameObject();
        // components::TransformComponent* transform;
        // transform = gameobject->GetComponent<components::TransformComponent>();
        glUseProgram(this->renderComponent->GetProgram());
        glBindVertexArray(this->renderComponent->GetVao());
        // 射影行列：45&deg;の視界、アスペクト比4:3、表示範囲：0.1単位  100単位
        glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 400.0f);
        // カメラ行列
        camerax += cameradiff * 1.3;
        if (camerax > 3 || camerax < -3)
        {
            cameradiff *= -1;
        }
        glm::mat4 View = glm::lookAt(
            glm::vec3(0, 0, 2), // ワールド空間でカメラは(4,3,3)にあります。
            glm::vec3(0, 0, 0), // 原点を見ています。
            glm::vec3(0, 1, 0)  // 頭が上方向(0,-1,0にセットすると上下逆転します。)
        );
        // モデル行列：単位行列(モデルは原点にあります。)
        glm::mat4 Model = glm::mat4(1.0f);  // 各モデルを変える！
        // Our ModelViewProjection : multiplication of our 3 matrices
        glm::mat4 MVP = Projection * View * Model; // 行列の掛け算は逆になることを思い出してください。
        auto vShader_mvp_pointer = glGetUniformLocation(this->renderComponent->GetProgram(), "mvp");
        glUniformMatrix4fv(vShader_mvp_pointer, 1, GL_FALSE, &MVP[0][0]);
        GLenum err;
        while ((err = glGetError()) != GL_NO_ERROR)
        {
            std::cout << err << " というエラーがある in rendergameobject" << std::endl;
        }

        SetFloatUniform(renderComponent->GetProgram(), "c", cValue);

        cValue += diff;
        if(cValue>1.0f&&diff>0)
        {
            cValue *= -1;
        }
        // glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    GLuint RenderManager::ShaderInit(std::string vs_shader_source, std::string fs_shader_source)
    {
        const auto program = glCreateProgram();

        //シェーダオブジェクト生成
        const auto vsShader = glCreateShader(GL_VERTEX_SHADER);
        const auto fsShader = glCreateShader(GL_FRAGMENT_SHADER);

        //シェーダコードをオブジェクトに渡す
        const char* vsShaderSource_char = vs_shader_source.c_str();
        std::cout << "vertex \n" << vs_shader_source << std::endl;
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

    GLuint RenderManager::ShaderInitFromFilePath(const std::string vsFilePath, const std::string fsFilePath)
    {
        return ShaderInit(ReadFile(vsFilePath), ReadFile(fsFilePath));
        // return 0;
    }

    GLuint RenderManager::GetColorBuffer()
    {
        return this->colorBuffer;
    }

    void RenderManager::SetWindowSize(ImVec2 vec2)
    {
        this->width = vec2.x;
        this->height = vec2.y;
    }

    void RenderManager::MeshBufferInit()
    {
    }

    GLboolean RenderManager::PrintShaderInfoLog(GLuint shader, const char* str)
    {
        std::cout << "compile log " << std::endl;
        GLint status;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
        if (status == GL_FALSE)
        {
            std::cerr << "Compile error in " << str << std::endl;
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
        std::cout << "file read .. " << std::endl;
        if (!reading_file)
        {
            std::cerr << "Could not read file " << filepath << ". File does not exist." << std::endl;
            return "";
        }
        std::string line = "";
        std::string a;
        while (std::getline(reading_file, a))
        {
            std::cout << "file reading now" << std::endl;
            content.append(a + "\n");
        }
        /*while (reading_file.eof())
        {
            std::cout << "file reading now" << std::endl;
            std::getline(reading_file, line);
            content.append(line + "\n");
        }*/
        reading_file.close();
        std::cout << "file contens is \n" << content << std::endl;

        return content;
    }
}
