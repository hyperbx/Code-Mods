#pragma once

namespace app::player
{
	class alignas(8) MsgSetAbilityEnabled : public hh::fnd::MessageAsyncHandlerInplace<MsgSetAbilityEnabled>, public fnd::AppMessage<MsgSetAbilityEnabled>
	{
	private:
		inline static uint32_t MessageID = 0x22AC;

	public:
		enum EAbilityType
		{
			EAbilityType_ControlCamera = 0,
			EAbilityType_Jump = 2,
			EAbilityType_Boost = 3,
			EAbilityType_HomingAttack = 5,
			EAbilityType_WallAction = 6,
			EAbilityType_ComboAttack = 7,
			EAbilityType_Cyloop = 8,
			EAbilityType_Parry = 9,
			EAbilityType_Lockon = 10
		};

		EAbilityType AbilityType{};
		bool IsEnabled{};

		MsgSetAbilityEnabled(EAbilityType in_abilityType, bool in_isEnabled) : MsgSetAbilityEnabled()
		{
			AbilityType = in_abilityType;
			IsEnabled = in_isEnabled;
		}

		MsgSetAbilityEnabled() : fnd::AppMessage<MsgSetAbilityEnabled>(MessageID) { }
	};
}