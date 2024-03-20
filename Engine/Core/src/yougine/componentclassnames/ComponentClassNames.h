#pragma once
#include <memory>
#include <vector>
#include <string>

namespace ComponentClassNames
{
    class ComponentClassNames
    {
    private:
        std::vector<std::string> componentClassNames;
        static std::shared_ptr<ComponentClassNames> instance;
    public:
        ComponentClassNames();

        static std::shared_ptr<ComponentClassNames> GetInstance();
        /**
         * \brief コンポーネントの名前を追加
         * \param componentName 名前空間まで含む(ex : "yougine::components::TransformComponent")
         * \return 追加出来たかどうか（成功ならtrue）
         */
        bool AddComponentName(std::string componentName);
        std::vector<std::string> GetComponentClassNames();
        void AddUserScriptNames();
    };
}
