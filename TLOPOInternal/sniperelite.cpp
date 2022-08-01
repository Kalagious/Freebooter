#include "sniperelite.h"
#include "cheats.h"


extern Cheats* cheatsGlobal;


SniperElite::SniperElite(Cheats* cheatsIn)
{
	name = "SniperElite";
	enable = false;
	cheats = cheatsIn;
	pDistanceFloat = NULL;
	fDistance = 3.273438;
}


bool SniperElite::tick()
{
	if (!pDistanceFloat)
	{
		pDistanceFloat = cheats->roguePython->createFloat(fDistance);
		if (!pDistanceFloat)
			return false;
	}


	if (pDistanceFloat->fValue != fDistance)
		pDistanceFloat->fValue = fDistance;

	return true;
}

void SniperElite::drawActive()
{
	if (enable)
		ImGui::CollapsingHeader("   Sniper Elite", ImGuiTreeNodeFlags_Leaf);
}

void SniperElite::drawMenuEntry()
{
	if (ImGui::CollapsingHeader("Sniper Elite"))
	{
		ImGui::Checkbox("Enable##SniperElite", &enable);
		ImGui::DragFloat("Distance##SniperElite", &fDistance, 5, 10, 1000);
	}
}
