#include "UserScriptCompiler.h"

#include "../Projects/Project.h"

void builders::UserScriptCompiler::Compile()
{
    //cmake D:\Yougin\ -DCMAKE_BUILD_TYPE=Release -G"Visual Studio 16 2019" -B D:\Yougin\a
    //cmake --build D:\Yougin\a  --config Release
    //の様なコマンドを実行
    auto projectpath = projects::Project::GetInstance()->GetProjectFolderPath();
    auto userscript_buildoutputpath = projects::Project::GetInstance()->GetUserScriptFolderAbsolutePath();
    std::string config_cmd = "cmake " + projectpath.string() + " -DCMAKE_BUILD_TYPE=Release -G\"Visual Studio 16 2019\" -B " + userscript_buildoutputpath.string();
    std::string build_cmd = "cmake --build " + userscript_buildoutputpath.string() + " --config Release";

    auto cmd = config_cmd + " & " + build_cmd;
    system(cmd.c_str());
}

std::filesystem::path builders::UserScriptCompiler::GetDLLPath()
{
    auto dll_path = projects::Project::GetInstance()->GetUserScriptFolderAbsolutePath() / "Release/UserScriptProject.dll";
    return dll_path;
}
