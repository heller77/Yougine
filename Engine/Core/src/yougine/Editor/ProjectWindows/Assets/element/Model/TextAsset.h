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
        TextAsset(std::filesystem::path path, int asset_id);

        void Export() override;
    };
}
