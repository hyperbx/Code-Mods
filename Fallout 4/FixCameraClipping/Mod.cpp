EXPORT F4SEPluginVersionData F4SEPlugin_Version =
{
    F4SEPluginVersionData::kVersion,
    1,
    "Fix Camera Clipping",
    "Hyper",

    F4SEPluginVersionData::kAddressIndependence_Signatures,
    F4SEPluginVersionData::kStructureIndependence_NoStructs,

    { RUNTIME_VERSION_1_10_984, 0 },

    0
};

extern "C"
{
    DECLARE_ASM_HOOK(SetNearDistance);

    uint64_t g_pSigSetNearDistance = 0;

    float GetNearDistance(float in_fov)
    {
        return max(5.0f / tan((std::clamp(in_fov, 1.0f, 179.0f) * DEG2RADf) * 0.5f), 0.01f);
    }
}

EXPORT bool F4SEPlugin_Load(const F4SEInterface* in_pInfo)
{
    // v1.10.984: 0x142095BF4
    g_pSigSetNearDistance = (uint64_t)ScanSignature
    (
        "\xF3\x0F\x10\x1D\xCC\xCC\xCC\xCC\x0F\x28\xCE\xF3\x0F\x10\x15\xCC\xCC\xCC\xCC\x48\x8B\x0D\xCC\xCC\xCC\xCC\xE8\xCC\xCC\xCC\xCC\x0F\x28\xC6\xE8\xCC\xCC\xCC\xCC\x48\x8B\x15",
        "xxxx????xxxxxxx????xxx????x????xxxx????xxx"
    );

    if (!g_pSigSetNearDistance)
        return false;

    INSTALL_HOOK_ADDRESSED(SetNearDistance, g_pSigSetNearDistance);

    return true;
}
