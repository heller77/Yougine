#pragma once
#include "Asset.h"}
#include <string>
namespace editor::projectwindows::assets::elements::model
{
    class TextAsset :public Asset
    {
    private:
        std::string text;


    public:
        TextAsset(std::filesystem::path path, std::shared_ptr<utility::youginuuid::YougineUuid> uuid);
        TextAsset(std::filesystem::path assetinfofile_path);
        void Export() override;

        std::string ToString() override;
    };
}
