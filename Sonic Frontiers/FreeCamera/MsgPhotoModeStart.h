#pragma once

namespace app::game
{
	class alignas(8) MsgPhotoModeStart : public hh::fnd::MessageAsyncHandlerInplace<MsgPhotoModeStart>, public fnd::AppMessage<MsgPhotoModeStart>
	{
	private:
		inline static uint32_t MessageID = 0x222A;

	public:
		MsgPhotoModeStart() : fnd::AppMessage<MsgPhotoModeStart>(MessageID) { }
	};
}