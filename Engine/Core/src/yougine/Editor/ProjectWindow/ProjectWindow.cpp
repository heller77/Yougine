#include "ProjectWindow.h"
#include <filesystem>
void ProjectWindow::Draw()
{

    std::string path = "./";
    ImGui::Begin(editor_windows_manager->GetWindowName(window_name).c_str());
    auto e = std::filesystem::directory_iterator(path);
    for(const auto & file:e)
    {
        std::string filename = file.path().string();
        ImGui::Button(filename.c_str()); ImGui::SameLine();
    }

    ImGui::End();
}
