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
}


bool MinigunGoBurr::tick()
{
	if (!pRechargeFloat)
	{
		pRechargeFloat = cheats->roguePython->createFloat(0);
		if (!pRechargeFloat)
			return false;
	}
	if (cheatsGlobal->minigunGoBurr->enable && cheatsGlobal->bMouseDown && cheatsGlobal->minigunGoBurr->bEnableAutoClick)
	{
		CallWindowProc(ScreenManager::hGameWindowProc, cheatsGlobal->hWnd, WM_LBUTTONDOWN, NULL, NULL);
		CallWindowProc(ScreenManager::hGameWindowProc, cheatsGlobal->hWnd, WM_LBUTTONUP, NULL, NULL);
	}
	return true;
}

void MinigunGoBurr::drawActive()
{
	if (enable)
		ImGui::CollapsingHeader("   Rapid Cannons", ImGuiTreeNodeFlags_Leaf);
}

void MinigunGoBurr::drawMenuEntry()
{
	if (ImGui::CollapsingHeader("Rapid Cannons"))
	{
		ImGui::Checkbox("Enable##Rapid Cannons", &enable);
		ImGui::Checkbox("Enable AutoClicker##Rapid Cannons", &bEnableAutoClick);

	}
}
