#pragma once
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../components/RenderComponent.h"
namespace yougine::managers
{
	class RenderManager
	{
	public:

		void Initialize();

		void RenderScene();
		GLuint ShaderInit(const std::string& vs_shader_source, const std::string& fs_shader_source);

	private:
		void RenderOneGameObject(comoponents::RenderComponent render_component);



		void MeshBufferInit();

		GLboolean PrintShaderInfoLog(GLuint shader, const char* str);

		std::string ReadFile(std::string filepath);
	};
}
