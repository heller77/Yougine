#include "MenuBar.h"

#include "../BuildScript/Builder.h"
#include "../Projects/Project.h"

editor::MenuBar::MenuBar(EditorWindowsManager* editor_windows_manager, yougine::Scene* scene): EditorWindow(editor_windows_manager,editor::EditorWindowName::MenuBar)
{
    //ビルド先のぱす（初期値だが、とりあえず）
    auto buildpath = projects::Project::GetInstance()->projectFolderPath + "build";
    strcpy_s(buildexportpath, buildpath.c_str());
    //シーンファイルの参照（本来はプロジェクトのフォルダーにあるのを、ビルド時に選択、エクスポートが正しいが、今回は既にビルドさきにあるものとする）
    auto scenefilepath = projects::Project::GetInstance()->projectFolderPath + "build\scene.json";
    strcpy_s(sceenfilepath, scenefilepath.c_str());
    this->scene=scene;
}

void editor::MenuBar::Draw()
{
    ImGui::Begin("Menu bar");

    auto size = ImGui::GetContentRegionAvail();
    if(ImGui::Button("Build"))
    {
        // std::cout << buildexportpath << std::endl;
        //buildexportpathのパスにexeをエクスポートする
        auto builder = new builders::Builder();
        builder->Build(buildexportpath,scene);
    }
 
    ImGui::InputText("exportpath", buildexportpath, 256);
    ImGui::InputText("scenefilepath", sceenfilepath, 256);
    ImGui::End();
}

void editor::MenuBar::Build()
{
    auto builder = new builders::Builder();
    // builder->Build()
}
