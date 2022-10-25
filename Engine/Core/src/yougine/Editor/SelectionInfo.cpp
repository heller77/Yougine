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

    yougine::GameObject* SelectionInfo::GetSelectObject()
    {
        return game_object;
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
