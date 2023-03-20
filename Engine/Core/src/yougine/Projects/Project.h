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

    public:
        //プロジェクトフォルダのパスを格納（main.cppで指定しているが、実行時引数とかで貰うようにするのがよさそう）
        std::string projectFolderPath;

        static Project* GetInstance();
        void Initialize(std::string project_file_path);
        void SetDataBase(std::shared_ptr<editor::projectwindows::assets::elements::model::assetdatabases::AssetDatabase> asset_database);
        std::shared_ptr < editor::projectwindows::assets::elements::model::assetdatabases::AssetDatabase>  GetDataBase();
    };
}
