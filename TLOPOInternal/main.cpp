#include "windows.h"
#include "cheats.h"
#include "general.h"
#include <tlhelp32.h>
#include <iostream>
#include "hookmanager.h"

Cheats* cheatsGlobal;

void mainCode(HMODULE hModule)
{
	AllocConsole();
	FILE* console;
	freopen_s(&console, "CONOUT$", "w", stdout);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = true;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);


	printf(" [*] Starting!\n");
	::ShowWindow(::GetConsoleWindow(), SW_SHOW);
	SetWindowTextA(::GetConsoleWindow(), "Freebooter");
	

	Cheats cheats;
	cheatsGlobal = &cheats;

	
	while (!cheats.uninject)
	{

		cheats.tick();
		if (GetAsyncKeyState(VK_END) & 0x01)
			cheats.uninject = true;
	}
	cheats.cleanup();

	if (console)
		fclose(console);
	FreeConsole();

	FreeLibraryAndExitThread(hModule, 0);
}


const char* TryGetCString(const char* ptr) {
	__try {
		if (ptr && *ptr) { // Try to read at least 1 byte
			return ptr;
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		printf(" [!] Caught Access Violation!!\n");
	}
	return nullptr;
}



LONG WINAPI VectoredHandler(PEXCEPTION_POINTERS pExceptionInfo) {
	DWORD code = pExceptionInfo->ExceptionRecord->ExceptionCode;

	if (code == EXCEPTION_INT_OVERFLOW) {
		MessageBoxA(NULL, "Integer overflow caught in injected DLL!", "VEH Triggered", MB_OK);
		return EXCEPTION_CONTINUE_EXECUTION; // or EXCEPTION_CONTINUE_SEARCH
	}

	return EXCEPTION_CONTINUE_SEARCH;
}