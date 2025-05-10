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


class RogueType
{
public:
	int64_t iRefCount;
	char pad_0008[16];
	char* pName;
	char pad_0020[888];
	class RogueFunction* pFunctions;
};

class RogueString
{
public:
	int64_t iRefCount;
	char pad_0008[8];
	int64_t iLength;
	char pad_0018[24];
	char sData[800];
};

class RogueFunction
{
public:
	int64_t iRefCount;
	int64_t pType;
	char pad_0010[40];
	int64_t pReturnType;
	RogueString* pName;
	char pad_0048[32];
	int64_t pFullName;
	char pad_0070[24];
};






class RoguePython
{
public:
	RoguePython(Cheats* cheatsIn);
	void init();
	char* readType(RogueObject* pAttributeValue);
	void readAttribute(RogueObject* pAttributeName);
	void readValue(RogueInt* pValue);
	RogueFloat* createFloat(float fValue);
	RogueInt* createInt(int64_t iValue);
	void dumpFunctions(RogueType* pStart);
	std::string readString(RogueString* pString);



	RogueInt* rIOne;

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
		static const uint32_t DOMETHOD = 8;
		static const uint32_t STARTFIGHTING = 9;
		static const uint32_t TESTLEGENDARY = 10;
		static const uint32_t CURRENTORNEXTSTATE = 11;
		static const uint32_t REELINGFISH = 12;
		static const uint32_t HOOKED = 13;
		static const uint32_t FISHONHOOK = 14;
		static const uint32_t SWIMMING = 15;
		static const uint32_t OFFSCREEN = 16;
		static const uint32_t SETVOLLEY = 17;





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
		static const uint32_t FISH = 8;


		static const uint32_t STRING = 8;
		static const uint32_t DICT = 9;
		static const uint32_t LIST = 10;
	
	} TYPES;


	std::vector<uint64_t> vPyTypes;
	std::vector<uint64_t> vAttr2Str;

};