#include "betterrepairing.h"
#include "cheats.h"


extern Cheats* cheatsGlobal;


BetterRepairing::BetterRepairing(Cheats* cheatsIn)
{
	name = "BetterRepairing";
	enable = false;
	cheats = cheatsIn;
	bEnableInstantHammer = true;
}


void BetterRepairing::drawActive()
{
	if (enable)
		ImGui::CollapsingHeader("   Better Repairing", ImGuiTreeNodeFlags_Leaf);
}

void BetterRepairing::drawMenuEntry()
{
	if (ImGui::CollapsingHeader("Better Repairing"))
	{
		ImGui::Checkbox("Enable##BetterRepairing", &enable);
		ImGui::Checkbox("Enable Instant Hammer##BetterRepairing", &bEnableInstantHammer);

	}
}
