#pragma once
#include "hooks.h"

class RogueObject;

class PyObject_SetAttrHook : public Hook
{
public:

	bool initialize();
	PyObject_SetAttrHook(void* moduleBaseIn);
	typedef uint64_t(__fastcall* tTargetPtr)(RogueObject* pObject, RogueObject* pAttributeName, RogueObject* pValue);
	static uint64_t __fastcall hookFunction(RogueObject* pObject, RogueObject* pAttributeName, RogueObject* pValue);
	static tTargetPtr oFunction;
	static uint64_t pCannonValue;
};

