#include "SelectionInfo.h"

namespace editor
{
    SelectionInfo* SelectionInfo::m_selection_info = nullptr;

    SelectionInfo::SelectionInfo()
    {
        game_object = nullptr;
    }

    SelectionInfo::~SelectionInfo()
    {

    }

    SelectTarget SelectionInfo::GetRecentClickTarget()
    {
        return this->most_recent_select_target;
    }

    void SelectionInfo::Create()
    {
        if (!m_selection_info)
        {
            m_selection_info = new SelectionInfo();
        }
    }

    void SelectionInfo::Destroy()
    {
        if (m_selection_info)
        {
            delete m_selection_info;
            m_selection_info = nullptr;
        }
    }

    SelectionInfo* SelectionInfo::GetInstance()
    {
        if (m_selection_info)
            return m_selection_info;
        return nullptr;
    }

    void SelectionInfo::SetSelectionInfo(yougine::GameObject* game_object, bool flame_selected)
    {
        //今選択されたのはヒエラルキーですよ
        this->most_recent_select_target = SelectTarget::Hierarchy;

        this->flame_selected = flame_selected;
        if (this->game_object != game_object)
        {
            this->game_object = game_object;

            if (game_object != nullptr)
            {
                InitializeComponentViewersOnChangeObject(this->game_object);
            }
        }
    }

    void SelectionInfo::SetSelctionInfo(
        std::shared_ptr<projectwindows::assets::elements::view::IElementOfProjectView> select_projectwindow_element)
    {
        //今選択されたのはプロジェクトウィンドー
        this->most_recent_select_target = SelectTarget::Projectwindow;

        this->select_projectwindow_element = select_projectwindow_element;
    }

    yougine::GameObject* SelectionInfo::GetSelectObject()
    {
        return game_object;
    }

    std::shared_ptr<projectwindows::assets::elements::view::IElementOfProjectView> SelectionInfo::
        GetSelectElementInProjectWindow()
    {
        return this->select_projectwindow_element;
    }

    bool SelectionInfo::GetSelectedFlag()
    {
        return flame_selected;
    }

    void SelectionInfo::SetSelectedFlag(bool flame_selected)
    {
        this->flame_selected = flame_selected;
    }

    void SelectionInfo::InitializeComponentViewersOnChangeObject(yougine::GameObject* game_object)
    {
        for (ComponentViewer* c_viewer : component_viewers)
        {
            delete c_viewer;
            c_viewer = nullptr;
        }

        //vectorのサイズと容量を0にする
        component_viewers.clear();

        for (yougine::components::Component* c : game_object->GetComponents())
        {
            component_viewers.push_back(new ComponentViewer(c));
        }
    }

    std::vector<ComponentViewer*> SelectionInfo::GetComponentViewers()
    {
        return component_viewers;
    }

}
