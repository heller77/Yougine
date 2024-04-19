#pragma once
#include <GL/glew.h>

#include "../Asset.h"

namespace editor::projectwindows::assets::elements::model::image
{
    class ImageAsset : public Asset
    {
    public:
        void Export() override;

        std::string ToString() override;

        void InitializeParameter() override;

    private:
        unsigned char* image;
        GLuint textureID;
        void Initialize();
    public:
        ImageAsset(std::filesystem::path path, std::shared_ptr<utility::youginuuid::YougineUuid> uuid);
        ImageAsset(std::filesystem::path assetinfofile_path);

        /**
         * \brief 画像のバッファへのポインターを取得
         * \return
         */
        unsigned char* GetImagePtr();
        GLuint GetGLImage();
    };
}
