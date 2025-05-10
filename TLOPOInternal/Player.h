#pragma once
//#include "general.h"
#include "NextPosObject.h"
class Player
{
public:
	char pad_0000[56]; //0x0000
	char* name; //0x0038
	char pad_0040[160]; //0x0040
	NextPosObject* nextPosObject; //0x00E0
	char pad_00E8[16]; //0x00E8
	char* avatarDoId; //0x00F8
	char pad_0100[3968]; //0x0100
}; //Size: 0x1080
