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

	/// <summary>
	/// Compares two sets of characters, but returns a Boolean value for more sane people.
	/// </summary>
	/// <param name="charPtr1">Characters to compare against.</param>
	/// <param name="charPtr2">Characters to test.</param>
	/// <returns>Boolean result - true if they're the same, false if not.</returns>
	static bool Compare(const char* charPtr1, const char* charPtr2);

	/// <summary>
	/// Compares two strings, but returns a Boolean value for more sane people.
	/// </summary>
	/// <param name="str1">String to compare against.</param>
	/// <param name="str2">String to test.</param>
	/// <returns>Boolean result - true if they're the same, false if not.</returns>
	static bool Compare(string str1, string str2);

	/// <summary>
	/// Checks if the string contains numbers.
	/// </summary>
	/// <param name="str">String to check.</param>
	/// <returns>Boolean result - true if it contains numbers, false if not.</returns>
	static bool ContainsNumbers(string str);

	/// <summary>
	/// Extracts numbers from a string and converts the result to an integer.
	/// </summary>
	/// <param name="str">String to get numbers from.</param>
	/// <returns>The digits from the string as an integer.</returns>
	static int GetDigits(string str);
};