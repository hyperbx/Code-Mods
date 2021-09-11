using namespace std;

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
	static bool FileExists(const string& path);

	/// <summary>
	/// Compares two files and returns whether or not they're identical.
	/// </summary>
	static bool Compare(const string& file1, const string& file2);
};

inline bool IOHelper::FileExists(const string& path)
{
	struct stat buffer;

	return stat(path.c_str(), &buffer) == 0;
}

inline bool IOHelper::Compare(const string& file1, const string& file2)
{
	ifstream f1(file1, ifstream::binary | ifstream::ate);
	ifstream f2(file2, ifstream::binary | ifstream::ate);

	// I/O error.
	if (f1.fail() || f2.fail())
		return false;

	// Size mismatch.
	if (f1.tellg() != f2.tellg())
		return false;

	// Seek back to beginning and use std::equal to compare contents.
	f1.seekg(0, ifstream::beg);
	f2.seekg(0, ifstream::beg);

	return std::equal(istreambuf_iterator<char>(f1.rdbuf()),
					  istreambuf_iterator<char>(),
					  istreambuf_iterator<char>(f2.rdbuf()));
}