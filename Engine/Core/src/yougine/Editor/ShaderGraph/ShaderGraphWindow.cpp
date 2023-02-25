#include "ShaderGraphWindow.h"

namespace editor::shadergraph
{
    ShaderGraphWindow::ShaderGraphWindow(EditorWindowsManager* editor_windows_manager) : EditorWindow(editor_windows_manager, editor::EditorWindowName::ShaderGraphWindow)
    {
        InitializeMenuLists();
    }

    void ShaderGraphWindow::InitializeMenuLists()
    {
        menu_bar_list =
        {
            "Add Node",
        };

        menu_item_list =
        {
            "Sample Node",
        };
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
            int id = nodes.empty() ? 1 : nodes.back()->output_info.back().first + 1;
            AddNode(id, 1, 1, item);
        }
    }


    void ShaderGraphWindow::PhaseNode()
    {
        for (ShaderGraphNode* node : nodes)
        {
            DrawNode(node);
        }
    }

    /*
     * 描画するノードを増やしたいときに呼び出す
     *
     * id ... 前ノードのoutput_attr.back()+1の値を渡す
     * num_inputs ... input_attrの数
     * num_outputs ... ouput_attrの数
     */
    void ShaderGraphWindow::AddNode(int id, int num_inputs, int num_outputs, std::string name)
    {
        ShaderGraphNode* node = new ShaderGraphNode();
        node->id = id;

        for (int inputID = node->id + 1; inputID < num_inputs + node->id + 1; inputID++)
        {
            std::pair<std::string, std::string> p = std::make_pair(node->GetInitInputVal().first, node->GetInitInputVal().second);
            node->input_info.emplace_back(std::make_pair(inputID, std::make_pair("1", "1")));
        }

        for (int outputID = node->input_info.back().first + 1; outputID < num_outputs + node->input_info.back().first + 1; outputID++)
        {
            std::pair<std::string, std::string> p = (node->GetInitOutputVal());
            node->output_info.emplace_back(std::make_pair(outputID, std::make_pair("2", "2")));
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
        ImGui::TextUnformatted(node->name.c_str());
        ImNodes::EndNodeTitleBar();

        for (std::pair<int, std::pair<std::string, std::string>> intput : node->input_info)
        {
            ImNodes::BeginInputAttribute(intput.first);
            ImGui::Text("input");
            ImNodes::EndInputAttribute();
        }

        for (std::pair<int, std::pair<std::string, std::string>> output : node->output_info)
        {
            ImNodes::BeginOutputAttribute(output.first);
            ImGui::Indent(40);
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
            //リンクするノードを探索
            std::pair<ShaderGraphNode*, ShaderGraphNode*> sub_nodes; //0がinput(親), 1がoutput(子)
            int input_attr = link.end_attr, output_attr = link.start_attr;
            std::cout << "input_attr : " + std::to_string(input_attr) + ", output_attr : " + std::to_string(output_attr) << std::endl;

            bool is_detected_input_node = false, is_detected_output_node = false;
            //int first_attr_id = input_attr < output_attr ? 0 : 1;
            for (ShaderGraphNode* node : nodes)
            {
                if (!is_detected_input_node)
                {
                    for (std::pair<int, std::pair<std::string, std::string>> input : node->input_info)
                    {
                        int i_attr = input.first;
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
                    for (std::pair<int, std::pair<std::string, std::string>> output : node->output_info)
                    {
                        int o_attr = output.first;
                        is_detected_output_node = (o_attr == output_attr);
                        if (is_detected_output_node)
                        {
                            sub_nodes.second = node;
                            break;
                        }
                    }
                }
            }

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
            std::cout << "PinClicked:" + std::to_string(pin) << std::endl;
            //選択されているリンクを解除
            int l_id;
            if (ImNodes::IsLinkHovered(&l_id))
            {
                std::cout << "LinkDestroyed" << std::endl;
                //ImNodes::ClearLinkSelection();

                //解除されたリンクを除いたlinksリストに更新
                std::vector<Link> newLinks;
                for (Link ll : links)
                {
                    if (ll.id != l_id) newLinks.push_back(ll);
                }
                links = newLinks;
            }
        }
    }

    /*
     * pair<int, int> first ... input_attr(親側), second ... output_attr(子側)
     */
    void ShaderGraphWindow::UpdateLinkedNode(ShaderGraphNode* parent_node, ShaderGraphNode* child_node, std::pair<int, int> attr_pair)
    {
        child_node->SetParentNode(parent_node); //これAddだわ

        UpdateNodeValue(child_node, attr_pair);
    }

    void ShaderGraphWindow::UpdateNodeValue(ShaderGraphNode* child_node, std::pair<int, int> attr_pair)
    {
        if ((child_node->UpdateParentNodeValue(attr_pair)))
        {
            for (Link link : links)
            {
                std::cout << "links : " + std::to_string(link.start_attr) + ", " + std::to_string(link.end_attr) << std::endl;
                if (link.start_attr == child_node->GetParentNode()->output_info[0].first)
                {
                    int input_attr = link.end_attr;
                    int output_attr = link.start_attr;
                    UpdateNodeValue(child_node->GetParentNode(), std::make_pair(input_attr, output_attr));
                }
            }
        }
    }
}
