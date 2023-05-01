#pragma once

class Player
{
public:
	static void CreateInput()
	{
		auto optionData = FrontiersInput::GetOptionData();

		if (optionData == nullptr)
			return;

		if (optionData->header.status == FrontiersInput::STATUS_ZERO_FILL)
			return;

		InputHelper::Instance->SetInputMap
		(
			std::unordered_map<int, int>
			{
				FINPUT.GetVirtualKeysFromActionType(FrontiersInput::ActionType_ACT_Jump),
				FINPUT.GetVirtualKeysFromActionType(FrontiersInput::ActionType_ACT_StompAttack)
			}
		);

		InputHelper::Instance->SetTriggerMap
		(
			std::unordered_map<int, int>
			{
				FINPUT.GetVirtualKeysFromActionType(FrontiersInput::ActionType_ACT_Boost)
			}
		);
	}

	static void Install();
};

CL_SCAN_SIGNATURE(m_SigSetCurrentState, "\x48\x89\x5C\x24\x08\x48\x89\x74\x24\x10\x57\x48\x83\xEC\x20\x48\x8B\xD9\x41\x8B\xF8\x48\x81\xC1\x88\x00\x00\x00\x8B\xF2\xE8\xCC\xCC\xCC\xCC\x3B", "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx????x");
CL_SCAN_SIGNATURE(m_SigStateDropDashStart, "\x48\x89\x5C\x24\x10\x48\x89\x6C\x24\x18\x56\x57\x41\x56\x48\x83\xEC\x50\x48\x8B\xE9\x48\x8B\xF2", "xxxxxxxxxxxxxxxxxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigStateDropDashUpdate, "\x48\x89\x5C\x24\x08\x48\x89\x6C\x24\x10\x48\x89\x74\x24\x18\x57\x48\x83\xEC\x30\x48\x8B\xF1\x0F", "xxxxxxxxxxxxxxxxxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigStateDropDashEnd, "\x48\x89\x5C\x24\x08\x57\x48\x83\xEC\x20\x48\x8B\xD9\x48\x8B\xFA\x48\x8B\xCA\xE8\xCC\xCC\xCC\xCC\xB2", "xxxxxxxxxxxxxxxxxxxx????x");
CL_SCAN_SIGNATURE(m_SigPostureDropDashUpdate, "\x48\x8B\xC4\x48\x89\x58\x08\x48\x89\x70\x10\x57\x48\x81\xEC\xA0\x00\x00\x00\x48\x8B\x71", "xxxxxxxxxxxxxxxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigStateDoubleJumpUpdate, "\x48\x89\x5C\x24\x10\x57\x48\x83\xEC\x30\x0F\xB6\x81", "xxxxxxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigStateRecoveryJumpUpdate, "\x48\x89\x74\x24\x10\x57\x48\x83\xEC\x30\x48\x8B\xFA\x0F\x29\x74\x24\x20\x48\x8B\xF1", "xxxxxxxxxxxxxxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigStateStompingLandUpdate, "\x40\x53\x56\x57\x48\x83\xEC\x60\x48\x8B\xFA", "xxxxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigGOCPlayerHsmUpdate, "\x40\x53\x55\x48\x83\xEC\x28\x49", "xxxxxxxx");
CL_SCAN_SIGNATURE(m_SigGOCPlayerHsmGroundStateUpdate, "\x40\x53\x41\x56\x41\x57\x48\x83\xEC\x20\xF6\x81\x1C", "xxxxxxxxxxxxx");
CL_SCAN_SIGNATURE(m_SigPlayerSpeedUpdateCaller, "\xE8\xCC\xCC\xCC\xCC\x80\xBF\x10\x01\x00\x00\x00", "x????xxxxxxx");

CL_SCAN_SIGNATURE_ALLOW_NULL(m_SigDropDashCameraDelay, "\x73\x2A\xF3\x0F\x10\x05\xCC\xCC\xCC\xCC\x45\x33\xC9", "xxxxxx????xxx");
CL_SCAN_SIGNATURE_ALLOW_NULL(m_SigSquatToSlideWorkaround, "\x75\x27\x45\x31\xC0\x48\x89\xF9", "xxxxxxxx");
CL_SCAN_SIGNATURE_ALLOW_NULL(m_SigDropDashUngroundedExitFunc, "\xE8\xCC\xCC\xCC\xCC\x84\xC0\x75\xD8\x48\x8B\xCF", "x????xxxxxxx");
CL_SCAN_SIGNATURE_ALLOW_NULL(m_SigExitStateWithTricks, "\x48\x89\x5C\x24\x10\x48\x89\x6C\x24\x18\x48\x89\x74\x24\x20\x57\x48\x83\xEC\x40\x48\x8B\x59", "xxxxxxxxxxxxxxxxxxxxxxx");
CL_SCAN_SIGNATURE_ALLOW_NULL(m_SigForceGrindJumpPosture, "\x73\x09\x0F\x28\x1D\xCC\xCC\xCC\xCC\xEB\x35\x0F\x2F\xDA", "xxxxx????xxxxx");
CL_SCAN_SIGNATURE_ALLOW_NULL(m_SigFixDropDashSideView, "\x74\x10\x0F\x28\xCF", "xxxxx");