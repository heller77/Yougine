#pragma once
#include <filesystem>
#include <string>
#include "windows.h"
namespace builders
{
    class UserScriptCompiler
    {
    private:
        static HMODULE userscriptModule;
    public:
        static void Compile();
        static std::filesystem::path GetDLLPath();
        static HMODULE GetModule();

    };
}
