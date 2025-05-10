#include "cannonflashsuppressor.h"
#include "cheats.h"


extern Cheats* cheatsGlobal;


CannonFlashSuppressor::CannonFlashSuppressor(Cheats* cheatsIn)
{
	name = "CannonFlashSuppressor";
	enable = false;
	cheats = cheatsIn;
}


void CannonFlashSuppressor::drawActive()
{
	if (enable)
		ImGui::CollapsingHeader("   Cannon Flash Suppressor", ImGuiTreeNodeFlags_Leaf);
}

void CannonFlashSuppressor::drawMenuEntry()
{
	bool bIsOpened = ImGui::CollapsingHeader("Cannon Flash Suppressor (!)");

	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted("Causes crash after a few seconds WIP");
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}

	if (bIsOpened)
	{
		ImGui::Checkbox("Enable##CannonFlashSuppressor", &enable);
	}
}
