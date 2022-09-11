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
        SelectionInfo* selection_info;
        const int MAX_SIZE_OBJ_NAME = 38;

    private:
        void ShowGameObjectData();

    public:
        InspectorWindow(EditorWindowsManager*, yougine::Scene*, yougine::InputManager*);
        ~InspectorWindow();

        using EditorWindow::Draw;
        virtual void Draw();
    };
}