#define STAGE_GIGANTO 0
#define STAGE_WYVERN  1
#define STAGE_KNIGHT  2
#define STAGE_SUPREME 3

enum EDifficulty : uint8_t
{
	EDifficulty_Easy,
	EDifficulty_Medium,
	EDifficulty_Hard
};

EDifficulty m_Difficulty = EDifficulty_Easy;

std::unordered_map<uint8_t, std::vector<uint32_t>> m_Easy =
{
	{ STAGE_GIGANTO, { 45,  75,  105, 135 } },
	{ STAGE_WYVERN,  { 270, 300, 330, 360 } },
	{ STAGE_KNIGHT,  { 105, 135, 165, 195 } },
	{ STAGE_SUPREME, { 69,  99,  129, 159 } },
};

std::unordered_map<uint8_t, std::vector<uint32_t>> m_EasyAll =
{
	{ STAGE_GIGANTO, { 45,  75,  105, 135 } },
	{ STAGE_WYVERN,  { 315, 375, 435, 495 } },
	{ STAGE_KNIGHT,  { 420, 510, 600, 690 } },
	{ STAGE_SUPREME, { 489, 609, 729, 849 } },
};

std::unordered_map<uint8_t, std::vector<uint32_t>> m_Medium =
{
	{ STAGE_GIGANTO, { 150, 180, 210, 240 } },
	{ STAGE_WYVERN,  { 300, 330, 360, 390 } },
	{ STAGE_KNIGHT,  { 195, 225, 255, 285 } },
	{ STAGE_SUPREME, { 90,  120, 150, 180 } },
};

std::unordered_map<uint8_t, std::vector<uint32_t>> m_MediumAll =
{
	{ STAGE_GIGANTO, { 150, 180, 210, 240  } },
	{ STAGE_WYVERN,  { 450, 510, 570, 630  } },
	{ STAGE_KNIGHT,  { 645, 735, 825, 915  } },
	{ STAGE_SUPREME, { 735, 855, 975, 1095 } },
};

std::unordered_map<uint8_t, std::vector<uint32_t>> m_Hard =
{
	{ STAGE_GIGANTO, { 170, 200, 230, 260 } },
	{ STAGE_WYVERN,  { 330, 360, 390, 420 } },
	{ STAGE_KNIGHT,  { 210, 240, 270, 300 } },
	{ STAGE_SUPREME, { 105, 135, 165, 195 } },
};

std::unordered_map<uint8_t, std::vector<uint32_t>> m_HardAll =
{
	{ STAGE_GIGANTO, { 170, 200, 230,  260  } },
	{ STAGE_WYVERN,  { 550, 560, 620,  680  } },
	{ STAGE_KNIGHT,  { 710, 800, 890,  980  } },
	{ STAGE_SUPREME, { 815, 935, 1055, 1175 } },
};

CL_SCAN_SIGNATURE(m_SigLoadAsset, "\x48\x89\x5C\x24\x08\x48\x89\x74\x24\x10\x57\x48\x81\xEC\xD0\x00\x00\x00\x49\x8B\xF8", "xxxxxxxxxxxxxxxxxxxxx");

HOOK(int64_t, __fastcall, LoadAsset, m_SigLoadAsset(), int64_t a1, const char* in_assetName, const char** in_resourceType)
{
	auto result = originalLoadAsset(a1, in_assetName, in_resourceType);

	if (StringHelper::Compare(*in_resourceType, "ResReflection") && StringHelper::Compare(in_assetName, "battlerush"))
	{
		auto battleRushParameter = reinterpret_cast<BattleRushParameter*>(*(int64_t*)(result + 0x60));

		if (battleRushParameter)
		{
			for (int stageIdx = 0; stageIdx < 4; stageIdx++)
			{
				auto& stage = battleRushParameter->stages[stageIdx];

				// This probably isn't needed, but why not.
				stage.numPhases = 1;

				// Remove time limit from phases.
				for (auto& phaseLimitTime : stage.phaseLimitTime)
					phaseLimitTime = 0.0f;

				// Set rank times.
				for (int rankIdx = 0; rankIdx < 4; rankIdx++)
				{
					switch (m_Difficulty)
					{
						case EDifficulty_Easy:
							stage.phaseRank[0].rankTime[rankIdx]    = m_Easy[stageIdx][rankIdx];
							stage.phaseRank[0].rankTimeAll[rankIdx] = m_EasyAll[stageIdx][rankIdx];
							break;

						case EDifficulty_Medium:
							stage.phaseRank[0].rankTime[rankIdx]    = m_Medium[stageIdx][rankIdx];
							stage.phaseRank[0].rankTimeAll[rankIdx] = m_MediumAll[stageIdx][rankIdx];
							break;

						case EDifficulty_Hard:
							stage.phaseRank[0].rankTime[rankIdx]    = m_Hard[stageIdx][rankIdx];
							stage.phaseRank[0].rankTimeAll[rankIdx] = m_HardAll[stageIdx][rankIdx];
							break;
					}
				}
			}
		}
	}

	return result;
}

HOOK
(
	HANDLE,
	__fastcall,
	KernelBaseCreateFileA,
	PROC_ADDRESS("Kernel32.dll", "CreateFileA"),
	LPCSTR lpFileName,
	DWORD dwDesiredAccess,
	DWORD dwShareMode,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	DWORD dwCreationDisposition,
	DWORD dwFlagsAndAttributes,
	HANDLE hTemplateFile
)
{
	if (dwDesiredAccess & GENERIC_READ)
	{
		if (StringHelper::ContainsSubstring(lpFileName, "auto0"))
		{
			m_Difficulty = EDifficulty_Easy;
		}
		else if (StringHelper::ContainsSubstring(lpFileName, "manual0"))
		{
			m_Difficulty = EDifficulty_Medium;
		}
		else if (StringHelper::ContainsSubstring(lpFileName, "manual1"))
		{
			m_Difficulty = EDifficulty_Hard;
		}
	}

	return originalKernelBaseCreateFileA(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}

HOOK
(
	HANDLE,
	__fastcall,
	KernelBaseCreateFileW,
	PROC_ADDRESS("Kernel32.dll", "CreateFileW"),
	LPCWSTR lpFileName,
	DWORD dwDesiredAccess,
	DWORD dwShareMode,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	DWORD dwCreationDisposition,
	DWORD dwFlagsAndAttributes,
	HANDLE hTemplateFile
)
{
	// Disable save data writing.
	if (dwDesiredAccess & GENERIC_WRITE && StringHelper::ContainsSubstring(StringHelper::WideCharToString(lpFileName), "gamedata.sav"))
		return INVALID_HANDLE_VALUE;

	return originalKernelBaseCreateFileW(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}

EXPORT void Init()
{
	INSTALL_HOOK(LoadAsset);
	INSTALL_HOOK(KernelBaseCreateFileA);
	INSTALL_HOOK(KernelBaseCreateFileW);
}