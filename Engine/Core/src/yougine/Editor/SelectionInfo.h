#pragma once
#include "../GameObject.h"

namespace editor
{
    class SelectionInfo
    {

    private:
        static SelectionInfo* m_selection_info;
        yougine::GameObject* game_object = nullptr;
        bool flame_selected = false;

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
        void SetSelectedFlag(bool);
    };
}
