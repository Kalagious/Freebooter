#include "minigungoburr.h"
#include "cheats.h"


extern Cheats* cheatsGlobal;


MinigunGoBurr::MinigunGoBurr(Cheats* cheatsIn)
{
	name = "MinigunGoBurr";
	enable = false;
	cheats = cheatsIn;
	pRechargeFloat = NULL;
	bEnableAutoClick = true;
	bMouseDown = false;
	hWnd = NULL;
}


bool MinigunGoBurr::tick()
{
	if (!pRechargeFloat)
	{
		pRechargeFloat = cheats->roguePython->createFloat(0);
		if (!pRechargeFloat)
			return false;
	}
	if (cheatsGlobal->minigunGoBurr->enable && cheatsGlobal->minigunGoBurr->bMouseDown && cheatsGlobal->minigunGoBurr->bEnableAutoClick)
	{
		CallWindowProc(ScreenManager::hGameWindowProc, hWnd, WM_LBUTTONDOWN, NULL, NULL);
		CallWindowProc(ScreenManager::hGameWindowProc, hWnd, WM_LBUTTONUP, NULL, NULL);
	}
	return true;
}

void MinigunGoBurr::drawActive()
{
	if (enable)
		ImGui::CollapsingHeader("   Minigun Go Burr", ImGuiTreeNodeFlags_Leaf);
}

void MinigunGoBurr::drawMenuEntry()
{
	if (ImGui::CollapsingHeader("Minigun Go Burr"))
	{
		ImGui::Checkbox("Enable##MinigunGoBurr", &enable);
		ImGui::Checkbox("Enable AutoClicker##MinigunGoBurr", &bEnableAutoClick);

	}
}
