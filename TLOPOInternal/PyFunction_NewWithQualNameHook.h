#pragma once
#include "hooks.h"


class PyFunction_NewWithQualNameHook : public Hook
{
public:

	bool initialize();
	PyFunction_NewWithQualNameHook(void* moduleBaseIn);
	typedef int64_t (__fastcall* tTargetPtr)(int64_t a1, int64_t a2, int64_t a3);
	static int64_t __fastcall hookFunction(int64_t a1, int64_t a2, int64_t a3);
	static tTargetPtr oFunction;
};

