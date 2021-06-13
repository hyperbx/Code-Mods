#pragma once

struct ArchiveDependency
{
    string archive;
    vector<string> dependencies;

    ArchiveDependency() {};

    ArchiveDependency(string archive, vector<string> dependencies) : archive(archive), dependencies(dependencies) {};
};

class ArchiveTreePatcher
{
public:
    static vector<ArchiveDependency> archiveDependencies;

    /// <summary>
    /// Installs the mid-ASM hooks.
    /// </summary>
    static void Install();
};