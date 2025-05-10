#include "PyDict_SetItemHook.h"
#include <vector>
#include <string>
#include <sstream>
#include "cheats.h"
#include "GeneralObject.h"
#include <fstream>

extern Cheats* cheatsGlobal;


PyDict_SetItemHook::tTargetPtr PyDict_SetItemHook::oFunction;


int64_t __fastcall PyDict_SetItemHook::hookFunction(int64_t a1, int64_t a2, int64_t a3)
{
	return PyDict_SetItemHook::oFunction(a1, a2, a3);
}


PyDict_SetItemHook::PyDict_SetItemHook(void* moduleBaseIn)
{
	hookName = "PyDict_SetItem Hook";
	hookLen = 15;
	viSig = { 0x0B, 0x48, 0x39, 0x42, 0x08, 0x75, 0x0A, 0x48, 0x8B, 0x42, 0x18, 0x48, 0x83, 0xF8, 0xFF, 0x75, 0x0E, 0x48, 0x8B, 0xCB, 0xE8, 0x53, 0x38, 0xFC, 0xFF, 0x48, 0x83, 0xF8, 0xFF, 0x74, 0xC6, 0x4C, 0x8B, 0xCE, 0x4C, 0x8B, 0xC0, 0x48, 0x8B, 0xD3, 0x48, 0x8B, 0xCF, 0x48, 0x8B, 0x5C, 0x24, 0x30, 0x48, 0x8B, 0x74, 0x24, 0x38, 0x48, 0x83, 0xC4, 0x20, 0x5F };
	moduleBase = moduleBaseIn;
	iSigOffset = 0x54;
	enabled = false;
}


bool PyDict_SetItemHook::initialize()
{
	targetAddr = signatureScan(viSig, iSigOffset, moduleBase);
	if (!targetAddr)
		return false;

	PyDict_SetItemHook::oFunction = (tTargetPtr)(targetAddr);

	PyDict_SetItemHook::oFunction = (tTargetPtr)DetourFunction64((void*)PyDict_SetItemHook::oFunction, (void*)PyDict_SetItemHook::hookFunction, hookLen);
	enabled = true;
	return true;
}