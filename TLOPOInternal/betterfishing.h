#pragma once
#include "module.h"
#include "general.h"
#include "roguepython.h"

class Cheats;

class BetterFishing : public Module
{
public:
	BetterFishing(Cheats* cheatsIn);
	Cheats* cheats;
	bool bInstantCatch;
	bool bNoFighting;
	bool bInstantReel;
	bool bFasterLengendaries;
	void drawActive();
	void drawMenuEntry();
};