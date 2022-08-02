#include "roguepython.h"
#include "cheats.h"

RoguePython::RoguePython(Cheats* cheatsIn)
{
	cheats = cheatsIn;
}


void RoguePython::init()
{

	for (int i = 0; i < 7; i++)
		vPyTypes.push_back(0);

	for (int i = 0; i < 7; i++)
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

void RoguePython::readType(RogueObject* pValue)
{
	bool bTypesFound = true;
	for (int i = 0; i < vPyTypes.size(); i++)
		if (!vPyTypes.at(i))
			bTypesFound = false;
	if (bTypesFound || !cheats->hookManager->bHooksInitialized)
		return;

	char* pTypeName = (char*)((uint64_t*)((uint64_t*)pValue)[1])[3];
	uint64_t pType = ((uint64_t*)pValue)[1];

	if (vPyTypes.at(TYPES.INT) == NULL)
	{
		if (!strcmp(pTypeName, "int"))
		{
			printf(" [*] RP - Int Type Found\n");
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
			printf(" [*] RP - Float Type Found\n");
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
}


void RoguePython::readAttribute(RogueObject* pAttributeName)
{
	bool bStringsFound = true;
	for (int i = 0; i < vAttr2Str.size(); i++)
		if (!vAttr2Str.at(i))
			bStringsFound = false;
	if (bStringsFound)
		return;


	PyVarObjectCust* tmp = (PyVarObjectCust*)pAttributeName;
	std::string tmpAttName(tmp->sName);

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
}