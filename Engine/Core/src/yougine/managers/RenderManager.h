#pragma once
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../components/RenderComponent.h"
#include "../components/Camera/CameraComponent.h"

#include "imgui/imgui.h"

#include "UserShare/managers/ComponentList.h"


namespace yougine::managers
{
    namespace shader = editor::projectwindows::assets::elements::model::shader;

    class RenderManager
    {
    public:
        RenderManager(int width, int height, ComponentList* component_list);

        RenderManager(int width, int height, GLint input_framebuffer, ComponentList* component_list);

        void Initialize();

        void RenderScene();

        static GLuint ShaderInit(std::string vs_shader_source, std::string fs_shader_source);

        static GLuint ShaderInitFromFilePath(const std::string vsFilePath, const std::string fsFilePath);

        static GLuint ShaderInitFromFilePath(const std::shared_ptr<shader::ShaderFileAsset> vsAsset, const std::shared_ptr<shader::ShaderFileAsset> fsAsset);

        GLuint GetColorBuffer();

        void SetWindowSize(ImVec2 vec2);
        static void geterror(std::string adderErrortext);
        static void getcurrentbindProgram();
    private:
        ComponentList* component_list;

        int width, height;

        GLuint frameBuffer;


        GLuint colorBuffer;

        GLuint depthBuffer;

        void RenderOneGameObject(components::RenderComponent* render_component, components::camera::CameraComponent* camera);

        void MeshBufferInit();

        static GLboolean PrintShaderInfoLog(GLuint shader, const char* str);

        static std::string ReadFile(std::string filepath);
    };
}
