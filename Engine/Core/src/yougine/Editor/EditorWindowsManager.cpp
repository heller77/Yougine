#include "EditorWindowsManager.h"

namespace Editor
{
	using std::vector;
	using std::map;

	EditorWindowsManager::EditorWindowsManager()
	{
		str_window_name =
		{
			{ EditorWindowName::SceneWindow, "Scene" },
			{ EditorWindowName::HierarchyWindow, "Hierarchy" },
			{ EditorWindowName::GameWindow, "Game" },
			{ EditorWindowName::ProjectWindow, "Project" },
			{ EditorWindowName::InspectorWindow, "Inspector" }
		};
	}

	void EditorWindowsManager::CreateWindows(GLFWwindow* window)
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		for (EditorWindow* editor_window : editor_window_list)
		{
			editor_window->Draw();
		}

		ImGui::Render();
		glClearColor(0.3, 0.3, 0.3, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	void EditorWindowsManager::AddWindow(EditorWindow* new_window)
	{
		editor_window_list.push_back(new_window);
	}

	void EditorWindowsManager::DeleteWindow(EditorWindow* delete_target)
	{
		std::vector<EditorWindow*> new_list;

		for (EditorWindow* editor_window : editor_window_list)
		{
			if (editor_window != delete_target)
			{
				new_list.push_back(editor_window);
			}
		}

		editor_window_list = new_list;
	}

	std::string EditorWindowsManager::GetWindowName(EditorWindowName window_name)
	{
		return str_window_name[window_name];
	}
}