#pragma once
#include <filesystem>
#include <string>

namespace builders
{
    class UserScriptCompiler
    {
    public:
        static void Compile();
        static std::filesystem::path GetDLLPath();

    };
}
