#include "__pypperoni_IMPL_call_funcHook.h"
#include <vector>
#include <string>
#include <sstream>
#include "cheats.h"
#include "GeneralObject.h"
#include <fstream>
#include "roguepython.h"

#define TEST_STRING(x) cheatsGlobal->roguePython->vAttr2Str.at(cheatsGlobal->roguePython->ATTRIBUTES.x) && cheatsGlobal->roguePython->vAttr2Str.at(cheatsGlobal->roguePython->ATTRIBUTES.x) == (uint64_t)pFunctionName
#define IS_FUNCTION(x) cheatsGlobal->roguePython->vPyTypes.at(cheatsGlobal->roguePython->TYPES.x) && cheatsGlobal->roguePython->vPyTypes.at(cheatsGlobal->roguePython->TYPES.x) == (uint64_t)((RogueObject*)function)->PyType

extern Cheats* cheatsGlobal;


__pypperoni_IMPL_call_funcHook::tTargetPtr __pypperoni_IMPL_call_funcHook::oFunction;


uint64_t __fastcall __pypperoni_IMPL_call_funcHook::hookFunction(RogueObject*** pStackPointer, int64_t iOpArg, RogueObject* pKwargs)
{
	RogueObject** pfunc = (*pStackPointer) - iOpArg - 1;
	RogueObject* function = *pfunc;

	if (!function)
		return __pypperoni_IMPL_call_funcHook::oFunction(pStackPointer, iOpArg, pKwargs);



	RogueObject* pFunctionName = NULL;
	uint64_t pRetVal = NULL;
	bool bKnownType = false;
	std::string sFunctionName = "";


	cheatsGlobal->roguePython->readType(function);

	// Method
	if (IS_FUNCTION(METHOD))
	{
		RogueObject* method = (RogueObject*)((uint64_t*)function)[2];
		pFunctionName = (RogueObject*)((uint64_t*)method)[8];
		bKnownType = true;

	} // Builtin Function
	//else if (cheatsGlobal->roguePython->vPyTypes.at(cheatsGlobal->roguePython->TYPES.BUILTIN) == (uint64_t)((RogueObject*)function)->PyType)
	//{

	//} // Function
	else if (IS_FUNCTION(FUNCTION))
	{
		pFunctionName = (RogueObject*)((uint64_t*)function)[8];
		bKnownType = true;
	}

	if (pFunctionName && bKnownType)
	{
		cheatsGlobal->roguePython->readAttribute(pFunctionName);
		sFunctionName = std::string(((PyVarObjectCust*)pFunctionName)->sName);
;	}


	// Pre Execution Hooks
	if (cheatsGlobal->cannonFlashSuppressor->enable && TEST_STRING(PLAYFIREEFFECT))
		return cheatsGlobal->roguePython->vPyTypes.at(cheatsGlobal->roguePython->TYPES.NONE);


	if (sFunctionName.find("hitNail") != std::string::npos)
	{
		//printf("%f %d\n", ((RogueFloat*)*((*pStackPointer) - 1))->fValue, iOpArg);
		static RogueFloat* tmpFloat = cheatsGlobal->roguePython->createFloat(1.875);
		*((*pStackPointer) - 1) = (RogueObject*)tmpFloat;
	}
	if (sFunctionName.find("doMethod") != std::string::npos)
	{
		if (iOpArg == 3)
		{
			printf("%s %s %d\n", sFunctionName.c_str(), ((PyVarObjectCust*)*((*pStackPointer) - 1))->sName, iOpArg);
			std::string tmpStr(((PyVarObjectCust*)*((*pStackPointer) - 1))->sName);
			if (tmpStr.find("StartFighting") != std::string::npos)
			{
				printf("yay");
				return cheatsGlobal->roguePython->vPyTypes.at(cheatsGlobal->roguePython->TYPES.NONE);
			}
		}
		else
		{ 
			printf("%s %s %d\n", sFunctionName.c_str(), ((PyVarObjectCust*)*((*pStackPointer) - 2))->sName, iOpArg);
			std::string tmpStr(((PyVarObjectCust*)*((*pStackPointer) - 2))->sName);
			if (tmpStr.find("StartFighting") != std::string::npos)
			{
				printf("yay");

				return cheatsGlobal->roguePython->vPyTypes.at(cheatsGlobal->roguePython->TYPES.NONE);
			}
		}

		//return cheatsGlobal->roguePython->vPyTypes.at(cheatsGlobal->roguePython->TYPES.NONE);

		//*((*pStackPointer) - 1) = (RogueObject*)0x00007FF7B7FCCD40;
		//static RogueFloat* tmpFloat2 = cheatsGlobal->roguePython->createFloat(0);
		//((RogueFloat*)*((*pStackPointer) - 1))->fValue = 5
	}


	pRetVal = __pypperoni_IMPL_call_funcHook::oFunction(pStackPointer, iOpArg, pKwargs);
	cheatsGlobal->roguePython->readType((RogueObject*)pRetVal);


	// Post Execution Hooks
	if (pRetVal)
	{
		if (cheatsGlobal->cooldownsAreCringe->enable && TEST_STRING(GETRECHARGETIME))
			((RogueFloat*)pRetVal)->fValue = cheatsGlobal->cooldownsAreCringe->fDelay;

		else if (cheatsGlobal->sniperElite->enable && TEST_STRING(GETMODIFIEDRANGE) && cheatsGlobal->sniperElite->tick())
		{
			if (((RogueFloat*)pRetVal)->PyType == (void*)cheatsGlobal->roguePython->vPyTypes.at(cheatsGlobal->roguePython->TYPES.FLOAT))
				((RogueFloat*)pRetVal)->fValue = cheatsGlobal->sniperElite->fDistance;
		}
		else if (cheatsGlobal->moreLikeGuidelines->enable && TEST_STRING(OBEYSCODE) && cheatsGlobal->roguePython->vPyTypes.at(cheatsGlobal->roguePython->TYPES.BOOLTRUE))
			if (pRetVal == (uint64_t)cheatsGlobal->roguePython->vPyTypes.at(cheatsGlobal->roguePython->TYPES.BOOLFALSE))
				pRetVal = cheatsGlobal->roguePython->vPyTypes.at(cheatsGlobal->roguePython->TYPES.BOOLTRUE);



	}

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