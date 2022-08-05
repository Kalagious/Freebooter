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
	if (ImGui::CollapsingHeader("Cannon Flash Suppressor"))
	{
		ImGui::Checkbox("Enable##CannonFlashSuppressor", &enable);
	}
}
