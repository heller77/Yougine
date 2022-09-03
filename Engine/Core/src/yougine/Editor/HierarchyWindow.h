#pragma once
#include "EditorWindow.h"
#include "vector"

namespace editor
{
	class HierarchyWindow : public EditorWindow
	{
	private:
		std::vector<std::string> MENU_ITEMS_LIST;
		std::vector<std::vector<std::string>> node_trees_list;

	private:
		void RenderMenuItems();
		void RenderObjectsTree(std::vector<std::string>);
		void RecursiveTree(std::vector<std::string>, int);

	public:
		HierarchyWindow(EditorWindowsManager*);
		~HierarchyWindow();

		using EditorWindow::Draw;
		virtual void Draw();
	};
}