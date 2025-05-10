#pragma once
#include "module.h"
#include "NextPosObject.h"
#include "general.h"

class Cheats;

class Fly : public Module
{
public:
	Fly(Cheats* cheatsIn);
	bool tick();
	float vertSpeedMult;
	Vector3 virtualPos;
	Cheats* cheats;


	void drawActive();
	void drawMenuEntry();
};