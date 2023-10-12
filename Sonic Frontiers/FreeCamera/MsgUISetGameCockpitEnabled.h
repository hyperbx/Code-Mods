#pragma once

namespace app::ui
{
	class alignas(8) MsgUISetGameCockpitEnabled : public hh::fnd::MessageAsyncHandlerInplace<MsgUISetGameCockpitEnabled>, public fnd::AppMessage<MsgUISetGameCockpitEnabled>
	{
	private:
		inline static uint32_t MessageID = 0x238B;

	public:
		bool IsEnabled{};

		MsgUISetGameCockpitEnabled() : fnd::AppMessage<MsgUISetGameCockpitEnabled>(MessageID) { }

		MsgUISetGameCockpitEnabled(bool in_isEnabled) : MsgUISetGameCockpitEnabled()
		{
			IsEnabled = in_isEnabled;
		}
	};
}