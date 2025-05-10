#pragma once
#include "module.h"
#include "general.h"
#include "roguepython.h"

class Cheats;

class CannonFlashSuppressor : public Module
{
public:
	CannonFlashSuppressor(Cheats* cheatsIn);
	Cheats* cheats;
	void drawActive();
	void drawMenuEntry();
};