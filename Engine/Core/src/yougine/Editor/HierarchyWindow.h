#pragma once
#include "EditorWindow.h"
#include "../Scene.h"
#include <algorithm>
#include <list>

namespace editor
{
	class HierarchyWindow : public EditorWindow
	{
	private:
		yougine::Scene* scene;
		std::vector<std::string> MENU_ITEMS_LIST;
		//useless for memory
		std::vector<std::vector<std::string>> tree_objects_list;

	private:
		void RenderMenuItems();
		void RenderObjectsTree();
		void RecursiveTree(std::vector<std::string>, int);

	public:
		HierarchyWindow(EditorWindowsManager*, yougine::Scene*);
		~HierarchyWindow();

		using EditorWindow::Draw;
		virtual void Draw();
		void AddObjectToTreeList(std::string name, std::string top_name);
	};
}