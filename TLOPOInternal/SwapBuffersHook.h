#pragma once
#include "hooks.h"


class SwapBuffersHook : public Hook
{
public:

	bool initialize();
	SwapBuffersHook(void* moduleBaseIn);
	typedef bool (__fastcall* tTargetPtr)(HDC hDc);
	static bool __fastcall hookFunction(HDC hDc);
	static tTargetPtr oFunction;
	static HWND hGameWindow;
	static WNDPROC hGameWindowProc;
};

