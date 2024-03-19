#pragma once
#include "EditorWindowsManager.h"
#include "UserShare/Scene.h"

namespace editor
{
    class EditorWindowsManager;
    enum class EditorWindowName;

    /**
     * \brief メニューバーの各項目が選択されたときその項目に属しているアイテムを表示する
     * MenuItem自身から更にプルダウンするために, 自身の子供のMenuItemを持っている
     *
     * 子供のMenuItem*がnullのとき, SelectedItemProcessを呼び出してアイテム選択処理を実行する
     *
     * std::string ... アイテムの表示文字列
     * MenuItem* ... 一つ下の子供
     */
    struct MenuItem
    {
        std::vector < std::pair<std::string, std::vector<MenuItem*>>> items;
    };

    /**
     * \brief メニューバー(windowの上に出てくるプルダウンメニュー)
     */
    struct PullDownMenuBar
    {
        std::vector < std::pair< std::string, std::vector<MenuItem*>> > menu_items;
    };


    class EditorWindow
    {
    protected:
        EditorWindowsManager* editor_windows_manager;
        EditorWindowName window_name;
        bool is_selected = false;
        PullDownMenuBar* pulldown_menu_bar;

    public:
        EditorWindow(EditorWindowsManager*, EditorWindowName);
        virtual void Draw();

    protected:
        void Setup();
        void RenderMenuBar();
        void RenderMenuItems(std::vector<MenuItem*> menu_items);
        virtual void SelectedItemProcess(std::string item);
        virtual void InitializeMenuLists();
    };
}
