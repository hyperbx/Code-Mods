#pragma once

struct ArchiveDependency
{
    std::string archive;
    std::vector<std::string> dependencies;

    ArchiveDependency() {};

    ArchiveDependency(std::string archive, std::vector<std::string> dependencies) : archive(archive), dependencies(dependencies) {};
};

class ArchiveTreePatcher
{
public:
    static std::vector<ArchiveDependency> archiveDependencies;

    /// <summary>
    /// Installs the mid-ASM hooks.
    /// </summary>
    static void Install();
};