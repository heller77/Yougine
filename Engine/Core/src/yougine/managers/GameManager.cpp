#include "GameManager.h"

GameManager::GameManager(std::vector<IManager*> manager_list)
{
    this->manager_list = manager_list;
}

void GameManager::Update()
{
    for (IManager* manager : (this->manager_list))
    {
        manager->Update();
    }
}
