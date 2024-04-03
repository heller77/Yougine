#pragma once
#include <functional>

#include "UserShare/components/userscriptcomponents/IUpdatable.h"

namespace yougine::managers
{
    class UserScriptComponentEntryPointManager
    {
    private:
        components::userscriptcomponents::IUpdatable* update_entrypoint;
    public:
        UserScriptComponentEntryPointManager();

        /**
         * \brief update関数を追加する
         * \param method
         */
        void SetUpdate(components::userscriptcomponents::IUpdatable* i_updatable);

        /**
         * \brief updateを実行する（ユーザは呼ばないで！）
         */
        void Update();

    };
}
