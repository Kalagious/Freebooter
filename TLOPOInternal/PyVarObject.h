#pragma once
#include "general.h"

class PyVarObjectCust
{
public:
	char pad_0000[16]; //0x0000
	int64_t iNameLen; //0x0010
	char pad_0018[24]; //0x0018
	char sName[16]; //0x0030
	char pad_0040[8]; //0x0040
}; //Size: 0x0048
