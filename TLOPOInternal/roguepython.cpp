#include "roguepython.h"
#include "cheats.h"

RoguePython::RoguePython(Cheats* cheatsIn)
{
	cheats = cheatsIn;
	rIOne = nullptr;
}


void RoguePython::init()
{

	for (int i = 0; i < 9; i++)
		vPyTypes.push_back(0);

	for (int i = 0; i < 18; i++)
		vAttr2Str.push_back(0);


}


RogueFloat* RoguePython::createFloat(float fValue)
{
	if (!vPyTypes.at(TYPES.FLOAT))
		return NULL;
	
	RogueFloat* tmpFloat = new RogueFloat();
	if (!tmpFloat)
		return NULL;
	tmpFloat->iRefCnt = 10;
	tmpFloat->PyType = (RogueFloat*)vPyTypes.at(TYPES.FLOAT);
	tmpFloat->fValue = fValue;

	return tmpFloat;
}

RogueInt* RoguePython::createInt(int64_t iValue)
{
	if (!vPyTypes.at(TYPES.INT))
		return NULL;

	RogueInt* tmpInt = new RogueInt();
	if (!tmpInt)
		return NULL;
	tmpInt->iRefCnt = 10;
	tmpInt->PyType = (RogueFloat*)vPyTypes.at(TYPES.INT);
	tmpInt->iValue = iValue;

	return tmpInt;
}

char* RoguePython::readType(RogueObject* pValue)
{
	if (!pValue)
		return 0x0;

	bool bTypesFound = true;
	for (int i = 0; i < vPyTypes.size(); i++)
		if (!vPyTypes.at(i))
			bTypesFound = false;

	char* pTypeName = (char*)((uint64_t*)((uint64_t*)pValue)[1])[3];
	uint64_t pType = ((uint64_t*)pValue)[1];
	
	if (!TryGetCString(pTypeName))
		return 0;

	if (bTypesFound || !cheats->hookManager->bHooksInitialized)
		return pTypeName;

	readValue((RogueInt*)pValue);
	

	if (vPyTypes.at(TYPES.INT) == NULL)
	{
		if (!strcmp(pTypeName, "int"))
		{
			printf(" [*] RP - Int Type Found %p\n", pType);
			vPyTypes.at(TYPES.INT) = pType;
		}
	}
	if (vPyTypes.at(TYPES.BOOLTRUE) == NULL)
	{
		if (!strcmp(pTypeName, "bool") && ((uint64_t*)pValue)[2] == 1)
		{
			printf(" [*] RP - Bool Type True Found\n");
			vPyTypes.at(TYPES.BOOLTRUE) = (uint64_t)pValue;
		}
	}
	if (vPyTypes.at(TYPES.BOOLFALSE) == NULL)
	{
		if (!strcmp(pTypeName, "bool") && ((uint64_t*)pValue)[2] == 0)
		{
			printf(" [*] RP - Bool Type False Found\n");
			vPyTypes.at(TYPES.BOOLFALSE) = (uint64_t)pValue;
		}
	}
	if (vPyTypes.at(TYPES.FLOAT) == NULL)
	{
		if (!strcmp(pTypeName, "float"))
		{
			printf(" [*] RP - Float Type Found %p\n", pType);
			vPyTypes.at(TYPES.FLOAT) = pType;
		}
	}
	if (vPyTypes.at(TYPES.METHOD) == NULL)
	{
		if (!strcmp(pTypeName, "method"))
		{
			printf(" [*] RP - Method Type Found\n");
			vPyTypes.at(TYPES.METHOD) = pType;
		}
	}
	if (vPyTypes.at(TYPES.BUILTIN) == NULL)
	{
		if (!strcmp(pTypeName, "builtin_function_or_method"))
		{
			printf(" [*] RP - BuiltIn Type Found\n");
			vPyTypes.at(TYPES.BUILTIN) = pType;
		}
	}
	if (vPyTypes.at(TYPES.NONE) == NULL)
	{
		if (!strcmp(pTypeName, "NoneType"))
		{
			printf(" [*] RP - None Type Found\n");
			vPyTypes.at(TYPES.NONE) = (uint64_t)pValue;
		}
	}
	if (vPyTypes.at(TYPES.FUNCTION) == NULL)
	{
		if (!strcmp(pTypeName, "function"))
		{
			printf(" [*] RP - Function Type Found\n");
			vPyTypes.at(TYPES.FUNCTION) = pType;
		}
	}
	if (vPyTypes.at(TYPES.FISH) == NULL)
	{
		if (!strcmp(pTypeName, "Fish"))
		{
			printf(" [*] RP - Fish Type Found\n");
			vPyTypes.at(TYPES.FISH) = pType;
		}
	}
	return pTypeName;
}



void RoguePython::readAttribute(RogueObject* pAttributeName)
{

	if (!pAttributeName)
		return;

	bool bStringsFound = true;
	for (int i = 0; i < vAttr2Str.size(); i++)
		if (!vAttr2Str.at(i))
			bStringsFound = false;
	if (bStringsFound || !pAttributeName)
		return;


	PyVarObjectCust* tmp = (PyVarObjectCust*)pAttributeName;
	std::string tmpAttName;
	
	if (TryGetCString(tmp->sName))
	{
		tmpAttName = tmp->sName;
	}
	else
	{
		return;
	}




	

	if (vAttr2Str.at(ATTRIBUTES.SPEED) == NULL)
		if (tmpAttName.find("speed") != std::string::npos && tmpAttName.length() == 5)
			vAttr2Str.at(ATTRIBUTES.SPEED) = (uint64_t)pAttributeName;

	if (vAttr2Str.at(ATTRIBUTES.SHIPSPEED) == NULL)
		if (tmpAttName.find("_ShipPilot__speed") != std::string::npos)
			vAttr2Str.at(ATTRIBUTES.SHIPSPEED) = (uint64_t)pAttributeName;

	if (vAttr2Str.at(ATTRIBUTES.SHIPROTATIONSPEED) == NULL)
		if (tmpAttName.find("_ShipPilot__rotationSpeed") != std::string::npos)
			vAttr2Str.at(ATTRIBUTES.SHIPROTATIONSPEED) = (uint64_t)pAttributeName;

	if (vAttr2Str.at(ATTRIBUTES.CANNONRECHARGE) == NULL)
		if (tmpAttName.find("recharge") != std::string::npos)
			vAttr2Str.at(ATTRIBUTES.CANNONRECHARGE) = (uint64_t)pAttributeName;

	if (vAttr2Str.at(ATTRIBUTES.GETRECHARGETIME) == NULL)
		if (tmpAttName.find("RechargeTime") != std::string::npos)
			vAttr2Str.at(ATTRIBUTES.GETRECHARGETIME) = (uint64_t)pAttributeName;

	if (vAttr2Str.at(ATTRIBUTES.GETMODIFIEDRANGE) == NULL)
		if (tmpAttName.find("getModifiedAttackRange") != std::string::npos)
			vAttr2Str.at(ATTRIBUTES.GETMODIFIEDRANGE) = (uint64_t)pAttributeName;

	if (vAttr2Str.at(ATTRIBUTES.OBEYSCODE) == NULL)
		if (tmpAttName.find("obeysPirateCode") != std::string::npos)
			vAttr2Str.at(ATTRIBUTES.OBEYSCODE) = (uint64_t)pAttributeName;

	if (vAttr2Str.at(ATTRIBUTES.PLAYFIREEFFECT) == NULL)
		if (tmpAttName.find("playFireEffect") != std::string::npos)
			vAttr2Str.at(ATTRIBUTES.PLAYFIREEFFECT) = (uint64_t)pAttributeName;

	if (vAttr2Str.at(ATTRIBUTES.DOMETHOD) == NULL)
		if (tmpAttName.find("doMethod") != std::string::npos)
			vAttr2Str.at(ATTRIBUTES.DOMETHOD) = (uint64_t)pAttributeName;

	if (vAttr2Str.at(ATTRIBUTES.STARTFIGHTING) == NULL)
		if (tmpAttName.find("StartFighting") != std::string::npos)
			vAttr2Str.at(ATTRIBUTES.STARTFIGHTING) = (uint64_t)pAttributeName;

	if (vAttr2Str.at(ATTRIBUTES.TESTLEGENDARY) == NULL)
		if (tmpAttName.find("testLegendaryFishingGameLaterTask") != std::string::npos)
			vAttr2Str.at(ATTRIBUTES.TESTLEGENDARY) = (uint64_t)pAttributeName;

	if (vAttr2Str.at(ATTRIBUTES.CURRENTORNEXTSTATE) == NULL)
		if (tmpAttName.find("getCurrentOrNextState") != std::string::npos)
			vAttr2Str.at(ATTRIBUTES.CURRENTORNEXTSTATE) = (uint64_t)pAttributeName;

	if (vAttr2Str.at(ATTRIBUTES.REELINGFISH) == NULL)
		if (tmpAttName.find("ReelingFish") != std::string::npos)
			vAttr2Str.at(ATTRIBUTES.REELINGFISH) = (uint64_t)pAttributeName;

	if (vAttr2Str.at(ATTRIBUTES.HOOKED) == NULL)
		if (tmpAttName.find("Hooked") != std::string::npos)
			vAttr2Str.at(ATTRIBUTES.HOOKED) = (uint64_t)pAttributeName;

	if (vAttr2Str.at(ATTRIBUTES.FISHONHOOK) == NULL)
		if (tmpAttName.find("FishOnHook") != std::string::npos)
			vAttr2Str.at(ATTRIBUTES.FISHONHOOK) = (uint64_t)pAttributeName;

	if (vAttr2Str.at(ATTRIBUTES.SWIMMING) == NULL)
		if (tmpAttName.find("Swimming") != std::string::npos)
			vAttr2Str.at(ATTRIBUTES.SWIMMING) = (uint64_t)pAttributeName;

	if (vAttr2Str.at(ATTRIBUTES.OFFSCREEN) == NULL)
		if (tmpAttName.find("Offscreen") != std::string::npos)
			vAttr2Str.at(ATTRIBUTES.OFFSCREEN) = (uint64_t)pAttributeName;

	if (vAttr2Str.at(ATTRIBUTES.SETVOLLEY) == NULL)
		if (tmpAttName.find("SetVolley") != std::string::npos)
			vAttr2Str.at(ATTRIBUTES.SETVOLLEY) = (uint64_t)pAttributeName;


}



void RoguePython::dumpFunctions(RogueType* pStart)
{
	RogueFunction* pCurrent = (RogueFunction*)((uint64_t)pStart->pFunctions + 0x18);

	while (pCurrent)
	{
		printf("%s\n", readString(pCurrent->pName));
		pCurrent += 1;
	}
}

std::string RoguePython::readString(RogueString* pString)
{
	std::string sOut;
	for (int i = 0; i < pString->iLength; i++)
	{
		sOut += pString->sData[i];
	}
	return sOut;
}



void RoguePython::readValue(RogueInt* pValue)
{
	if (!pValue || rIOne)
		return;

	if (vPyTypes.at(TYPES.INT) && pValue->PyType == (void*)vPyTypes.at(TYPES.INT))
		if (pValue->iValue == 1)
		{
			rIOne = pValue;
			printf(" [*] Found One!\n");
		}

}