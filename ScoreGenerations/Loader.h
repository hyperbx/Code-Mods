#pragma once

#define MODS_DEFAULT "mods\\ModsDB.ini"

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

		string config;

		/// <summary>
		/// Reads the configuration for the active mod.
		/// </summary>
		static ModInformation ReadConfig(string path)
		{
			ModInformation modInfo;

			if (IOHelper::FileExists(path))
			{
				INIReader reader(path);

				modInfo.title = reader.Get("Desc", "Title", "");
				modInfo.description = reader.Get("Desc", "Description", "");
				modInfo.version = reader.Get("Desc", "Version", "");
				modInfo.date = reader.Get("Desc", "Date", "");
				modInfo.author = reader.Get("Desc", "Author", "");
				modInfo.authorURL = reader.Get("Desc", "AuthorURL", "");

				modInfo.dll = reader.Get("Main", "DLLFile", "");
				modInfo.code = reader.Get("Main", "CodeFile", "");
				modInfo.schema = reader.Get("Main", "ConfigSchemaFile", "");

				modInfo.config = path;
			}

			return modInfo;
		}
	};
};