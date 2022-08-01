#include "fly.h"
#include "cheats.h"


extern Cheats* cheatsGlobal;


Fly::Fly(Cheats* cheatsIn)
{
	name = "Fly";
	vertSpeedMult = 0.1;
	enable = false;
	cheats = cheatsIn;
}


bool Fly::tick()
{
	NextPosObject* nextPos = cheats->localPlayer->nextPosObject;
	//printf("X: %f.2  Y: %f.2\n", nextPos->x, nextPos->y);
	if (enable)
	{
		if (GetAsyncKeyState(VK_SPACE))
			virtualPos.z += vertSpeedMult;
		if (GetAsyncKeyState(VK_LCONTROL))
			virtualPos.z -= vertSpeedMult;
		nextPos->z = virtualPos.z;
	}
	else
	{
		virtualPos.x = nextPos->x;
		virtualPos.y = nextPos->y;
		virtualPos.z = nextPos->z;
	}
	return true;
}

void Fly::drawActive()
{
	if (enable)
		ImGui::CollapsingHeader("   Fly", ImGuiTreeNodeFlags_Leaf);
}

void Fly::drawMenuEntry()
{
	if (ImGui::CollapsingHeader("Fly"))
	{
		ImGui::Checkbox("Enable##Fly", &enable);
		ImGui::DragFloat("Vertical Speed##Fly", &vertSpeedMult, 0.01, 0, 2);
	}
}