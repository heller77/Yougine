#include "ProjectWindow.h"
#include <filesystem>
#include <memory>
#include <memory>
#include <memory>
#include <memory>
#include <tinygltf/json.hpp>
#include <fstream>
#include <memory>

#include "../../Projects/Project.h"
#include "Assets/element/Model/TextAsset.h"
#include "Assets/element/Model/Material/Material.h"
#include "Assets/element/Model/shader/ShaderFileAsset.h"
#include "Assets/element/view/DefaultFileElementOfProjectView.h"
#include "Assets/element/view/FolderElementOfProjectView.h"

#include "../SelectionInfo.h"

editor::projectwindows::ProjectWindow::ProjectWindow(editor::EditorWindowsManager* editor_windows_manager,
    yougine::Scene* scene)
    : EditorWindow(editor_windows_manager, editor::EditorWindowName::ProjectWindow)
{
    now_display_folderpath = projects::Project::GetInstance()->GetUserFolderPath().string();
    auto lastchar = now_display_folderpath[now_display_folderpath.size() - 1];
    if (lastchar == '/') {
        now_display_folderpath.pop_back();
    }

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
        std::filesystem::path path = file.path();


        std::filesystem::path assetinfo_path = path.string() + ".assetinfo";

        using json = nlohmann::ordered_json;

        //フォルダなら
        if (is_directory)
        {
            auto folderelement
                = std::shared_ptr<assets::elements::view::FolderElementOfProjectView>(
                    new assets::elements::view::FolderElementOfProjectView(filename, button_size));
            folderelement->SetSelectEvent(
                [=]()
                {
                    //フォルダーを一個下に移動
                    this->now_display_folderpath += "/" + folderelement->GetFolderName();
                    //ビューを更新
                    this->UpdateNextFrame();
                }
            );
            assetvies_vector.emplace_back(folderelement);
        }
        else
        {
            //ファイル拡張子
            std::string extension = file.path().extension().string().replace(0, 1, "");
            if (!std::filesystem::exists(std::filesystem::status(assetinfo_path)))
            {
                if (extension != "assetinfo") {
                    auto defaultfile
                        = std::make_shared<assets::elements::view::DefaultFileElementOfProjectView>(filename, button_size, nullptr);
                    assetvies_vector.emplace_back(defaultfile);
                }
                continue;
            }
            std::ifstream reading(assetinfo_path.string(), std::ios::in);
            json o_json;
            reading >> o_json;

            std::string asset_id = o_json["uuid"];
            auto uuid = std::shared_ptr<utility::youginuuid::YougineUuid>(new utility::youginuuid::YougineUuid(asset_id));


            //フォルダ以外
            std::cout << "extension " << extension << std::endl;
            if (extension == "cpp")
            {
            }
            else if (extension == "shader" || extension == "frag" || extension == "vert") {
                // auto shaderasset = std::make_shared<assets::elements::model::shader::ShaderFileAsset>(path, 0);
                auto shaderasset = projects::Project::GetInstance()->GetDataBase()->GetAsset(uuid->convertstring());
                auto button
                    = std::make_shared<assets::elements::view::DefaultFileElementOfProjectView>(filename, button_size, shaderasset);
                assetvies_vector.emplace_back(button);
                button->SetSelectEvent([=]()
                    {
                        SelectionInfo::GetInstance()->SetSelctionInfo(button);
                    });
            }
            else if (extension == "mat")
            {
                auto shaderasset = projects::Project::GetInstance()->GetDataBase()->GetAsset(uuid->convertstring());
                auto button
                    = std::make_shared<assets::elements::view::DefaultFileElementOfProjectView>(filename, button_size, shaderasset);
                assetvies_vector.emplace_back(button);
                button->SetSelectEvent([=]()
                    {
                        SelectionInfo::GetInstance()->SetSelctionInfo(button);
                    });

            }
            else if (extension == "h")
            {
                auto cppAsset = projects::Project::GetInstance()->GetDataBase()->GetAsset(uuid->convertstring());
                auto button
                    = std::make_shared<assets::elements::view::DefaultFileElementOfProjectView>(filename, button_size, cppAsset);
                assetvies_vector.emplace_back(button);
                button->SetSelectEvent([=]()
                    {
                        SelectionInfo::GetInstance()->SetSelctionInfo(button);
                    });
            }
            else if (extension == "png" || extension == "jpeg")
            {
                auto imageasset = projects::Project::GetInstance()->GetDataBase()->GetAsset(uuid->convertstring());
                auto button
                    = std::make_shared<assets::elements::view::DefaultFileElementOfProjectView>(filename, button_size, imageasset);
                assetvies_vector.emplace_back(button);
                button->SetSelectEvent([=]()
                    {
                        SelectionInfo::GetInstance()->SetSelctionInfo(button);
                    });
            }
            else
            {
                //アセット生成
                // auto asset = std::make_shared<assets::elements::model::TextAsset>(path, 0);
                auto asset = projects::Project::GetInstance()->GetDataBase()->GetAsset(uuid->convertstring());
                auto defaultfile
                    = std::make_shared<assets::elements::view::DefaultFileElementOfProjectView>(filename, button_size, asset);
                assetvies_vector.emplace_back(defaultfile);
                //クリックされたらSelectionInfoにボタンの参照をセットする
                defaultfile->SetSelectEvent([=]()
                    {
                        SelectionInfo::GetInstance()->SetSelctionInfo(defaultfile);
                    });

            }
        }
    }
}

void editor::projectwindows::ProjectWindow::UpdateNextFrame()
{
    is_updateelements_flag = true;
}

void editor::projectwindows::ProjectWindow::Draw()
{
    if (is_updateelements_flag)
    {
        this->CreateView(this->now_display_folderpath);
        is_updateelements_flag = false;
    }


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
        //プロジェクトのパスより上だったら上がらない
        auto projectpath = projects::Project::GetInstance()->GetUserFolderPath();
        auto relativePath = parent.lexically_relative(projectpath);
        bool isupper_fromProjectpath = false;
        for (const auto& part : relativePath)
        {
            if (part == "..") {
                // ".."が見つかった場合、基準パスより上にある
                isupper_fromProjectpath = true;
                break;
            }
        }

        if (!isupper_fromProjectpath)
        {
            std::cout << "parent path : " << parent << std::endl;

            this->now_display_folderpath = parent.string();
            UpdateNextFrame();
        }
    }
    ImGui::SameLine();
    ImGui::Text(path.c_str());
    ImGui::SameLine();

    //アセットをリロードするボタン。
    if (ImGui::Button("AssetReload"))
    {
        projects::Project::GetInstance()->AssetInitialize();
        CreateView(this->now_display_folderpath);
    }

    ImGui::Separator();

    ImVec2 button_size(140, 40);



    // ウィンドウ全体での右クリックメニュー
    if (ImGui::BeginPopupContextWindow("project_context_menu")) {

        if (ImGui::BeginMenu("filegenerate")) {
            // 「txt」というメニューアイテム
            if (ImGui::MenuItem("mat")) {
                // ポップアップを開く
                show_input_popup = true;
                this->inputwindow_generatefile_extension = ".mat";
            }
            else if (ImGui::MenuItem("input filenname(with extension)"))
            {
                // ポップアップを開く
                show_input_popup = true;
                this->inputwindow_generatefile_extension = "";
            }

            // 「create」メニューの終了
            ImGui::EndMenu();
        }

        //アセットを選択した状態なら
        if (SelectionInfo::GetInstance()->GetRecentClickTarget() == SelectTarget::Projectwindow &&
            SelectionInfo::GetInstance()->GetSelectElementInProjectWindow() != nullptr
            )
        {
            auto selectfile = SelectionInfo::GetInstance()->GetSelectElementInProjectWindow();
            auto asset = selectfile->GetAsset();
            if (ImGui::BeginMenu("remove"))
            {
                auto removefile_label = "remove " + asset->GetFilePath().filename().string();
                if (ImGui::MenuItem(removefile_label.c_str())) {
                    auto filepath = asset->GetFilePath();
                    auto assetinfofilepath = asset->GetAssetInfoFilePath();
                    std::filesystem::remove(filepath);
                    std::filesystem::remove(assetinfofilepath);

                    projects::Project::GetInstance()->AssetInitialize();
                    CreateView(this->now_display_folderpath);
                    SelectionInfo::GetInstance()->SetSelctionInfo(nullptr);
                }
                ImGui::EndMenu();
            }


        }


        ImGui::EndPopup();

    }
    // ウィンドウの表示制御
    if (show_input_popup) {
        ImGui::Begin("file generate", &show_input_popup);

        if (inputwindow_generatefile_extension == "")
        {
            // テキスト入力
            ImGui::InputText("inputfilename", inputwindow_textbuffer, IM_ARRAYSIZE(inputwindow_textbuffer));
        }
        else {
            // テキスト入力
            ImGui::InputText(inputwindow_generatefile_extension.c_str(), inputwindow_textbuffer, IM_ARRAYSIZE(inputwindow_textbuffer));
        }
        // ファイル生成ボタン
        if (ImGui::Button("generate")) {
            // テキストに基づいてファイルを生成
            auto generatefile = now_display_folderpath + "/" + inputwindow_textbuffer + inputwindow_generatefile_extension;
            std::ofstream file(generatefile);
            std::cout << generatefile << " generate" << std::endl;
            projects::Project::GetInstance()->AssetInitialize();
            CreateView(this->now_display_folderpath);

            // ウィンドウを閉じる
            show_input_popup = false;
        }

        ImGui::End();
    }


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
