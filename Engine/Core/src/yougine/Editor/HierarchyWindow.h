#pragma once
#include "EditorWindow.h"
#include "../Scene.h"
#include <algorithm>
#include <list>

namespace editor
{
    struct SelectionInfo
    {
        yougine::GameObject* game_object = nullptr;
    };

    class HierarchyWindow : public EditorWindow
    {
    private:
        yougine::Scene* scene;
        std::vector<std::string> MENU_ITEMS_LIST;
        struct SelectionInfo s_selection_info;

    private:
        void SetSelectionInfo(yougine::GameObject*);
        void RenderMenuItems();
        void RenderObjectsTree();
        void RecursiveTree(std::vector<yougine::GameObject*>);
        void CreateGameObject(std::string, yougine::GameObject*);

    public:
        HierarchyWindow(EditorWindowsManager*, yougine::Scene*);
        ~HierarchyWindow();

        using EditorWindow::Draw;
        virtual void Draw();
    };
}