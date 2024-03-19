#include "UserScriptComponentEntryPointManager.h"

yougine::managers::UserScriptComponentEntryPointManager::UserScriptComponentEntryPointManager()
{
    this->updateMethods = {};
}

void yougine::managers::UserScriptComponentEntryPointManager::AddUpdate(std::function<void()> method)
{
    this->updateMethods.push_back(method);
}

void yougine::managers::UserScriptComponentEntryPointManager::Update()
{
    for (auto callback : this->updateMethods)
    {
        callback();
    }
}
