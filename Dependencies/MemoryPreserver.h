#pragma once

#include <unordered_map>
#include <vector>

class MemoryPreserver
{
	static std::unordered_map<int, std::vector<char>> preservedMemory;

public:
	static const void Add(int location, const size_t length)
	{
		char* buffer = new char[length];
		memcpy(buffer, (void*)(location), length);

		// Remove the current key from preserved memory if it already exists.
		if (preservedMemory.find(location) != preservedMemory.end())
			preservedMemory.erase(location);

		preservedMemory.emplace(location, std::vector<char>(buffer, buffer + sizeof(buffer)));

		delete buffer;
	}

	static const void Remove(int location)
	{
		preservedMemory.erase(location);
	}

	static const void Restore(int location)
	{
		int i = 0;

		for (char c : preservedMemory.at(location))
		{
			WRITE_MEMORY(location + i, const char, c);
			i++;
		}
	}
};

inline std::unordered_map<int, std::vector<char>> MemoryPreserver::preservedMemory;

#define PRESERVE_MEMORY(location, length) MemoryPreserver::Add(location, length);
#define RESTORE_MEMORY(location) MemoryPreserver::Restore(location);