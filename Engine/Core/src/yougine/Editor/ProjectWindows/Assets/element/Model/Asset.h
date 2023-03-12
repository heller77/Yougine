#pragma once

#include <filesystem>
#include <map>
#include <memory>
#include <string>

#include "AssetParameter/Parameter.h"


namespace editor::projectwindows::assets::elements::model
{

#define GETVALUENAME(name) (#name)
    /**
     * \brief アセットを表す
     */
    class Asset
    {
    protected:
        std::map<std::string, std::shared_ptr<assetparameters::Parameter>> parameter;
        std::filesystem::path path;
        unsigned int asset_id;
    public:
        Asset(std::filesystem::path path, int asset_id);
        std::map<std::string, std::shared_ptr<assetparameters::Parameter>> GetParameter();
        virtual void Export() = 0;

    };
}
