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
        this->game_object = game_object;
        this->flame_selected = flame_selected;
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


}
