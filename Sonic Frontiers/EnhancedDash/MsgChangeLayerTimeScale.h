#pragma once

namespace app::game
{
	class alignas(8) MsgChangeLayerTimeScale : public hh::fnd::MessageAsyncHandlerInplace<MsgChangeLayerTimeScale>, public fnd::AppMessage<MsgChangeLayerTimeScale>
	{
	private:
		inline static uint32_t MessageID = 0x20AB;

	public:
		char LayerName[16]{};
		float TimeScale{};
		int Unk2{};
		float Unk3{};

		MsgChangeLayerTimeScale(const char* in_pLayerName, float in_timeScale, int in_unk2, float in_unk3) : MsgChangeLayerTimeScale()
		{
			strncpy(LayerName, in_pLayerName, 16);

			TimeScale = in_timeScale;
			Unk2 = in_unk2;
			Unk3 = in_unk3;
		}

		MsgChangeLayerTimeScale() : fnd::AppMessage<MsgChangeLayerTimeScale>(MessageID) { }
	};
}