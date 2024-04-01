#pragma once
#include <memory>
#include <string>

#include "../Editor/ProjectWindows/Assets/element/Model/AssetDataBases/AssetDatabase.h"

namespace projects
{
    class Project
    {
    private:


        static Project* instance;
        std::shared_ptr<editor::projectwindows::assets::elements::model::assetdatabases::AssetDatabase> asset_database;
        std::shared_ptr<editor::projectwindows::assets::elements::model::Asset> GenerateAssetFromFile(std::filesystem::path path, std::shared_ptr<utility::youginuuid::YougineUuid> uuid);

        /**
         * \brief プロジェクトパス/userFolder　ユーザがスクリプトやアセットを置く場所
         */
        std::filesystem::path userfolder;

        /**
         * \brief プロジェクトフォルダ直下にある
         */
        std::filesystem::path engineresourcefolder;

        std::filesystem::path engineresource_InfofilePath;

        /**
         * \brief エンジンのリソースについての情報をjsonをパースしたもの。
         */
        nlohmann::json engineresource_info_json_obj;

        //プロジェクトフォルダのパスを格納（main.cppで指定しているが、実行時引数とかで貰うようにするのがよさそう）
        std::filesystem::path projectFolderPath;




    public:

        const std::string c_userfolder = "userFolder";
        const std::string c_libraryfolder = "libFolder";
        const std::string c_libraryfolder_ResourceInfojsonFileName = "ResourceInfo.json";
        const std::string c_userscript_buildfolder = "userscriptbuild";
        static Project* GetInstance();
        void Initialize(std::string project_file_path);
        void SetDataBase(std::shared_ptr<editor::projectwindows::assets::elements::model::assetdatabases::AssetDatabase> asset_database);
        std::shared_ptr < editor::projectwindows::assets::elements::model::assetdatabases::AssetDatabase>  GetDataBase();
        void AssetInitialize();
        std::filesystem::path GetUserFolderPath();
        std::filesystem::path GetProjectFolderPath();

        /**
         * \brief ユーザスクリプトをビルド出力する先
         * \return
         */
        std::filesystem::path GetUserScriptFolderAbsolutePath();

        std::string GetProjectFolderPath_ByTypeString();

        /**
         * \brief エンジン側が提供するリソースの情報を取得できる
         * \param parameterName
         * \return
         */
        nlohmann::basic_json<> GetParameterFromEngineResourceJson(std::string parameterName);

        std::filesystem::path GetEngineResouceFolderPath();

        static const std::string GetNowIsDebugOrRelease();

    };
}
