#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "ComponentsIncluder.h"
#include <string>
#include "../utilitys/YougineMath.h"

namespace editor
{
    class ComponentViewer
    {
#define GETVALUENAME(name) (#name)

    private:
        yougine::components::Component* component;
        std::string component_name;

    public:
        ComponentViewer(yougine::components::Component* component);
        ~ComponentViewer();
        void DrawViews();
        std::string GetComponentName();

    private:
        void Vector3View(utility::Vector3* value);
        void IntView(int* value);
        void FloatView(float* value);
        void StringView(std::string* value);
        void BoolView(bool* value);
    };
}