#include "../../../Dependencies/CommonLoader/CommonLoader/CommonLoaderAPI.h"

namespace CMF::System::Memory
{
    inline void* SignatureScanner::Scan(const char* in_pPattern, const char* in_pMask, void* in_pBegin)
    {
        auto pApi = CommonLoader_GetAPI();

        if (!pApi)
        {
            Status = { false, "Failed to acquire CommonLoader API." };
            return nullptr;
        }

        pApi->SetState(CMN_LOADER_STATE_SKIP_SIG_VALIDATION, 1);

        return pApi->ScanSignature(in_pPattern, in_pMask);
    }
}
