#include "screenmanager.h"

WNDPROC ScreenManager::hGameWindowProc;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK windowProc_hook(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{


	CallWindowProc(ImGui_ImplWin32_WndProcHandler, hWnd, uMsg, wParam, lParam);


	// Otherwise call the game's wndProc function
	return CallWindowProc(ScreenManager::hGameWindowProc, hWnd, uMsg, wParam, lParam);
}

ScreenManager::ScreenManager()
{
	hGameWindow = NULL;
	bShowGUI = false;
	imGUIInitialized = false;
}


bool ScreenManager::initializeImGui(HDC hDc)
{
	hGameWindow = WindowFromDC(hDc);
	hGameWindowProc = (WNDPROC)SetWindowLongPtr(hGameWindow, GWLP_WNDPROC, (LONG_PTR)windowProc_hook);
	ImGui::CreateContext();
	if (!hGameWindow)
		return false;
	ImGui_ImplWin32_Init(hGameWindow);
	ImGui_ImplOpenGL3_Init();
	ImGui::StyleColorsDark();
	ImGui::GetStyle().AntiAliasedFill = false;
	ImGui::GetStyle().AntiAliasedLines = false;
	ImGui::CaptureMouseFromApp();
	ImGui::GetStyle().WindowTitleAlign = ImVec2(0.5f, 0.5f);

	imGUIInitialized = true;

	return true;
}

void ScreenManager::cleanUp()
{
	if (imGUIInitialized)
	{
		(WNDPROC)SetWindowLongPtr(hGameWindow, GWLP_WNDPROC, (LONG_PTR)hGameWindowProc);

		ImGui_ImplWin32_Shutdown();
		ImGui_ImplOpenGL3_Shutdown();
		ImGui::DestroyContext();
	}
	imGUIInitialized = false;
}