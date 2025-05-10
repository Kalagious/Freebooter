#include "morelikeguidelines.h"
#include "cheats.h"


extern Cheats* cheatsGlobal;


MoreLikeGuidelines::MoreLikeGuidelines(Cheats* cheatsIn)
{
	name = "MoreLikeGuidelines";
	enable = false;
	cheats = cheatsIn;
}


void MoreLikeGuidelines::drawActive()
{
	if (enable)
		ImGui::CollapsingHeader("   Gun Target Bypass", ImGuiTreeNodeFlags_Leaf);
}

void MoreLikeGuidelines::drawMenuEntry()
{
	if (ImGui::CollapsingHeader("Gun Target Bypass"))
	{
		ImGui::Checkbox("Enable##Gun Target Bypass", &enable);
	}
}
