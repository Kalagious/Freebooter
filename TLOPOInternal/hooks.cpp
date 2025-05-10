#include "Hooks.h"
#include <iostream>
#include <vector>
#include <windows.h>
#include <tlHelp32.h>
#include <stdint.h>
#include <tchar.h>
#include <psapi.h>


bool Hook::remove()
{
	printf(" [*] Unhooking %s at %#8X\n", hookName.c_str(), targetAddr);
	DWORD oldProtect;
	VirtualProtect((BYTE*)targetAddr, hookLen, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((BYTE*)targetAddr, stolenBytes, hookLen);
	VirtualProtect((BYTE*)targetAddr, hookLen, oldProtect, &oldProtect);
	enabled = false;
	return true;
}


void* Hook::DetourFunction64(void* pSource, void* pDestination, int dwLen)
{
	DWORD MinLen = 14;

	if (dwLen < MinLen) return NULL;

	BYTE stub[] = {
	0xFF, 0x25, 0x00, 0x00, 0x00, 0x00, // jmp qword ptr [$+6]
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 // ptr
	};

	void* pTrampoline = VirtualAlloc(0, dwLen + sizeof(stub), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	DWORD dwOld = 0;
	VirtualProtect(pSource, dwLen, PAGE_EXECUTE_READWRITE, &dwOld);
	memcpy(stolenBytes, (BYTE*)pSource, dwLen);


	DWORD64 retto = (DWORD64)pSource + dwLen;

	// trampoline
	memcpy(stub + 6, &retto, 8);
	memcpy((void*)((DWORD_PTR)pTrampoline), pSource, dwLen);
	memcpy((void*)((DWORD_PTR)pTrampoline + dwLen), stub, sizeof(stub));

	// orig
	memcpy(stub + 6, &pDestination, 8);
	memcpy(pSource, stub, sizeof(stub));

	for (int i = MinLen; i < dwLen; i++)
	{
		*(BYTE*)((DWORD_PTR)pSource + i) = 0x90;
	}

	VirtualProtect(pSource, dwLen, dwOld, &dwOld);
	return (void*)((DWORD_PTR)pTrampoline);
}


void* Hook::signatureScan(std::vector<uint8_t> bpSig, int32_t iOffset, void* pBase)
{

	if (bpSig.size() <= 0)
	{
		printf("	[!] Sig is empty!\n");
		return NULL;
	}


	MODULEINFO miModule;
	GetModuleInformation(GetCurrentProcess(), (HMODULE)pBase, &miModule, sizeof(miModule));
	uint64_t iModuleSize = miModule.SizeOfImage;

	if (!pBase || !iModuleSize)
	{
		printf(" [!] Error finding module during Sig Scan!\n");
		return NULL;
	}

	void* pCurrRegion = 0;
	void* pCurrRegionEnd = 0;
	MEMORY_BASIC_INFORMATION miMemInfo;
    int32_t iSuccessiveMatches = 0;
    for (uint64_t iBaseOffset = 0; iBaseOffset < iModuleSize; iBaseOffset++)
    {
		if ((uint64_t)pBase + iBaseOffset > (uint64_t)pCurrRegionEnd)
		{
			VirtualQuery((void*)((uint64_t)pBase + iBaseOffset), &miMemInfo, sizeof(miMemInfo));
			if (miMemInfo.State == 0x1000 && miMemInfo.Protect == 0x40)
			{
				pCurrRegion = miMemInfo.BaseAddress;
				pCurrRegionEnd = (void*)((uint64_t)pCurrRegion + miMemInfo.RegionSize);
			}
		}
		

		if (pCurrRegion < (void*)((uint64_t)pBase + iBaseOffset) && (void*)((uint64_t)pBase + iBaseOffset) < pCurrRegionEnd)
		{

			if (*(uint8_t*)((uint64_t)pBase + iBaseOffset) == bpSig.at(iSuccessiveMatches) || bpSig.at(iSuccessiveMatches) == 0x3F)
			    iSuccessiveMatches++;
			else
			    iSuccessiveMatches = 0;

			if (iSuccessiveMatches >= bpSig.size())
			{
				printf(" 	[*] Found %s at %p\n", hookName.c_str(), (void*)((uint64_t)pBase + iBaseOffset - bpSig.size() - iOffset + 1));
				return (void*)((uint64_t)pBase + iBaseOffset - bpSig.size() - iOffset + 1);
			}
		}
    }
    return NULL;
}
