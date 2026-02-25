#include "../../../Framework/Framework.h"

DECLARE_HOOK(bool, __stdcall, ParseArchiveTree, 0xD4C8E0, void* in_pUnk, char* in_pData, const size_t in_length, void* in_pDatabase)
{
    std::string str{};
    std::stringstream stream{};

    for (const auto& rArchive : ArchiveTree::Archives)
    {
        stream << "<Node>" << std::endl;
        stream << "  <Name>" << rArchive.Name << "</Name>" << std::endl;
        stream << "  <Archive>" << rArchive.Name << "</Archive>" << std::endl;
        stream << "  <Order>0</Order>" << std::endl;
        stream << "  <DefAppend>" << rArchive.Name << "</DefAppend>" << std::endl;

        for (const auto& rDependency : rArchive.Dependencies)
        {
            stream << "<Node>" << std::endl;
            stream << "  <Name>" << rDependency << "</Name>" << std::endl;
            stream << "  <Archive>" << rDependency << "</Archive>" << std::endl;
            stream << "  <Order>0</Order>" << std::endl;
            stream << "</Node>" << std::endl;
        }

        stream << "</Node>" << std::endl;
    }

    str = stream.str();

    const auto newSize = in_length + str.size();
    auto pBuffer = std::make_unique<char[]>(newSize);

    memcpy(pBuffer.get(), in_pData, in_length);

    auto pInsertionPos = strstr(pBuffer.get(), "<Include>");

    memmove(pInsertionPos + str.size(), pInsertionPos, in_length - (size_t)(pInsertionPos - pBuffer.get()));
    memcpy(pInsertionPos, str.c_str(), str.size());

    return original_ParseArchiveTree(in_pUnk, pBuffer.get(), newSize, in_pDatabase);
}

inline void ArchiveTree::Install()
{
    INSTALL_HOOK(ParseArchiveTree);
}
