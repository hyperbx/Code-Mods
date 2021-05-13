using namespace std;

#pragma once

class StringHelper
{
public:
	/// <summary>
	/// Converts the input string to lowercase.
	/// </summary>
	/// <param name="str">String to make lowercase.</param>
	static string ToLower(string str);

	/// <summary>
	/// Unquotes the string - useful for string to char conversion.
	/// </summary>
	/// <param name="str">String to unquote.</param>
	static string Unquote(string str);
};