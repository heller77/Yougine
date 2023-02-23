#pragma once
#include "imnodes/imnodes.h"
#include "imgui/imgui.h"
#include "../EditorWindow.h"
#include "ShaderGraphNode.h"

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

    class ShaderGraphWindow : public EditorWindow
    {
    private:
        std::vector<ShaderGraphNode*> nodes;
        std::vector<Link> links; //このリストに格納されているリンク構造体のリンクを描画
        int currentLinks = 0; //Link.idの指標
        std::vector<std::pair<std::pair<ShaderGraphNode*, ShaderGraphNode*>, std::pair<int, int>>> linked_nodes_pair;

    private:
        void SearchSelectingNodeID();
        void PhaseLink();
        void PhaseAddLink();
        void PhaseDisLink();
        void PhaseNode();
        void AddNode(int id, int num_inputs, int num_outputs, std::string name);
        void DrawNode(ShaderGraphNode* node);
        void SendOutputValToInput(std::pair<ShaderGraphNode*, ShaderGraphNode*>, int input_attr, int output_attr);
        void UpdateLinkedNodesValue();

    public:
        ShaderGraphWindow(EditorWindowsManager* editor_windows_manager);
        void Draw() override;

    protected:
        void SelectedItemProcess(std::string item) override;
        void InitializeMenuLists() override;
    };
}
