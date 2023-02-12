#include <filesystem>
#include <glm/vec4.hpp>

#include "ShaderfileOverwriter.h"

namespace yougine::shadergraph
{
    ShaderfileOverwriter::ShaderfileOverwriter(std::string targetFilePath, std::string filename)
    {
        this->targetFilePath = targetFilePath;
        this->filename = filename;
    }

    void ShaderfileOverwriter::UpdateFile()
    {
        std::ofstream shaderfile;
        std::string path = targetFilePath + filename;
        shaderfile.open(path, std::ios::out);

        shaderfile << "#version 430" << std::endl;
        shaderfile << "out vec4 fragment" << std::endl;
        shaderfile << "in vec3 vNormal;" << std::endl;
        shaderfile << "uniform float c;" << std::endl;
        shaderfile << "void main() {" << std::endl;
        shaderfile << "fragment = glm::vec4(vNormal, 1.0);" << std::endl;
        shaderfile << "//405" << std::endl;
        shaderfile << "}" << std::endl;

        shaderfile.close();
    }


}
