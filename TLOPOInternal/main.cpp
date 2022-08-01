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
	info.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	printf(" [*] Starting!\n");
	::ShowWindow(::GetConsoleWindow(), SW_SHOW);
	SetWindowTextA(::GetConsoleWindow(), "Freebooter");
	

	Cheats cheats;
	cheatsGlobal = &cheats;

	
	while (!cheats.uninject)
	{
		::ShowWindow(::GetConsoleWindow(), SW_SHOW);

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


