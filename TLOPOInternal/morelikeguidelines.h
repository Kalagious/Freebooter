#pragma once
#include "module.h"
#include "general.h"
#include "roguepython.h"

class Cheats;

class MoreLikeGuidelines : public Module
{
public:
	MoreLikeGuidelines(Cheats* cheatsIn);
	Cheats* cheats;
	void drawActive();
	void drawMenuEntry();
};