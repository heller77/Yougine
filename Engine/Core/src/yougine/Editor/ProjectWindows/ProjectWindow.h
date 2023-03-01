#pragma once
#include "../EditorWindow.h"
#include "../../Projects/Project.h"
#include "Assets/element/view/IElementOfProjectView.h"

namespace editor::projectwindows
{
    class ProjectWindow : public editor::EditorWindow
    {
    private:
        /**
         * \brief 今ProjectWindowで表示している絶対パス
         */
        std::string now_display_folderpath;
        std::vector<std::shared_ptr<assets::elements::view::IElementOfProjectView>> assetvies_vector;

        /**
         * \brief パスを変える
         */
        void ChangeDisplayPath(std::string path);

        /**
         * \brief ビューを作る
         * \param now_display_path
         */
        void CreateView(std::string now_display_path);

        /**
         * \brief 次のフレームに描画更新を行うようにする
         */
        void UpdateNextFrame();

        /**
         * \brief 次のフレームで描画を更新するかを判断するためのフラグ
         */
        bool is_updateelements_flag;
    public:
        void Draw() override;


        ProjectWindow(editor::EditorWindowsManager* editor_windows_manager, yougine::Scene* scene);
    };
}
