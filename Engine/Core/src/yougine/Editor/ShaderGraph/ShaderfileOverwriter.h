#pragma once
#include <string>
#include "Nodes/MainShaderGraphNode.h"
#include <iostream>
#include <fstream>

namespace editor::shadergraph
{
    class ShaderfileOverwriter
    {
    private:
        std::string targetFilePath;
        std::string filename;

    private:

    public:
        ShaderfileOverwriter(std::string targetFilePath, std::string filename);
        void UpdateFile(std::vector < std::string > shader_codes);
    };
}
