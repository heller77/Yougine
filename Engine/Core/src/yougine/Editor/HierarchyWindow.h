#pragma once
#include "EditorWindow.h"
#include "../Scene.h"
#include <algorithm>
#include  "../InputManager.h"
namespace editor
{
    class HierarchyWindow : public EditorWindow
    {
    private:
        yougine::Scene* scene;
        yougine::InputManager* input_manager;
        std::vector<std::string> MENU_ITEMS_LIST;
        SelectionInfo* selection_info = nullptr;
        bool flame_click_trigger = false;

    private:
        void RenderMenuItems();
        void RenderObjectsTree();
        void RecursiveTree(std::list<yougine::GameObject*>);
        yougine::GameObject* CreateGameObject(std::string, yougine::GameObject*);
        void InitializeFlameProperties();

    public:
        HierarchyWindow(EditorWindowsManager*, yougine::Scene*, yougine::InputManager*);
        ~HierarchyWindow();

        void Draw()override;
    };
}