#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <fstream>
#include <windows.h>
#include <string>
#include <iostream>
#include <tchar.h>
#include <stdlib.h>
#include <filesystem>



// Injector for CSGO internal cheats
bool fileExists(const std::string& name) {
    std::ifstream f(name.c_str());
    return f.good();
}


DWORD GetProcId(const wchar_t* procName)
{
    DWORD procId = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hSnap != INVALID_HANDLE_VALUE)
    {
        PROCESSENTRY32 procEntry;
        procEntry.dwSize = sizeof(procEntry);

        if (Process32First(hSnap, &procEntry))
        {
            do
            {
                if (!wcscmp(procEntry.szExeFile, procName))
                {
                    procId = procEntry.th32ProcessID;
                    break;
                }
            } while (Process32Next(hSnap, &procEntry));
        }
    }
    CloseHandle(hSnap);
    return procId;
}

uint32_t main()
{
    char dllPath[512];

    GetCurrentDirectoryA(512, dllPath);

    std::string cwdStr(dllPath);

    
    cwdStr += "\\TLOPOInternal.dll";
    if (!fileExists(cwdStr))
        return 0;

    strcpy_s(dllPath, cwdStr.c_str());

    DWORD procId = 0;

    printf("Scanning for process...\n");
    while (!procId)
    {
        procId = GetProcId(L"tlopo.exe");
        Sleep(30);
    }

    HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, 0, procId);

    if (hProc && hProc != INVALID_HANDLE_VALUE)
    {
        printf("Process has been found!\n");

        void* loc = VirtualAllocEx(hProc, 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
        if (!loc) {
            throw std::exception("VALLOC failed");
        }
        printf("Memory allocated at %#8X\n", (uintptr_t)loc);

        WriteProcessMemory(hProc, loc, dllPath, strlen(dllPath) + 1, 0);
        printf("DLL Path Written");

        HANDLE hThread = CreateRemoteThread(hProc, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, loc, 0, 0);
        printf("\nLibrary Loaded!\n");
        if (hThread)
        {
            CloseHandle(hThread);
        }
    }
    else
        printf("Error\n");

    if (hProc)
    {
        CloseHandle(hProc);
    }
    return 0;
}