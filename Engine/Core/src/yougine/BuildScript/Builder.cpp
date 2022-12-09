#include "Builder.h"

void builders::Builder::Build(std::string scenfilepath, std::string exportpath)
{
    auto cmakepath = "";
    system("cd tmpbuild/build & cmake ./../../../GameBuildProject -G\"Visual Studio 16 2019\" & cmake --build . & cd Debug & cd & ExeProject.exe");
    // system("cd");
    // system("cd tmpbuild");
    // system("cd");
}
