#include "hookmanager.h"

HookManager::HookManager(void* tlopoExeIn, void* openGl32In)
{
	tlopoExe = tlopoExeIn;
	openGl32 = openGl32In;

	unamedHook = new UnamedHook(tlopoExe);
	pyFunction_NewWithQualNameHook = new PyFunction_NewWithQualNameHook(tlopoExe);
	pyObject_SetAttrHook = new PyObject_SetAttrHook(tlopoExe);
	pyDict_SetItemHook = new PyDict_SetItemHook(tlopoExe);
	pypperoni_IMPL_call_funcHook = new __pypperoni_IMPL_call_funcHook(tlopoExe);
	swapBuffersHook = new SwapBuffersHook(openGl32);

	bHooksInitialized = false;
}


void HookManager::InitalizeHooks()
{
	printf(" [*] Initializing Game Hooks:\n");
	if (!unamedHook->enabled)
		unamedHook->initialize();
	//if (!pyFunction_NewWithQualNameHook->enabled)
	//	pyFunction_NewWithQualNameHook->initialize();
	if (!pyObject_SetAttrHook->enabled)
		pyObject_SetAttrHook->initialize();
	/*if (!pyDict_SetItemHook->enabled)
		pyDict_SetItemHook->initialize();*/
	if (!pypperoni_IMPL_call_funcHook->enabled)
		pypperoni_IMPL_call_funcHook->initialize();
	if (!swapBuffersHook->enabled)
		swapBuffersHook->initialize();

	printf(" [*] Hooks Initialized!\n\n");
	bHooksInitialized = true;
}


void HookManager::removeAll()
{
	if (unamedHook->enabled)
		unamedHook->remove();
	if (pyFunction_NewWithQualNameHook->enabled)
		pyFunction_NewWithQualNameHook->remove();
	if (pyObject_SetAttrHook->enabled)
		pyObject_SetAttrHook->remove();
	if (pyDict_SetItemHook->enabled)
		pyDict_SetItemHook->remove();
	if (pypperoni_IMPL_call_funcHook->enabled)
		pypperoni_IMPL_call_funcHook->remove();
	if (swapBuffersHook->enabled)
		swapBuffersHook->remove();

	Sleep(10);
}
