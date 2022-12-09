#include "MenuBar.h"

#include "../BuildScript/Builder.h"

editor::MenuBar::MenuBar(EditorWindowsManager* editor_windows_manager): EditorWindow(editor_windows_manager,editor::EditorWindowName::MenuBar)
{
}

void editor::MenuBar::Draw()
{
    ImGui::Begin("Menu bar");

    auto size = ImGui::GetContentRegionAvail();
    if(ImGui::Button("Build"))
    {
        
    }
    
    ImGui::End();
}

void editor::MenuBar::Build()
{
    auto builder = new builders::Builder();
    // builder->Build()
}
