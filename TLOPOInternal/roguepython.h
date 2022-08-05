#pragma once
#include "general.h"

class Cheats;

class RogueObject
{
public:
	uint64_t iRefCnt;
	void* PyType;
};

class RogueFloat
{
public:
	uint64_t iRefCnt;
	void* PyType;
	uint32_t padding;
	float fValue;
};

class RogueInt
{
public:
	uint64_t iRefCnt;
	void* PyType;
	uint32_t padding;
	int64_t iValue;
};

class RoguePython
{
public:
	RoguePython(Cheats* cheatsIn);
	void init();
	void readType(RogueObject* pAttributeValue);
	void readAttribute(RogueObject* pAttributeName);
	RogueFloat* createFloat(float fValue);
	RogueInt* createInt(int64_t iValue);
	Cheats* cheats;

	struct _attributes
	{
		static const uint32_t SPEED = 0;
		static const uint32_t SHIPSPEED = 1;
		static const uint32_t SHIPROTATIONSPEED = 2;
		static const uint32_t CANNONRECHARGE = 3;
		static const uint32_t GETRECHARGETIME = 4;
		static const uint32_t GETMODIFIEDRANGE = 5;
		static const uint32_t OBEYSCODE = 6;
		static const uint32_t PLAYFIREEFFECT = 7;




	} ATTRIBUTES;

	struct _types
	{
		static const uint32_t FLOAT = 0;
		static const uint32_t METHOD = 1;
		static const uint32_t BUILTIN = 2;
		static const uint32_t INT = 3;
		static const uint32_t BOOLTRUE = 4;
		static const uint32_t BOOLFALSE = 5;
		static const uint32_t NONE = 6;
		static const uint32_t FUNCTION = 7;


		static const uint32_t STRING = 8;
		static const uint32_t DICT = 9;
		static const uint32_t LIST = 10;
	
	} TYPES;


	std::vector<uint64_t> vPyTypes;
	std::vector<uint64_t> vAttr2Str;
};