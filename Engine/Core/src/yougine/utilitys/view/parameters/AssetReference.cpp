#include "AssetReference.h"

#include <string>
#include <vector>

#include "../../../Projects/Project.h"
#include "imgui/imgui.h"

void utility::view::parameters::AssetReference::Draw()
{
    auto assetdatabase = projects::Project::GetInstance()->GetDataBase();
    auto asset_map = assetdatabase->GetAssetList();
    std::vector<std::string> item_vec;
    for (auto pair : asset_map)
    {
        auto asset = pair.second;
        item_vec.emplace_back(asset->ToString());
    }

    std::string combo_preview_value = item_vec[select_index];
    if (ImGui::BeginCombo(label.c_str(), combo_preview_value.c_str()))
    {
        for (int n = 0; n < item_vec.size(); n++)
        {
            const bool is_selected = (select_index == n);
            //選んだ時
            if (ImGui::Selectable(item_vec[n].c_str(), is_selected)) {
                select_index = n;
            }
            if (is_selected) {
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }
}

utility::view::parameters::AssetReference::AssetReference(std::string label)
{
    this->label = label;
    this->select_index = 0;
}
