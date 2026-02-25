#include "Signatures.h"

// Pre-next-gen metadata
EXPORT bool F4SEPlugin_Query(const F4SEInterface* in_pF4SE, PluginInfo* in_pInfo)
{
    in_pInfo->infoVersion = PluginInfo::kInfoVersion;
    in_pInfo->name = g_ModInfo.Name.c_str();
    in_pInfo->version = g_ModInfo.Version.ToUInt32();

    return true;
}

// Post-next-gen metadata
EXPORT F4SEPluginVersionData F4SEPlugin_Version =
{
    F4SEPluginVersionData::kVersion,

    g_ModInfo.Version.ToUInt32(),
    MOD_NAME,
    MOD_AUTHOR,

    F4SEPluginVersionData::kAddressIndependence_Signatures,
    F4SEPluginVersionData::kStructureIndependence_NoStructs,

    // No version requirements.
    // Tested versions: 1.10.163, 1.10.984
    // Researched versions (untested, should work): 1.1.29, 1.3.47, 1.10.130, 1.10.138, 1.10.155, 1.10.162, 1.10.980
    { 0 },

    0
};

DECLARE_HOOK(void, __fastcall, BSShaderUtil_SetCameraFOV, Sig_BSShaderUtil_SetCameraFOV(), void* apCamera, float afFOV, float afFar, float afNear)
{
    afNear = std::max(5.0f / tan(cmf::sys::num::ToRadiansF(std::clamp(afFOV, 1.0f, 179.0f)) * 0.5f), 0.01f);

    original_BSShaderUtil_SetCameraFOV(apCamera, afFOV, afFar, afNear);
}

EXPORT bool F4SEPlugin_Load(const F4SEInterface* in_pF4SE)
{
    cmf::sys::Logger::Init();

    if (!cmf::sys::mem::SignatureScanner::Status.Success)
    {
        LOGFN_ERROR("Error: {}\n{}", cmf::sys::mem::SignatureScanner::Status.pMessage, cmf::sys::mem::SignatureScanner::Status.GetPatternString());
        MessageBoxA(nullptr, "Failed to install patches.", MOD_NAME, MB_ICONERROR);
        return false;
    }

    INSTALL_HOOK(BSShaderUtil_SetCameraFOV);

    return true;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    return TRUE;
}
