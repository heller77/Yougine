#pragma once
#include "imnodes/imnodes.h"
#include "imgui/imgui.h"
#include "../EditorWindow.h"

namespace editor::shadergraph
{
    /*
     * リンク構造体
     */
    struct Link
    {
        int id; //リンク固有ID
        int start_attr, end_attr; //始点ID, 終点ID 
    };

    struct Node
    {
        int id;
        std::vector<int> input_attrs;
        std::vector<int> output_attrs;
    };

    class ShaderGraphWindow : public EditorWindow
    {
    private:
        std::vector<Node> nodes;
        std::vector<Link> links; //このリストに格納されているリンク構造体のリンクを描画
        int currentLinks = 0; //Link.idの指標

    private:
        void SearchSelectingNodeID();
        void PhaseLink();
        void PhaseAddLink();
        void PhaseDisLink();
        void PhaseNode();
        void AddNode(int id, int num_inputs, int num_outputs);
        void DrawNode(int id, std::vector<int> input_attrs, std::vector<int> output_attrs);

    public:
        ShaderGraphWindow(EditorWindowsManager* editor_windows_manager);
        void Draw() override;
    };
}
