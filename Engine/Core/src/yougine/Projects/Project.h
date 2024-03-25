#pragma once
#include <memory>
#include <string>

#include "../Editor/ProjectWindows/Assets/element/Model/AssetDataBases/AssetDatabase.h"

namespace projects
{
    class Project
    {
    private:

        const std::string c_userfolder = "userFolder";
        static Project* instance;
        std::shared_ptr<editor::projectwindows::assets::elements::model::assetdatabases::AssetDatabase> asset_database;
        std::shared_ptr<editor::projectwindows::assets::elements::model::Asset> GenerateAssetFromFile(std::filesystem::path path, std::shared_ptr<utility::youginuuid::YougineUuid> uuid);

        /**
         * \brief プロジェクトパス/userFolder　ユーザがスクリプトやアセットを置く場所
         */
        std::filesystem::path userfolder;
        //プロジェクトフォルダのパスを格納（main.cppで指定しているが、実行時引数とかで貰うようにするのがよさそう）
        std::filesystem::path projectFolderPath;

    public:


        static Project* GetInstance();
        void Initialize(std::string project_file_path);
        void SetDataBase(std::shared_ptr<editor::projectwindows::assets::elements::model::assetdatabases::AssetDatabase> asset_database);
        std::shared_ptr < editor::projectwindows::assets::elements::model::assetdatabases::AssetDatabase>  GetDataBase();
        void AssetInitialize();
        std::filesystem::path GetUserFolderPath();
        std::filesystem::path GetProjectFolderPath();

        std::string GetProjectFolderPath_ByTypeString();
    };
}
