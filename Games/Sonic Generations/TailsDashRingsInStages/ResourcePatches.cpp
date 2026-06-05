#include "ResourcePatches.h"
#include "../Dependencies/ArchiveTree.h"

static void UpdateModels(const char* in_pModelName = nullptr)
{
	if (!in_pModelName)
	{
		in_pModelName = Configuration::ColourType == ColourType::GreenOriginal
			? "mis_obj_TailsDashring_HD"
			: "cmn_obj_TailsDashring_HD";
	}

	LOGFN_UTILITY("Loading model: {}", in_pModelName);

	// Replace rainbow ring model.
	if (Configuration::UseCustomRainbowRings)
		WRITE(0x1A47574, const char*, "rnb_obj_TailsDashring_HD");

	// Replace dash ring model.
	WRITE(0x1A47578, const char*, in_pModelName);

	// Replace Tails mission dash ring model.
	if (Configuration::IsOverrideTailsDashRing)
		WRITE(0x1A4757C, const char*, in_pModelName);
}

static void __fastcall UpdateAnimations(const int in_type)
{
	LOGFN_UTILITY("Type: {}", in_type);

	switch (in_type)
	{
		case 0:
		{
			// Replace rainbow ring material animations.
			WRITE(0x115ACE8, const char*, "rnb_obj_TailsDashring_light1");
			WRITE(0x115AC6A, const char*, Configuration::UseCustomRainbowRings ? "rnb_obj_TailsDashring_light2" : "cmn_obj_rainbowring_HD");
			WRITE(0x115AD66, const char*, "rnb_obj_TailsDashring_light3");

			break;
		}

		case 1:
		{
			// Replace dash ring material animations.
			WRITE(0x115ACE8, const char*, "cmn_obj_TailsDashring_light1");
			WRITE(0x115AC6A, const char*, "cmn_obj_TailsDashring_light2");
			WRITE(0x115AD66, const char*, "cmn_obj_TailsDashring_light3");

			// Replace Tails' dash ring material animations
			// if we're using the default materials.
			if (Configuration::ColourType == ColourType::GreenOriginal)
			{
				Configuration::IsOverrideTailsDashRing = false;
			}
			else
			{
				break;
			}
		}

		case 2:
		{
			// Replace Tails' dash ring material animations.
			WRITE(0x115ACE8, const char*, "mis_obj_TailsDashring_light1");
			WRITE(0x115AC6A, const char*, "mis_obj_TailsDashring_light2");
			WRITE(0x115AD66, const char*, "mis_obj_TailsDashring_light3");

			// Replace dash ring material animations
			// if we're overriding Tails' ones.
			if (Configuration::IsOverrideTailsDashRing)
				UpdateAnimations(1);

			break;
		}
	}
}

static void UpdateSounds()
{
	int soundId = 0x3D0CFC;

	switch (Configuration::SoundType)
	{
		case SoundType::DashRing:
			soundId = 0x3D0CFC;
			break;

		case SoundType::RainbowRing:
			soundId = 0x3D10E5;
			break;

		case SoundType::DashPanel:
			soundId = 0x3D10E6;
			break;

		case SoundType::ClassicSpring:
			soundId = 0x3D10DF;
			break;

		case SoundType::ModernSpring:
			soundId = 0x3D10DE;
			break;
	}

	// Replace dash ring sound ID.
	WRITE(0x1A6B7FC, int, soundId);

	// Replace Tails' dash ring sound ID.
	if (Configuration::IsOverrideTailsDashRing)
		WRITE(0x1A6B800, int, soundId);
}

DECLARE_ASM_HOOK_32(CObjRainbowRing_AddCallback_UpdateModels, 0x115ABC1)
{
	static void* s_interruptAddress = (void*)0x65FFF0;
	static void* s_returnAddress = (void*)0x115ABC6;

	UpdateModels();

	__asm
	{
		call [s_interruptAddress]
		jmp  [s_returnAddress]
	}
}

DECLARE_ASM_HOOK_32(CObjRainbowRing_AddCallback_UpdateAnimations, 0x115AC63)
{
	static void* s_returnAddress = (void*)0x115AC69;

	__asm
	{
		mov  ecx, eax
		call [UpdateAnimations]
		mov  edx, eax
		jmp  [s_returnAddress]
	}
}

DECLARE_STATIC_HOOK(int, __cdecl, CObjMsnNumberDashRing_Ctor, 0xEDBD40, int a1)
{
	// Restore original dash ring model.
	UpdateModels("cmn_obj_dashring_HD");

	return original_CObjMsnNumberDashRing_Ctor(a1);
}

void ResourcePatches::Install()
{
	const char* pArchiveName{};

	switch (Configuration::ColourType)
	{
		case ColourType::Green:
			pArchiveName = "cmn_dashring_tails_green";
			break;

		case ColourType::Orange:
			pArchiveName = "cmn_dashring_tails_orange";
			break;

		case ColourType::Red:
			pArchiveName = "cmn_dashring_tails_red";
			break;

		case ColourType::Purple:
			pArchiveName = "cmn_dashring_tails_purple";
			break;

		case ColourType::Blue:
			pArchiveName = "cmn_dashring_tails_blue";
			break;

		default:
			pArchiveName = "cmn_dashring_tails_green_dif";
			break;
	}

	static std::vector<std::string> s_cmnArchiveNames = { "cmn100", "cmn200", "pam_cmn" };

	ArchiveTree::Archives.push_back({ pArchiveName, { s_cmnArchiveNames } });

	if (Configuration::UseCustomRainbowRings)
		ArchiveTree::Archives.push_back({ "cmn_dashring_tails_rainbow", { s_cmnArchiveNames } });

	ArchiveTree::Install();

	UpdateModels();
	UpdateSounds();

	INSTALL_ASM_HOOK_32(CObjRainbowRing_AddCallback_UpdateModels);
	INSTALL_ASM_HOOK_32(CObjRainbowRing_AddCallback_UpdateAnimations);
}