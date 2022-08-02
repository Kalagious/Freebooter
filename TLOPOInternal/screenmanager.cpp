#include "screenmanager.h"
#include "cheats.h"

WNDPROC ScreenManager::hGameWindowProc;
bool ScreenManager::bShowGUI;

extern Cheats* cheatsGlobal;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK windowProc_hook(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	if (!cheatsGlobal->minigunGoBurr->hWnd)
		cheatsGlobal->minigunGoBurr->hWnd = hWnd;
	if (uMsg == WM_LBUTTONDOWN)
	{
		cheatsGlobal->minigunGoBurr->bMouseDown = true;
	}

	if (uMsg == WM_LBUTTONUP)
	{
		cheatsGlobal->minigunGoBurr->bMouseDown = false;
	}



	if (ScreenManager::bShowGUI)
	{
		CallWindowProc(ImGui_ImplWin32_WndProcHandler, hWnd, uMsg, wParam, lParam);
		return true;
	}

	// Otherwise call the game's wndProc function
	return CallWindowProc(ScreenManager::hGameWindowProc, hWnd, uMsg, wParam, lParam);
}

ScreenManager::ScreenManager()
{
	hGameWindow = NULL;
	ScreenManager::bShowGUI = false;
	imGUIInitialized = false;
	bShowActiveModules = true;
}


bool ScreenManager::initializeImGui(HDC hDc)
{
	hGameWindow = WindowFromDC(hDc);
	hGameWindowProc = (WNDPROC)SetWindowLongPtr(hGameWindow, GWLP_WNDPROC, (LONG_PTR)windowProc_hook);
	if (!hGameWindow)
		return false;
	ImGui::CreateContext();

	ImGui_ImplWin32_Init(hGameWindow);
	ImGui_ImplOpenGL3_Init();
	ImGui::StyleColorsDark();
	ImGui::GetStyle().AntiAliasedFill = true;
	ImGui::GetStyle().AntiAliasedLines = true;
	ImGui::CaptureMouseFromApp();

	ImGuiIO& io = ImGui::GetIO();
	pBodyFont = io.Fonts->AddFontFromFileTTF("C:/Users/Jordan/Documents/Cheats/TLOPO/TLOPOInternal/ImGui/Fonts/RobotoCondensed-Bold.ttf", 24);
	pHeaderFont = io.Fonts->AddFontFromFileTTF("C:/Users/Jordan/Documents/Cheats/TLOPO/TLOPOInternal/ImGui/Fonts/RobotoCondensed-Bold.ttf", 32);
	ImGui::GetStyle().Colors[ImGuiCol_TitleBg] = ImVec4(0.1, 0.1, 0.1, 0.8);
	ImGui::GetStyle().Colors[ImGuiCol_TitleBgActive] = ImVec4(0.1, 0.1, 0.1, 0.8);
	ImGui::GetStyle().Colors[ImGuiCol_FrameBg] = ImVec4(0.1, 0.1, 0.1, 0.8);
	ImGui::GetStyle().Colors[ImGuiCol_Header] = ImVec4(0.1, 0.1, 0.1, 0.8);
	ImGui::GetStyle().Colors[ImGuiCol_HeaderActive] = ImVec4(0.1, 0.1, 0.1, 0.8);
	ImGui::GetStyle().Colors[ImGuiCol_FrameBgActive] = ImVec4(0.2, 0.2, 0.2, 0.8);
	ImGui::GetStyle().Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.2, 0.2, 0.2, 0.8);
	ImGui::GetStyle().Colors[ImGuiCol_HeaderActive] = ImVec4(0.2, 0.2, 0.2, 0.8);
	ImGui::GetStyle().Colors[ImGuiCol_HeaderHovered] = ImVec4(0.2, 0.2, 0.2, 0.8);



	ImGui::GetStyle().WindowTitleAlign = ImVec2(0.5f, 0.5f);
	ImGui::GetStyle().FrameBorderSize = 1;
	ImGui::GetStyle().WindowBorderSize = 2;
	ImGui::GetStyle().TabBorderSize = 1;
	ImGui::GetStyle().WindowRounding = 12;
	ImGui::GetStyle().FrameRounding = 4;






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