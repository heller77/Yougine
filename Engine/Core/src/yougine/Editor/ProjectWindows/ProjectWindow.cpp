#include "ProjectWindow.h"
#include <filesystem>

#include "../../Projects/Project.h"

void editor::projectwindows::ProjectWindow::Draw()
{
    auto style = ImGui::GetStyle();
    // style.ScaleAllSizes(2);
    //表示するファイルパス
    std::string path = this->now_display_folderpath;
    ImGui::Begin(editor_windows_manager->GetWindowName(window_name).c_str());
    auto file_and_folder_list = std::filesystem::directory_iterator(path);

    //表示するパスを上げる
    if (ImGui::Button("up"))
    {
        auto parent = std::filesystem::path(path).parent_path();
        std::cout << "parent path : " << parent << std::endl;
        this->now_display_folderpath = parent.string();
    }
    ImGui::SameLine();
    ImGui::Text(path.c_str());
    ImGui::Separator();

    ImVec2 button_size(140, 40);
    //今いる場所のファイルとフォルダを表示
    for (const auto& file : file_and_folder_list)
    {
        auto is_directory = file.is_directory();
        std::string filename = file.path().filename().string();
        float hue = 0.1;
        //フォルダなら
        if (is_directory)
        {
            ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(hue, 0.6f, 0.6f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(hue, 0.7f, 0.7f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(hue, 0.8f, 0.8f));
            if (ImGui::Button(filename.c_str(), button_size))
            {
                this->now_display_folderpath += "/" + filename;
            }

            ImGui::PopStyleColor(3);
        }
        else
        {
            //フォルダ以外
            ImGui::Button(filename.c_str(), button_size);
        }
        //ウィンドサイズに合わせて改行したりしなかったり
        float window_visible_width_worldspace = ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;
        float lastbutton_x = ImGui::GetItemRectMax().x;

        float next_button_x = lastbutton_x + style.ItemSpacing.x + button_size.x;
        //次のボタンがウィンドーの表示領域をこえているか
        if (next_button_x < window_visible_width_worldspace)
        {
            ImGui::SameLine();
        }
    }

    ImGui::End();
}
