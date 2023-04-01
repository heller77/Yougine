#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "ComponentsIncluder.h"
#include <string>
#include <any>
#include "../utilitys/YougineMath.h"
#include "../utilitys/Split.cpp"
#include "../utilitys/Quaternion.h"

namespace editor
{
    class ComponentViewer
    {
    private:
        yougine::components::Component* component;
        std::string component_name;
        std::vector<std::vector<std::any>> accessable_properties;

    public:
        ComponentViewer(yougine::components::Component* component);
        ~ComponentViewer();
        void DrawViews();
        std::string GetComponentName();

    private:
        void Bool3View(utility::Bool3* value, const char* name);
        void Vector3View(utility::Vector3* value, const char* name);
        void IntView(int* value, const char* name);
        void FloatView(float* value, const char* name);
        void StringView(std::string* value, const char* name);
        void BoolView(bool* value, const char* name);
        void QuaternionView(std::shared_ptr<utility::Quaternion> value, const char* name);
    };
}
