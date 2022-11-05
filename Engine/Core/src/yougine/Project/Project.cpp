#include "Project.h"

projects::Project* projects::Project::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new Project();
    }
    return instance;
}

projects::Project* projects::Project::instance;
