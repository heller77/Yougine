#include "Builder.h"

#include <iostream>

void builders::Builder::Build(std::string scenfilepath, std::string exportpath)
{
    auto cmakepath = "";
    std::string cddirectoryCMD = "mkdir tmpbuild & cd tmpbuild & mkdir build & cd build";
    std::string cmakebuildcmd = "cd tmpbuild/build & cmake ./../../../GameBuildProject -G\"Visual Studio 16 2019\" & cmake --build .";
    std::string copyDebugfolderToExortoathcmd = "xcopy .\\Debug " + exportpath+"\\Debug\\ /s /y";
    std::string runcmd = "cd " + exportpath + "& cd Debug &" + " cd & " + "ExeProject.exe";
    std::string cmd = cddirectoryCMD+" & " + cmakebuildcmd + " & " + copyDebugfolderToExortoathcmd + " & " + runcmd;
    std::cout << cmd << std::endl;
    system(cmd.c_str());
    system("rmdir /S /Q .\\tmpbuild");
    // system("cd");
    // system("cd tmpbuild");
    // system("cd");
}
