#pragma once
#include "module.h"
#include "general.h"
#include "roguepython.h"

class Cheats;

class InfiniteCannons : public Module
{
public:
	InfiniteCannons(Cheats* cheatsIn);
	bool tick();
	Cheats* cheats;
	RogueFloat* pValueFloat;
	void drawActive();
	void drawMenuEntry();
};