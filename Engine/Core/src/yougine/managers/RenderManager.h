#pragma once
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../components/RenderComponent.h"

#include "imgui/imgui.h"
namespace yougine::managers
{
    class RenderManager
    {
    public:
        RenderManager(int width, int height, ComponentList* component_list);

        void Initialize();

        void RenderScene();

        GLuint ShaderInit(std::string vs_shader_source, std::string fs_shader_source);
        GLuint ShaderInitFromFilePath(const std::string vsFilePath, const std::string fsFilePath);
        GLuint GetColorBuffer();
        void SetWindowSize(ImVec2 vec2);

    private:
        ComponentList* component_list;
        int width, height;
        // GLuint program;
        // GLuint vao;
        // GLuint frameBuffer;

        comoponents::RenderComponent* renderComponent;

        // GLuint colorBuffer;
        //
        // GLuint depthBuffer;

        void RenderOneGameObject(comoponents::RenderComponent* render_component);

        void MeshBufferInit();

        GLboolean PrintShaderInfoLog(GLuint shader, const char* str);

        std::string ReadFile(std::string filepath);
    };
}
