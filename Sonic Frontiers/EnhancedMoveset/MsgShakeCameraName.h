#pragma once

namespace app::camera
{
	class alignas(16) MsgShakeCameraName : public hh::fnd::MessageAsyncHandlerInplace<MsgShakeCameraName>, public fnd::AppMessage<MsgShakeCameraName>
	{
	private:
		inline static uint32_t MessageID = 0x22C6;

		const char* pShakeCameraName{};
		INSERT_PADDING(0x20);

	public:
		MsgShakeCameraName(const char* in_pShakeCameraName) : MsgShakeCameraName()
		{
			pShakeCameraName = in_pShakeCameraName;
		}

		MsgShakeCameraName() : fnd::AppMessage<MsgShakeCameraName>(MessageID) { }
	};
}