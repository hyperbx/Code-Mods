string StringHelper::ToLower(string str)
{
	if (!str.empty())
		transform(str.begin(), str.end(), str.begin(), ::tolower);

	return str;
}

string StringHelper::Unquote(string str)
{
	if (!str.empty())
		str.erase(remove(str.begin(), str.end(), '\"'), str.end());

	return str;
}

bool StringHelper::Compare(const char* charPtr1, const char* charPtr2)
{
	return strcmp(charPtr1, charPtr2) == 0 ? true : false;
}

bool StringHelper::Compare(string str1, string str2)
{
	return strcmp(str1.c_str(), str2.c_str()) == 0 ? true : false;
}

bool StringHelper::ContainsNumbers(string str)
{
	return any_of(str.begin(), str.end(), ::isdigit);
}

int StringHelper::GetDigits(string str)
{
	return stoi(StringHelper::ContainsNumbers(str) ? regex_replace(str, regex("[^0-9]*([0-9]+).*"), string("$1")) : "0");
}