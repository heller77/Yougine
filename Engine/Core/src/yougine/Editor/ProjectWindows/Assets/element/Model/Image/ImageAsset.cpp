#include "ImageAsset.h"
#include "tinygltf/stb_image.h"

void editor::projectwindows::assets::elements::model::image::ImageAsset::Export()
{

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
    int width, height, channels;
    image = stbi_load(assetfile.string().c_str(), &width, &height, &channels, 0);
    if (image == nullptr) {
        std::cerr << "Error: Image could not be loaded." << std::endl;
    }
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
