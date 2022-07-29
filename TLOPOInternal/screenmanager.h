#pragma once
#pragma comment(lib, "OpenGL32.lib")
#include "general.h"
#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_opengl3.h"
#include "ImGUI/imgui_impl_win32.h"
#include <gl\GL.h>
#include <string>

class ScreenManager
{
public:

	ScreenManager();

	bool imGUIInitialized;
	bool bShowGUI;

	bool initializeImGui(HDC hDc);
	void cleanUp();

	void drawGUI();
	void DrawOutline(float x, float y, float width, float height, float lineWidth, const GLubyte color[3]);
	void DrawFilledRect(float x, float y, float width, float height, const float color[3]);
	void RestoreGL();
	void SetupOrtho();
	HWND hGameWindow;
	static WNDPROC hGameWindowProc;
};

