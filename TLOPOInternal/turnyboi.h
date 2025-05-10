#pragma once
#include "module.h"
#include "general.h"
#include "roguepython.h"

class Cheats;

class TurnyBoi : public Module
{
public:
	TurnyBoi(Cheats* cheatsIn);
	RogueObject* tick();
	Cheats* cheats;
	RogueFloat* pRightFloat;
	RogueFloat* pLeftFloat;
	float fTurnSpeed;
	void drawActive();
	void drawMenuEntry();
};