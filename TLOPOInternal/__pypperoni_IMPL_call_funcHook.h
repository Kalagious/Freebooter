#pragma once
#include "hooks.h"

class RogueObject;

class __pypperoni_IMPL_call_funcHook : public Hook
{
public:

	bool initialize();
	__pypperoni_IMPL_call_funcHook(void* moduleBaseIn);
	typedef uint64_t (__fastcall* tTargetPtr)(RogueObject*** pStackPointer, int64_t iOpArg, RogueObject* pKwargs);
	static uint64_t __fastcall hookFunction(RogueObject*** pStackPointer, int64_t iOpArg, RogueObject* pKwargs);
	static tTargetPtr oFunction;
};

