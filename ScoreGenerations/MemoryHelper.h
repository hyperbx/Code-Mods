#include <memory>

#pragma once

class MemoryHelper
{
public:
	static bool WriteProtected(void* address, const char* data, size_t size);
};

const HANDLE process = GetCurrentProcess();

bool MemoryHelper::WriteProtected(void* address, const char* data, size_t size)
{
	DWORD old;
	bool result = false;

	result = VirtualProtect(address, size, PAGE_READWRITE, &old);

	WriteProcessMemory(process, address, data, size, nullptr);
	VirtualProtect(address, size, old, &old);

	return result;
}