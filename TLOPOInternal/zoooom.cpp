#include "zoooom.h"
#include "cheats.h"


extern Cheats* cheatsGlobal;


Zoooom::Zoooom(Cheats* cheatsIn)
{
	name = "Zooooom";
	fSpeed = 3.5;
	enable = false;
	cheats = cheatsIn;
	pSpeedFloat = NULL;

}


bool Zoooom::tick()
{
	if (!pSpeedFloat)
	{
		pSpeedFloat = cheats->roguePython->createFloat(fSpeed);
	}

	if (pSpeedFloat)
	{
		if (pSpeedFloat->fValue != fSpeed)
			pSpeedFloat->fValue = fSpeed;
	}
	return true;
}

void Zoooom::drawActive()
{
	if (enable)
		ImGui::CollapsingHeader("   Speed(Player)", ImGuiTreeNodeFlags_Leaf);
}

void Zoooom::drawMenuEntry()
{
	if (ImGui::CollapsingHeader("Speed(Player)"))
	{
		ImGui::Checkbox("Enable##Zoooom", &enable);
		ImGui::DragFloat("Speed##Zoooom", &fSpeed, 0.01, 2, 6);
	}
}

