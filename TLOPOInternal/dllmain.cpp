#include "general.h"

DWORD APIENTRY CheatThread(HMODULE hModule)
{
    mainCode(hModule);
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
#pragma warning(disable: 6387)
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
        //AddVectoredExceptionHandler(1, VectoredHandler);

        CloseHandle(CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)CheatThread, hModule, NULL, NULL));
#pragma warning(default: 6387)
    return TRUE;
}

