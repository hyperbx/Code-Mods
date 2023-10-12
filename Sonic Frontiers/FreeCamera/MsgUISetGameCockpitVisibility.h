#pragma once

namespace app::ui
{
	class alignas(8) MsgUISetGameCockpitVisibility : public hh::fnd::MessageAsyncHandlerInplace<MsgUISetGameCockpitVisibility>, public fnd::AppMessage<MsgUISetGameCockpitVisibility>
	{
	private:
		inline static uint32_t MessageID = 0x238C;

	public:
		bool IsVisible{};

		MsgUISetGameCockpitVisibility() : fnd::AppMessage<MsgUISetGameCockpitVisibility>(MessageID) { }

		MsgUISetGameCockpitVisibility(bool in_isVisible) : MsgUISetGameCockpitVisibility()
		{
			IsVisible = in_isVisible;
		}
	};
}