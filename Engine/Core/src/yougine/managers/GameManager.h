#pragma once
#include <vector>

#include "IManager.h"

class GameManager
{
    std::vector<IManager*> manager_list;
    
public:
    GameManager(std::vector<IManager*> manager_list);
    void Update();
};
