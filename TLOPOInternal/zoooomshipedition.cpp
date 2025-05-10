#include "zoooom.h"
#include "cheats.h"


extern Cheats* cheatsGlobal;


ZoooomShipEdition::ZoooomShipEdition(Cheats* cheatsIn)
{
	name = "Zooooom (Ship Ed.)";
	fSpeed = 3.8;
	enable = false;
	cheats = cheatsIn;
	pSpeedFloat = NULL;

}


bool ZoooomShipEdition::tick()
{
	if (!pSpeedFloat)
	{
		pSpeedFloat = cheats->roguePython->createFloat(fSpeed);
		if (!pSpeedFloat)
			return false;
	}

	if (pSpeedFloat)
	{
		if (pSpeedFloat->fValue != fSpeed)
			pSpeedFloat->fValue = fSpeed;
	}


	return true;
}

void ZoooomShipEdition::drawActive()
{
	if (enable)
		ImGui::CollapsingHeader("   Speed(Ship)", ImGuiTreeNodeFlags_Leaf);
}

void ZoooomShipEdition::drawMenuEntry()
{
	if (ImGui::CollapsingHeader("Speed(Ship)"))
	{
		ImGui::Checkbox("Enable##ZoooomShipEdition", &enable);
		ImGui::DragFloat("Speed##ZoooomShipEdition", &fSpeed, 0.01, 2, 6);
	}
}
