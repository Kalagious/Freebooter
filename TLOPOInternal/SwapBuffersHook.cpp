#include "SwapBuffersHook.h"
#include <vector>
#include <string>
#include <sstream>
#include "cheats.h"
#include "GeneralObject.h"
#include <fstream>

extern Cheats* cheatsGlobal;


SwapBuffersHook::tTargetPtr SwapBuffersHook::oFunction;


bool __fastcall SwapBuffersHook::hookFunction(HDC hDc)
{
	if (!cheatsGlobal->screenManager->imGUIInitialized)
		cheatsGlobal->screenManager->initializeImGui(hDc);

	cheatsGlobal->screenManager->drawGUI();

	
	return SwapBuffersHook::oFunction(hDc);
}

SwapBuffersHook::SwapBuffersHook(void* moduleBaseIn)
{
	hookName = "SwapBuffers Hook";
	hookLen = 15;	
	viSig = { 0x48, 0x89, 0x5C, 0x24, 0x08, 0x48, 0x89, 0x74, 0x24, 0x10, 0x57, 0x48, 0x83, 0xEC, 0x40, 0x48, 0x8B, 0xF1, 0x33, 0xFF, 0xE8, 0x3F, 0x3F, 0x3F, 0x3F, 0x85, 0xC0, 0x74, 0x16, 0x8D, 0x4F, 0x01, 0x48, 0xFF, 0x15, 0x3F, 0x3F, 0x3F, 0x3F, 0x0F, 0x1F, 0x44, 0x00, 0x00, 0x33, 0xC0 };
	moduleBase = moduleBaseIn;

	iSigOffset = 0;
	enabled = false;
}


bool SwapBuffersHook::initialize()
{
	//targetAddr = signatureScan(viSig, iSigOffset, moduleBase);
	//if (!targetAddr)
	//	return false;
	targetAddr = (void*)((uint64_t)GetProcAddress(GetModuleHandle(L"opengl32.dll"), "wglSwapBuffers"));

	SwapBuffersHook::oFunction = (tTargetPtr)(targetAddr);

	SwapBuffersHook::oFunction = (tTargetPtr)DetourFunction64((void*)SwapBuffersHook::oFunction, (void*)SwapBuffersHook::hookFunction, hookLen);
	enabled = true;
	return true;
}