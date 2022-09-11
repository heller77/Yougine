#pragma once
#include "EditorWindow.h"
#include "../InputManager.h"

namespace editor
{
    class InspectorWindow : public EditorWindow
    {
    private:
        yougine::Scene* scene;
        yougine::InputManager* input_manager;

    public:
        InspectorWindow(EditorWindowsManager*, yougine::Scene*, yougine::InputManager*);
        ~InspectorWindow();

        using EditorWindow::Draw;
        virtual void Draw();
    };
}