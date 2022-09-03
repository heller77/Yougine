#pragma once
#include "EditorWindow.h"
#include "../Scene.h"
#include <algorithm>
#include <list>

namespace editor
{
	struct SelectionInfo
	{
		std::string obj_name = "";
		int f_index = -1; //one dimension
		int b_index = -1; //two dimension
	};

	class HierarchyWindow : public EditorWindow
	{
	private:
		yougine::Scene* scene;
		std::vector<std::string> MENU_ITEMS_LIST;
		//useless for memory
		std::vector<std::vector<std::string>> tree_objects_list;
		struct SelectionInfo s_selection_info;
		std::string STR_EMPTY = "";

	private:
		void SetSelectionInfo(std::string, int, int);
		void RenderMenuItems();
		void RenderObjectsTree();
		void RecursiveTree(std::vector<std::string>, int, int);
		void CreateGameObject(std::string, std::string);

	public:
		HierarchyWindow(EditorWindowsManager*, yougine::Scene*);
		~HierarchyWindow();

		using EditorWindow::Draw;
		virtual void Draw();
		void AddObjectToTreeList(std::string, std::string);
	};
}