#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "imgui/imgui.h"
#include <stdio.h>
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <vector>
#include <map>
#include <string>
#include "EditorWindow.h"

namespace Editor
{
	class EditorWindow;

	enum class EditorWindowName
	{
		SceneWindow,
		HierarchyWindow,
		GameWindow,
		ProjectWindow,
		InspectorWindow,
	};

	class EditorWindowsManager
	{
	private:
		std::vector<EditorWindow*> editor_window_list;
		std::map<EditorWindowName, std::string> str_window_name;

	public:
		EditorWindowsManager();
		void CreateWindows(GLFWwindow*);
		void AddWindow(EditorWindow* new_window);
		void DeleteWindow(EditorWindow* delete_target);
		std::string GetWindowName(EditorWindowName);
	};
}