#include "Asset.h"

#include <tinygltf/json.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <memory>

editor::projectwindows::assets::elements::model::Asset::Asset(std::filesystem::path path, std::shared_ptr<utility::youginuuid::YougineUuid> uuid)
{
    is_assetinfo_file_exist = false;
    this->path = path;
    this->uuid = uuid;
}

editor::projectwindows::assets::elements::model::Asset::Asset(const std::filesystem::path assetinfo_file_path)
{
    this->assetinfo_filepath = assetinfo_file_path;
    this->is_assetinfo_file_exist = true;

    this->path = assetinfo_file_path.parent_path().string() + "\\" + assetinfo_file_path.stem().string();
    using json = nlohmann::ordered_json;

    // std::ifstream reading(assetinfo_file_path.string(), std::ios::in);
    //
    // json o_json;
    // reading >> o_json;

    this->asset_info = std::make_shared<assetinfos::AssetInfoFile>(assetinfo_file_path);
    if (asset_info->IsContainValue("uuid")) {
        std::string asset_id = asset_info->GetParameter("uuid");
        this->uuid = std::shared_ptr<utility::youginuuid::YougineUuid>(new utility::youginuuid::YougineUuid(asset_id));
    }
    else
    {
        //file not has uuid
        this->uuid = std::shared_ptr<utility::youginuuid::YougineUuid>(new utility::youginuuid::YougineUuid());
    }


}

std::map<std::string, std::shared_ptr<editor::projectwindows::assets::elements::model::assetparameters::Parameter>>
editor::projectwindows::assets::elements::model::Asset::GetParameter()
{
    return this->parameter;
}

std::shared_ptr<utility::youginuuid::YougineUuid> editor::projectwindows::assets::elements::model::Asset::GetAssetId()
{
    return this->uuid;
}

void editor::projectwindows::assets::elements::model::Asset::SwapParameter(std::string parameter_name,
    std::shared_ptr<assetparameters::Parameter> parameter)
{
    bool is_parameter_exist = this->parameter.find(parameter_name) != this->parameter.end();
    if (is_parameter_exist)
    {
        this->parameter[parameter_name] = parameter;
    }
    else
    {
        std::cout << "not exist" << std::endl;
    }
}

// std::function<void(std::shared_ptr<editor::projectwindows::assets::elements::model::Asset>)> editor::projectwindows::
// assets::elements::model::Asset::Generate_Field_SwitchFunction(std::shared_ptr<shader::ShaderFileAsset>& field,
//     std::shared_ptr<inspectorwindows::assetviews::options::AssetViewOption> option, std::string parameter_name)
// {
//     std::function<void(std::shared_ptr<Asset>)> function = [=](std::shared_ptr<Asset> input)
//     {
//         auto input_cast_ptr = std::dynamic_pointer_cast<shader::ShaderFileAsset>(input);
//         std::shared_ptr<shader::ShaderFileAsset> input_cast_shared_ptr = std::shared_ptr<shader::ShaderFileAsset>(input_cast_ptr);
//         std::cout << typeid(field).name() << std::endl;
//         if (input_cast_shared_ptr)
//         {
//             field = input_cast_shared_ptr;
//             // auto parameter = std::make_shared<assetparameters::Parameter>(field->GetAssetId(), option);
//             // SwapParameter(parameter_name, std::make_shared<assetparameters::Parameter>(field->GetAssetId(), option));
//         }
//         else
//         {
//             std::cout << "cast failed!! in Field_SwitchFunction" << std::endl;
//         }
//     };
//     return function;
// }