#pragma once
#include "EditorWindowsManager.h"

namespace editor
{
	class EditorWindowsManager;
	enum class EditorWindowName;

	class EditorWindow
	{
	private:
		EditorWindowsManager* editor_windows_manager;
	protected:
		EditorWindowName window_name;

	public:
		EditorWindow(EditorWindowsManager*, EditorWindowName);
		~EditorWindow();
		void Draw();

	protected:
		void Setup();
	};
}
