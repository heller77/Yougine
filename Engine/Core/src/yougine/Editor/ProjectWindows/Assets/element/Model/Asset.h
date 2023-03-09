#pragma once
#include <any>
#include <map>
#include <string>

namespace editor::projectwindows::assets::elements::model
{
    /**
     * \brief アセットを表す
     */
    class Asset
    {
    private:
        std::map<std::string, std::any> parameter;
        std::string filepath;
    public:
        Asset();
        std::map<std::string, std::any> GetParameter();
    };
}
