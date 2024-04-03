#include "UserScriptComponentEntryPointManager.h"

#include <iostream>

yougine::managers::UserScriptComponentEntryPointManager::UserScriptComponentEntryPointManager()
{
    this->update_entrypoint = nullptr;
}

void yougine::managers::UserScriptComponentEntryPointManager::SetUpdate(components::userscriptcomponents::IUpdatable* i_updatable)
{
    if (update_entrypoint != nullptr)
    {
        std::cout << "update に既に登録されています。上書きします。" << std::endl;
    }
    update_entrypoint = i_updatable;
}

void yougine::managers::UserScriptComponentEntryPointManager::Update()
{
    if (update_entrypoint != nullptr)
    {
        this->update_entrypoint->Update();
    }
}
