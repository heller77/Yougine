#include "AssetReference.h"

#include <iostream>
#include <string>
#include <vector>

#include "../../../Projects/Project.h"
#include "imgui/imgui.h"

void utility::view::parameters::AssetReference::Draw()
{
    auto assetdatabase = projects::Project::GetInstance()->GetDataBase();

    std::string combo_preview_value = id_names[select_index].GetName();
    if (ImGui::BeginCombo(label.c_str(), combo_preview_value.c_str()))
    {
        for (int n = 0; n < id_names.size(); n++)
        {

            const bool is_selected = (select_index == n);
            auto asset = assetdatabase->GetAsset(id_names[n].GetId());
            std::filesystem::path filename = asset->GetFilePath();
            auto filename_extension = filename.extension();
            if (filename.extension() != this->extension && extension != "")
            {
                continue;
            }

            //選んだ時
            if (ImGui::Selectable(id_names[n].GetName().c_str(), is_selected)) {
                std::cout << n << " " << id_names[n].GetId() << std::endl;
                if (asset_set_func) {
                    asset_set_func(assetdatabase->GetAsset(id_names[n].GetId()));
                }
                select_index = n;
            }
            if (is_selected) {
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }
}

utility::view::parameters::AssetReference::AssetReference(std::string label, std::shared_ptr<utility::youginuuid::YougineUuid> yougine_uuid, std::filesystem::path extension, std::function<void(std::shared_ptr<editor::projectwindows::assets::elements::model::Asset>)> asset_set_func)
{
    this->label = label;

    this->extension = extension;

    auto assetdatabase = projects::Project::GetInstance()->GetDataBase();
    const auto asset_map = assetdatabase->GetAssetList();
    // std::vector<std::string> item_vec;
    // std::vector<id_name> id_names;
    bool find = false;
    int i = 0;
    for (auto pair : asset_map)
    {
        auto asset = pair.second;
        // item_vec.emplace_back(asset->ToString());
        auto id_string = asset->GetAssetId()->convertstring();
        id_name idname = { id_string, asset->ToString() };
        if (id_string == yougine_uuid->convertstring())
        {
            find = true;
            select_index = i;
        }
        id_names.emplace_back(idname);
        i++;
    }

    if (!find)
    {
        select_index = 0;
    }

    auto now = asset_map.find(yougine_uuid->convertstring());
    this->asset_set_func = asset_set_func;

}
