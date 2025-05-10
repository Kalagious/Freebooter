#pragma once
#include "module.h"
#include "general.h"
#include "roguepython.h"

class Cheats;

class BetterRepairing : public Module
{
public:
	BetterRepairing(Cheats* cheatsIn);
	Cheats* cheats;
	bool bEnableInstantHammer;
	void drawActive();
	void drawMenuEntry();
};