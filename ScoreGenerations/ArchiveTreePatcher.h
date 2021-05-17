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

    static void Install();
};