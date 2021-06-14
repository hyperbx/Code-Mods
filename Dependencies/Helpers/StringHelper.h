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