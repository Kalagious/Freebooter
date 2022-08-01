#include "minigungoburr.h"
#include "cheats.h"


extern Cheats* cheatsGlobal;


MinigunGoBurr::MinigunGoBurr(Cheats* cheatsIn)
{
	name = "MinigunGoBurr";
	enable = false;
	cheats = cheatsIn;
	pRechargeFloat = NULL;
}


bool MinigunGoBurr::tick()
{
	if (!pRechargeFloat)
	{
		pRechargeFloat = cheats->roguePython->createFloat(0);
		if (!pRechargeFloat)
			return false;
	}
	return true;
}

void MinigunGoBurr::drawActive()
{
	if (enable)
		ImGui::CollapsingHeader("   Minigun Go Burr", ImGuiTreeNodeFlags_Leaf);
}

void MinigunGoBurr::drawMenuEntry()
{
	if (ImGui::CollapsingHeader("Minigun Go Burr"))
	{
		ImGui::Checkbox("Enable##MinigunGoBurr", &enable);
	}
}
