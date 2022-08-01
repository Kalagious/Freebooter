#include "__pypperoni_IMPL_call_funcHook.h"
#include <vector>
#include <string>
#include <sstream>
#include "cheats.h"
#include "GeneralObject.h"
#include <fstream>
#include "roguepython.h"

#define TEST_STRING(x) cheatsGlobal->roguePython->vAttr2Str.at(cheatsGlobal->roguePython->ATTRIBUTES.x) == (uint64_t)pAttributeName

extern Cheats* cheatsGlobal;


__pypperoni_IMPL_call_funcHook::tTargetPtr __pypperoni_IMPL_call_funcHook::oFunction;


uint64_t __fastcall __pypperoni_IMPL_call_funcHook::hookFunction(RogueObject*** pStackPointer, int64_t iOpArg, RogueObject* pKwargs)
{
	RogueObject** pfunc = (*pStackPointer) - iOpArg - 1;
	RogueObject* method = *pfunc;


	uint64_t pRetVal = NULL;

	cheatsGlobal->roguePython->readType(method);

	if (cheatsGlobal->roguePython->vPyTypes.at(cheatsGlobal->roguePython->TYPES.METHOD) == (uint64_t)((RogueObject*)method)->PyType)
	{
		RogueObject* function = (RogueObject*)((uint64_t*)method)[2];
		RogueObject* pAttributeName = (RogueObject*)((uint64_t*)function)[8];


		pRetVal = __pypperoni_IMPL_call_funcHook::oFunction(pStackPointer, iOpArg, pKwargs);

		PyVarObjectCust* tmp = (PyVarObjectCust*)pAttributeName;
		std::string tmpAttName(tmp->sName);
		static int tmpInt = 0;
		if (tmpInt < 10)
			tmpInt++;
		else
			tmpInt = 0;
		if (tmpAttName.find("getTeam") != std::string::npos && tmpAttName.length() == 7)
		{
			pRetVal = 0x00007FF77F9AC100+0x20*tmpInt;
			printf("%s  %p %p %d\n", tmp->sName, pStackPointer, pRetVal, iOpArg);

		}




		
		cheatsGlobal->roguePython->readAttribute(pAttributeName);
		if (pRetVal)
		{
			if (cheatsGlobal->cooldownsAreCringe->enable && TEST_STRING(GETRECHARGETIME))
				((RogueFloat*)pRetVal)->fValue = cheatsGlobal->cooldownsAreCringe->fDelay;

			else if (cheatsGlobal->sniperElite->enable && TEST_STRING(GETMODIFIEDRANGE) && cheatsGlobal->sniperElite->tick())
			{
				//((RogueFloat*)pRetVal)->fValue = 10;
				//pRetVal = (uint64_t)cheatsGlobal->sniperElite->pDistanceFloat;
				printf("%p\n", pRetVal);
			}
			else if (cheatsGlobal->moreLikeGuidelines->enable && TEST_STRING(OBEYSCODE) && cheatsGlobal->roguePython->vPyTypes.at(cheatsGlobal->roguePython->TYPES.BOOLTRUE))
				pRetVal = cheatsGlobal->roguePython->vPyTypes.at(cheatsGlobal->roguePython->TYPES.BOOLTRUE);
		}

	}


	if (!pRetVal)
		pRetVal = __pypperoni_IMPL_call_funcHook::oFunction(pStackPointer, iOpArg, pKwargs);


	return pRetVal;
}


__pypperoni_IMPL_call_funcHook::__pypperoni_IMPL_call_funcHook(void* moduleBaseIn)
{
	hookName = "__pypperoni_IMPL_call_func Hook";
	hookLen = 15;
	viSig = { 0x48, 0x89, 0x5C, 0x24, 0x08, 0x48, 0x89, 0x6C, 0x24, 0x10, 0x48, 0x89, 0x74, 0x24, 0x18, 0x48, 0x89, 0x7C, 0x24, 0x20, 0x41, 0x55, 0x41, 0x56, 0x41, 0x57, 0x48, 0x83, 0xEC, 0x20, 0x4C, 0x63, 0xF2, 0x45, 0x33, 0xFF, 0x48, 0x8B, 0x11, 0x4D, 0x8B, 0xE8, 0x48, 0x8B, 0xF9, 0x41, 0x8B, 0xEF, 0x4A, 0x8D, 0x04, 0xF5, 0x00, 0x00, 0x00, 0x00, 0x48, 0x2B, 0xD0, 0x48, 0x8B, 0x5A, 0xF8, 0x48, 0x8D, 0x72 };
	moduleBase = moduleBaseIn;
	iSigOffset = 0;
	enabled = false;
}


bool __pypperoni_IMPL_call_funcHook::initialize()
{
	targetAddr = signatureScan(viSig, iSigOffset, moduleBase);
	if (!targetAddr)
		return false;

	__pypperoni_IMPL_call_funcHook::oFunction = (tTargetPtr)(targetAddr);

	__pypperoni_IMPL_call_funcHook::oFunction = (tTargetPtr)DetourFunction64((void*)__pypperoni_IMPL_call_funcHook::oFunction, (void*)__pypperoni_IMPL_call_funcHook::hookFunction, hookLen);
	enabled = true;
	return true;
}