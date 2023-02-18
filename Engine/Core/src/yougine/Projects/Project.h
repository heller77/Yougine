#pragma once
#include <string>

namespace projects
{
    class Project
    {
    private:
        static Project* instance;

    public:
        //プロジェクトフォルダのパスを格納（main.cppで指定しているが、実行時引数とかで貰うようにするのがよさそう）
        std::string projectFolderPath;

        static Project* GetInstance();
        void Initialize(std::string project_file_path);
    };
}
