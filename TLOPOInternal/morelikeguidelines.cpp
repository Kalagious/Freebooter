#include "morelikeguidelines.h"
#include "cheats.h"


extern Cheats* cheatsGlobal;


MoreLikeGuidelines::MoreLikeGuidelines(Cheats* cheatsIn)
{
	name = "SniperElite";
	enable = false;
	cheats = cheatsIn;
}


void MoreLikeGuidelines::drawActive()
{
	if (enable)
		ImGui::CollapsingHeader("   More Like Guidelines", ImGuiTreeNodeFlags_Leaf);
}

void MoreLikeGuidelines::drawMenuEntry()
{
	if (ImGui::CollapsingHeader("More Like Guidelines"))
	{
		ImGui::Checkbox("Enable##MoreLikeGuidelines", &enable);
	}
}
