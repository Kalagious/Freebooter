#pragma once
#include "module.h"
#include "general.h"
#include "roguepython.h"

class Cheats;

class MinigunGoBurr : public Module
{
public:
	MinigunGoBurr(Cheats* cheatsIn);
	bool tick();
	Cheats* cheats;
	RogueFloat* pRechargeFloat;
	bool bEnableAutoClick;

	void drawActive();
	void drawMenuEntry();
};