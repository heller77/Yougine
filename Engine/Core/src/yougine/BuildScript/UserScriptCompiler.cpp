#include "UserScriptCompiler.h"


#include "../Projects/Project.h"

HMODULE builders::UserScriptCompiler::userscriptModule;

void builders::UserScriptCompiler::Compile()
{
    FreeLibrary(userscriptModule);
    auto dllfolder = builders::UserScriptCompiler::GetDLLPath().parent_path();
    std::filesystem::remove_all(dllfolder);

    //cmake D:\Yougin\ -DCMAKE_BUILD_TYPE=Release -G"Visual Studio 16 2019" -B D:\Yougin\a
    //cmake --build D:\Yougin\a  --config Release
    //の様なコマンドを実行
    auto projectpath = projects::Project::GetInstance()->GetProjectFolderPath();
    auto userscript_buildoutputpath = projects::Project::GetInstance()->GetUserScriptFolderAbsolutePath();
    std::string config_cmd = "cmake " + projectpath.string() + " -DCMAKE_BUILD_TYPE=" + projects::Project::GetNowIsDebugOrRelease() + " -G\"Visual Studio 16 2019\" -B " + userscript_buildoutputpath.string();
    std::string build_cmd = "cmake --build " + userscript_buildoutputpath.string() + " --config " + projects::Project::GetNowIsDebugOrRelease();

    auto cmd = config_cmd + " & " + build_cmd;
    system(cmd.c_str());

    //DLLをロード。
    auto userscriptpath = builders::UserScriptCompiler::GetDLLPath();
    userscriptModule = LoadLibrary(userscriptpath.string().c_str());

}

std::filesystem::path builders::UserScriptCompiler::GetDLLPath()
{
    auto relativepath = projects::Project::GetNowIsDebugOrRelease() + "/UserScriptProject.dll";
    auto dll_path = projects::Project::GetInstance()->GetUserScriptFolderAbsolutePath() / relativepath;
    return dll_path;
}

HMODULE builders::UserScriptCompiler::GetModule()
{
    return userscriptModule;
}
