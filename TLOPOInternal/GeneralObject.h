#pragma once
#include "general.h"

class Object
{
public:
	char pad_0000[56]; //0x0000
	uint64_t pName; //0x0038
	char pad_0040[8]; //0x0040
	int8_t iNameLen; //0x0048
	char pad_0049[432]; //0x0049
}; //Size: 0x01F9

