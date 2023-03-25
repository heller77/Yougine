#pragma once
#include <memory>
#include <string>

#include "ParameterView.h"
#include "../../../Editor/ProjectWindows/Assets/element/Model/Asset.h"

namespace utility::view::parameters
{
    struct id_name
    {
    private:
        std::string id;
        std::string name;
    public:
        id_name(const std::string& id, const std::string& name)
            : id(id),
            name(name)
        {
        }

        std::string GetId() { return this->id; }

        std::string GetName() { return this->name; }
    };
    class AssetReference : public ParameterView
    {
    private:
        std::string label;
        // std::string select_id;
        int select_index;
        std::vector<id_name> id_names;
        std::function<void(std::shared_ptr<editor::projectwindows::assets::elements::model::Asset>)> asset_set_func;
    public:
        void Draw() override;
        AssetReference(std::string label, std::shared_ptr<utility::youginuuid::YougineUuid> yougine_uuid, std::function<void(std::shared_ptr<editor::projectwindows::assets::elements::model::Asset>)> asset_set_func);
    };
}
