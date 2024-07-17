#pragma once
#include <Windows.h>

DWORD GetProcessID(const char* procname);

DWORD GetModuleBaseAddress(DWORD procId, const char* modname);
