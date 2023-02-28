﻿#include "ProjectWindow.h"
#include <filesystem>

#include "../../Projects/Project.h"
#include "Assets/element/DefaultFileElementOfProjectView.h"
#include "Assets/element/FolderElementOfProjectView.h"

editor::projectwindows::ProjectWindow::ProjectWindow(editor::EditorWindowsManager* editor_windows_manager,
    yougine::Scene* scene)
    : EditorWindow(editor_windows_manager, editor::EditorWindowName::ProjectWindow)
{
    now_display_folderpath = projects::Project::GetInstance()->projectFolderPath;
    CreateView(now_display_folderpath);
}

void editor::projectwindows::ProjectWindow::ChangeDisplayPath(std::string path)
{
}

/**
 * \brief viewで必要なelementをassetvies_vectorに追加
 * \param now_display_path
 */
void editor::projectwindows::ProjectWindow::CreateView(std::string now_display_path)
{
    //空にする
    assetvies_vector.clear();
    ImVec2 button_size(140, 40);
    // auto folderelement
    //     = std::shared_ptr<Assets::elements::FolderElementOfProjectView>(
    //         new Assets::elements::FolderElementOfProjectView("folder", button_size));

    // assetvies_vector.emplace_back(folderelement);

    auto file_and_folder_list = std::filesystem::directory_iterator(now_display_path);
    //今いる場所のファイルとフォルダを表示
    for (const auto& file : file_and_folder_list)
    {
        auto is_directory = file.is_directory();
        std::string filename = file.path().filename().string();

        //フォルダなら
        if (is_directory)
        {
            auto folderelement
                = std::shared_ptr<Assets::elements::FolderElementOfProjectView>(
                    new Assets::elements::FolderElementOfProjectView(filename, button_size));
            assetvies_vector.emplace_back(folderelement);
        }
        else
        {
            //ファイル拡張子
            std::string extension = file.path().extension().string().replace(0, 1, "");
            //フォルダ以外
            std::cout << "extension " << extension << std::endl;
            if (extension == "cpp")
            {
            }
            else
            {
                std::shared_ptr<Assets::elements::DefaultFileElementOfProjectView> defaultfile
                    = std::shared_ptr<Assets::elements::DefaultFileElementOfProjectView>(new Assets::elements::DefaultFileElementOfProjectView(filename, button_size));
                assetvies_vector.emplace_back(defaultfile);
            }
        }
    }
}

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

    for (auto element_of_project_view : this->assetvies_vector)
    {
        element_of_project_view->DrawElement();
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

    //今いる場所のファイルとフォルダを表示
    // for (const auto& file : file_and_folder_list)
    // {
    //     auto is_directory = file.is_directory();
    //     std::string filename = file.path().filename().string();
    //     float hue = 0.1;
    //     //フォルダなら
    //     if (is_directory)
    //     {
    //         ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(hue, 0.6f, 0.6f));
    //         ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(hue, 0.7f, 0.7f));
    //         ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(hue, 0.8f, 0.8f));
    //         if (ImGui::Button(filename.c_str(), button_size))
    //         {
    //             this->now_display_folderpath += "/" + filename;
    //         }
    //
    //         ImGui::PopStyleColor(3);
    //     }
    //     else
    //     {
    //         //フォルダ以外
    //         ImGui::Button(filename.c_str(), button_size);
    //     }
    //     //ウィンドサイズに合わせて改行したりしなかったり
    //     float window_visible_width_worldspace = ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;
    //     float lastbutton_x = ImGui::GetItemRectMax().x;
    //
    //     float next_button_x = lastbutton_x + style.ItemSpacing.x + button_size.x;
    //     //次のボタンがウィンドーの表示領域をこえているか
    //     if (next_button_x < window_visible_width_worldspace)
    //     {
    //         ImGui::SameLine();
    //     }
    // }

    ImGui::End();
}
