#pragma once
#include "module.h"
#include "general.h"
#include "roguepython.h"

class Cheats;

class SniperElite : public Module
{
public:
	SniperElite(Cheats* cheatsIn);
	bool tick();
	Cheats* cheats;
	RogueFloat* pDistanceFloat;
	float fDistance;
	void drawActive();
	void drawMenuEntry();
};