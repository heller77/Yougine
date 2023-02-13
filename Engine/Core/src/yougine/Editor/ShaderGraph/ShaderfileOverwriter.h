#pragma once
#include <string>
#include "MainShaderGraphNode.h"
#include <iostream>
#include <fstream>

namespace yougine::shadergraph
{
    class ShaderfileOverwriter
    {
    private:
        std::string targetFilePath;
        std::string filename;

    private:

    public:
        ShaderfileOverwriter(std::string targetFilePath, std::string filename);
        void UpdateFile();
    };
}
