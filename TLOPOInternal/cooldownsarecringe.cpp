#include "cooldownsarecringe.h"
#include "cheats.h"


extern Cheats* cheatsGlobal;


CoolDownsAreCringe::CoolDownsAreCringe(Cheats* cheatsIn)
{
	name = "Cooldowns Are Cringe";
	fDelay = 0;
	enable = false;
	cheats = cheatsIn;
	pDelayFloat = NULL;

}


void CoolDownsAreCringe::drawActive()
{
	if (enable)
		ImGui::CollapsingHeader("   Cooldowns Are Cringe", ImGuiTreeNodeFlags_Leaf);
}

void CoolDownsAreCringe::drawMenuEntry()
{
	if (ImGui::CollapsingHeader("Cooldowns Are Cringe"))
	{
		ImGui::Checkbox("Enable##CooldownsAreCringe", &enable);
		ImGui::DragFloat("Cooldown Delay##CooldownsAreCringe", &fDelay, 1, 0, 60);
	}
}

