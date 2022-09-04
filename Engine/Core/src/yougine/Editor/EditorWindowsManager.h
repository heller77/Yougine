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
#include <algorithm>
#include "EditorWindow.h"

namespace editor
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
        //render windows list on editor
        std::vector<EditorWindow*> render_window_list;
        //hide windows list on editor, reuse this elems when add window
        //hide list elems are not duplication
        std::vector<EditorWindow*> hide_window_list;
        std::map<EditorWindowName, std::string> str_window_name;

    public:
        EditorWindowsManager();
        void CreateWindows(GLFWwindow*);
        void AddRenderWindow(EditorWindow* new_window);
        void HideWindow(EditorWindow* delete_target);
        std::string GetWindowName(EditorWindowName);

    private:
        void CheckDuplicationOnList(std::vector<EditorWindow*>);
    };
}