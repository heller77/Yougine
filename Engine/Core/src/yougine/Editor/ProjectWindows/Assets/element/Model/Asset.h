#pragma once

#include <filesystem>
#include <iostream>
#include <map>
#include <memory>
#include <string>

#include "AssetInfos/AssetInfoFile.h"
#include "UserShare/utilitys/uuid/YougineUuid.h"
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
        std::filesystem::path assetinfo_filepath;
        bool is_assetinfo_file_exist;
        std::shared_ptr<utility::youginuuid::YougineUuid> uuid;
        std::shared_ptr<assetinfos::AssetInfoFile> asset_info;
    public:
        Asset(std::filesystem::path path, std::shared_ptr<utility::youginuuid::YougineUuid> uuid);
        Asset(const std::filesystem::path assetinfo_file_path);
        std::map<std::string, std::shared_ptr<assetparameters::Parameter>> GetParameter();
        virtual void Export() = 0;
        std::shared_ptr<utility::youginuuid::YougineUuid> GetAssetId();

        void SwapParameter(std::string parameter_name, std::shared_ptr<assetparameters::Parameter> parameter);

        // template <class fieldType>
        // std::function<void(std::shared_ptr<Asset>)> Generate_Field_SwitchFunction(
        //     fieldType& field, std::shared_ptr<inspectorwindows::assetviews::options::AssetViewOption> option, std::string parameter_name);
        //
        // std::function<void(std::shared_ptr<Asset>)> Generate_Field_SwitchFunction(std::shared_ptr<shader::ShaderFileAsset>& field,
        //     std::shared_ptr<inspectorwindows::assetviews::options::AssetViewOption> option, std::string parameter_name);
        /**
        * \brief
        * \tparam fieldType Assetのサブクラス
        * \param field
        * \param option
        * \param parameter_name
        * \return
        */
        template <class fieldType>
        std::function<void(std::shared_ptr<Asset>)> Generate_Field_SwitchFunction_Template(std::shared_ptr<fieldType>* field,
            std::shared_ptr<inspectorwindows::assetviews::options::AssetViewOption> option, std::string parameter_name) {
            std::function<void(std::shared_ptr<Asset>)> function = [=](std::shared_ptr<Asset> input)
            {
                std::shared_ptr<fieldType> input_cast_ptr = std::dynamic_pointer_cast<fieldType>(input);
                // std::shared_ptr<fieldType> input_cast_shared_ptr = std::shared_ptr<fieldType>(input_cast_ptr);
                // std::cout << typeid(field).name() << std::endl;
                if (input_cast_ptr)
                {
                    *field = input_cast_ptr;
                    auto parameter = std::make_shared<assetparameters::Parameter>((*field)->GetAssetId(), option);
                    SwapParameter(parameter_name, std::make_shared<assetparameters::Parameter>((*field)->GetAssetId(), option));
                }
                else
                {
                    std::cout << "cast failed!! in Field_SwitchFunction" << std::endl;
                }
            };
            return function;
        }

        virtual std::string ToString() = 0;
        virtual void InitializeParameter() = 0;

    };

}
