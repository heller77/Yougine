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

		node_trees_list =
		{
			{"Obj1", "Obj1_c1", "Obj1_c2"},
			{"Obj2", "Obj2_c1", "Obj2_c2"},
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

		RenderObjectsTree(node_trees_list[0]);
		RenderObjectsTree(node_trees_list[1]);

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

	void HierarchyWindow::RenderObjectsTree(std::vector<std::string> node_names)
	{
		int n = 0;
		if (ImGui::TreeNode(node_names[n].c_str()))
		{
			/*
			* 
			* node_names[0]
			*  - node_names[1]
			*  - node_names[2]
			* 
			*/
			RecursiveTree(node_names, ++n);
			ImGui::TreePop();
		}
	}

	void HierarchyWindow::RecursiveTree(std::vector<std::string> node_names, int n)
	{
		if (n < node_names.size())
		{
			if (ImGui::TreeNode(node_names[n].c_str()))
			{
				ImGui::TreePop();
			}

			RecursiveTree(node_names, ++n);
		}
	}
}