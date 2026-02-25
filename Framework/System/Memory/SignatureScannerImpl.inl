namespace CMF::System::Memory
{
    inline void* SignatureScanner::ScanImpl(const char* in_pPattern, const char* in_pMask, void* in_pBegin, const size_t in_length)
    {
        if (!Status.Success)
            return nullptr;

        const auto patternLength = strlen(in_pMask);

        for (size_t i = 0; i < in_length; i++)
        {
            auto pMemory = (char*)in_pBegin + i;
            auto patternSeek = 0UL;

            for (patternSeek = 0; patternSeek < patternLength; patternSeek++)
            {
                if (in_pMask[patternSeek] != '?' && in_pPattern[patternSeek] != pMemory[patternSeek])
                    break;
            }

            if (patternSeek == patternLength)
            {
                Status = { true, nullptr, in_pPattern, in_pMask };

                return pMemory;
            }
        }

        Status = { false, "Failed to locate signature.", in_pPattern, in_pMask };

        return nullptr;
    }
    
    inline void* SignatureScanner::Scan(std::vector<std::tuple<const char*, const char*>> in_patterns)
    {
        void* pResult{};
        
        for (size_t i = 0; i < in_patterns.size(); i++)
        {
            auto tpl = in_patterns[i];
            auto pPattern = std::get<0>(tpl);
            auto pMask = std::get<1>(tpl);

            if (i <= in_patterns.size() - 1)
                Reset();

            pResult = Scan(pPattern, pMask);

            if (pResult)
                break;
        }

        return pResult;
    }
}
