#include "sniperelite.h"
#include "cheats.h"


extern Cheats* cheatsGlobal;


SniperElite::SniperElite(Cheats* cheatsIn)
{
	name = "SniperElite";
	enable = false;
	cheats = cheatsIn;
	pDistanceFloat = NULL;
	fDistance = 100;
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
		ImGui::CollapsingHeader("   Weapon Range", ImGuiTreeNodeFlags_Leaf);
}

void SniperElite::drawMenuEntry()
{
	if (ImGui::CollapsingHeader("Weapon Range"))
	{
		ImGui::Checkbox("Enable##WeaponRange", &enable);
		ImGui::DragFloat("Distance##WeaponRange", &fDistance, 5, 10, 1000);
	}
}
