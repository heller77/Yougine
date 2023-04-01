#pragma once
#include "imnodes/imnodes.h"
#include "imgui/imgui.h"
#include "../EditorWindow.h"
#include "Nodes/ShaderGraphNode.h"
#include "Nodes/ShaderGraphInputNodes.h"
#include "Nodes/UnlitShaderGraphNode.h"
#include "../../utilitys/Split.cpp"
#include "ShaderfileOverwriter.h"
#include "ShaderGraphInputFieldViewer.h"

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
        ShaderfileOverwriter* shaderfile_overwriter;
        MainShaderGraphNode* main_node;
        std::shared_ptr<ShaderGraphInputFieldViewer> shader_graph_input_field_viewer;
        float indent_space_arrange_width = 0.0f;
        std::vector<std::string*> stack_defined_variable_shadercode;
        std::vector<std::string*> stack_defined_function_shadercode;
        std::vector<std::string*> stack_main_shadercode;

    private:
        void SearchSelectingNodeID();
        void PhaseLink();
        void PhaseAddLink();
        void PhaseDisLink();
        void PhaseNode();
        void CreateNode(ShaderGraphNode* node, std::string node_name);
        void AddNode(ShaderGraphNode* node, int id, int num_inputs, int num_outputs, std::string name);
        void DrawNode(ShaderGraphNode* node);
        void UpdateLinkedNode(ShaderGraphNode* parent_node, ShaderGraphNode* child_node, std::pair<int, int> attr_pair);
        void UpdateNodeValue(ShaderGraphNode* child_node, std::pair<int, int> attr_pair);
        void DisLinkNodes(std::pair<int, int> link_pair);
        std::pair<ShaderGraphNode*, ShaderGraphNode*> FindSubNodesByLinkAttr(std::pair<int, int> attr_pair);
        void AddCode(ShaderGraphNode* node);
        void RemoveCode(ShaderGraphNode* node);
        void MakeupLinkNodeCodeList(std::vector<std::string>* link_list, ShaderGraphNode* node);
        void UpdateStackIndex(ShaderGraphNode* node, int start_index);
        void ResisterSortedLinkedCodeList(std::vector<std::string*>* stack_code_list, ShaderGraphNode* p_node);
        void SearchLeafIndexNodeAndResetStackIndex(ShaderGraphNode* node, ShaderGraphNode* leaf_node, int p_node_stack_index);
        void UnResisterSortedLinkedCodeList(std::vector<std::string*>* stack_code_list, ShaderGraphNode* p_node);
        void DebugCode(std::vector<std::string*> code_list);


    public:
        ShaderGraphWindow(EditorWindowsManager* editor_windows_manager);
        //ShaderGraphWindow(EditorWindowsManager* editor_windows_manager, std::string shaderfile_output_filepath, std::string shaderfile_filename);
        void Draw() override;

    protected:
        void SelectedItemProcess(std::string item) override;
        void InitializeMenuLists() override;
    };
}
