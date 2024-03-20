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

        /**
         * \brief update関数を追加する
         * \param method
         */
        void AddUpdate(std::function<void(void)> method);

        /**
         * \brief updateを実行する（ユーザは呼ばないで！）
         */
        void Update();

    };
}
