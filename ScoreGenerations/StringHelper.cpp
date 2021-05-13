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