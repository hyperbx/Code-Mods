#pragma once

namespace app::game
{
	class alignas(8) MsgResumeWorld : public hh::fnd::MessageAsyncHandlerInplace<MsgResumeWorld>, public fnd::AppMessage<MsgResumeWorld>
	{
	private:
		inline static uint32_t MessageID = 0x2272;

	public:
		char Unk1[16];
		bool Unk2{};

		MsgResumeWorld() : fnd::AppMessage<MsgResumeWorld>(MessageID) { }

		MsgResumeWorld(const char* in_unk1, bool in_unk2) : MsgResumeWorld()
		{
			strncpy(Unk1, in_unk1, 16);

			Unk2 = in_unk2;
		}
	};
}