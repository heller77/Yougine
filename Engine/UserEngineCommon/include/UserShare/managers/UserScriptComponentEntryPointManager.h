#pragma once
#include <functional>
namespace yougine::managers
{
    class UserScriptComponentEntryPointManager
    {
    private:
        std::vector<std::function<void(void)>> updateMethods;
    public:
        UserScriptComponentEntryPointManager();

        void AddUpdate(std::function<void(void)> method);
        void Update();

    };
}
