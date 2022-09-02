#include "HierarchyWindow.h"

namespace editor
{
	HierarchyWindow::HierarchyWindow(EditorWindowsManager* editor_windows_manager):EditorWindow(editor_windows_manager, EditorWindowName::HierarchyWindow)
	{

	}

     void HierarchyWindow::Draw()
	{
		 ImGui::Begin(editor_windows_manager->GetWindowName(window_name).c_str());
		 ImGui::End();
		 glClearColor(1.0, 0., 0., 1.0);

		 glClear(GL_COLOR_BUFFER_BIT);
	}
}