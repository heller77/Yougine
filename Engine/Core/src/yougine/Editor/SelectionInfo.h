#pragma once
#include "../GameObject.h"
#include "ComponentViewer.h"

namespace editor
{
    class ComponentViewer;

    class SelectionInfo
    {

    private:
        static SelectionInfo* m_selection_info;
        yougine::GameObject* game_object = nullptr;
        bool flame_selected = false;
        bool is_selected_hierarchy_window = false;
        std::vector<ComponentViewer*> component_viewers;

    private:
        SelectionInfo();
        ~SelectionInfo();

    public:
        static void Create();
        static void Destroy();
        static SelectionInfo* GetInstance();
        void SetSelectionInfo(yougine::GameObject*, bool flame_selected = false);
        yougine::GameObject* GetSelectObject();
        bool GetSelectedFlag();
        bool GetIsSelectedHierarchyWindow();
        void SetSelectedFlag(bool);
        void InitializeComponentViewersOnChangeObject(yougine::GameObject* game_object);
        std::vector<ComponentViewer*> GetComponentViewers();
    };
}
