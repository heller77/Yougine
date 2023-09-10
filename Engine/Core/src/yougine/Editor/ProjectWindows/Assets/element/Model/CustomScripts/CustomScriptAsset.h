#pragma once
#include "../Asset.h"

namespace editor::projectwindows::assets::elements::model::customscript
{
    class CustomScriptAsset : public Asset
    {
    private:
        std::string scriptname;
    public:
        CustomScriptAsset(const std::filesystem::path& path,
            const std::shared_ptr<utility::youginuuid::YougineUuid>& uuid)
            : Asset(path, uuid)
        {
        }

        explicit CustomScriptAsset(const std::filesystem::path& assetinfo_file_path)
            : Asset(assetinfo_file_path)
        {
        }

        void Export() override;

        std::string ToString() override;

        void InitializeParameter() override;
    };
}
