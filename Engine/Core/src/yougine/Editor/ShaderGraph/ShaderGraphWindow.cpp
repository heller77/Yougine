#include "ShaderGraphWindow.h"

namespace editor::shadergraph
{
    ShaderGraphWindow::ShaderGraphWindow(EditorWindowsManager* editor_windows_manager) : EditorWindow(editor_windows_manager, editor::EditorWindowName::ShaderGraphWindow)
    {

    }

    void ShaderGraphWindow::Draw()
    {
        ImGui::Begin("simple node editor");

        int nodeID1 = 1;
        ImNodes::BeginNodeEditor();
        ImNodes::BeginNode(nodeID1);

        ImNodes::BeginNodeTitleBar();
        ImGui::TextUnformatted("simple node :)");
        ImNodes::EndNodeTitleBar();

        int inputID1 = 2;
        int outputID1 = 3;
        ImNodes::BeginInputAttribute(inputID1);
        ImGui::Text("input");
        ImNodes::EndInputAttribute();

        ImNodes::BeginOutputAttribute(outputID1);
        ImGui::Indent(40);
        ImGui::Text("output");
        ImNodes::EndOutputAttribute();

        ImNodes::EndNode();


        int nodeID2 = 4;
        ImNodes::BeginNode(nodeID2);

        ImNodes::BeginNodeTitleBar();
        ImGui::TextUnformatted("simple node :)");
        ImNodes::EndNodeTitleBar();

        int inputID2 = 5;
        int outputID2 = 6;
        ImNodes::BeginInputAttribute(inputID2);
        ImGui::Text("input");
        ImNodes::EndInputAttribute();

        ImNodes::BeginOutputAttribute(outputID2);
        ImGui::Indent(40);
        ImGui::Text("output");
        ImNodes::EndOutputAttribute();

        ImNodes::EndNode();

        PhaseLink();

        ImNodes::EndNodeEditor();

        PhaseAddLink();
        //PhaseDisLink();

        ImGui::End();
    }

    void ShaderGraphWindow::PhaseLink()
    {
        for (Link& link : links)
        {
            ImNodes::Link(link.id, link.start_attr, link.end_attr);
        }
    }

    void ShaderGraphWindow::PhaseAddLink()
    {
        Link link;
        if (ImNodes::IsLinkCreated(&link.start_attr, &link.end_attr))
        {
            std::cout << "LinkCreated" << std::endl;
            link.id = ++currentLinks;
            links.push_back(link);
        }
    }

    void ShaderGraphWindow::PhaseDisLink()
    {
        int* linkID = 0;
        ImNodes::GetSelectedLinks(linkID);
        if (ImNodes::IsLinkSelected(*linkID))
        {
            std::cout << "LinkSelected" << std::endl;
            if (ImNodes::IsLinkDestroyed(linkID))
            {
                std::cout << "LinkDestroyed" << std::endl;
                ImNodes::ClearLinkSelection(*linkID);

                std::vector<Link> newLinks;
                for (Link ll : links)
                {
                    if (ll.id != *linkID) newLinks.push_back(ll);
                }
                links = newLinks;
            }
        }
    }
}
