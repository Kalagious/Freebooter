#include "betterfishing.h"
#include "cheats.h"


extern Cheats* cheatsGlobal;


BetterFishing::BetterFishing(Cheats* cheatsIn)
{
	name = "Better Fishing";
	enable = false;
	cheats = cheatsIn;
	bNoFighting = true;
	bInstantCatch = false;
	bInstantReel = false;
	bFasterLengendaries = false;
}


void BetterFishing::drawActive()
{
	if (enable)
		ImGui::CollapsingHeader("   Better Fishing", ImGuiTreeNodeFlags_Leaf);
}

void BetterFishing::drawMenuEntry()
{
	if (ImGui::CollapsingHeader("Better Fishing"))
	{
		ImGui::Checkbox("Enable##BetterFishing", &enable);
		ImGui::Checkbox("Enable No Fighting##BetterFishing", &bNoFighting);
		ImGui::Checkbox("Enable Instant Catch##BetterFishing", &bInstantCatch);
		ImGui::Checkbox("Enable Instant Reel##BetterFishing", &bInstantReel);
		ImGui::Checkbox("Enable Faster Legendaries##BetterFishing", &bFasterLengendaries);


	}
}
