#pragma once

namespace app::game
{
	class alignas(8) MsgSuspendWorld : public hh::fnd::MessageAsyncHandlerInplace<MsgSuspendWorld>, public fnd::AppMessage<MsgSuspendWorld>
	{
	private:
		inline static uint32_t MessageID = 0x22E9;

	public:
		char Unk1[16];
		uint64_t Unk2{};
		bool Unk3{};

		MsgSuspendWorld() : fnd::AppMessage<MsgSuspendWorld>(MessageID) { }

		MsgSuspendWorld(const char* in_unk1, uint64_t in_unk2, bool in_unk3) : MsgSuspendWorld()
		{
			strncpy(Unk1, in_unk1, 16);

			Unk2 = in_unk2;
			Unk3 = in_unk3;
		}
	};
}