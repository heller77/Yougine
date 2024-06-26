﻿#include "Project.h"

#include "../SceneFiles/SceneFileExporter.h"
#include <iostream>
#include <fstream>

#include "../BuildScript/UserScriptCompiler.h"
#include "../Editor/ProjectWindows/Assets/element/Model/TextAsset.h"
#include "../Editor/ProjectWindows/Assets/element/Model/CustomScripts/CustomScriptAsset.h"
#include "../Editor/ProjectWindows/Assets/element/Model/Image/ImageAsset.h"
#include "../Editor/ProjectWindows/Assets/element/Model/Material/Material.h"
#include "../Editor/ProjectWindows/Assets/element/Model/Mesh/MeshAsset.h"
#include "../Editor/ProjectWindows/Assets/element/Model/shader/ShaderFileAsset.h"

std::shared_ptr<editor::projectwindows::assets::elements::model::Asset> projects::Project::GenerateAssetFromFile(
    std::filesystem::path path, std::shared_ptr<utility::youginuuid::YougineUuid> uuid)
{
    //ファイル拡張子
    std::string extension = path.extension().string().replace(0, 1, "");
    //ファイルの名前だけ
    std::string filename = path.filename().string();

    std::filesystem::path assetinfo_path = path.string() + ".assetinfo";
    namespace  assetmodel = editor::projectwindows::assets::elements::model;

    //フォルダ以外
    std::cout << "extension " << extension << std::endl;
    if (extension == "assetinfo")
    {
        return nullptr;
    }
    if (extension == "shader" || extension == "frag" || extension == "vert") {
        if (std::filesystem::exists(std::filesystem::status(assetinfo_path)))
        {
            std::cout << "assetinfo exist!! : " << filename << std::endl;
            return std::shared_ptr<assetmodel::shader::ShaderFileAsset>(new assetmodel::shader::ShaderFileAsset(assetinfo_path));
        }
        auto shaderasset = std::shared_ptr<assetmodel::shader::ShaderFileAsset>(new editor::projectwindows::assets::elements::model::shader::ShaderFileAsset(path, uuid));
        shaderasset->Export();
        return shaderasset;
    }
    else if (extension == "txt")
    {
        std::ifstream ifs(path.string());
        if (ifs.fail()) {
            std::cerr << "Failed to open file. __ in project window" << std::endl;
            return nullptr;
        }
        //アセット生成
        auto asset = std::make_shared<assetmodel::TextAsset>(path, uuid);
        asset->Export();
        return asset;

    }
    else if (extension == "mat")
    {
        if (std::filesystem::exists(std::filesystem::status(assetinfo_path)))
        {
            std::cout << "assetinfo exist!! : " << filename << std::endl;
            return std::make_shared<assetmodel::materials::Material>(assetinfo_path);
        }
        auto material_asset = std::make_shared<assetmodel::materials::Material>(path, uuid);
        material_asset->Export();
        return material_asset;

    }
    else if (extension == "h")
    {
        if (std::filesystem::exists(std::filesystem::status(assetinfo_path)))
        {
            std::cout << "assetinfo exist!! : " << filename << std::endl;
            return std::make_shared<assetmodel::customscript::CustomScriptAsset>(assetinfo_path);
        }
        auto custom_script_asset = std::make_shared<assetmodel::customscript::CustomScriptAsset>(path, uuid);
        custom_script_asset->Export();
        return custom_script_asset;
    }
    else if (extension == "gltf")
    {
        if (std::filesystem::exists(std::filesystem::status(assetinfo_path)))
        {
            std::cout << "assetinfo exist!! : " << filename << std::endl;
            return std::make_shared<assetmodel::mesh::MeshAsset>(assetinfo_path);
        }
        auto mesh_asset = std::make_shared<assetmodel::mesh::MeshAsset>(path, uuid);
        mesh_asset->Export();
        return mesh_asset;
    }
    else if (extension == "png" || extension == "jpeg")
    {
        if (std::filesystem::exists(std::filesystem::status(assetinfo_path)))
        {
            std::cout << "assetinfo exist!! : " << filename << std::endl;
            return std::make_shared<assetmodel::image::ImageAsset>(assetinfo_path);
        }
        auto image_asset = std::make_shared<assetmodel::image::ImageAsset>(path, uuid);
        image_asset->Export();
        return image_asset;
    }
    else
    {
        std::ifstream ifs(path.string());
        if (ifs.fail()) {
            std::cerr << "Failed to open file. __ in project window" << std::endl;
            return nullptr;
        }
        //アセット生成
        auto asset = std::make_shared<assetmodel::TextAsset>(path, uuid);
        asset->Export();
        return asset;
    }
}

projects::Project::Project()
{
    isBuild = false;
}

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
    reading.close();
    //jsonからProjectpathを取得
    std::string projectpathstr = projectData["Projectpath"];
    this->projectFolderPath = projectpathstr;
    //プロジェクトのパスが存在するかどうか
    if (!std::filesystem::exists(projectFolderPath))
    {
        std::cout << projectFolderPath << " は存在しないため、エンジンは起動できません" << std::endl;
        std::cout << project_file_path << "にかかれたプロジェクトパスを確認してください" << std::endl;
        exit(1);
    }
    //エンジン自体のパスを取得
    std::string enginemainbodypath_string = projectData["EngineManBodyPath"];
    this->engine_mainbody_path = enginemainbodypath_string;
    ;

    //userfolderのパスを設定
    this->userfolder = this->projectFolderPath / c_userfolder;
    //userfolder無ければ生成
    std::filesystem::create_directory(userfolder);

    //ビルドフォルダを作成
    this->project_build_export_path = projectFolderPath / this->c_projectbuildexportfolder;
    std::filesystem::create_directory(this->project_build_export_path);


    //エンジン側が提供するリソースをプロジェクトに配置
    this->engineresourcefolder = this->projectFolderPath / c_libraryfolder;
    //engineresourcefolderというフォルダが無ければ作成
    std::filesystem::create_directory(engineresourcefolder);
    //配置
    //test.vertをプロジェクトフォルダに配置
    std::string resourcefolder = "./Resource/";
    std::filesystem::copy(resourcefolder, this->engineresourcefolder, std::filesystem::copy_options::overwrite_existing | std::filesystem::copy_options::recursive);

    //エンジン側が提供するリソース情報を管理するjsonファイルのパス
    this->engineresource_InfofilePath = this->engineresourcefolder / this->c_libraryfolder_ResourceInfojsonFileName;
    std::ifstream engineresourceinfofile(engineresource_InfofilePath, std::ios::in);
    engineresourceinfofile >> engineresource_info_json_obj;

    //シーンファイルパス設定
    this->now_targetscenefile_path = this->projectFolderPath / "build/scene.json";

    std::vector<std::string> sceneFilePathVector;
    for (std::string a : projectData["SceneFileLocations"])
    {
        std::cout << a << std::endl;
    }

    //ユーザスクリプトコンパイル
    builders::UserScriptCompiler::Compile();

    this->AssetInitialize();
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

void projects::Project::AssetInitialize()
{
    //アセットデータベース作成
    this->asset_database = std::make_shared<editor::projectwindows::assets::elements::model::assetdatabases::AssetDatabase>();
    projects::Project::GetInstance()->SetDataBase(asset_database);

    auto projectpath = this->userfolder.string();

    auto file_and_folder_list = std::filesystem::recursive_directory_iterator(projectpath);
    //再帰的にプロジェクトパス以下のファイル全てをAssetクラスをさくせい　
    //とりあえず、作成=>初期化
    for (auto entry : file_and_folder_list)
    {
        std::cout << "----" << std::endl;
        auto path_string = entry.path().string();
        std::cout << entry.path().string() << std::endl;


        auto uuid = std::make_shared<utility::youginuuid::YougineUuid>();
        // auto uuid = new utility::youginuuid::YougineUuid();
        std::cout << "asset id : " << uuid->convertstring() << std::endl << std::endl;

        auto asset = this->GenerateAssetFromFile(entry.path(), uuid);

        if (asset != nullptr) {
            this->asset_database->AddAsset(asset->GetAssetId(), asset);
        }
        else
        {
            std::cerr << "asset is null" << " : " << path_string << std::endl;
        }
    }
    // auto nowfilepath = std::filesystem::current_path();
    // std::filesystem::path engine_Default_Path = "./Resource/Export/";
    auto exportfile = std::filesystem::recursive_directory_iterator(this->engineresourcefolder);

    for (auto entry : exportfile)
    {
        std::cout << "----" << std::endl;
        auto path_string = entry.path().string();
        std::cout << entry.path().string() << std::endl;


        auto uuid = std::make_shared<utility::youginuuid::YougineUuid>();
        // auto uuid = new utility::youginuuid::YougineUuid();
        std::cout << "asset id : " << uuid->convertstring() << std::endl << std::endl;

        auto asset = this->GenerateAssetFromFile(entry.path(), uuid);

        if (asset != nullptr) {
            this->asset_database->AddAsset(asset->GetAssetId(), asset);
        }
        else
        {
            std::cerr << "asset is null" << " : " << path_string << std::endl;
        }
    }

    auto asset_list = projects::Project::GetInstance()->GetDataBase()->GetAssetList();
    for (auto pair : asset_list)
    {
        auto asset = pair.second;
        asset->InitializeParameter();
    }
}

std::filesystem::path projects::Project::GetUserFolderPath()
{
    return this->userfolder;
}

std::filesystem::path projects::Project::GetProjectFolderPath()
{
    return this->projectFolderPath;
}

std::filesystem::path projects::Project::GetUserScriptFolderAbsolutePath()
{
    return this->projectFolderPath / this->c_userscript_buildfolder;
}

std::string projects::Project::GetProjectFolderPath_ByTypeString()
{
    return this->projectFolderPath.string();
}

nlohmann::basic_json<> projects::Project::GetParameterFromEngineResourceJson(std::string parameterName)
{
    return this->engineresource_info_json_obj[parameterName];
}

std::filesystem::path projects::Project::GetEngineResouceFolderPath()
{
    return this->projectFolderPath / this->c_libraryfolder;
}

std::filesystem::path projects::Project::GetBuildExportPath()
{
    return project_build_export_path;
}

const std::string projects::Project::GetNowIsDebugOrRelease()
{
#if _DEBUG
    return "Debug";
#else
    return "Release";
#endif
}

std::filesystem::path projects::Project::GetNowSceneFilePath()
{
    return now_targetscenefile_path;
}

std::filesystem::path projects::Project::GetEngineMainBodyPath()
{
    return this->engine_mainbody_path;
}

std::filesystem::path projects::Project::GetUserEngineCommonDLLPath()
{
    return this->engine_mainbody_path / "UserEngineCommon.dll";
}

void projects::Project::SetBuild(bool isBuildMode)
{
    this->isBuild = isBuildMode;
}

bool projects::Project::GetIsBuild()
{
    return this->isBuild;
}

projects::Project* projects::Project::instance;
