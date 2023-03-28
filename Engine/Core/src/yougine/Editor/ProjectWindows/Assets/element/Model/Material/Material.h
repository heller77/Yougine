#pragma once
#include "../shader/ShaderFileAsset.h"
#include "ShaderInputParameters/ShaderInputAndTypeStruct.h"

namespace editor::projectwindows::assets::elements::model::materials
{
    class Material : public Asset
    {
    private:
        std::shared_ptr<shader::ShaderFileAsset> vert_asset_uuid;

        std::shared_ptr<shader::ShaderFileAsset> frag_asset_uuid;

        std::vector<std::shared_ptr<shaderinputparameters::ShaderInputAndTypeStruct>> shader_input_parameters;

        void Initialize();

    public:
        Material(const std::filesystem::path& path, const std::shared_ptr<utility::youginuuid::YougineUuid>& uuid);

        Material(const std::filesystem::path& assetinfo_file_path);

        void InitializeParameter() override;

        // void SwapParameter(std::string parameter_name, std::shared_ptr<assetparameters::Parameter> parameter);
        void Export() override;

        void InputInject(std::shared_ptr<shader::ShaderFileAsset>& inputed,
            std::shared_ptr<shader::ShaderFileAsset>& new_value);

        std::string ToString() override;

        std::function<void(std::shared_ptr<Asset>)> Generate_Field_SwitchFunction(
            std::shared_ptr<shader::ShaderFileAsset>* field,
            std::shared_ptr<inspectorwindows::assetviews::options::AssetViewOption> option, std::string parameter_name);
    };
}
