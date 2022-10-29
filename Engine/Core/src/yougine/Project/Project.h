#pragma once
#include <string>

namespace Projects
{
    class Project
    {
    private:
        static Project* instance;

    public:
        //プロジェクトフォルダのパスを格納（main.cppで指定しているが、実行時引数とかで貰うようにするのがよさそう）
        std::string projectFolderPath;

        static Project* GetInstance();
    };
}
