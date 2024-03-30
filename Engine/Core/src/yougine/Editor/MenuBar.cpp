#include "MenuBar.h"

#include "../BuildScript/Builder.h"
#include "../BuildScript/UserScriptCompiler.h"
#include "../Projects/Project.h"

editor::MenuBar::MenuBar(EditorWindowsManager* editor_windows_manager, yougine::Scene* scene) : EditorWindow(editor_windows_manager, editor::EditorWindowName::MenuBar)
{
    //ビルド先のぱす（初期値だが、とりあえず）
    auto buildpath = projects::Project::GetInstance()->GetProjectFolderPath_ByTypeString() + "build";
    strcpy_s(buildexportpath, buildpath.c_str());
    //シーンファイルの参照（本来はプロジェクトのフォルダーにあるのを、ビルド時に選択、エクスポートが正しいが、今回は既にビルドさきにあるものとする）
    auto scenefilepath = projects::Project::GetInstance()->GetProjectFolderPath_ByTypeString() + "build\scene.json";
    strcpy_s(sceenfilepath, scenefilepath.c_str());
    this->scene = scene;

    this->play = false;
}

void editor::MenuBar::Draw()
{
    ImGui::Begin("Menu bar");

    auto size = ImGui::GetContentRegionAvail();
    if (ImGui::Button("Build"))
    {
        // std::cout << buildexportpath << std::endl;
        //buildexportpathのパスにexeをエクスポートする
        auto builder = new builders::Builder();
        builder->Build(buildexportpath, scene);
    }

    ImGui::InputText("exportpath", buildexportpath, 256);
    ImGui::InputText("scenefilepath", sceenfilepath, 256);
    if (ImGui::Button("save"))
    {
        auto builder = new builders::Builder();
        builder->Save(scene);
    }

    if (ImGui::Button("Play"))
    {
        if (play)
        {
            play = false;
        }
        else
        {
            play = true;
            builders::UserScriptCompiler::Compile();
        }
    }
    ImGui::SameLine();
    std::string playtext = "";
    if (play)
    {
        playtext = "play";
    }
    else
    {
        playtext = "stop";
    }
    ImGui::Text(playtext.c_str());
    ImGui::End();
}

bool editor::MenuBar::GetPlay()
{
    return this->play;
}

void editor::MenuBar::Build()
{
    auto builder = new builders::Builder();
    // builder->Build()
}
