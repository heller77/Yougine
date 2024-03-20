#include "Material.h"

#include <iostream>
#include <memory>
#include <tinygltf/json.hpp>
#include <fstream>
#include <memory>

#include "../../../../../../Projects/Project.h"
#include "../AssetInfoExporter/AssetInfoFileExporter.h"
using option_type = editor::inspectorwindows::assetviews::options::AssetViewOption;
void editor::projectwindows::assets::elements::model::materials::Material::Initialize()
{
    auto onlydisplay_option = std::make_shared<option_type>(false, true);
    this->parameter["path"] = std::make_shared<assetparameters::Parameter>(this->path.string(), onlydisplay_option);
    this->parameter[GETVALUENAME(uuid)] = std::make_shared<assetparameters::Parameter>(uuid->convertstring(), onlydisplay_option);

    auto fragment_assetoption = std::make_shared<option_type>(false, false, true);
    // auto fragassetset_function
    //     = this->Generate_Field_SwitchFunction(&frag_asset_uuid, fragment_assetoption,
    //         GETVALUENAME(frag_asset_uuid));
    auto fragassetset_function
        = this->Generate_Field_SwitchFunction_Template<shader::ShaderFileAsset>(&frag_asset_uuid, fragment_assetoption,
            GETVALUENAME(frag_asset_uuid));
    fragment_assetoption->SetInputAction(fragassetset_function);
    // fragment_assetoption->SetInputAction([&, fragment_assetoption](std::shared_ptr<editor::projectwindows::assets::elements::model::Asset> input)
    //     {
    //         std::cout << "input tostring " << input->ToString() << std::endl;
    //         std::shared_ptr<shader::ShaderFileAsset> input_asset;
    //         input_asset = std::dynamic_pointer_cast<shader::ShaderFileAsset>(input);
    //
    //         if (input_asset) {
    //             // this->frag_asset_uuid = input_asset;
    //             InputInject(this->frag_asset_uuid, input_asset);
    //             auto parameter = std::make_shared<assetparameters::Parameter>(frag_asset_uuid->GetAssetId(), fragment_assetoption);
    //             this->SwapParameter(GETVALUENAME(frag_asset_uuid), std::make_shared<assetparameters::Parameter>(frag_asset_uuid->GetAssetId(), fragment_assetoption));
    //         }
    //     });
    this->parameter[GETVALUENAME(frag_asset_uuid)] = std::make_shared<assetparameters::Parameter>(frag_asset_uuid->GetAssetId(), fragment_assetoption);

    auto vertex_assetoption = std::make_shared<option_type>(false, false, true);
    auto vert_function
        = this->Generate_Field_SwitchFunction(&vert_asset_uuid, vertex_assetoption,
            GETVALUENAME(vert_asset_uuid));

    vertex_assetoption->SetInputAction(vert_function);

    this->parameter[GETVALUENAME(vert_asset_uuid)] = std::make_shared<assetparameters::Parameter>(vert_asset_uuid->GetAssetId(), vertex_assetoption);

    auto shaderinputs_assetoption = std::make_shared<option_type>(false, false, false);
    auto f = std::make_shared <shaderinputparameters::ShaderInputAndTypeStruct>(ShaderInputParameterType::kFloat, "c", 3.0f);
    shader_input_parameters.emplace_back(f);
    auto f2 = std::make_shared <shaderinputparameters::ShaderInputAndTypeStruct>(ShaderInputParameterType::kInt, "sample_int", 45);
    shader_input_parameters.emplace_back(f2);
    auto ve3_color = std::make_shared<shaderinputparameters::ShaderInputAndTypeStruct>(ShaderInputParameterType::kVec3, "color_vec3", utility::Vector3(1, 1, 1));
    shader_input_parameters.emplace_back(ve3_color);
    this->parameter[GETVALUENAME(shader_input_parameters)] = std::make_shared<assetparameters::Parameter>(shader_input_parameters, shaderinputs_assetoption);;
}


editor::projectwindows::assets::elements::model::materials::Material::Material(const std::filesystem::path& path,
    const std::shared_ptr<utility::youginuuid::YougineUuid>& uuid) :Asset(path, uuid)
{
}
editor::projectwindows::assets::elements::model::materials::Material::Material(
    const std::filesystem::path& assetinfo_file_path) : Asset(assetinfo_file_path)
{
}

void editor::projectwindows::assets::elements::model::materials::Material::InitializeParameter()
{
    //assetinfoファイルある場合
    if (is_assetinfo_file_exist)
    {
        using json = nlohmann::ordered_json;

        std::ifstream reading(assetinfo_filepath.string(), std::ios::in);

        json o_json;
        reading >> o_json;

        std::string vertname = GETVALUENAME(vert_asset_uuid);
        if (o_json.contains(vertname)) {
            std::string asset_id = o_json[vertname];
            this->vert_asset_uuid = std::dynamic_pointer_cast<shader::ShaderFileAsset>(projects::Project::GetInstance()->GetDataBase()->GetAsset(asset_id));
        }
        else
        {
            vert_asset_uuid = shader::ShaderFileAsset::GetDefaultVertexShader();
        }

        std::string fragname = GETVALUENAME(frag_asset_uuid);
        if (o_json.contains(fragname)) {
            std::string asset_id = o_json[fragname];
            this->frag_asset_uuid = std::dynamic_pointer_cast<shader::ShaderFileAsset>(projects::Project::GetInstance()->GetDataBase()->GetAsset(asset_id));
        }
        else
        {
            frag_asset_uuid = shader::ShaderFileAsset::GetDefaultFragmentShader();
        }
    }
    else
    {
        frag_asset_uuid = shader::ShaderFileAsset::GetDefaultFragmentShader();
        vert_asset_uuid = shader::ShaderFileAsset::GetDefaultVertexShader();
    }
    Initialize();
}

// void editor::projectwindows::assets::elements::model::materials::Material::SwapParameter(std::string parameter_name, std::shared_ptr<assetparameters::Parameter> parameter)
// {
//     bool is_parameter_exist = this->parameter.find(parameter_name) != this->parameter.end();
//     if (is_parameter_exist)
//     {
//         this->parameter[parameter_name] = parameter;
//     }
//     else
//     {
//         std::cout << "not exist" << std::endl;
//     }
//
// }

void editor::projectwindows::assets::elements::model::materials::Material::Export()
{
    nlohmann::json json;
    json[GETVALUENAME(uuid)] = uuid->convertstring();
    if (vert_asset_uuid && frag_asset_uuid) {
        json[GETVALUENAME(vert_asset_uuid)] = vert_asset_uuid->GetAssetId()->convertstring();
        json[GETVALUENAME(frag_asset_uuid)] = frag_asset_uuid->GetAssetId()->convertstring();
    }

    auto exporter = std::make_shared<assetinfos::AssetInfoFileExporter>();
    exporter->ExportAssetInfoFile(this->path, json);

}

void editor::projectwindows::assets::elements::model::materials::Material::InputInject(
    std::shared_ptr<shader::ShaderFileAsset>& inputed, std::shared_ptr<shader::ShaderFileAsset>& new_value)
{
    inputed = new_value;
}

std::string editor::projectwindows::assets::elements::model::materials::Material::ToString()
{
    return this->path.filename().string() + "(Material)";
}

std::function<void(std::shared_ptr<editor::projectwindows::assets::elements::model::Asset>)> editor::projectwindows::
assets::elements::model::materials::Material::Generate_Field_SwitchFunction(
    std::shared_ptr<shader::ShaderFileAsset>* field,
    std::shared_ptr<inspectorwindows::assetviews::options::AssetViewOption> option, std::string parameter_name)
{
    std::function<void(std::shared_ptr<Asset>)> function = [=](std::shared_ptr<Asset> input)
    {
        auto input_cast_ptr = std::dynamic_pointer_cast<shader::ShaderFileAsset>(input);
        // std::shared_ptr<shader::ShaderFileAsset> input_cast_shared_ptr = std::shared_ptr<shader::ShaderFileAsset>(input_cast_ptr);
        // std::cout << typeid(field).name() << std::endl;
        if (input_cast_ptr)
        {
            std::cout << this->frag_asset_uuid->GetAssetId()->convertstring() << std::endl;
            *field = input_cast_ptr;
            auto parameter = std::make_shared<assetparameters::Parameter>((*field)->GetAssetId(), option);
            SwapParameter(parameter_name, std::make_shared<assetparameters::Parameter>((*field)->GetAssetId(), option));
            std::cout << this->frag_asset_uuid->GetAssetId()->convertstring() << std::endl;
        }
        else
        {
            std::cout << "cast failed!! in Field_SwitchFunction" << std::endl;
        }
    };
    return function;
}

std::shared_ptr<editor::projectwindows::assets::elements::model::shader::ShaderFileAsset> editor::projectwindows::assets
::elements::model::materials::Material::GetVertexShader()
{
    return this->vert_asset_uuid;
}

std::shared_ptr<editor::projectwindows::assets::elements::model::shader::ShaderFileAsset> editor::projectwindows::assets
::elements::model::materials::Material::GetFragmentShader()
{
    return this->frag_asset_uuid;
}

std::vector<std::shared_ptr<editor::projectwindows::assets::elements::model::materials::shaderinputparameters::
    ShaderInputAndTypeStruct>> editor::projectwindows::assets::elements::model::materials::Material::GetShaderInputs()
{
    return this->shader_input_parameters;
}
