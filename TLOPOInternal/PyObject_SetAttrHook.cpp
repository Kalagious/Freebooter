#include "PyObject_SetAttrHook.h"
#include <vector>
#include <string>
#include <sstream>
#include "cheats.h"
#include "allclasses.h"
#include "roguepython.h"


extern Cheats* cheatsGlobal;


#define TEST_STRING(x) cheatsGlobal->roguePython->vAttr2Str.at(cheatsGlobal->roguePython->ATTRIBUTES.x) == (uint64_t)pAttributeName

PyObject_SetAttrHook::tTargetPtr PyObject_SetAttrHook::oFunction;


uint64_t __fastcall PyObject_SetAttrHook::hookFunction(RogueObject* pObject, RogueObject* pAttributeName, RogueObject* pValue)
{
	cheatsGlobal->roguePython->readAttribute((RogueObject*)pAttributeName);
	cheatsGlobal->roguePython->readType((RogueObject*)pValue);

	if (!pValue)
		return PyObject_SetAttrHook::oFunction(pObject, pAttributeName, pValue);



	PyVarObjectCust* tmp = (PyVarObjectCust*)pAttributeName;
	std::string tmpAttName(tmp->sName);
		

	uint64_t pModValue = 0;


	//cheatsGlobal->myfile << tmpAttName.c_str();
	//cheatsGlobal->myfile << '\n';
	if (cheatsGlobal->turnyBoi->enable && TEST_STRING(SHIPROTATIONSPEED))
	{
		uint64_t tmpTurn = (uint64_t)cheatsGlobal->turnyBoi->tick();
		if (tmpTurn && ((RogueFloat*)(pValue))->fValue != 0)
			pModValue = tmpTurn;
	}
	else if (cheatsGlobal->zoooom->enable && TEST_STRING(SPEED) && cheatsGlobal->zoooom->tick() && ((RogueFloat*)(pValue))->fValue != 0)
		pModValue = (uint64_t)cheatsGlobal->zoooom->pSpeedFloat;

	else if (cheatsGlobal->zoooomShipEdition->enable && TEST_STRING(SHIPSPEED) && cheatsGlobal->zoooomShipEdition->tick() && ((RogueFloat*)(pValue))->fValue != 0)
		pModValue = (uint64_t)cheatsGlobal->zoooomShipEdition->pSpeedFloat;

	else if (cheatsGlobal->minigunGoBurr->enable && TEST_STRING(CANNONRECHARGE) && cheatsGlobal->minigunGoBurr->tick())
		pModValue = (uint64_t)cheatsGlobal->minigunGoBurr->pRechargeFloat;

	if (!pModValue)
		pModValue = (uint64_t)pValue;
	
	return PyObject_SetAttrHook::oFunction(pObject, pAttributeName, (RogueObject*)pModValue);
}


PyObject_SetAttrHook::PyObject_SetAttrHook(void* moduleBaseIn)
{ 
	hookName = "RogueObject_SetAttrHook Hook";
	hookLen = 16;
	viSig = { 0x48, 0xFF, 0x02, 0x48, 0x8D, 0x4C, 0x24, 0x48, 0xE8, 0x3F, 0x3F, 0x3F, 0x3F, 0x48, 0x8B, 0x83, 0x98, 0x00, 0x00, 0x00, 0x48, 0x85, 0xC0, 0x74, 0x3F, 0x48, 0x8B, 0x54, 0x24, 0x48, 0x4C, 0x8B, 0xC6, 0x48, 0x8B, 0xCF, 0xFF, 0xD0, 0x48, 0x8B, 0x4C, 0x24, 0x48, 0x8B, 0xD8, 0x48, 0x83, 0x29, 0x01, 0x75, 0x3F, 0x48, 0x8B, 0x51, 0x08, 0xFF, 0x52, 0x30 };
	moduleBase = moduleBaseIn;
	iSigOffset = 0x4B;
	enabled = false;
}


bool PyObject_SetAttrHook::initialize()
{
	targetAddr = signatureScan(viSig, iSigOffset, moduleBase);
	if (!targetAddr)
		return false;

	PyObject_SetAttrHook::oFunction = (tTargetPtr)(targetAddr);
	PyObject_SetAttrHook::oFunction = (tTargetPtr)DetourFunction64((void*)PyObject_SetAttrHook::oFunction, (void*)PyObject_SetAttrHook::hookFunction, hookLen);
	enabled = true;
	return true;
}