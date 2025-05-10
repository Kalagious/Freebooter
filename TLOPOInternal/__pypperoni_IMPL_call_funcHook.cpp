#include "__pypperoni_IMPL_call_funcHook.h"
#include <vector>
#include <string>
#include <sstream>
#include "cheats.h"
#include "GeneralObject.h"
#include <fstream>
#include "roguepython.h"

#define TEST_METHOD_NAME(x) cheatsGlobal->roguePython->vAttr2Str.at(cheatsGlobal->roguePython->ATTRIBUTES.x) && cheatsGlobal->roguePython->vAttr2Str.at(cheatsGlobal->roguePython->ATTRIBUTES.x) == (uint64_t)pMethod
#define TEST_STRING(x, y) cheatsGlobal->roguePython->vAttr2Str.at(cheatsGlobal->roguePython->ATTRIBUTES.x) && cheatsGlobal->roguePython->vAttr2Str.at(cheatsGlobal->roguePython->ATTRIBUTES.x) == (uint64_t)y
#define IS_FUNCTION(x) cheatsGlobal->roguePython->vPyTypes.at(cheatsGlobal->roguePython->TYPES.x) && cheatsGlobal->roguePython->vPyTypes.at(cheatsGlobal->roguePython->TYPES.x) == (uint64_t)((RogueObject*)function)->PyType
#define STACK(x) *((*pStackPointer) - x)
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
	bool bIsBuiltin = false;
	std::string sFunctionName = "";


	cheatsGlobal->roguePython->readType(function);

	// Method
	if (IS_FUNCTION(METHOD))
	{
		RogueObject* method = (RogueObject*)((uint64_t*)function)[2];
		pFunctionName = (RogueObject*)((uint64_t*)method)[8];
		bKnownType = true;

	} // Builtin Function
	else if (IS_FUNCTION(BUILTIN))
	{
		pFunctionName = (RogueObject*)*(uint64_t*)((uint64_t*)function)[2];
		bIsBuiltin = true;
		bKnownType = true;
	} // Function
	else if (IS_FUNCTION(FUNCTION))
	{
		pFunctionName = (RogueObject*)((uint64_t*)function)[2];
		bKnownType = true;
	}

	if (pFunctionName && bKnownType)
	{
		if (!bIsBuiltin)
		{
			cheatsGlobal->roguePython->readAttribute(pFunctionName);
			sFunctionName = std::string(((PyVarObjectCust*)pFunctionName)->sName);
		}
		else
		{
			sFunctionName = std::string((char*)pFunctionName);
		}
	}

	// Pre Execution Hooks
	if (cheatsGlobal->cannonFlashSuppressor->enable && TEST_STRING(PLAYFIREEFFECT, pFunctionName))
		return cheatsGlobal->roguePython->vPyTypes.at(cheatsGlobal->roguePython->TYPES.NONE);

	


	if (TEST_STRING(DOMETHOD, pFunctionName))
	{
		RogueObject* pMethod = NULL;
		if (iOpArg == 4)
			pMethod = *((*pStackPointer) - 2);
		else
			pMethod = *((*pStackPointer) - 1);

		cheatsGlobal->roguePython->readAttribute(pMethod);




	}

	if (sFunctionName.find("setVolley") != std::string::npos && cheatsGlobal->infiniteCannons->tick() && cheatsGlobal->infiniteCannons->enable)
	{
		RogueFloat* tmp = (RogueFloat*)*((*pStackPointer) - 1);
		if (tmp && cheatsGlobal->roguePython->rIOne)
		{
			if ((uint32_t)tmp->PyType == cheatsGlobal->roguePython->vPyTypes.at(cheatsGlobal->roguePython->TYPES.FLOAT) && tmp->fValue == 0);
			{
				*((*pStackPointer) - 1) = (RogueObject*)cheatsGlobal->roguePython->rIOne;
			}

		}
	}


	if (cheatsGlobal->noAttackCooldown->enable && sFunctionName.find("triggerInputLock") != std::string::npos)
		return cheatsGlobal->roguePython->vPyTypes.at(cheatsGlobal->roguePython->TYPES.NONE);






	//if (sFunctionName.find("getAreaList") != std::string::npos)
	//{
	//	RogueFloat* tmp = (RogueFloat*)STACK(1);
	//	if (tmp)
	//	{
	//		if ((uint32_t)tmp->PyType == cheatsGlobal->roguePython->vPyTypes.at(cheatsGlobal->roguePython->TYPES.FLOAT));
	//		{

	//			printf("%d %f\n", iOpArg, tmp->fValue);
	//			STACK(1) = (RogueObject*)cheatsGlobal->roguePython->createFloat(4);
	//		}

	//	}
	//}











	pRetVal = __pypperoni_IMPL_call_funcHook::oFunction(pStackPointer, iOpArg, pKwargs);
	cheatsGlobal->roguePython->readType((RogueObject*)pRetVal);
	cheatsGlobal->roguePython->readAttribute((RogueObject*)pRetVal);








	// Post Execution Hooks
	if (pRetVal)
	{
		static bool bOverwritePos = false;


		if (bOverwritePos && (sFunctionName.find("getZ") != std::string::npos || sFunctionName.find("getX") != std::string::npos) && sFunctionName.length() == 4)
		{
			((RogueFloat*)pRetVal)->fValue = -2.5;
		}



		//if (sFunctionName.find("getTeam") != std::string::npos && sFunctionName.length() == 7)
		//{
		//	RogueObject* self = *((*pStackPointer) - 0);
		//	char* pTypeName = cheatsGlobal->roguePython->readType(self);
		//	//printf("%p %s\n", self, pTypeName);
		//	if (strcmp(pTypeName, "LocalPirate"))
		//	{
		//		pRetVal = (uint64_t)cheatsGlobal->roguePython->createFloat(11);
		//	}
		//	//if (((RogueObject*)pRetVal)->PyType == (void*)cheatsGlobal->roguePython->vPyTypes.at(cheatsGlobal->roguePython->TYPES.INT));
		//	//pRetVal = (uint64_t)cheatsGlobal->roguePython->createFloat(1);
		//}


		//if (sFunctionName.find("max") != std::string::npos && sFunctionName.length() == 3 && iOpArg == 2)
		//{
		//	if (*((*pStackPointer) - 1))
		//	{

		//	
		//		if (!strcmp(cheatsGlobal->roguePython->readType(*((*pStackPointer) - 1)), "float"))
		//		{

		//			RogueFloat* tmp = (RogueFloat*)*((*pStackPointer) - 1);
		//			if (tmp->fValue = 0.5)
		//			{
		//				//printf("%p\n", (uint64_t) * ((*pStackPointer) - 1));

		//				pRetVal = (uint64_t)cheatsGlobal->roguePython->createFloat(0.1);
		//			}
		//		}
		//	}

		//}



		//if (sFunctionName.find("getDuration") != std::string::npos && sFunctionName.length() == 11 && cheatsGlobal->minigunGoBurr->bMouseDown)
		//{
		//	if (((RogueObject*)pRetVal)->PyType == (void*)cheatsGlobal->roguePython->vPyTypes.at(cheatsGlobal->roguePython->TYPES.FLOAT));
		//	pRetVal = (uint64_t)cheatsGlobal->roguePython->createFloat(0.1);
		//}



		if (!bIsBuiltin && sFunctionName.length() > 1)
		{

			cheatsGlobal->myfile << sFunctionName + "(";
			if (iOpArg > 0)
				cheatsGlobal->myfile << cheatsGlobal->roguePython->readType(*((*pStackPointer) - 0));
			cheatsGlobal->myfile << ")\n";

		}

		if (cheatsGlobal->iTicks % 500 == 0 && cheatsGlobal->noAttackCooldown)
			cheatsGlobal->noAttackCooldown->tick();


		if (cheatsGlobal->noAttackCooldown->enable && !bIsBuiltin && sFunctionName.length() > 1 && iOpArg > 0)
		{
			if (sFunctionName.find("get") != std::string::npos)
			{
				if (!strcmp(cheatsGlobal->roguePython->readType(**pStackPointer), "CombatAnimations"))
				{
					return cheatsGlobal->roguePython->vPyTypes.at(cheatsGlobal->roguePython->TYPES.NONE);
				}
			}
		}


		if (cheatsGlobal->cooldownsAreCringe->enable && TEST_STRING(GETRECHARGETIME, pFunctionName))
			((RogueFloat*)pRetVal)->fValue = cheatsGlobal->cooldownsAreCringe->fDelay;

		else if (cheatsGlobal->sniperElite->enable && TEST_STRING(GETMODIFIEDRANGE, pFunctionName) && cheatsGlobal->sniperElite->tick())
		{
			if (((RogueFloat*)pRetVal)->PyType == (void*)cheatsGlobal->roguePython->vPyTypes.at(cheatsGlobal->roguePython->TYPES.FLOAT))
				((RogueFloat*)pRetVal)->fValue = cheatsGlobal->sniperElite->fDistance;
		}
		else if (cheatsGlobal->moreLikeGuidelines->enable && TEST_STRING(OBEYSCODE, pFunctionName) && cheatsGlobal->roguePython->vPyTypes.at(cheatsGlobal->roguePython->TYPES.BOOLTRUE))
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