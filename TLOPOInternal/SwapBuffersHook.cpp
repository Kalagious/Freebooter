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
	hookLen = 16;	
	viSig = { 0x40, 0x53, 0x48, 0x83, 0xEC, 0x20, 0x48, 0x8B, 0xD9, 0x48, 0x8B, 0x89, 0x90, 0x0C, 0x00, 0x00, 0x48, 0x85, 0xC9, 0x74, 0x55, 0x80, 0xBB, 0xE8, 0x01, 0x00, 0x00, 0x00, 0x74, 0x4C, 0x48, 0x89, 0x7C, 0x24, 0x30, 0x48, 0x8B, 0xBB, 0x60, 0x01, 0x00 };

	moduleBase = moduleBaseIn;

	iSigOffset = 0;
	enabled = false;
}


bool SwapBuffersHook::initialize()
{
	//targetAddr = signatureScan(viSig, iSigOffset, moduleBase);
	//if (!targetAddr)
	//	return false;
	targetAddr = (void*)((uint64_t)moduleBase + 0x43200);
	SwapBuffersHook::oFunction = (tTargetPtr)(targetAddr);

	SwapBuffersHook::oFunction = (tTargetPtr)DetourFunction64((void*)SwapBuffersHook::oFunction, (void*)SwapBuffersHook::hookFunction, hookLen);
	enabled = true;
	return true;
}