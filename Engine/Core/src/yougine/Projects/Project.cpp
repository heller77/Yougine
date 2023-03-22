#include "Project.h"

#include "../SceneFiles/SceneFileExporter.h"
#include <iostream>
#include <fstream>
projects::Project* projects::Project::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new Project();
    }
    return instance;
}

void projects::Project::Initialize(std::string project_file_path)
{
    //projectファイルのパース結果が入る
    json projectData;
    //プロジェクトファイル読み込み
    std::ifstream reading(project_file_path, std::ios::in);
    if (!reading)
    {
        std::cout << "failed read Project.json" << std::endl;
    }
    //プロジェクトファイルをパースしてprojectDataに代入
    try {
        reading >> projectData;
    }
    catch (json::parse_error& er)
    {
        std::cerr << "projectparse error at byte " << er.byte << std::endl;
    }

    this->projectFolderPath = projectData["Projectpath"];
    std::vector<std::string> sceneFilePathVector;
    for (std::string a : projectData["SceneFileLocations"])
    {
        std::cout << a << std::endl;
    }
}

void projects::Project::SetDataBase(
    std::shared_ptr<editor::projectwindows::assets::elements::model::assetdatabases::AssetDatabase> asset_database)
{
    this->asset_database = asset_database;
}

std::shared_ptr<editor::projectwindows::assets::elements::model::assetdatabases::AssetDatabase> projects::Project::
GetDataBase()
{
    return this->asset_database;
}

projects::Project* projects::Project::instance;
