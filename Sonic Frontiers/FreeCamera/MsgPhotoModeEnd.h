#pragma once

namespace app::game
{
	class alignas(8) MsgPhotoModeEnd : public hh::fnd::MessageAsyncHandlerInplace<MsgPhotoModeEnd>, public fnd::AppMessage<MsgPhotoModeEnd>
	{
	private:
		inline static uint32_t MessageID = 0x2229;

	public:
		MsgPhotoModeEnd() : fnd::AppMessage<MsgPhotoModeEnd>(MessageID) { }
	};
}