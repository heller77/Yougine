#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "ComponentsIncluder.h"
#include <string>
#include <any>
#include "UserShare/utilitys/YougineMath.h"
#include "UserShare/utilitys/Split.h"
#include "UserShare/utilitys/Quaternion.h"

#include "PropertiesInputField.h"

namespace editor
{
    class ComponentViewer
    {
    private:
        yougine::components::Component* component;
        std::string component_name;
        std::shared_ptr<PropertiesInputField> properties_input_field;

    public:
        ComponentViewer(yougine::components::Component* component);
        ~ComponentViewer();
        void DrawViews();
        std::string GetComponentName();
        yougine::components::Component* GetComponent();
    };
}
