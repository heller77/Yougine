#include "SceneWindow.h"

#include <iostream>

editor::SceneWindow::SceneWindow(editor::EditorWindowsManager* editor_windows_manager,
    yougine::Scene* scene) : EditorWindow(editor_windows_manager,
        editor::EditorWindowName::SceneWindow)
{
    this->renderManager = new yougine::managers::RenderManager(1920, 1080,scene->GetComponentList());
}

void editor::SceneWindow::Draw()
{
    ImGui::Begin("Scene View window");

    auto size = ImGui::GetContentRegionAvail();
    // auto size2 = ImGui::GetWindowSize();
    // renderManager->SetWindowSize(size);
    renderManager->RenderScene();
    ImGui::Image((void*)(intptr_t)renderManager->GetColorBuffer(), ImVec2(size.x, size.y), ImVec2(0, 1), ImVec2(1, 0));
    ImGui::End();
}
