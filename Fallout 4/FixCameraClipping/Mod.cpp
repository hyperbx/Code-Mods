#define MOD_NAME    "Fix Camera Clipping"
#define MOD_VERSION 2

bool g_isNextGen = true;

void ShowUnsupportedMessage()
{
    MessageBoxA(nullptr, "Fallout 4 version 1.10.163 or 1.10.984 is required.", MOD_NAME, MB_ICONERROR);
}

// Pre-next-gen metadata
EXPORT bool F4SEPlugin_Query(const F4SEInterface* in_pF4SE, PluginInfo* in_pInfo)
{
    in_pInfo->infoVersion = PluginInfo::kInfoVersion;
    in_pInfo->name = MOD_NAME;
    in_pInfo->version = MOD_VERSION;

    g_isNextGen = false;

    if (in_pF4SE->runtimeVersion != RUNTIME_VERSION_1_10_163)
    {
        ShowUnsupportedMessage();
        return false;
    }

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

    { RUNTIME_VERSION_1_10_163, RUNTIME_VERSION_1_10_984, 0 },

    0
};

extern "C"
{
    DECLARE_ASM_HOOK(SetNearDistance_1_10_163);
    DECLARE_ASM_HOOK(SetNearDistance_1_10_984);

    uint64_t g_pSigSetNearDistance = 0;
    uint64_t g_pNiCameraSingleton = 0;

    float GetNearDistance(float in_fov)
    {
        return max(5.0f / tan((std::clamp(in_fov, 1.0f, 179.0f) * DEG2RADf) * 0.5f), 0.01f);
    }
}

EXPORT bool F4SEPlugin_Load(const F4SEInterface* in_pF4SE)
{
    if (g_isNextGen)
    {
        // 1.10.984: 0x142095BF4
        g_pSigSetNearDistance = (uint64_t)ScanSignature
        (
            "\xF3\x0F\x10\x1D\xCC\xCC\xCC\xCC\x0F\x28\xCE\xF3\x0F\x10\x15\xCC\xCC\xCC\xCC\x48\x8B\x0D\xCC\xCC\xCC\xCC\xE8\xCC\xCC\xCC\xCC\x0F\x28\xC6\xE8\xCC\xCC\xCC\xCC\x48\x8B\x15",
            "xxxx????xxxxxxx????xxx????x????xxxx????xxx"
        );
    }
    else
    {
        // 1.10.163: 0x14284FEDF
        auto pNiCameraSingletonLdr = (uint64_t)ScanSignature
        (
            "\x48\x8B\x0D\xCC\xCC\xCC\xCC\xF3\x0F\x10\x1D\xCC\xCC\xCC\xCC\xF3\x0F\x10\x15\xCC\xCC\xCC\xCC\x0F\x28\xCE\xE8\xCC\xCC\xCC\xCC\x0F\x28\xC6\xE8\xCC\xCC\xCC\xCC\x48\x8B\x15",
            "xxx????xxxx????xxxx????xxxx????xxxx????xxx"
        );

        if (!pNiCameraSingletonLdr)
        {
            ShowUnsupportedMessage();
            return false;
        }

        // Gets the effective address from the instruction
        // mov rcx, qword ptr cs:[0x146723238] at 0x14284FEDF.
        g_pNiCameraSingleton = pNiCameraSingletonLdr + (*(uint32_t*)(pNiCameraSingletonLdr + 3)) + 7;

        // 1.10.163: 0x14284FEE6
        g_pSigSetNearDistance = (uint64_t)ScanSignature
        (
            "\xF3\x0F\x10\x1D\xCC\xCC\xCC\xCC\xF3\x0F\x10\x15\xCC\xCC\xCC\xCC\x0F\x28\xCE\xE8\xCC\xCC\xCC\xCC\x0F\x28\xC6\xE8\xCC\xCC\xCC\xCC\x48\x8B\x15",
            "xxxx????xxxx????xxxx????xxxx????xxx"
        );
    }

    if (!g_pSigSetNearDistance)
    {
        ShowUnsupportedMessage();
        return false;
    }

    if (g_isNextGen)
    {
        INSTALL_HOOK_ADDRESSED(SetNearDistance_1_10_984, g_pSigSetNearDistance);
    }
    else
    {
        INSTALL_HOOK_ADDRESSED(SetNearDistance_1_10_163, g_pSigSetNearDistance);
    }

    return true;
}
