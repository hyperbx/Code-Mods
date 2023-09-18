#pragma once

#include <cstdio>
#include <vector>

struct Mod
{
	const char* Name;
	const char* Path;
};

struct ModInfo
{
	std::vector<Mod*>* ModList;
	Mod* CurrentMod;
};