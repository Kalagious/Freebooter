#pragma once
#include "hooks.h"


class PyObject_SetAttrHook : public Hook
{
public:

	bool initialize();
	PyObject_SetAttrHook(void* moduleBaseIn);
	typedef int64_t(__fastcall* tTargetPtr)(PyObject* pObject, PyObject* pAttributeName, PyObject* pValue);
	static int64_t __fastcall hookFunction(PyObject* pObject, PyObject* pAttributeName, PyObject* pValue);
	static tTargetPtr oFunction;
	static uint64_t pCannonValue;
};

