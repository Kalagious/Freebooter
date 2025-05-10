#pragma once
#include "module.h"
#include "general.h"
#include "roguepython.h"

class Cheats;

class CoolDownsAreCringe : public Module
{
public:
	CoolDownsAreCringe(Cheats* cheatsIn);
	float fDelay;
	Cheats* cheats;
	RogueFloat* pDelayFloat;
	void drawActive();
	void drawMenuEntry();
};