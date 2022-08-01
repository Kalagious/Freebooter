#pragma once
#include "module.h"
#include "general.h"
#include "roguepython.h"

class Cheats;

class ZoooomShipEdition : public Module
{
public:
	ZoooomShipEdition(Cheats* cheatsIn);
	bool tick();
	float fSpeed;
	Cheats* cheats;
	RogueFloat* pSpeedFloat;
	void drawActive();
	void drawMenuEntry();
};