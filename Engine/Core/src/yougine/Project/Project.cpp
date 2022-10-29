#include "Project.h"

Projects::Project* Projects::Project::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new Project();
    }
    return instance;
}

Projects::Project* Projects::Project::instance;
