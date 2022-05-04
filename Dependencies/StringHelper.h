#pragma once

#include <iostream>
#include <iomanip>
#include <regex>
#include <sstream>
#include <string>

class StringHelper
{
public:
	/// <summary>
	/// Converts the input string to lowercase.
	/// </summary>
	/// <param name="str">String to make lowercase.</param>
	static std::string ToLower(std::string str)
	{
		if (!str.empty())
			std::transform(str.begin(), str.end(), str.begin(), ::tolower);

		return str;
	}

	/// <summary>
	/// Unquotes the string - useful for string to char conversion.
	/// </summary>
	/// <param name="str">String to unquote.</param>
	static std::string Unquote(std::string str)
	{
		if (!str.empty())
			str.erase(std::remove(str.begin(), str.end(), '\"'), str.end());

		return str;
	}

	/// <summary>
	/// Compares two sets of characters, but returns a Boolean value for more sane people.
	/// </summary>
	/// <param name="charPtr1">Characters to compare against.</param>
	/// <param name="charPtr2">Characters to test.</param>
	/// <returns>Boolean result - true if they're the same, false if not.</returns>
	static bool Compare(const char* charPtr1, const char* charPtr2)
	{
		return strcmp(charPtr1, charPtr2) == 0 ? true : false;
	}

	/// <summary>
	/// Compares two strings, but returns a Boolean value for more sane people.
	/// </summary>
	/// <param name="str1">String to compare against.</param>
	/// <param name="str2">String to test.</param>
	/// <returns>Boolean result - true if they're the same, false if not.</returns>
	static bool Compare(std::string str1, std::string str2)
	{
		return strcmp(str1.c_str(), str2.c_str()) == 0 ? true : false;
	}

	/// <summary>
	/// Checks if the string contains a substring.
	/// </summary>
	/// <param name="str">String to check.</param>
	/// <returns>Boolean result - true if it contains the substring, false if not.</returns>
	static bool ContainsSubstring(std::string str1, std::string str2)
	{
		return str1.find(str2) != std::string::npos;
	}

	/// <summary>
	/// Checks if the string contains numbers.
	/// </summary>
	/// <param name="str">String to check.</param>
	/// <returns>Boolean result - true if it contains numbers, false if not.</returns>
	static bool ContainsNumbers(std::string str)
	{
		return std::any_of(str.begin(), str.end(), ::isdigit);
	}

	/// <summary>
	/// Extracts numbers from a string and converts the result to an integer.
	/// </summary>
	/// <param name="str">String to get numbers from.</param>
	/// <returns>The digits from the string as an integer.</returns>
	static int GetDigits(std::string str)
	{
		return std::stoi(StringHelper::ContainsNumbers(str) ? std::regex_replace(str, std::regex("[^0-9]*([0-9]+).*"), std::string("$1")) : "0");
	}

	/// <summary>
	/// Removes all spaces from a string.
	/// </summary>
	/// <param name="str">String to remove spaces from.</param>
	/// <returns>String without spaces.</returns>
	static std::string RemoveSpaces(std::string str)
	{
		str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());

		return str;
	}

	/// <summary>
	/// Removes the last character from a string.
	/// </summary>
	/// <param name="str">String to remove last character from.</param>
	/// <returns>String without last character.</returns>
	static std::string RemoveLastCharacter(std::string str)
	{
		str.pop_back();
		return str;
	}

	/// <summary>
	/// Extracts comma separated strings.
	/// </summary>
	/// <param name="str">String to extract from.</param>
	/// <returns>Vector of the strings.</returns>
	static std::vector<std::string> GetCommaSeparatedStrings(std::string str)
	{
		std::vector<std::string> strings;
		std::istringstream stream(str);
		std::string token;

		while (std::getline(stream, token, ','))
			strings.push_back(token);

		return strings;
	}
	
	/// <summary>
	/// Checks if a character array is empty.
	/// </summary>
	static bool IsEmpty(const char* charPtr)
	{
		if (charPtr && !charPtr[0])
			return true;

		return false;
	}

	/// <summary>
	/// Converts a string containing hexadecimal data to a byte array.
	/// </summary>
	static uint8_t* HexStringToByteArray(const char* hash)
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

	/// <summary>
	/// Converts an array of bytes into a string of hexadecimal bytes.
	/// </summary>
	static std::string ByteArrayToHexString(const uint8_t* data, const size_t size)
	{
		std::stringstream ss;

		ss << std::hex << std::setfill('0');

		for (int i = 0; i < size; i++)
			ss << std::hex << std::setw(2) << static_cast<int>(data[i]);

		return ss.str();
	}
};