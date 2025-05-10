#include "infinitecannons.h"
#include "cheats.h"


extern Cheats* cheatsGlobal;


InfiniteCannons::InfiniteCannons(Cheats* cheatsIn)
{
	name = "InfiniteCannons";
	enable = false;
	cheats = cheatsIn;
	pValueFloat = NULL;
}


bool InfiniteCannons::tick()
{
	if (!TryGetCString((char*)pValueFloat) || pValueFloat->fValue != 1)
	{
		pValueFloat = cheats->roguePython->createFloat(1);
		if (!pValueFloat)
			return false;
	}

	return true;
}

void InfiniteCannons::drawActive()
{
	if (enable)
		ImGui::CollapsingHeader("   Infinite Cannonballs", ImGuiTreeNodeFlags_Leaf);
}

void InfiniteCannons::drawMenuEntry()
{
	if (ImGui::CollapsingHeader("Infinite Cannonballs"))
	{
		ImGui::Checkbox("Enable##InfiniteCannonballs", &enable);
	}
}
