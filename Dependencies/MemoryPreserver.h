#pragma once

#include <unordered_map>
#include <vector>

class MemoryPreserver
{
	inline static std::unordered_map<size_t, std::vector<char>> m_PreservedMemory;

public:
	static const void Add(const size_t location, const size_t length)
	{
		if (location == 0)
			return;

		char* buffer = new char[length];
		memcpy(buffer, (void*)location, length);

		// Remove the current key from preserved memory if it already exists.
		if (m_PreservedMemory.find(location) != m_PreservedMemory.end())
			m_PreservedMemory.erase(location);

		m_PreservedMemory.emplace(location, std::vector<char>(buffer, buffer + length));

		delete buffer;
	}

	static const void Remove(const size_t location)
	{
		m_PreservedMemory.erase(location);
	}

	static const void Restore(const size_t location)
	{
		int i = 0;

		if (location == 0)
			return;

		for (char c : m_PreservedMemory.at(location))
		{
			WRITE_MEMORY(location + i, const char, c);
			i++;
		}
	}
};

#define PRESERVE_MEMORY(location, length) MemoryPreserver::Add(location, length);
#define RESTORE_MEMORY(location)          MemoryPreserver::Restore(location);