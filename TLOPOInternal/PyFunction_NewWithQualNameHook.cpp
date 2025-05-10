#include "PyFunction_NewWithQualNameHook.h"
#include <vector>
#include <string>
#include <sstream>
#include "cheats.h"
#include "GeneralObject.h"
#include <fstream>

extern Cheats* cheatsGlobal;


PyFunction_NewWithQualNameHook::tTargetPtr PyFunction_NewWithQualNameHook::oFunction;


int64_t __fastcall PyFunction_NewWithQualNameHook::hookFunction(int64_t a1, int64_t a2, int64_t a3)
{

	printf("Called: %p\n", a3);
	return PyFunction_NewWithQualNameHook::oFunction(a1, a2, a3);
}


PyFunction_NewWithQualNameHook::PyFunction_NewWithQualNameHook(void* moduleBaseIn)
{
	hookName = "PyFunction_NewWithQualName Hook";
	hookLen = 15;
	viSig = { 0x33, 0xC9, 0x48, 0x89, 0x48, 0x50, 0x48, 0xFF, 0x45, 0x00, 0x48, 0x89, 0x68, 0x10, 0x48, 0xFF, 0x06, 0x48, 0x89, 0x70, 0x18, 0x48, 0x8B, 0x45, 0x50, 0x48, 0x89, 0x43, 0x40, 0x48, 0xFF, 0x00 };
	moduleBase = moduleBaseIn;
	iSigOffset = 0x121;
	enabled = false;
}


bool PyFunction_NewWithQualNameHook::initialize()
{
	targetAddr = signatureScan(viSig, iSigOffset, moduleBase);
	if (!targetAddr)
		return false;

	PyFunction_NewWithQualNameHook::oFunction = (tTargetPtr)(targetAddr);

	PyFunction_NewWithQualNameHook::oFunction = (tTargetPtr)DetourFunction64((void*)PyFunction_NewWithQualNameHook::oFunction, (void*)PyFunction_NewWithQualNameHook::hookFunction, hookLen);
	enabled = true;
	return true;
}