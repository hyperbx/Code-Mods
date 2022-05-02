vector<string> commonArchives = { "cmn100", "cmn200", "pam_cmn" };
vector<ArchiveDependency> ArchiveTreePatcher::archiveDependencies = {};

HOOK(bool, __stdcall, ParseArchiveTree, 0xD4C8E0, void* a1, char* pData, const size_t size, void* pDatabase)
{
    string str;
    {
        stringstream stream;

        for (ArchiveDependency const& node : ArchiveTreePatcher::archiveDependencies)
        {
            stream << "  <Node>\n";
            stream << "    <Name>" << node.archive << "</Name>\n";
            stream << "    <Archive>" << node.archive << "</Archive>\n";
            stream << "    <Order>" << 0 << "</Order>\n";
            stream << "    <DefAppend>" << node.archive << "</DefAppend>\n";

            for (string const& dependency : node.dependencies)
            {
                stream << "    <Node>\n";
                stream << "      <Name>" << dependency << "</Name>\n";
                stream << "      <Archive>" << dependency << "</Archive>\n";
                stream << "      <Order>" << 0 << "</Order>\n";
                stream << "    </Node>\n";
            }

            stream << "  </Node>\n";
        }

        str = stream.str();
    }

    const size_t newSize = size + str.size();
    const unique_ptr<char[]> pBuffer = std::make_unique<char[]>(newSize);

    memcpy(pBuffer.get(), pData, size);

    char* pInsertionPos = strstr(pBuffer.get(), "<Include>");

    memmove(pInsertionPos + str.size(), pInsertionPos, size - (size_t)(pInsertionPos - pBuffer.get()));
    memcpy(pInsertionPos, str.c_str(), str.size());

    return originalParseArchiveTree(a1, pBuffer.get(), newSize, pDatabase);
}

void ArchiveTreePatcher::Install()
{
    const char* type = "cmn_dashring_tails_green";

    switch (Configuration::colourType)
    {
        case Configuration::Orange:
            type = "cmn_dashring_tails_orange";
            break;

        case Configuration::Red:
            type = "cmn_dashring_tails_red";
            break;

        case Configuration::Green:
            type = "cmn_dashring_tails_green";
            break;

        case Configuration::GreenDiffuse:
            type = "cmn_dashring_tails_green_dif";
            break;

        case Configuration::Purple:
            type = "cmn_dashring_tails_purple";
            break;

        case Configuration::Blue:
            type = "cmn_dashring_tails_blue";
            break;
    }

    ArchiveTreePatcher::archiveDependencies.push_back(ArchiveDependency(type, { commonArchives }));

    if (Configuration::useCustomRainbowRings)
        ArchiveTreePatcher::archiveDependencies.push_back(ArchiveDependency("cmn_dashring_tails_rainbow", { commonArchives }));

    INSTALL_HOOK(ParseArchiveTree);
}