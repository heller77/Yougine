#pragma once
#include "imnodes/imnodes.h"
#include "imgui/imgui.h"
#include "../EditorWindow.h"
#include "Nodes/ShaderGraphNode.h"
#include "Nodes/ShaderGraphInputNodes.h"
#include "Nodes/UnlitShaderGraphNode.h"
#include "UserShare/utilitys/Split.h"
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
        /*
        std::vector<std::string*> stack_defined_variable_shadercode;
        std::vector<std::string*> stack_defined_function_shadercode;
        std::vector<std::string*> stack_main_shadercode;
        */
        std::vector<std::shared_ptr<OutputInfo>> stack_defined_variable_shadercode;//include main code
        std::vector<std::shared_ptr<OutputInfo>> stack_defined_function_shadercode;
        //std::vector<std::shared_ptr<OutputInfo>> stack_main_shadercode;

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
        void AddCode(ShaderGraphNode* linked_node);
        void RemoveCode(ShaderGraphNode* dislinked_node);
        void MakeupLinkNodeCodeList(std::vector<std::shared_ptr<OutputInfo>>* link_list, ShaderGraphNode* node, int base_index);
        void UpdateStackIndex(std::vector<std::shared_ptr<OutputInfo>>* code_list, int start_index, int modifired_num);
        void ResisterSortedLinkedCodeList(std::vector<std::shared_ptr<OutputInfo>>* stack_code_list, ShaderGraphNode* linked_node);
        void SearchLeafIndexNodeAndResetStackIndex(ShaderGraphNode* node, ShaderGraphNode* leaf_node, int top_index, int* leaf_index);
        void UnResisterSortedLinkedCodeList(std::vector<std::shared_ptr<OutputInfo>>* stack_code_list, ShaderGraphNode* dislinked_node);
        void DebugCode(std::vector<std::shared_ptr<OutputInfo>> code_list);
        ShaderGraphNode* SearchMainNode(ShaderGraphNode* node);
        void CreateMainNode(MainShaderGraphNode* main_node, std::string name);
        void SetVNOfNode(ShaderGraphNode* node);


    public:
        ShaderGraphWindow(EditorWindowsManager* editor_windows_manager);
        //ShaderGraphWindow(EditorWindowsManager* editor_windows_manager, std::string shaderfile_output_filepath, std::string shaderfile_filename);
        void Draw() override;

    protected:
        void SelectedItemProcess(std::string item) override;
        void InitializeMenuLists() override;
    };
}
