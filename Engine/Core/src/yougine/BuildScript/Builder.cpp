﻿#include "Builder.h"

#include <direct.h>
#include <iostream>
#include <regex>

#include "UserShare//components/Component.h"
#include "../Projects/Project.h"
#include "../SceneFiles/SceneFileExporter.h"

void builders::Builder::Build(std::string exportpath, yougine::Scene* scene)
{
    //シーンファイルのエクスポート（本来はeditor上の操作によりエクスポートしたい。
    //なんならビルド先にできるのおかしい。ビルド時にファイルコピーがされるべき）
    auto sceneexporter = new yougine::SceneFiles::SceneFileExporter();
    auto projectpath = projects::Project::GetInstance()->GetProjectFolderPath_ByTypeString();
    auto buildfolder = projectpath + "build\\";
    if (_mkdir(buildfolder.c_str()))
    {
        std::cout << "buildフォルダ作成" << std::endl;
    }

    // sceneexporter->ScenefileExportFromScene(scene, projectpath + "build\\scene.json");
    Save(scene);




    std::string exportpath_for_cmd = std::regex_replace(exportpath, std::regex("/"), "\\");

    //リソースファイルをコピー
    std::string resourcefolder = "./Resource/";
    std::filesystem::copy(resourcefolder, exportpath_for_cmd + "/Resource", std::filesystem::copy_options::overwrite_existing | std::filesystem::copy_options::recursive);


    auto cmakepath = "";
    std::string cddirectoryCMD = "dir&mkdir tmpbuild & cd tmpbuild & mkdir build & cd build";
    std::string cmakebuildcmd =
        "cmake .\\..\\..\\..\\GameBuildProject -G\"Visual Studio 16 2019\" & cmake --build .";
    // std::string copyDebugfolderToExortoathcmd = "xcopy Debug " + exportpath_for_cmd + " /s /y";
    std::string runcmd = "cd " + exportpath_for_cmd + " & " + "ExeProject.exe";
    std::string cmd = cddirectoryCMD + " & " + cmakebuildcmd + " & " + runcmd;
    std::cout << cmd << std::endl;
    system(cmd.c_str());
    // system("rmdir /S /Q .\\tmpbuild");
}

void builders::Builder::Save(yougine::Scene* scene)
{
    //シーンファイルのエクスポート（本来はeditor上の操作によりエクスポートしたい。
    //なんならビルド先にできるのおかしい。ビルド時にファイルコピーがされるべき）
    auto projectpath = projects::Project::GetInstance()->GetProjectFolderPath_ByTypeString();
    auto exportPath = projectpath + "build\\scene.json";

    auto sceneexporter = new yougine::SceneFiles::SceneFileExporter();
    sceneexporter->ScenefileExportFromScene(scene, exportPath);
}
