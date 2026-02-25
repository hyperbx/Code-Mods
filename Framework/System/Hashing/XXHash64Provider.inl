namespace CMF::System::Hashing
{
    inline bool XXHash64Provider::Reset()
    {
        return XXH3_64bits_reset(&m_State) == XXH_OK;
    }

    inline bool XXHash64Provider::Update(const uint8_t* in_pData, const size_t in_length)
    {
        return XXH3_64bits_update(&m_State, in_pData, in_length) == XXH_OK;
    }

    inline uint64_t XXHash64Provider::Digest()
    {
        return XXH3_64bits_digest(&m_State);
    }
}
