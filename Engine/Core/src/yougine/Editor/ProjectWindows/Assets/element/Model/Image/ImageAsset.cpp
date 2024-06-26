﻿#include "ImageAsset.h"

#include <GL/glew.h>

#include "../../../../../../managers/RenderManager.h"
#include "../AssetInfos/AssetInfoFileExporter.h"
#include "tinygltf/stb_image.h"

void editor::projectwindows::assets::elements::model::image::ImageAsset::Export()
{
    nlohmann::json json;
    json[GETVALUENAME(uuid)] = uuid->convertstring();

    auto exporter = std::make_shared<assetinfos::AssetInfoFileExporter>();
    exporter->ExportAssetInfoFile(this->path, json);
}

std::string editor::projectwindows::assets::elements::model::image::ImageAsset::ToString()
{
    return this->path.filename().string() + "(ImageAsset)";
}

void editor::projectwindows::assets::elements::model::image::ImageAsset::InitializeParameter()
{

}

void editor::projectwindows::assets::elements::model::image::ImageAsset::Initialize()
{

    auto assetfile = this->GetFilePath();

    std::cout << "texture  : " << assetfile.string() << std::endl;

    int width, height, channels;
    image = stbi_load(assetfile.string().c_str(), &width, &height, &channels, 0);
    if (image == nullptr) {
        std::cerr << "Error: Image could not be loaded." << std::endl;
    }
    yougine::managers::RenderManager::geterror("pre image glgentexture(so context is not good ?)");
    textureID = -1;
    // テクスチャオブジェクトの生成
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    std::cout << "texture id : " << textureID << std::endl;
    yougine::managers::RenderManager::geterror("image asset initialize[glGenTextures glBindTexture] , textureid : ");


    // テクスチャパラメータの設定
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    yougine::managers::RenderManager::geterror("image asset initialize[glTexParameteri ]");
    std::cout << "texparameter -- " << std::endl;
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    // テクスチャへ画像データをgpuにアップロード
    if (channels == 4) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    }
    else {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    }
    yougine::managers::RenderManager::geterror("image asset initialize[glTexImage2D ]");

    // cpu側のメモリを解放
    stbi_image_free(image);

    glBindTexture(GL_TEXTURE_2D, 0);
    yougine::managers::RenderManager::geterror("image asset initialize glBindTexture");
}

editor::projectwindows::assets::elements::model::image::ImageAsset::ImageAsset(std::filesystem::path path,
    std::shared_ptr<utility::youginuuid::YougineUuid> uuid) : Asset(path, uuid)
{
    Initialize();
}

editor::projectwindows::assets::elements::model::image::ImageAsset::ImageAsset(std::filesystem::path assetinfofile_path) :
    Asset(assetinfofile_path)
{
    Initialize();
}

unsigned char* editor::projectwindows::assets::elements::model::image::ImageAsset::GetImagePtr()
{
    return this->image;
}

GLuint editor::projectwindows::assets::elements::model::image::ImageAsset::GetGLImage()
{
    return this->textureID;
}
