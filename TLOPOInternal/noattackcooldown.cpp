#include "noattackcooldown.h"
#include "cheats.h"


extern Cheats* cheatsGlobal;


NoAttackCooldown::NoAttackCooldown(Cheats* cheatsIn)
{
	name = "NoAttackCooldown";
	enable = false;
	cheats = cheatsIn;
	bEnableAutoClick = true;

}


bool NoAttackCooldown::tick()
{
	if (cheatsGlobal->noAttackCooldown->enable && cheatsGlobal->bMouseDown && cheatsGlobal->noAttackCooldown->bEnableAutoClick && cheatsGlobal->hWnd && ScreenManager::hGameWindowProc)
	{
		CallWindowProc(ScreenManager::hGameWindowProc, cheatsGlobal->hWnd, WM_LBUTTONDOWN, NULL, NULL);
		CallWindowProc(ScreenManager::hGameWindowProc, cheatsGlobal->hWnd, WM_LBUTTONUP, NULL, NULL);
	}
	return true;
}

void NoAttackCooldown::drawActive()
{
	if (enable)
		ImGui::CollapsingHeader("   No Attack Cooldown", ImGuiTreeNodeFlags_Leaf);
}

void NoAttackCooldown::drawMenuEntry()
{
	bool bIsOpened = ImGui::CollapsingHeader("No Attack Cooldown (!)");

	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted("Only works in short bursts!");
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}

	if (bIsOpened)
	{
		
		ImGui::Checkbox("Enable##NoAttackCooldown", &enable);
		ImGui::Checkbox("Enable AutoClicker##NoAttackCooldown", &bEnableAutoClick);

	}
}
