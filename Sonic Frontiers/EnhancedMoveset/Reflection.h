#pragma once

#include "SonicParameters.h"

// Don't worry, I hate these macros too.

#define RFL_GET_PARAM(hierarchy) Reflection::pSonicParameters->hierarchy

#define RFL_GET_CONTEXTUAL_PARAM(hierarchy) \
(BlackboardHelper::IsSideView() \
	? Reflection::pSonicParameters->cyberspaceSV.hierarchy \
	: BlackboardHelper::IsCyberSpace() \
		? Reflection::pSonicParameters->cyberspace.hierarchy \
		: Reflection::pSonicParameters->forwardView.hierarchy)

#define RFL_SET_PARAM(hierarchy, value) RFL_GET_PARAM(hierarchy) = value;

#define RFL_SET_CONTEXTUAL_PARAM(hierarchy, value) RFL_GET_CONTEXTUAL_PARAM(hierarchy) = value;

#define RFL_RESET_PARAM(hierarchy) RFL_GET_PARAM(hierarchy) = Reflection::OriginalSonicParameters.hierarchy; 

#define RFL_RESET_CONTEXTUAL_PARAM(hierarchy) \
RFL_GET_CONTEXTUAL_PARAM(hierarchy) = (BlackboardHelper::IsSideView() \
	? Reflection::OriginalSonicParameters.cyberspaceSV.hierarchy \
	: BlackboardHelper::IsCyberSpace() \
		? Reflection::OriginalSonicParameters.cyberspace.hierarchy \
		: Reflection::OriginalSonicParameters.forwardView.hierarchy); \

// Hooks
CL_SCAN_SIGNATURE(m_SigLoadAssetCaller, 0x140C70AE3, "\xE8\xCC\xCC\xCC\xCC\x48\x85\xC0\x74\x22\x80\x78\x10\x00", "x????xxxxxxxxx");

// Patches
CL_SCAN_SIGNATURE_ALLOW_NULL(m_SigDropDashTurningDelay, 0x140896A8B, "\x73\x19\x48\x8B\x47\x40", "xxxxxx");

class Reflection
{
public:
	inline static SonicParameters* pSonicParameters;
	inline static SonicParameters OriginalSonicParameters;

	inline static bool IsParametersBackedUp = false;

	static void Refresh();
	static void Install();
};

