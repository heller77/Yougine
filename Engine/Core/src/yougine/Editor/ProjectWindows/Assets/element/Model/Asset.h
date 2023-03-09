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
    protected:
        std::map<std::string, std::any> parameter;
    private:
        std::string filepath;
    public:
        Asset();
        std::map<std::string, std::any> GetParameter();
    };
}
