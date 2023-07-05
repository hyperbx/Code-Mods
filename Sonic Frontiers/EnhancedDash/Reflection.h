#pragma once

#include "SonicParameters.h"

#define RFL_GET_PARAM(hierarchy) Reflection::SonicParameters->hierarchy

#define RFL_GET_CONTEXTUAL_PARAM(hierarchy) \
(BlackboardHelper::IsSideView() \
	? Reflection::SonicParameters->cyberspaceSV.hierarchy \
	: BlackboardHelper::IsCyberSpace() \
		? Reflection::SonicParameters->cyberspace.hierarchy \
		: Reflection::SonicParameters->forwardView.hierarchy)

class Reflection
{
public:
	inline static SonicParameters* SonicParameters;

	static void Install();
};

CL_SCAN_SIGNATURE(m_SigLoadAsset, "\x48\x89\x5C\x24\x08\x48\x89\x74\x24\x10\x57\x48\x81\xEC\xD0\x00\x00\x00\x49\x8B\xF8", "xxxxxxxxxxxxxxxxxxxxx");

CL_SCAN_SIGNATURE_ALLOW_NULL(m_SigDropDashTurningDelay, "\x73\x19\x48\x8B\x47\x40", "xxxxxx");