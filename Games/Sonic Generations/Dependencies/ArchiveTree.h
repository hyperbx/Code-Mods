#pragma once

#include <string>
#include <vector>

struct Archive
{
    std::string Name{};
    std::vector<std::string> Dependencies{};

    Archive() {}

    Archive(const std::string& in_rName, const std::vector<std::string>& in_rDependencies)
        : Name(in_rName), Dependencies(in_rDependencies) {}
};

class ArchiveTree
{
public:
    inline static std::vector<Archive> Archives{};
    
    static void Install();
};

#include "ArchiveTree.inl"
