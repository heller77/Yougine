#pragma once
#include <any>
#include <map>
#include <memory>
#include <string>

#include "../../../../InspectorWindows/AssetView/Option/AssetViewOption.h"
#include "AssetParameter/Parameter.h"

namespace editor::projectwindows::assets::elements::model
{


    /**
     * \brief アセットを表す
     */
    class Asset
    {
    protected:
        std::map<std::string, std::shared_ptr<assetparameters::Parameter>> parameter;
    private:
        std::string filepath;
    public:
        Asset();
        std::map<std::string, std::shared_ptr<assetparameters::Parameter>> GetParameter();
    };
}
