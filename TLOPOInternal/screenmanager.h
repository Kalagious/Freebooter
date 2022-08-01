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
	bool bShowActiveModules;
	static bool bShowGUI;

	bool initializeImGui(HDC hDc);
	void cleanUp();

	void drawGUI();
	void DrawOutline(float x, float y, float width, float height, float lineWidth, const GLubyte color[3]);
	void DrawFilledRect(float x, float y, float width, float height, const float color[3]);
	void RestoreGL();
	void SetupOrtho();


	void DrawMovementCategory();
	void DrawGeneralCategory();
	void DrawVisualCategory();
	void DrawAttackCategory();
	void DrawActive();
	void DrawMain();



	ImFont* pBodyFont;
	ImFont* pHeaderFont;
	HWND hGameWindow;
	static WNDPROC hGameWindowProc;
};

