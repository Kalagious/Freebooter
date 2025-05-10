#pragma once
#include <iostream>
#include <vector>
#include <windows.h>
#include <tlHelp32.h>
#include <stdint.h>
#include <tchar.h>
#include "unamedhook.h"
#include "PyFunction_NewWithQualNameHook.h"
#include "PyObject_SetAttrHook.h"
#include "PyDict_SetItemHook.h"
#include "__pypperoni_IMPL_call_funcHook.h"
#include "SwapBuffersHook.h"

class HookManager
{
public:

	HookManager(void* tlopoExeIn, void* openGl32In);
	void removeAll();
	void InitalizeHooks();
	bool bHooksInitialized;
	UnamedHook* unamedHook;
	PyFunction_NewWithQualNameHook* pyFunction_NewWithQualNameHook;
	PyObject_SetAttrHook* pyObject_SetAttrHook;
	PyDict_SetItemHook* pyDict_SetItemHook;
	__pypperoni_IMPL_call_funcHook* pypperoni_IMPL_call_funcHook;
	SwapBuffersHook* swapBuffersHook;
	void* tlopoExe;
	void* openGl32;

};