#pragma once
#include "EditorWindow.h"
#include "vector"

namespace editor
{
	class HierarchyWindow : public EditorWindow
	{
	private:
		std::vector<std::string> MENU_ITEMS_LIST;

	private:
		void RenderMenuItems();

	public:
		HierarchyWindow(EditorWindowsManager*);
		~HierarchyWindow();

		using EditorWindow::Draw;
		virtual void Draw();
	};
}