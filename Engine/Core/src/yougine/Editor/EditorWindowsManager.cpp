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

	/*
	* Render windows in render_window_list
	*/
	void EditorWindowsManager::CreateWindows(GLFWwindow* window)
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		for (EditorWindow* editor_window : render_window_list)
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

	/*
	* add render window on editor
	* 
	* if exist target in hide_window_list, add target to render_window_list, remove target on hide_window_list
	* not exist in hide_window, add target to render_window_list
	*/
	template <class T> void EditorWindowsManager::AddRenderWindow()
	{
		EditorWindow* add_target;
		std::vector<EditorWindow> new_hide_list(hide_window_list.size());
		std::copy(hide_window_list.begin(), hide_window_list.end(), new_hide_list.begin());

		for (int i=0; i<hide_window_list.size; i++)
		{
			add_target = dynamic_cast<T*>(hide_window_list[i]);
			if (add_target != nullptr)
			{
				new_hide_list.erase(std::remove(new_hide_list.begin(), new_hide_list.end(), add_target), new_hide_list.end());
				break;
			}
		}

		render_window_list.push_back(T*);
		hide_window_list = new_hide_list;
	}

	/*
	* remove target on render_window_list, add to hide_target
	* 
	* if target window class are exits, the one remove, the others are not hide
	*/
	template <class T> void EditorWindowsManager::HideWindow()
	{
		EditorWindow* hide_target;
		std::vector<EditorWindow*> new_list;
		bool is_hided = false;

		for (EditorWindow* editor_window : render_window_list)
		{
			hide_target = dynamic_cast<T*>(editor_window);
			if (hide_target == nullptr || is_hided)
			{
				new_list.push_back(editor_window);
			}
			else
			{
				hide_window_list.push_back(hide_target);
				is_hided = true;
			}
		}

		render_window_list = new_list;
		CheckDuplicationOnList(hide_window_list);
	}

	std::string EditorWindowsManager::GetWindowName(EditorWindowName window_name)
	{
		return str_window_name[window_name];
	}

	/*
	* call by HideWindow()
	*/
	void EditorWindowsManager::CheckDuplicationOnList(std::vector<EditorWindow*> list)
	{
		std::sort(list.begin(), list.end());
		list.erase(std::unique(list.begin(), list.end()), list.end());
	}
}