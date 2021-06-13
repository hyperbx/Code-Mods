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

string StringHelper::ToLower(string str)
{
	transform(str.begin(), str.end(), str.begin(), ::tolower);

	return str;
}

string StringHelper::Unquote(string str)
{
	str.erase(remove(str.begin(), str.end(), '\"'), str.end());

	return str;
}