#pragma once

#define MODS_DEFAULT "mods\\ModsDB.ini"

class Loader
{
public:
	static std::string GetExecutablePath();
	static std::string GetWorkingDirectory();
	static std::string GetCpkRedirConfig();
	static std::string GetModsDatabase();
	static std::string GetModsDirectory();

	static void ConfigureScoreGenerations();

	struct ModInformation
	{
		std::string title;
		std::string description;
		std::string version;
		std::string date;
		std::string author;
		std::string authorURL;

		std::string dll;
		std::string code;
		std::string schema;

		std::string config;

		/// <summary>
		/// Reads the configuration for the active mod.
		/// </summary>
		static ModInformation ReadConfig(std::string path)
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