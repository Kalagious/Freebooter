#pragma once
#include "module.h"
#include "general.h"
#include "roguepython.h"

class Cheats;

class NoAttackCooldown : public Module
{
public:
	NoAttackCooldown(Cheats* cheatsIn);
	bool tick();
	Cheats* cheats;
	bool bEnableAutoClick;

	void drawActive();
	void drawMenuEntry();
};