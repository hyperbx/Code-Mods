using namespace std;

#pragma once

#include <regex>
#include <iostream>
#include <iomanip>

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
	/// Checks if the string contains a substring.
	/// </summary>
	/// <param name="str">String to check.</param>
	/// <returns>Boolean result - true if it contains the substring, false if not.</returns>
	static bool ContainsSubstring(string str1, string str2);

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

	/// <summary>
	/// Removes all spaces from a string.
	/// </summary>
	/// <param name="str">String to remove spaces from.</param>
	/// <returns>String without spaces.</returns>
	static string RemoveSpaces(string str);

	/// <summary>
	/// Extracts comma separated strings.
	/// </summary>
	/// <param name="str">String to extract from.</param>
	/// <returns>Vector of the strings.</returns>
	static vector<string> GetCommaSeparatedStrings(string str);
	
	/// <summary>
	/// Checks if a character array is empty.
	/// </summary>
	static bool IsEmpty(const char* charPtr);

	/// <summary>
	/// Converts a string containing hexadecimal data to a byte array.
	/// </summary>
	static uint8_t* HexStringToByteArray(const char* hex);

	/// <summary>
	/// Converts an array of bytes into a string of hexadecimal bytes.
	/// </summary>
	static string ByteArrayToHexString(const uint8_t* data, const size_t size);
};

inline string StringHelper::ToLower(string str)
{
	if (!str.empty())
		transform(str.begin(), str.end(), str.begin(), ::tolower);

	return str;
}

inline string StringHelper::Unquote(string str)
{
	if (!str.empty())
		str.erase(remove(str.begin(), str.end(), '\"'), str.end());

	return str;
}

inline bool StringHelper::Compare(const char* charPtr1, const char* charPtr2)
{
	return strcmp(charPtr1, charPtr2) == 0 ? true : false;
}

inline bool StringHelper::Compare(string str1, string str2)
{
	return strcmp(str1.c_str(), str2.c_str()) == 0 ? true : false;
}

inline bool StringHelper::ContainsSubstring(string str1, string str2)
{
	return str1.find(str2) != string::npos;
}

inline bool StringHelper::ContainsNumbers(string str)
{
	return any_of(str.begin(), str.end(), ::isdigit);
}

inline int StringHelper::GetDigits(string str)
{
	return stoi(StringHelper::ContainsNumbers(str) ? regex_replace(str, regex("[^0-9]*([0-9]+).*"), string("$1")) : "0");
}

inline string StringHelper::RemoveSpaces(string str)
{
	str.erase(remove_if(str.begin(), str.end(), ::isspace), str.end());

	return str;
}

inline vector<string> StringHelper::GetCommaSeparatedStrings(string str)
{
	vector<string> strings;
	istringstream stream(str);
	string token;

	while (getline(stream, token, ','))
		strings.push_back(token);

	return strings;
}

inline bool StringHelper::IsEmpty(const char* charPtr)
{
	if (charPtr && !charPtr[0])
		return true;
	
	return false;
}

inline uint8_t* StringHelper::HexStringToByteArray(const char* hash)
{
	if (hash == NULL)
		return NULL;

	size_t slength = strlen(hash);
	if ((slength % 2) != 0) // must be even
		return NULL;

	size_t dlength = slength / 2;

	uint8_t* data = (uint8_t*)malloc(dlength);

	memset(data, 0, dlength);

	size_t index = 0;
	while (index < slength)
	{
		char c = hash[index];
		int value = 0;
		if (c >= '0' && c <= '9')
			value = (c - '0');
		else if (c >= 'A' && c <= 'F')
			value = (10 + (c - 'A'));
		else if (c >= 'a' && c <= 'f')
			value = (10 + (c - 'a'));
		else
			return NULL;

		data[(index / 2)] += value << (((index + 1) % 2) * 4);

		index++;
	}

	return data;
}

inline string StringHelper::ByteArrayToHexString(const uint8_t* data, const size_t size)
{
	stringstream ss;

	ss << std::hex << std::setfill('0');

	for (int i = 0; i < size; i++)
		ss << std::hex << std::setw(2) << static_cast<int>(data[i]);

	return ss.str();
}