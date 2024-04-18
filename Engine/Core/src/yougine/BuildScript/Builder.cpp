#include "Builder.h"

#include <direct.h>
#include <iostream>
#include <regex>

#include "UserShare//components/Component.h"
#include "../Projects/Project.h"
#include "../SceneFiles/SceneFileExporter.h"

void builders::Builder::Build(std::string exportpath, yougine::Scene* scene)
{

    Save(scene);

    std::string exportpath_for_cmd = std::regex_replace(exportpath, std::regex("/"), "\\");

    //リソースファイルをコピー
    std::string resourcefolder = "./Resource/";
    std::filesystem::copy(resourcefolder, exportpath_for_cmd + "/Resource", std::filesystem::copy_options::overwrite_existing | std::filesystem::copy_options::recursive);

    auto gemeengine_mainbody_path = projects::Project::GetInstance()->GetEngineMainBodyPath();

    auto cmakepath = "";
    std::string cddirectoryCMD = "cd " + gemeengine_mainbody_path.string() + "& dir&mkdir tmpbuild & cd tmpbuild & mkdir build & cd build";
    //ゲームビルドプロジェクトのパス（todo: 配布するときとデバッグ時にパスが変わるのでよしなにする）
    // std::string gamebuildprojectpath = ".\\..\\..\\..\\GameBuildProject";
    auto gamebuildprojectpath = gemeengine_mainbody_path / "GameBuildProject";
    std::string cmakebuildcmd =
        "cmake " + gamebuildprojectpath.string() + " -G\"Visual Studio 16 2019\" -DROOTPATH=" + gemeengine_mainbody_path.string() + " & cmake --build . --config Release & cmake --install . --prefix ./ --config Release ";
    auto build_cmd = cddirectoryCMD + " & " + cmakebuildcmd;
    system(build_cmd.c_str());
    //binにexeがあるので、そこにUserEngineCommon.dllを配置
    auto UserEngineCommonDLL_Path = projects::Project::GetInstance()->GetUserEngineCommonDLLPath();
    auto binfolder = gemeengine_mainbody_path / "tmpbuild/build/bin/";
    std::filesystem::copy(UserEngineCommonDLL_Path, binfolder, std::filesystem::copy_options::overwrite_existing);
    std::cout << "UserEngineCommonDLL copy to binfolder" << std::endl;


    // std::string copyDebugfolderToExortoathcmd = "xcopy bin " + exportpath_for_cmd + " /s /y";
    std::filesystem::copy(binfolder, exportpath_for_cmd, std::filesystem::copy_options::overwrite_existing);


    std::string runcmd = "cd " + exportpath_for_cmd + " & " + "ExeProject.exe &";
    //exeを配置し、実行するコマンド
    std::string distribute_and_execute_cmd = runcmd;
    std::cout << distribute_and_execute_cmd << std::endl;
    system(distribute_and_execute_cmd.c_str());
    // system("rmdir /S /Q .\\tmpbuild");
}

void builders::Builder::Save(yougine::Scene* scene)
{
    //シーンファイルのエクスポート（本来はeditor上の操作によりエクスポートしたい。
    //なんならビルド先にできるのおかしい。ビルド時にファイルコピーがされるべき）
    auto projectpath = projects::Project::GetInstance()->GetProjectFolderPath_ByTypeString();
    auto exportPath = projects::Project::GetInstance()->GetNowSceneFilePath().string();

    auto sceneexporter = new yougine::SceneFiles::SceneFileExporter();
    sceneexporter->ScenefileExportFromScene(scene, exportPath);
}
