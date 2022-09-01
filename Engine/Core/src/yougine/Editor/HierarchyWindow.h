#pragma once
#include "EditorWindow.h"

namespace editor
{
	class HierarchyWindow : public EditorWindow
	{
	public:
		HierarchyWindow(EditorWindowsManager*);
		~HierarchyWindow();
	};
}