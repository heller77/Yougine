#pragma once
#include "../GameObject.h"
#include "ComponentViewer.h"
#include "ProjectWindows/Assets/element/view/IElementOfProjectView.h"

namespace editor
{
    enum class SelectTarget { HierarchyWindow, Projectwindow };
    class ComponentViewer;

    class SelectionInfo
    {

    private:
        //最も最近に選択されたtargetを格納（target == window）
        SelectTarget most_recent_select_target;

        static SelectionInfo* m_selection_info;

        yougine::GameObject* game_object = nullptr;
        std::shared_ptr<projectwindows::assets::elements::view::IElementOfProjectView> select_projectwindow_element;

        bool flame_selected = false;
        bool is_selected_hierarchy_window = false;
        std::vector<ComponentViewer*> component_viewers;

    private:
        SelectionInfo();
        ~SelectionInfo();

    public:
        SelectTarget GetRecentClickTarget();

        static void Create();
        static void Destroy();
        static SelectionInfo* GetInstance();

        void SetSelectionInfo(yougine::GameObject*, bool flame_selected = false);

        //プロジェクトウィンドーで選択したものをセットするときに呼ばれる
        void SetSelctionInfo(std::shared_ptr<projectwindows::assets::elements::view::IElementOfProjectView> select_projectwindow_element);

        yougine::GameObject* GetSelectObject();

        //プロジェクトウィンドーで選択したものを返す
        std::shared_ptr<projectwindows::assets::elements::view::IElementOfProjectView> GetSelectElementInProjectWindow();

        bool GetSelectedFlag();
        bool GetIsSelectedHierarchyWindow();
        void SetSelectedFlag(bool);
        void InitializeComponentViewersOnChangeObject(yougine::GameObject* game_object);
        std::vector<ComponentViewer*> GetComponentViewers();
    };
}
