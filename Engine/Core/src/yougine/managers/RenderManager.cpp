#include "RenderManager.h"

#include <fstream>
#include <iostream>
#include <vector>
#include "UserShare/GameObject.h"

#include "UserShare/components/TransformComponent.h"

#include "glm/glm.hpp"
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Projects/Project.h"
#include "UserShare/utilitys/Quaternion.h"

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
        this->component_list = component_list;
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
        this->colorBuffer = colorBuffer;
        geterror("in rendermanager constructer");

        //デプスバッファ
        GLuint depthBuffer;
        glGenRenderbuffers(1, &depthBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
        this->depthBuffer = depthBuffer;
        geterror("in rendermanager constructer");

        //フレームバッファ
        GLuint frameBuffer;
        glGenFramebuffers(1, &frameBuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
            this->colorBuffer, 0);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER,
            this->depthBuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        this->frameBuffer = frameBuffer;

        geterror("in rendermanager constructer");
    }

    RenderManager::RenderManager(int width, int height, GLint input_framebuffer, ComponentList* component_list)
    {
        this->component_list = component_list;
        this->width = width;
        this->height = height;
        geterror("in rendermanager constructer");

        //カラーバッファ
        GLuint colorBuffer;
        glGenTextures(1, &colorBuffer);
        glBindTexture(GL_TEXTURE_2D, colorBuffer);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        this->colorBuffer = colorBuffer;
        geterror("in rendermanager constructer colorBuffer");

        //デプスバッファ
        GLuint depthBuffer;
        glGenRenderbuffers(1, &depthBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
        this->depthBuffer = depthBuffer;
        geterror("in rendermanager constructer depthBuffer");

        //フレームバッファ
        GLuint frameBuffer = input_framebuffer;
        auto isbuild = projects::Project::GetInstance()->GetIsBuild();
        std::cout << isbuild << std::endl;
        if (!isbuild) {
            glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
            geterror("in rendermanager constructer glBindFramebuffer");

            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                this->colorBuffer, 0);
            geterror("in rendermanager constructer glFramebufferTexture2D");


            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER,
                this->depthBuffer);
            geterror("in rendermanager constructer glFramebufferRenderbuffer");

            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            geterror("in rendermanager constructer glBindFramebuffer");
        }
        this->frameBuffer = frameBuffer;

        geterror("in rendermanager constructer frameBuffer");

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
        geterror("RenderScene");

        auto camera = components::camera::CameraComponent::GetMainCamera();

        glBindFramebuffer(GL_FRAMEBUFFER, this->frameBuffer);
        glViewport(0, 0, this->width, this->height);
        constexpr GLfloat color[]{ 0.0f, 0.3f, 0.5f, 0.8f }, depth(1.0f);
        glClearBufferfv(GL_COLOR, 0, color);
        glClearBufferfv(GL_DEPTH, 0, &depth);
        glEnable(GL_DEPTH_TEST);
        // glEnable(GL_CULL_FACE);
        geterror("RenderScene");

        int i = 0;
        //オブジェクトそれぞれ描画
        auto render_component_list = component_list->GetReferObjectList(components::ComponentName::kRender);
        for (auto render_component : render_component_list)
        {
            auto cast_rendercomponent = dynamic_cast<components::RenderComponent*>(render_component);
            if (camera != nullptr) {
                RenderOneGameObject(cast_rendercomponent, camera);
            }
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        GLenum err;
        while ((err = glGetError()) != GL_NO_ERROR)
        {
            std::cout << err << " というエラーがある in renderscene" << std::endl;
        }
    }

    float cValue = 0;

    float diff = 0.01f;


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
    void SetVec3Uniform(GLint program, const char* name, utility::Vector3 value)
    {
        GLuint loc = glGetUniformLocation(program, name);

        RenderManager::geterror("glGetUniformLocation");

        // Send the float data
        glUniform3f(loc, value.x, value.y, value.z);
        RenderManager::geterror("glUniform3f");
    }
    void SetTextureSampler(GLint program, const char* name, GLuint texture)
    {
        GLuint loc = glGetUniformLocation(program, name);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(loc, 0);
    }
    /**
     * \brief ゲームオブジェクトを描画する
     * \param render_component 描画対象のレンダーコンポーネント
     */
    void RenderManager::RenderOneGameObject(components::RenderComponent* render_component, components::camera::CameraComponent* camera)
    {
        geterror("RenderOneGameObject beforegetprogram");

        auto program = render_component->GetProgram();
        // GLint linkStatus;
        // glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
        // if (linkStatus == GL_FALSE) {
        //     // リンク失敗の処理
        //     char infoLog[512];
        //     glGetProgramInfoLog(program, 512, NULL, infoLog);
        //     std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        // }

        glUseProgram(render_component->GetProgram());
        geterror("RenderOneGameObject GetProgram");

        glBindVertexArray(render_component->GetVao());
        geterror("RenderOneGameObject GetVao()");
        glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 400.0f);

        auto cameraposition = camera->GetTransform()->GetPosition();
        auto cameraposition_glmvec3 = glm::vec3(cameraposition.x, cameraposition.y, cameraposition.z);
        glm::mat4 View = glm::lookAt(
            cameraposition_glmvec3,
            glm::vec3(0, 0, 0),
            glm::vec3(0, 1, 0)
        );

        auto gameobject = render_component->GetGameObject();
        //transformComponent取得
        auto transform = gameobject->GetComponent<components::TransformComponent>();
        //位置を取得
        auto position = transform->GetPosition();
        //回転を取得
        auto rotation = transform->GetRotation();
        //スケールを取得
        auto scale = transform->GetScale();
        glm::mat4 ScaleMat = glm::scale(glm::vec3(scale.x, scale.y, scale.z));

        //Model行列を定義
        glm::mat4 Model = glm::translate(glm::vec3(position.x, position.y, position.z)) * rotation->ConvertToGlmMat4() * ScaleMat;
        glm::mat4 MVP = Projection * View * Model;
        auto vShader_mvp_pointer = glGetUniformLocation(render_component->GetProgram(), "mvp");
        glUniformMatrix4fv(vShader_mvp_pointer, 1, GL_FALSE, &MVP[0][0]);

        geterror("RenderOneGameObject");

        auto shaderinputs = render_component->GetMaterial()->GetShaderInputs();
        for (auto shader_input_and_type_struct : shaderinputs)
        {
            if (shader_input_and_type_struct->GetValueType() == editor::projectwindows::assets::elements::model::materials::ShaderInputParameterType::kFloat) {
                SetFloatUniform(render_component->GetProgram(), shader_input_and_type_struct->GetName()->c_str(), *shader_input_and_type_struct->Get_float_value());
            }
            else if (shader_input_and_type_struct->GetValueType() == editor::projectwindows::assets::elements::model::materials::ShaderInputParameterType::kVec3)
            {
                SetVec3Uniform(render_component->GetProgram(), shader_input_and_type_struct->GetName()->c_str(), *shader_input_and_type_struct->Get_vec3_value());
                geterror("renderobject");
            }
            else if (shader_input_and_type_struct->GetValueType() == editor::projectwindows::assets::elements::model::materials::ShaderInputParameterType::kImage)
            {
                SetTextureSampler(render_component->GetProgram(), shader_input_and_type_struct->GetName()->c_str(), shader_input_and_type_struct->Get_image_value()->GetGLImage());
                geterror("SetTextureSampler");
            }

        }

        cValue += diff;
        if (cValue > 1.0f && diff > 0)
        {
            cValue *= -1;
        }
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDrawElements(GL_TRIANGLES, render_component->draw_point_count, GL_UNSIGNED_INT, 0);
        // glDrawArrays(GL_TRIANGLE_STRIP,0, render_component->vertex_num);
        glBindVertexArray(0);
        geterror("renderobject");
    }

    GLuint RenderManager::ShaderInit(std::string vs_shader_source, std::string fs_shader_source)
    {
        geterror("ShaderInit");
        const auto program = glCreateProgram();

        //シェーダオブジェクト生成
        const auto vsShader = glCreateShader(GL_VERTEX_SHADER);
        const auto fsShader = glCreateShader(GL_FRAGMENT_SHADER);

        //シェーダコードをオブジェクトに渡す
        const char* vsShaderSource_char = vs_shader_source.c_str();
        std::cout << "vertex \n" << vs_shader_source << std::endl;
        glShaderSource(vsShader, 1, &vsShaderSource_char, nullptr);

        const char* fsShaderSource_char = fs_shader_source.c_str();
        std::cout << "vertex \n" << fs_shader_source << std::endl;
        glShaderSource(fsShader, 1, &fsShaderSource_char, nullptr);

        //コンパイル
        glCompileShader(vsShader);
        glCompileShader(fsShader);
        geterror("ShaderInit");
        //エラー
        PrintShaderInfoLog(vsShader, "vertex shader");
        PrintShaderInfoLog(fsShader, "fragment shader");

        //programにアタッチ
        glAttachShader(program, vsShader);
        glDeleteShader(vsShader);
        glAttachShader(program, fsShader);
        glDeleteShader(fsShader);

        glLinkProgram(program);

        geterror("ShaderInit");

        return program;
    }

    GLuint RenderManager::ShaderInitFromFilePath(const std::string vsFilePath, const std::string fsFilePath)
    {
        return ShaderInit(ReadFile(vsFilePath), ReadFile(fsFilePath));
        // return 0;
    }

    GLuint RenderManager::ShaderInitFromFilePath(const std::shared_ptr<shader::ShaderFileAsset> vsAsset,
        const std::shared_ptr<shader::ShaderFileAsset> fsAsset)
    {
        return ShaderInit(vsAsset->GetCode(), fsAsset->GetCode());
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
        reading_file.close();
        std::cout << "file contens is \n" << content << std::endl;

        return content;
    }

    void RenderManager::geterror(std::string adderErrortext)
    {
        GLenum err;
        while ((err = glGetError()) != GL_NO_ERROR)
        {
            std::cout << err << " というエラーがある " << adderErrortext << std::endl;
        }
    }

    void RenderManager::getcurrentbindProgram()
    {
        GLint currentProgram = 0;
        glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);

        if (currentProgram != 0) {
            printf("Currently bound shader program ID: %d\n", currentProgram);
        }
        else {
            printf("No shader program is currently bound.\n");
        }
    }
}

