#include "HierarchyWindow.h"
#include <iostream>

namespace editor
{
	HierarchyWindow::HierarchyWindow(EditorWindowsManager* editor_windows_manager, yougine::Scene* scene) :EditorWindow(editor_windows_manager, EditorWindowName::HierarchyWindow)
	{
		this->scene = scene;

		MENU_ITEMS_LIST =
		{
			"GameObject",
		};

		tree_objects_list =
		{
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

		RenderObjectsTree();

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

	void HierarchyWindow::RenderObjectsTree()
	{
		int n = 0;
		for (std::vector<std::string> list : tree_objects_list)
		{
			if (ImGui::TreeNode(list[n].c_str()))
			{
				RecursiveTree(list, ++n);
				ImGui::TreePop();
			}
		}
	}

	void HierarchyWindow::RecursiveTree(std::vector<std::string> node_names, int n)
	{
		if (n < node_names.size())
		{
			if (ImGui::TreeNode(node_names[n].c_str()))
			{
				RecursiveTree(node_names, ++n);
				ImGui::TreePop();
			}
		}
	}

	void HierarchyWindow::AddObjectToTreeList(std::string name, std::string top_name)
	{
		int tree_index = -1;

		for (int i = 0; i < tree_objects_list.size(); i++)
		{
			if (top_name == tree_objects_list[i][0])
			{
				tree_index = i;
			}
		}

		if (tree_index != -1)
		{
			tree_objects_list[tree_index].push_back(name);
		}
		else
		{
			tree_objects_list.push_back(std::vector<std::string>{ name });
		}

	}
}