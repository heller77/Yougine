#include "Builder.h"

#include <direct.h>
#include <iostream>

#include "../components/Component.h"
#include "../Projects/Project.h"
#include "../SceneFiles/SceneFileExporter.h"

void builders::Builder::Build( std::string exportpath,yougine::Scene* scene)
{
    //シーンファイルのエクスポート（本来はeditor上の操作によりエクスポートしたい。
    //なんならビルド先にできるのおかしい。ビルド時にファイルコピーがされるべき）
    auto sceneexporter = new yougine::SceneFiles::SceneFileExporter();
    auto projectpath = projects::Project::GetInstance()->projectFolderPath;
    auto buildfolder = projectpath + "build\\";
    if (_mkdir(buildfolder.c_str()))
    {
        std::cout << "buildフォルダ作成" << std::endl;
    }

    sceneexporter->ScenefileExportFromScene(scene, projectpath + "build\\scene.json");

    auto cmakepath = "";
    std::string cddirectoryCMD = "mkdir tmpbuild & cd tmpbuild & mkdir build & cd build";
    std::string cmakebuildcmd =
        "cd tmpbuild/build & cmake ./../../../GameBuildProject -G\"Visual Studio 16 2019\" & cmake --build .";
    std::string copyDebugfolderToExortoathcmd = "xcopy .\\Debug " + exportpath + " /s /y";
    std::string runcmd = "cd " + exportpath + "& cd Debug &" + " cd & " + "ExeProject.exe";
    std::string cmd = cddirectoryCMD + " & " + cmakebuildcmd + " & " + copyDebugfolderToExortoathcmd + " & " + runcmd;
    std::cout << cmd << std::endl;
    system(cmd.c_str());
    // system("rmdir /S /Q .\\tmpbuild");
}
