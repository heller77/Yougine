#include "ShaderGraphWindow.h"

namespace editor::shadergraph
{
    ShaderGraphWindow::ShaderGraphWindow(EditorWindowsManager* editor_windows_manager) : EditorWindow(editor_windows_manager, editor::EditorWindowName::ShaderGraphWindow)
    {
        InitializeMenuLists();

        shaderfile_overwriter = new ShaderfileOverwriter("F:/GameEngineProject/Yougine/Shaders/", "test.frag");
        shader_graph_input_field_viewer = std::make_shared<ShaderGraphInputFieldViewer>();
    }

    void ShaderGraphWindow::InitializeMenuLists()
    {
        MenuItem* item00 = new MenuItem();
        std::vector<MenuItem*> c_item00;
        MenuItem* item000 = new MenuItem();
        std::vector<MenuItem*> c_item000(0);
        item000->items.emplace_back(std::make_pair("Sample Node", c_item000));
        c_item00.push_back(item000);
        item00->items.emplace_back(std::make_pair("Debug", c_item00));

        MenuItem* item01 = new MenuItem();
        std::vector<MenuItem*> c_item01;
        MenuItem* item010 = new MenuItem();
        std::vector<MenuItem*> c_item010(0);
        item010->items.emplace_back(std::make_pair("Unlit", c_item010));
        c_item01.push_back(item010);
        item01->items.emplace_back(std::make_pair("Main", c_item01));

        MenuItem* item02 = new MenuItem();
        std::vector<MenuItem*> c_item02;

        MenuItem* item020 = new MenuItem();
        std::vector<MenuItem*> c_item020(0);
        item020->items.emplace_back(std::make_pair("Vector3", c_item020));

        MenuItem* item021 = new MenuItem();
        std::vector<MenuItem*> c_item021(0);
        item021->items.emplace_back(std::make_pair("Float", c_item021));

        c_item02.push_back(item020);
        c_item02.push_back(item021);

        item02->items.emplace_back(std::make_pair("Input", c_item02));

        pulldown_menu_bar = new PullDownMenuBar();
        std::vector<MenuItem*> items0;
        items0.push_back(item00);
        items0.push_back(item01);
        items0.push_back(item02);
        pulldown_menu_bar->menu_items.emplace_back(std::make_pair("Add Node", items0));


        MenuItem* item10 = new MenuItem();
        std::vector<MenuItem*> c_item10;
        MenuItem* item100 = new MenuItem();
        std::vector<MenuItem*> c_item100(0);
        item100->items.emplace_back(std::make_pair("Update", c_item100));
        c_item10.push_back(item100);
        item10->items.emplace_back(std::make_pair("Ex", c_item10));

        std::vector<MenuItem*> items1;
        items1.push_back(item10);
        pulldown_menu_bar->menu_items.emplace_back(std::make_pair("ShaderOverwriter", items1));

        //Create Main Node
        CreateMainNode(new UnlitShaderGraphNode(), "Unlit");
    }


    void ShaderGraphWindow::Draw()
    {
        ImGuiWindowFlags flags = (ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_MenuBar);
        ImGui::Begin("simple node editor", nullptr, flags);

        //メニューバー
        EditorWindow::RenderMenuBar();

        ImNodes::BeginNodeEditor();

        //ノードを描画
        PhaseNode();

        //ノード同士を繋げるリンク線を描画
        PhaseLink();

        ImNodes::EndNodeEditor();

        PhaseAddLink();
        PhaseDisLink();

        ImGui::End();
    }

    void ShaderGraphWindow::SelectedItemProcess(std::string item)
    {
        if (ImGui::MenuItem(item.c_str()))
        {
            if (item == "Unlit")
            {
                if (main_node == nullptr)
                {
                    CreateMainNode(new UnlitShaderGraphNode(), item);
                }
            }
            if (item == "Vector3")
            {
                CreateNode(new ShaderGraphVector3Node(), item);
            }
            if (item == "Float")
            {
                CreateNode(new ShaderGraphFloatNode(), item);
            }
            if (item == "Update")
            {
                if (main_node != nullptr)
                {
                    shaderfile_overwriter->UpdateFile(main_node->GetShaderCodeByOutputVal());
                }
                else
                {
                    std::cout << "Mainノードが存在しません" << std::endl;
                }
            }
        }
    }


    void ShaderGraphWindow::PhaseNode()
    {
        for (ShaderGraphNode* node : nodes)
        {
            DrawNode(node);
        }
    }

    void ShaderGraphWindow::CreateNode(ShaderGraphNode* node, std::string node_name)
    {
        int id = nodes.empty() ? 1 : nodes.back()->GetOutputInfos().back()->attr + 1;

        AddNode(node, id, node->GetInputInfos().size(), node->GetOutputInfos().size(), node_name);
    }


    /*
     * 描画するノードを増やしたいときに呼び出す
     *
     * id ... 前ノードのoutput_attr.back()+1の値を渡す
     * num_inputs ... input_attrの数
     * num_outputs ... ouput_attrの数
     */
    void ShaderGraphWindow::AddNode(ShaderGraphNode* node, int id, int num_inputs, int num_outputs, std::string name)
    {
        node->id = id;

        int index = 0;
        std::cout << "Add Node ID" + std::to_string(id) + " : " + name << std::endl;

        for (int inputID = node->id + 1; inputID < num_inputs + node->id + 1; inputID++)
        {
            node->SetInputInfoAttr(index++, inputID);
        }

        index = 0;
        for (int outputID = node->GetInputInfos().back()->attr + 1; outputID < num_outputs + node->GetInputInfos().back()->attr + 1; outputID++)
        {
            node->SetOutputInfoAttr(index++, outputID);
        }
        node->name = name;

        nodes.push_back(node);
    }

    /*
     * nodes配列に格納されているNode構造体をNodeとして描画する
     */
    void ShaderGraphWindow::DrawNode(ShaderGraphNode* node)
    {
        ImNodes::BeginNode(node->id);

        ImNodes::BeginNodeTitleBar();
        std::string txt = node->name + " : " + std::to_string(node->GetOutputInfos()[0]->stack_index);
        ImGui::TextUnformatted(txt.c_str());
        ImNodes::EndNodeTitleBar();

        for (std::shared_ptr<InputInfo> input_info : node->GetInputInfos())
        {
            ImNodes::BeginInputAttribute(input_info->attr);
            if (shader_graph_input_field_viewer->DrawView(input_info->val, input_info->label.c_str(), !(input_info->is_linked), input_info->field_width))
            {
                node->UpdateOutputVal();
                if (node->GetOutputInfos()[0]->linked_input_attr > -1) UpdateNodeValue(node, std::make_pair(node->GetOutputInfos()[0]->linked_input_attr, node->GetOutputInfos()[0]->attr));
            };
            ImNodes::EndInputAttribute();
        }

        for (std::shared_ptr<OutputInfo> output : node->GetOutputInfos())
        {
            ImNodes::BeginOutputAttribute(output->attr);
            ImGui::Indent(node->GetInputFieldWidth() + indent_space_arrange_width);
            ImGui::Text("output");
            ImNodes::EndOutputAttribute();
        }

        ImNodes::EndNode();
    }


    /*
     * Node同士をリンクする
     * linksリストに格納されているリンク構造体全てをリンク状態として描画する
     */
    void ShaderGraphWindow::PhaseLink()
    {
        for (Link& link : links)
        {
            ImNodes::Link(link.id, link.start_attr, link.end_attr);
        }
    }

    /*
     * リンク構造体を追加する
     * ノード1からノード2のピンにリンクを合わせたらそれらをリンクしているとみなし、リンク構造体を生成してlinksリストに追加する
     */
    void ShaderGraphWindow::PhaseAddLink()
    {
        Link link;
        if (ImNodes::IsLinkCreated(&link.start_attr, &link.end_attr))
        {
            std::pair<ShaderGraphNode*, ShaderGraphNode*> sub_nodes; //0がinput(親), 1がoutput(子)
            int input_attr = link.end_attr, output_attr = link.start_attr;

            //リンクするノードを探索
            sub_nodes = FindSubNodesByLinkAttr(std::make_pair(input_attr, output_attr));

            std::cout << "LinkCreated:" + std::to_string(link.start_attr) + "to" + std::to_string(link.end_attr) << std::endl;
            link.id = ++currentLinks;
            links.push_back(link);

            UpdateLinkedNode(sub_nodes.first, sub_nodes.second, std::make_pair(input_attr, output_attr));
        }
    }

    /*
     * リンクを解除する
     * リンクしているノードのピンをドラッグアンドドロップしたらそのリンクを解除する
     */
    void ShaderGraphWindow::PhaseDisLink()
    {
        int pin;
        //ノードのピンにマウスホバーされている状態で左クリック
        if (ImNodes::IsPinHovered(&pin) && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
        {
            //選択されているリンクを解除
            int l_id;
            if (ImNodes::IsLinkHovered(&l_id))
            {
                std::cout << "LinkDestroyed : " + std::to_string(l_id) << std::endl;
                //ImNodes::ClearLinkSelection();

                //解除されたリンクを除いたlinksリストに更新
                std::vector<Link> newLinks;
                for (Link ll : links)
                {
                    if (ll.id != l_id) newLinks.push_back(ll);
                    else
                    {
                        //ll.end_attr...input側, ll.start_attr...output側
                        DisLinkNodes(std::make_pair(ll.end_attr, ll.start_attr));
                    }
                }
                links = newLinks;
            }
        }
    }

    /*
     * return linked nodes
     *
     * Return
     * first ... inputされる側のノード(親ノード)
     * second ... outputする側のノード(子ノード)
     */
    std::pair<ShaderGraphNode*, ShaderGraphNode*> ShaderGraphWindow::FindSubNodesByLinkAttr(std::pair<int, int> attr_pair)
    {
        int input_attr = attr_pair.first, output_attr = attr_pair.second;
        std::pair<ShaderGraphNode*, ShaderGraphNode*> sub_nodes;

        bool is_detected_input_node = false, is_detected_output_node = false;
        //int first_attr_id = input_attr < output_attr ? 0 : 1;
        for (ShaderGraphNode* node : nodes)
        {
            if (!is_detected_input_node)
            {
                for (std::shared_ptr<InputInfo> input : node->GetInputInfos())
                {
                    int i_attr = input->attr;
                    is_detected_input_node = (i_attr == input_attr);
                    if (is_detected_input_node)
                    {
                        sub_nodes.first = node;
                        break;
                    }
                }
            }
            if (!is_detected_output_node)
            {
                for (std::shared_ptr<OutputInfo> output : node->GetOutputInfos())
                {
                    int o_attr = output->attr;
                    is_detected_output_node = (o_attr == output_attr);
                    if (is_detected_output_node)
                    {
                        sub_nodes.second = node;
                        break;
                    }
                }
            }
        }

        return sub_nodes;
    }


    void ShaderGraphWindow::DisLinkNodes(std::pair<int, int> link_pair)
    {
        std::pair<ShaderGraphNode*, ShaderGraphNode*> sub_nodes;
        sub_nodes = FindSubNodesByLinkAttr(link_pair);

        RemoveCode(sub_nodes.second);

        sub_nodes.first->DisLinkNode(link_pair);

        sub_nodes.second->InitOutputInfoLinkedInputAttr();
        UpdateNodeValue(sub_nodes.second, link_pair);
    }

    /*
     * pair<int, int> first ... input_attr(親側), second ... output_attr(子側)
     */
    void ShaderGraphWindow::UpdateLinkedNode(ShaderGraphNode* parent_node, ShaderGraphNode* child_node, std::pair<int, int> attr_pair)
    {
        child_node->SetParentNode(parent_node, attr_pair); //これAddだわ

        for (std::shared_ptr<InputInfo> input_info : parent_node->GetInputInfos())
        {
            if (input_info->attr == attr_pair.first)
            {
                child_node->GetOutputInfos()[0]->linked_input_attr = input_info->attr;
                input_info->linked_output_attr = child_node->GetOutputInfos()[0]->attr;
                parent_node->SetChildNode(input_info, child_node);
            }
        }

        AddCode(child_node);
        UpdateNodeValue(child_node, attr_pair);
    }

    /*
     * child_nodeの親ノードの子孫関係を検索し, 子孫全ての値を更新する
     */
    void ShaderGraphWindow::UpdateNodeValue(ShaderGraphNode* child_node, std::pair<int, int> attr_pair)
    {
        std::cout << std::to_string(attr_pair.first) + ", " + std::to_string(attr_pair.second) << std::endl;
        /*
         *親ノードが存在すれば親ノードの値を更新する
         */
        if ((child_node->UpdateParentNodeValue(attr_pair)))
        {
            /*
             * リンクしているペアから子孫関係を探索しattrを見つける
             */
            for (Link link : links)
            {
                //子ノードのoutput_attrがリンクペアのinput_attrに存在するとき, 親ノードを子とした親子関係が存在する
                if (link.start_attr == child_node->GetParentNode()->GetOutputInfos()[0]->attr)
                {
                    int input_attr = link.end_attr;
                    int output_attr = link.start_attr;
                    UpdateNodeValue(child_node->GetParentNode(), std::make_pair(input_attr, output_attr));
                }
            }
        }
    }

    /**
     * \brief
     * \param node
     */
    void ShaderGraphWindow::AddCode(ShaderGraphNode* linked_node)
    {
        if (SearchMainNode(linked_node) == nullptr) return;

        if (linked_node->GetCodeType() == CodeType::kVariable)
        {
            ResisterSortedLinkedCodeList(&stack_defined_variable_shadercode, linked_node);
        }
        if (linked_node->GetCodeType() == CodeType::kFunction)
        {
            int stackeds = stack_defined_function_shadercode.size();
            if (linked_node->GetOutputInfos()[0]->stack_index == -1)
            {
                stack_defined_function_shadercode.emplace_back(linked_node->GetOutputInfos()[0]);
                linked_node->GetOutputInfos()[0]->stack_index = stack_defined_function_shadercode.size() - 1;
            }
        }
        if (linked_node->GetCodeType() == CodeType::kMain)
        {
            ResisterSortedLinkedCodeList(&stack_defined_variable_shadercode, linked_node);
        }
    }

    ShaderGraphNode* ShaderGraphWindow::SearchMainNode(ShaderGraphNode* node)
    {
        if (node->GetParentNode() == main_node)
        {
            return node->GetParentNode();
        }
        if (node->GetParentNode() != nullptr)
        {
            SearchMainNode(node->GetParentNode());
        }
    }


    /**
     * \brief
     * \param stack_code_list 追加したいcode_listを入れる (例 : CodeType::kVariableの場合, variable_shadercodeのポインタを渡す
     * \param p_node 連結させたいリストの一番上階層の親ノードが入る. 基本的には使用先のnodeそのままでok
     *
     * stack_code_listにp_nodeが親となる階層構造を結合する
     *
     * 1. MakeupLinkNodeCodeListで結合したいリストを用意する
     * 2. stack_code_listに挿入するindexを定義
     * 3. stack_code_listに1.)のリストを挿入
     * 4. p_nodeの子ノードのOutputInfo->stack_indexを結合後のindexに更新
     */
    void ShaderGraphWindow::ResisterSortedLinkedCodeList(std::vector<std::shared_ptr<OutputInfo>>* stack_code_list, ShaderGraphNode* linked_node)
    {
        std::vector<std::shared_ptr<OutputInfo>> t_link_list;
        int based_index = linked_node->GetParentNode() != nullptr ? linked_node->GetParentNode()->GetOutputInfos()[0]->stack_index + 1 : 0;
        MakeupLinkNodeCodeList(&t_link_list, linked_node, based_index);

        int insert_index = based_index;
        (*stack_code_list).insert((*stack_code_list).begin() + insert_index, t_link_list.begin(), t_link_list.end());

        int added_num = t_link_list.size();
        UpdateStackIndex(stack_code_list, insert_index + added_num, added_num);

        DebugCode(*stack_code_list);
    }

    /**
     * \brief
     * \param link_list 結合するリスト
     * \param node リストに追加したいノード
     *
     * 再帰関数
     *
     * listの格納順
     * 例)
     * p_node
     *  - node1
     *    - node11
     *    - node12
     *  - node2
     *
     *  list = [p_node, node1, node11, node12, node2]
     *
     *  p_nodeはnode1, node2のoutputを知っていて, node1はnode11, node12のoutputを知っている必要がある
     */
    void ShaderGraphWindow::MakeupLinkNodeCodeList(std::vector<std::shared_ptr<OutputInfo>>* link_list, ShaderGraphNode* node, int base_index)
    {
        node->GetOutputInfos()[0]->stack_index = base_index + link_list->size();
        link_list->emplace_back((node->GetOutputInfos()[0]));
        for (std::shared_ptr<InputInfo> input_info : node->GetInputInfos())
        {
            if (input_info->child_node != nullptr)
            {
                MakeupLinkNodeCodeList(link_list, input_info->child_node, base_index);
            }
        }
    }

    void ShaderGraphWindow::SearchLeafIndexNodeAndResetStackIndex(ShaderGraphNode* node, ShaderGraphNode* leaf_node, int top_index, int* leaf_index)
    {
        int original_index = node->GetOutputInfos()[0]->stack_index;
        node->GetOutputInfos()[0]->stack_index = 0;
        for (std::shared_ptr<InputInfo> input_info : node->GetInputInfos())
        {
            if (input_info->child_node != nullptr)
            {
                SearchLeafIndexNodeAndResetStackIndex(input_info->child_node, leaf_node, top_index, leaf_index);
            }
            else
            {
                if (*leaf_index < original_index)
                {
                    leaf_node = node;
                    *leaf_index = original_index;
                }
            }
        }
    }

    void ShaderGraphWindow::RemoveCode(ShaderGraphNode* dislinked_node)
    {
        if (dislinked_node->GetCodeType() == CodeType::kVariable)
        {
            UnResisterSortedLinkedCodeList(&stack_defined_variable_shadercode, dislinked_node);
        }
        if (dislinked_node->GetCodeType() == CodeType::kFunction)
        {
            stack_defined_function_shadercode.erase(stack_defined_function_shadercode.begin() + dislinked_node->GetOutputInfos()[0]->stack_index);
        }
        if (dislinked_node->GetCodeType() == CodeType::kMain)
        {
            UnResisterSortedLinkedCodeList(&stack_defined_variable_shadercode, dislinked_node);
        }
    }

    /**
     * \brief
     * \param stack_code_list
     * \param dislinked_node 切ったノード(子ノード)
     */
    void ShaderGraphWindow::UnResisterSortedLinkedCodeList(std::vector<std::shared_ptr<OutputInfo>>* stack_code_list, ShaderGraphNode* dislinked_node)
    {
        ShaderGraphNode* leaf_node = dislinked_node;
        int top_index = dislinked_node->GetOutputInfos()[0]->stack_index;
        int leaf_index = leaf_node->GetOutputInfos()[0]->stack_index;

        SearchLeafIndexNodeAndResetStackIndex(dislinked_node, leaf_node, top_index, &leaf_index);

        std::pair<int, int> remove_range = std::make_pair(top_index, leaf_index);
        if (remove_range.first == remove_range.second)
        {
            std::cout << "このノード群に属するノードは一つです" << std::endl;
            (*stack_code_list).erase((*stack_code_list).begin() + remove_range.first);
        }
        else
        {
            (*stack_code_list).erase((*stack_code_list).begin() + remove_range.first, (*stack_code_list).begin() + remove_range.second + 1);
        }

        int start_index = remove_range.first + 1;
        int dec_num = (remove_range.second + 1) - (remove_range.first);
        UpdateStackIndex(stack_code_list, start_index, (dec_num * -1));

        DebugCode(*stack_code_list);
    }

    /**
     * \brief
     * \param node indexを更新する対象ノード
     * \param start_index リストの結合先index
     *
     * 再帰関数
     *
     * 結合対象のリストに格納されているノードのstack_indexを更新する
     * 各stack_indexには結合前stackリストの要素数分(start_index)+される
     *  再帰でstart_indexを+1して更新
     */
    void ShaderGraphWindow::UpdateStackIndex(std::vector<std::shared_ptr<OutputInfo>>* code_list, int start_index, int modifired_num)
    {
        for (int i = start_index; i < code_list->size(); i++)
        {
            (*code_list)[i]->stack_index += modifired_num;
        }
    }

    void ShaderGraphWindow::DebugCode(std::vector<std::shared_ptr<OutputInfo>> code_list)
    {
        std::cout << "" << std::endl;
        std::cout << "- Code List Log -" << std::endl;
        for (std::shared_ptr<OutputInfo> code : code_list)
        {
            std::cout << code->val << std::endl;
        }
        std::cout << "- This Log End -" << std::endl;
        std::cout << "" << std::endl;
    }

    void ShaderGraphWindow::CreateMainNode(MainShaderGraphNode* node, std::string name)
    {
        MainShaderGraphNode* t_node = node;
        main_node = t_node;
        CreateNode(t_node, name);
        stack_defined_variable_shadercode.emplace_back(main_node->GetOutputInfos()[0]);
    }

}
