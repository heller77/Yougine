#include "HierarchyWindow.h"
#include <iostream>

namespace editor
{
	HierarchyWindow::HierarchyWindow(EditorWindowsManager* editor_windows_manager) :EditorWindow(editor_windows_manager, EditorWindowName::HierarchyWindow)
	{
		MENU_ITEMS_LIST =
		{
			"GameObject",
		};
	}

	void HierarchyWindow::Draw()
	{
		ImGui::Begin(editor_windows_manager->GetWindowName(window_name).c_str(), nullptr, ImGuiWindowFlags_MenuBar);

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Create"))
			{
				RenderMenuItems();
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		ImGui::End();
		glClearColor(1.0, 0., 0., 1.0);

		glClear(GL_COLOR_BUFFER_BIT);
	}

	void HierarchyWindow::RenderMenuItems()
	{
		for (std::string item : MENU_ITEMS_LIST)
		{
			if (ImGui::MenuItem(item.c_str()));
		}
	}
}