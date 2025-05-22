#define MOD_NAME    "Fix Camera Clipping"
#define MOD_VERSION 3

// Pre-next-gen metadata
EXPORT bool F4SEPlugin_Query(const F4SEInterface* in_pF4SE, PluginInfo* in_pInfo)
{
    in_pInfo->infoVersion = PluginInfo::kInfoVersion;
    in_pInfo->name = MOD_NAME;
    in_pInfo->version = MOD_VERSION;

    return true;
}

// Post-next-gen metadata
EXPORT F4SEPluginVersionData F4SEPlugin_Version =
{
    F4SEPluginVersionData::kVersion,

    MOD_VERSION,
    MOD_NAME,
    "Hyper",

    F4SEPluginVersionData::kAddressIndependence_Signatures,
    F4SEPluginVersionData::kStructureIndependence_NoStructs,

    // No version requirements.
    // Tested versions: 1.10.163, 1.10.984
    // Researched versions (untested, should work): 1.1.29, 1.3.47, 1.10.130, 1.10.138, 1.10.155, 1.10.162, 1.10.980
    { 0 },

    0
};

HOOK(void, __fastcall, BSShaderUtilSetCameraFOV, 0, uint64_t apCamera, float afFOV, float afFar, float afNear)
{
    afNear = max(5.0f / tan((std::clamp(afFOV, 1.0f, 179.0f) * DEG2RADf) * 0.5f), 0.01f);

    originalBSShaderUtilSetCameraFOV(apCamera, afFOV, afFar, afNear);
}

EXPORT bool F4SEPlugin_Load(const F4SEInterface* in_pF4SE)
{
    // Scan for latest function first.
    // 1.10.980: 0x14206B620
    // 1.10.984: 0x14206BD40
    auto pBSShaderUtilSetCameraFOV = (uint64_t)ScanSignature
    (
        "\x48\x8B\xC4\x53\x48\x81\xEC\x90\x00\x00\x00\x0F\x29\x70\xE8\x0F\x28",
        "xxxxxxxxxxxxxxxxx"
    );

    if (!pBSShaderUtilSetCameraFOV)
    {
        // Scan for earlier function revision.
        // 1.1.29:   0x142CD2AE0
        // 1.3.47:   0x14283DBE0
        // 1.10.130: 0x142820310
        // 1.10.138: 0x142820310
        // 1.10.155: 0x142820420
        // 1.10.162: 0x142820430
        // 1.10.163: 0x142820430
        pBSShaderUtilSetCameraFOV = (uint64_t)ScanSignature
        (
            "\x48\x8B\xC4\x53\x48\x81\xEC\x90\x00\x00\x00\x0F\x29\x70\xE8\x0F\x29\x78\xD8\x44\x0F\x29\x40\xC8\xF3",
            "xxxxxxxxxxxxxxxxxxxxxxxxx"
        );
    }
    
    if (!pBSShaderUtilSetCameraFOV)
    {
        MessageBoxA(nullptr, "Unsupported game version.", MOD_NAME, MB_ICONERROR);
        return false;
    }

    INSTALL_HOOK_ADDRESSED(BSShaderUtilSetCameraFOV, pBSShaderUtilSetCameraFOV);

    return true;
}
