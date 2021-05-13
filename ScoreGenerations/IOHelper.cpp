bool IOHelper::FileExists(const string& path)
{
	struct stat buffer;

	return stat(path.c_str(), &buffer) == 0;
}