#pragma once
#include "EditorWindowsManager.h"

namespace editor
{
	class EditorWindowsManager;
	enum class EditorWindowName;

	class EditorWindow
	{
	protected:
		EditorWindowsManager* editor_windows_manager;
		EditorWindowName window_name;

	public:
		EditorWindow(EditorWindowsManager*, EditorWindowName);
		void Draw();

	protected:
		void Setup();
	};
}
