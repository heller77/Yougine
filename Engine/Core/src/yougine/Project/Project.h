#pragma once
#include <string>

namespace Projects
{
    class Project
    {
    private:
        static Project* instance;
    public:
        std::string projectFolderPath;
        static int g();
        static Project* GetInstance();

    };
    
}
