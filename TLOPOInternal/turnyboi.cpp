#include "turnyboi.h"
#include "cheats.h"


extern Cheats* cheatsGlobal;


TurnyBoi::TurnyBoi(Cheats* cheatsIn)
{
	name = "TurnyBoi";
	enable = false;
	cheats = cheatsIn;
	pRightFloat = NULL;
	pLeftFloat = NULL;
	fTurnSpeed = 3.7;
}


RogueObject* TurnyBoi::tick()
{
	if (!pRightFloat)
	{
		pRightFloat = cheats->roguePython->createFloat(-1*fTurnSpeed);
	}
	if (!pLeftFloat)
	{
		pLeftFloat = cheats->roguePython->createFloat(1*fTurnSpeed);
	}

	if (pRightFloat)
		pRightFloat->fValue = -1 * fTurnSpeed;
	if (pLeftFloat)
		pLeftFloat->fValue = 1 * fTurnSpeed;


	if (GetAsyncKeyState(0x41))
		return (RogueObject*)pLeftFloat;

	if (GetAsyncKeyState(0x44))
		return (RogueObject*)pRightFloat;

	return NULL;
}

void TurnyBoi::drawActive()
{
	if (enable)
		ImGui::CollapsingHeader("   Ship Turn Rate", ImGuiTreeNodeFlags_Leaf);
}

void TurnyBoi::drawMenuEntry()
{
	if (ImGui::CollapsingHeader("Ship Turn Rate"))
	{
		ImGui::Checkbox("Enable##TurnyBoi", &enable);
		ImGui::DragFloat("Turn Speed##TurnyBoi", &fTurnSpeed, 0.01, 2, 6);
	}
}
