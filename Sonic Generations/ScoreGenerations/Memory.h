#pragma once

class Memory
{
public:
	static void Preserve()
	{
		// StateHooks.cpp
		PRESERVE_MEMORY(0xD5A18C, 5);
	}
};

