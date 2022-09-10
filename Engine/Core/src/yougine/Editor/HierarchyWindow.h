#pragma once
#include "EditorWindow.h"
#include "../Scene.h"
#include <algorithm>
#include  "../InputManager.h"
namespace editor
{
    struct SelectionInfo
    {
        yougine::GameObject* game_object = nullptr;
        bool flame_selected = false;
    };

    class HierarchyWindow : public EditorWindow
    {
    private:
        yougine::Scene* scene;
        yougine::InputManager* input_manager;
        std::vector<std::string> MENU_ITEMS_LIST;
        struct SelectionInfo s_selection_info;
        bool flame_click_trigger = false;

    private:
        void SetSelectionInfo(yougine::GameObject*, bool flame_selected = false);
        void RenderMenuItems();
        void RenderObjectsTree();
        void RecursiveTree(std::list<yougine::GameObject*>);
        void CreateGameObject(std::string, yougine::GameObject*);
        void InitializeFlameProperties();

    public:
        HierarchyWindow(EditorWindowsManager*, yougine::Scene*, yougine::InputManager*);
        ~HierarchyWindow();

        using EditorWindow::Draw;
        virtual void Draw();
    };
}