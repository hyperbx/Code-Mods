#pragma once

#include <fstream>
#include <iterator>
#include <string>
#include <algorithm>

class IOHelper
{
public:
	/// <summary>
	/// Returns whether or not a file exists at the input location.
	/// </summary>
	static bool FileExists(const std::string& path)
	{
		struct stat buffer;

		return stat(path.c_str(), &buffer) == 0;
	}

	/// <summary>
	/// Compares two files and returns whether or not they're identical.
	/// </summary>
	static bool Compare(const std::string& file1, const std::string& file2)
	{
		std::ifstream f1(file1, std::ifstream::binary | std::ifstream::ate);
		std::ifstream f2(file2, std::ifstream::binary | std::ifstream::ate);

		// I/O error.
		if (f1.fail() || f2.fail())
			return false;

		// Size mismatch.
		if (f1.tellg() != f2.tellg())
			return false;

		// Seek back to beginning and use std::equal to compare contents.
		f1.seekg(0, std::ifstream::beg);
		f2.seekg(0, std::ifstream::beg);

		return std::equal(std::istreambuf_iterator<char>(f1.rdbuf()),
						  std::istreambuf_iterator<char>(),
						  std::istreambuf_iterator<char>(f2.rdbuf()));
	}
};