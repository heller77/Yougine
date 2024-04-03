#include "MenuBar.h"

#include "../BuildScript/Builder.h"
#include "../BuildScript/UserScriptCompiler.h"
#include "../Projects/Project.h"

editor::MenuBar::MenuBar(EditorWindowsManager* editor_windows_manager, yougine::Scene* scene) : EditorWindow(editor_windows_manager, editor::EditorWindowName::MenuBar)
{

    //シーンファイルの参照（本来はプロジェクトのフォルダーにあるのを、ビルド時に選択、エクスポートが正しいが、今回は既にビルドさきにあるものとする）
    this->sceenfilepath = projects::Project::GetInstance()->GetNowSceneFilePath().string();
    // strcpy_s(sceenfilepath, scenefilepath.c_str());
    this->scene = scene;

    this->play = false;
}

void editor::MenuBar::Draw()
{
    ImGui::Begin("Menu bar");

    auto buildpath = projects::Project::GetInstance()->GetBuildExportPath();
    auto size = ImGui::GetContentRegionAvail();
    if (ImGui::Button("Build"))
    {
        // std::cout << buildexportpath << std::endl;
        //buildexportpathのパスにexeをエクスポートする
        auto builder = new builders::Builder();
        builder->Build(buildpath.string(), scene);
    }

    // ImGui::InputText("exportpath", buildexportpath, 256);
    auto displaytext_buildpath = "buildexportpath : " + buildpath.string();
    ImGui::Text(displaytext_buildpath.c_str());

    auto scenefilepath = "scenefilepath" + sceenfilepath;
    ImGui::Text(scenefilepath.c_str());
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
