#pragma once
#include <functional>
#include <iostream>

#include "../Editor/ProjectWindows/Assets/element/Model/Asset.h"
#include "../Editor/ProjectWindows/Assets/element/Model/Image/ImageAsset.h"
#include "../managers/ComponentExportParameterManager.h"

namespace assetnamespace = editor::projectwindows::assets::elements::model;
namespace FunctionGenerator
{
    class FunctionGenerator
    {
    public:
        template <class fieldType>
        static std::function<void(std::shared_ptr<assetnamespace::Asset>)> Generate_Switch_Function(fieldType* field) {
            std::function<void(std::shared_ptr<assetnamespace::Asset>)> function
                = [=](std::shared_ptr<assetnamespace::Asset> input)
            {
                fieldType* input_cast_ptr = dynamic_cast<fieldType*>(input.get());
                if (input_cast_ptr != nullptr)
                {
                    *field = *input_cast_ptr;
                }
                else
                {
                    std::cout << "cast failed!! in Field_SwitchFunction" << std::endl;
                }
            };
            return function;
        }
        static std::function<void(std::shared_ptr<assetnamespace::Asset>)> Generate_Switch_Function(editor::projectwindows::assets::elements::model::image::ImageAsset* field) {
            std::function<void(std::shared_ptr<assetnamespace::Asset>)> function
                = [=](std::shared_ptr<assetnamespace::Asset> input)
            {
                editor::projectwindows::assets::elements::model::image::ImageAsset* input_cast_ptr = dynamic_cast<editor::projectwindows::assets::elements::model::image::ImageAsset*>(input.get());
                if (input_cast_ptr != nullptr)
                {
                    *field = *input_cast_ptr;
                }
                else
                {
                    std::cout << "cast failed!! in Field_SwitchFunction" << std::endl;
                }
            };
            return function;
        }
    };
}
