using namespace std;

#pragma once

class Loader
{
public:
	static string GetExecutablePath();
	static string GetWorkingDirectory();
	static string GetCpkRedirConfig();
	static string GetModsDatabase();
	static string GetModsDirectory();

	static void ConfigureScoreGenerations();

	struct ModInformation
	{
		string title;
		string description;
		string version;
		string date;
		string author;
		string authorURL;

		string dll;
		string code;
		string schema;

		static ModInformation ReadModINI(string path)
		{
			ModInformation modInfo;

			if (IOHelper::FileExists(path))
			{
				inipp::Ini<char> ini;
				std::ifstream file(path);
				ini.parse(file);

				inipp::extract(ini.sections["Desc"]["Title"], modInfo.title);
				inipp::extract(ini.sections["Desc"]["Description"], modInfo.description);
				inipp::extract(ini.sections["Desc"]["Version"], modInfo.version);
				inipp::extract(ini.sections["Desc"]["Date"], modInfo.date);
				inipp::extract(ini.sections["Desc"]["Author"], modInfo.author);
				inipp::extract(ini.sections["Desc"]["AuthorURL"], modInfo.authorURL);

				inipp::extract(ini.sections["Main"]["DLLFile"], modInfo.dll);
				inipp::extract(ini.sections["Main"]["CodeFile"], modInfo.code);
				inipp::extract(ini.sections["Main"]["ConfigSchemaFile"], modInfo.schema);

				file.close();
			}

			return modInfo;
		}
	};
};