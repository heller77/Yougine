#include <filesystem>
#include <glm/vec4.hpp>

#include "ShaderfileOverwriter.h"

namespace editor::shadergraph
{
    ShaderfileOverwriter::ShaderfileOverwriter(std::string targetFilePath, std::string filename)
    {
        this->targetFilePath = targetFilePath;
        this->filename = filename;
    }

    void ShaderfileOverwriter::UpdateFile(std::vector < std::string > shader_codes)
    {
        std::ofstream shaderfile;
        std::string path = targetFilePath + filename;
        shaderfile.open(path, std::ios::out);

        for (std::string code : shader_codes)
        {
            shaderfile << code << std::endl;
        }

        shaderfile.close();
    }


}
