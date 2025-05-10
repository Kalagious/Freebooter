#pragma once
#include <vector>
#include <windows.h>
#include <tlHelp32.h>
#include <stdint.h>
#include <tchar.h>
#include <iostream>
#include "general.h"

#pragma warning(disable:26495)
class Hook
{
public:
	std::string hookName;
	uint32_t hookLen;
	void* moduleBase;
	void* targetAddr;
	void* trampAddr;
	uint32_t stolenBytes[30];
	bool enabled;
	std::vector<uint8_t> viSig;
	int32_t iSigOffset;
	void* DetourFunction64(void* pSource, void* pDestination, int dwLen);
	void* signatureScan(std::vector<uint8_t> bpSig, int32_t iOffset, void* pBase);
	bool remove();
};
#pragma warning(default:26495)
