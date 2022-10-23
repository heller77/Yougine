#include "Project.h"

int Projects::Project::g()
{
    return 1;
}

Projects::Project* Projects::Project::GetInstance()
{
    
        if (instance == nullptr)
        {
            instance = new Project();
        }
        return instance;
    
}

Projects::Project* Projects::Project::instance;
