#pragma once
#include "module.h"
#include "general.h"
#include "roguepython.h"

class Cheats;

class Zoooom : public Module
{
public:
	Zoooom(Cheats* cheatsIn);
	bool tick();
	float fSpeed;
	Cheats* cheats;
	RogueFloat* pSpeedFloat;
	void drawActive();
	void drawMenuEntry();
};