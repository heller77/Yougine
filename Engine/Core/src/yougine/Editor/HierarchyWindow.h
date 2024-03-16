#pragma once
#include "EditorWindow.h"
#include "../Scene.h"
#include <algorithm>

#include "SelectionInfo.h"
#include  "../InputManager.h"
namespace editor
{
    class HierarchyWindow : public EditorWindow
    {
    private:
        yougine::Scene* scene;
        yougine::InputManager* input_manager;
        SelectionInfo* selection_info = nullptr;
        bool flame_click_trigger = false;

    private:
        void RenderObjectsTree();
        void RecursiveTree(std::list<yougine::GameObject*>);
        yougine::GameObject* CreateGameObject(std::string, yougine::GameObject*);
        void InitializeFlameProperties();

    public:
        HierarchyWindow(EditorWindowsManager*, yougine::Scene*, yougine::InputManager*);
        ~HierarchyWindow();

        void Draw()override;

    protected:
        void SelectedItemProcess(std::string item) override;
        void InitializeMenuLists() override;
    };
}